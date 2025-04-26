#include "polar_trig.hpp"
#include <cmath>
#include "pixel.hpp"
#include "polar_trig_static.hpp"
#include "wb_utils.hpp"

Polar_index::Polar_index() = default;
Polar_index::Polar_index(int m_rho_index, int m_theta_index) : rho_index(m_rho_index), theta_index(m_theta_index) {}
void Polar_index::init(int m_rho_index, int m_theta_index) {
    rho_index = m_rho_index;
    theta_index = m_theta_index;
}

Polar_point::Polar_point() = default;
Polar_point::Polar_point(double m_rho, double m_theta) : rho(m_rho), theta(m_theta) {}
void Polar_point::init(double m_rho, double m_theta) {
    rho = m_rho;
    theta = m_theta;
}

Polar_trig::Polar_trig() = default;
Polar_trig::Polar_trig(int m_x_max, int m_y_max) : Polar_trig(m_x_max, m_y_max, default_rho_inc, default_theta_inc) {}
Polar_trig::Polar_trig(int m_x_max, int m_y_max, int m_rho_inc, int m_theta_inc) :
    x_max(m_x_max), y_max(m_y_max), rho_inc(m_rho_inc), theta_inc(m_theta_inc) {
    rho_max = wb_utils::double_to_int_round((sqrt(y_max * y_max + x_max * x_max)) + rho_pad) / 2.0;
    nrhos = rho_max / rho_inc;
    nthetas = theta_max / theta_inc;
}
int Polar_trig::get_nrhos() const { return nrhos; }
int Polar_trig::get_nthetas() const { return nthetas; }
int Polar_trig::get_rho_inc() const { return rho_inc; }
int Polar_trig::get_theta_inc() const { return theta_inc; }
int Polar_trig::get_x_max() const { return x_max; }
int Polar_trig::get_y_max() const { return y_max; }
int Polar_trig::point_theta_to_rho(double x, double y, int theta_index)  {
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = x * cos_t + y * sin_t;
    return to_rho_index(rho);
}
// can have a singularity if theta ~= 180, sin ~= 0
double Polar_trig::rho_theta_x_to_y(int rho_index, int theta_index, double x)  {
    assert(!singular_sin_index(theta_index));
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = to_rho(rho_index);
    double y = (x * cos_t - rho) / sin_t;
    return y;
}
// can have a singularity if theta ~= 90, cos ~= 0
double Polar_trig::rho_theta_y_to_x(int rho_index, int theta_index, double y)  {
    assert(!singular_cos_index(theta_index));
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = to_rho(rho_index);
    double x = (rho - y * sin_t) / cos_t;
    return x;
}
bool Polar_trig::singular_cos(int theta)  { return theta == theta_max / 2; }
bool Polar_trig::singular_cos_index(int theta_index)  { return singular_cos(to_theta(theta_index)); }
bool Polar_trig::singular_sin(int theta)  { return theta == 0; }
bool Polar_trig::singular_sin_index(int theta_index)  { return singular_sin(to_theta(theta_index)); }
double Polar_trig::to_cos(int theta) { return polar_cos[theta]; }
double Polar_trig::to_cos_index(int theta_index) const { return to_cos(to_theta(theta_index)); }
void Polar_trig::to_index(Polar_index &polar_index, Polar_point &polar_point) const {
    polar_index.init(to_rho_index(polar_point.rho), to_theta_index(polar_point.theta));
}
void Polar_trig::to_point(Polar_point &polar_point, Polar_index &polar_index) const {
    polar_point.init(to_rho(polar_index.rho_index), to_theta(polar_index.theta_index));
}
double Polar_trig::to_rho(int rho_index) const {
    double rho = rho_index * rho_inc - nrhos;
    return rho;
}
int Polar_trig::to_rho_index(double rho) const {
    int rho_index = wb_utils::double_to_int_round((rho + nrhos) / rho_inc);
    return rho_index;
}
double Polar_trig::to_sin(int theta) { return polar_sin[theta]; }
double Polar_trig::to_sin_index(int theta_index) const { return to_sin(to_theta(theta_index)); }
int Polar_trig::to_theta(int theta_index) const {
    int theta = theta_index * theta_inc;
    return theta;
}
int Polar_trig::to_theta_index(int theta) const {
    int theta_index = theta / theta_inc;
    return theta_index;
}

