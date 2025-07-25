#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <map>
#include <memory>
#include "point.hpp"
#include "polar_line.hpp"

/**
 * @brief
 */
class Polar_trig {
    friend class Hough;
    double min_x{};
    double max_x{};
    double min_y{};
    double max_y{};
    int theta_inc{};
    int max_theta{};
    int min_theta{};
    int nthetas{};
    std::map<int, int> index_to_theta;
    std::map<int, int> theta_to_index;

public:
    Polar_trig();
    Polar_trig(double m_min_x, double m_max_x, double m_min_y, double m_max_y, int m_theta_inc, int m_min_theta,
               int m_max_theta);
    int add_thetas(int start_theta, int end_theta, int theta_index);
    int get_max_theta() const;
    double get_max_x() const;
    double get_max_y() const;
    int get_min_theta() const;
    double get_min_x() const;
    double get_min_y() const;
    int get_nthetas() const;
    int get_theta_inc() const;
    void initialize_thetas();
    bool is_theta_index_valid(int theta_index) const;
    bool is_theta_valid(int theta_index) const;
    static bool is_min_max_theta_valid(int theta);
    static int map_theta_pi(int theta);
    double theta_index_to_cos(int theta_index);
    double theta_index_to_sin(int theta_index);
    int theta_index_to_theta(int theta_index);
    int theta_to_theta_index(int theta);
};
#endif // SRC__POLAR_TRIG_HPP_
