#ifndef ARANDOM_LIBRARY_H
#define ARANDOM_LIBRARY_H



#include <random>
#include <cstdint>
#include <array>


namespace ak_util{

  class Random{
   public:
    Random() {
      std::random_device rd;
      engine.seed(rd());
    }

    /**
     *
     * 指定种子初始化
     *
     * */
    explicit Random(uint64_t seed) {
      engine.seed(seed);
    }
    /**
     *
     * 修改种子
     *
     * */
    void reseed(uint64_t seed) {
      engine.seed(seed);
    }

  /**
   *
   * return [0, 1)
   *
   * */
    double rand01() {
      static thread_local std::uniform_real_distribution<double> dist(0.0,1.0);
      return dist(engine);
    }
    /**
     *
     * [lo, hi) double
     *
     * */
    double randDouble(double lo, double hi) {
      std::uniform_real_distribution<double> dist(lo, hi);
      return dist(engine);
    }

   /**
    *
    * p% return a true
    *
    * */
    bool bernoulli(double p) {
      std::bernoulli_distribution dist(p);
      return dist(engine);
    }

    /**
     *
     * random int [lo, hi]
     *
     * */
    int randInt(int lo, int hi){
      std::uniform_int_distribution<int> dist(lo, hi);
      return dist(engine);
    }

    /**
     * [lo, hi] 闭区间 long long
     *
     * */
    long long randLong(long long lo, long long hi) {
      std::uniform_int_distribution<long long> dist(lo, hi);
      return dist(engine);
    }

  private:
   std::mt19937_64 engine;

  };
}

#endif//ARANDOM_LIBRARY_H
