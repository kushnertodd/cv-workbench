#ifndef SRC__BOUNDS_HPP_
#define SRC__BOUNDS_HPP_

#include <string>

class Bounds {
    friend class Hough;
    friend class Image;
    friend class Variance_stats;
    double max_value;
    double min_value;

public:
    Bounds();
    Bounds(double m_min_value, double m_max_value);
    double get_max_value() const;
    double get_min_value() const;
    static double map_input_to_output_bounds(double value, Bounds &input_bounds, Bounds &output_bounds);
    void set(double m_min_value, double m_max_value);
    std::string to_string(const std::string &prefix = "") const;
    void update(double value);
};

#endif // SRC__BOUNDS_HPP_
