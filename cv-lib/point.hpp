#ifndef SRC__POINT_HPP_
#define SRC__POINT_HPP_
#include <string>

class Point {
    friend class Polar_trig;
    friend class Image_header;
    friend class Line_segment;
    friend class WB_window;
    const double close_distance = 1.0;
    double x{};
    double y{};

public:
    Point();
    Point(double m_x, double m_y);
    Point(const Point &point);
    bool close(const Point &point) const;
    void copy(const Point &point);
    double distance(const Point &point) const;
    void init(int m_x, int m_y);
    std::string to_string() const;
};

#endif // SRC__POINT_HPP_
