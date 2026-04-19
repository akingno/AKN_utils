//
// Created by jacob on 2026/4/18.
//

#ifndef AKN_LOCK_SPINLOCK_H
#define AKN_LOCK_SPINLOCK_H
#include <atomic>
#include <cstdint>
#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif
#include <thread>

namespace akn {
    /*
     * akn::SpinLock - 极简自旋锁 (参考 folly::MicroSpinLock 实现)
     * 轻量，实例只占 1 字节；内部采用 TTAS 模式与自适应分段退避。
     * 无内核态切换开销；但在高冲突或长临界区下，会因繁忙等待严重浪费CPU吞吐量。
     * 仅适用于临界区极短（纳秒），且保证单点并发冲突极低的底层结构。
     * 常规多线程同步及高频争抢的全局队列，请默认使用 std::mutex。
     */
    struct SpinLock {
        enum : u_int8_t { FREE = 0, LOCKED = 1 };
        uint8_t  _lock; // 1

        static constexpr uint16_t SLOW_ITERATION = 3000;
        static constexpr uint8_t  MID_ITERATION  = 20;
        static constexpr uint8_t  FAST_ITERATION = 5;

        // 指数退让
        void lock() noexcept {
            while(!try_lock()) {
                uint16_t spin_count = 0;
                while (atom_cast()->load(std::memory_order_relaxed) == LOCKED) {
                    if (spin_count < FAST_ITERATION) {
                        // fast spin: 只自旋，什么都不做，期望几纳秒内拿到
                    }
                    else if (spin_count < FAST_ITERATION + MID_ITERATION) {
                        cpu_pause();
                    }
                    else if (spin_count < SLOW_ITERATION) {
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                        cpu_pause();
                    }
                    else {
                        // 三种自选后都拿不到，yield
                        std::this_thread::yield();
                        // yield后，为了防止死循环，重置计数器重新开始争抢
                        spin_count = 0;
                        continue;
                    }
                    spin_count++;
                }

            }
        }

        void unlock() {
            atom_cast()->store(FREE, std::memory_order_release);
        }

        bool try_lock() {
            return _exchange(LOCKED) == FREE; // == FREE说明现在是空闲的并且开始上锁，那么返回true因为ok了
        }

        std::atomic<uint8_t>* atom_cast() noexcept {
            return reinterpret_cast<std::atomic<uint8_t>*>(&_lock);
        }

        uint8_t _exchange(uint8_t newVal) noexcept {
            return std::atomic_exchange_explicit(atom_cast(), newVal, std::memory_order_acq_rel);
        }
        
        static void cpu_pause() noexcept {
            #if defined(__x86_64__) || defined(_M_X64)
            _mm_pause();
            #endif
        }

    };
}

#endif //AKN_LOCK_SPINLOCK_H
