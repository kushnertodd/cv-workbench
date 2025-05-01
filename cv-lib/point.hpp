#ifndef SRC__POINT_HPP_
#define SRC__POINT_HPP_
#include <string>

class Point {
    friend class Polar_trig;
    double x{};
    double y{};

public:
    Point();
    Point(double m_x, double m_y);
    Point(const Point &point);
    void init(int m_x, int m_y);
    std::string to_string() const;
};

#endif // SRC__POINT_HPP_
