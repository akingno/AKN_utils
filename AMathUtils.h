//
// Created by jacob on 2025/9/12.
//

#ifndef AKN_AMATHUTILS_H_
#define AKN_AMATHUTILS_H_

namespace akn{

/**
 *
 * 向下取整除法：向下取整
 *
 * */
inline int floor_div(int a, int b) {
  int q = a / b;
  int r = a % b;
  if ((r != 0) && ((r > 0) != (b > 0))) --q;
  return q;
}

/**
 * 向下取模:模一定非负, 如 -7%3 = 2
 * */
inline int floor_mod(int a, int b) {
  return a - b * floor_div(a, b);
}

}
#endif // AKN_LIBS__AMATHUTILS_H_
