//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_TRIG_HPP_
#define SRC__HOUGH_TRIG_HPP_

/**
 *  this is a non-static class to provide fast precomputed quantized
 *  cos() and sin() functions for hough as a f(int theta_inc)
 *
 *  requirements are:
 *  - the main program must:
 *    - declare a global Hough_trig variable
 *      Hough_trig::hough_trig;
 *    - call this function before any Hough methods are called:
 *      hough_trig.init(int theta_inc) e.g., theta_inc = 3 degrees
 *  - the Hough class must:
 *    - contain an extern reference for the global Hough_trig hough_trig variable
 *
 *  this class provides:
 *   - an init(int theta_inc) method that creates hough_cos[] and hough_sin[] arrays like:
 *     theta = 180 * theta_index / nthetas
 *     int hough_cos[int theta_index] = cos(180 * theta_index / nthetas)
 *     int hough_sin[int theta_index] = sin(180 * theta_index / nthetas)
 *  where:
 *    nthetas = 180 / theta_inc
 *    theta_index = 0..(nthetas-1)
 */
class Hough_trig {
 public:
  static int theta_inc;
  static int nthetas;
  static float *hough_cos;
  static float *hough_sin;

  Hough_trig();
  static void init(int m_theta_inc);
  static float deg_to_rad(float deg);
  static int index_to_deg(int index);
  static float cos(int theta_index);
  static float sin(int theta_index);
};

#endif //SRC__HOUGH_TRIG_HPP_
