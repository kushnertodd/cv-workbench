#include "variance_stats.hpp"
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"

/**
 * @brief
 */
Variance_stats::Variance_stats() :
    count(0), mean(0.0), M2(0.0), variance(0.0), sample_variance(0.0), standard_deviation(0.0) {}

/**
 * # Retrieve the mean, variance and sample variance from an aggregate
 * def finalize(existingAggregate):
 *     (count, mean, M2) = existingAggregate
 *     if count < 2:
 *         return double("nan")
 *     else:
 *         (mean, variance, sampleVariance) = (mean, M2 / count, M2 / (count - 1))
 *         return (mean, variance, sampleVariance)
 * @brief
 */
void Variance_stats::finalize() {
    assert(is_pixel_valid());
    variance = M2 / count;
    sample_variance = M2 / (count - 1);
    standard_deviation = sqrt(sample_variance);
}
/**
 * @brief
 * @return
 */
int Variance_stats::get_count() const { return count; }
/**
 * @brief
 * @return
 */
double Variance_stats::get_max_value() const { return bounds.get_max_value(); }
/**
 * @brief
 * @return
 */
double Variance_stats::get_mean() {
    finalize();
    return mean;
}
/**
 * @brief
 * @return
 */
double Variance_stats::get_min_value() const { return bounds.get_min_value(); }
/**
 * @brief
 * @return
 */
double Variance_stats::get_sample_variance() {
    finalize();
    return sample_variance;
}
/**
 * @brief
 * @return
 */
double Variance_stats::get_standard_deviation() {
    finalize();
    return standard_deviation;
}
/**
 * @brief
 * @return
 */
double Variance_stats::get_variance() {
    finalize();
    return variance;
}

/**
 * @brief test if the result is valid
 * @return
 */
bool Variance_stats::is_pixel_valid() const { return (count >= 2); }
/**
 * @brief
 * @param fp
 * @param path
 * @param errors
 */
void Variance_stats::read(FILE *fp, const std::string &path, Errors &errors) {
    wb_utils::read_int(fp, count, "Image_header::read_header", "", "missing image count", errors);

    float mean_float = 0.0;
    if (!errors.has_error())
        wb_utils::read_float(fp, mean_float, "Image_header::read_header", "", "missing image mean", errors);
    if (!errors.has_error())
        mean = mean_float;

    float standard_deviation_float = 0.0;
    if (!errors.has_error())
        wb_utils::read_float(fp, standard_deviation_float, "Image_header::read_header", "",
                             "missing image standard_deviation", errors);
    if (!errors.has_error())
        standard_deviation = standard_deviation_float;

    float min_value = 0.0;
    if (!errors.has_error())
        wb_utils::read_float(fp, min_value, "Image_header::read_header", "", "missing image min_value", errors);
    if (!errors.has_error())
        bounds.min_value = min_value;

    float max_value = 0.0;
    if (!errors.has_error())
        wb_utils::read_float(fp, max_value, "Image_header::read_header", "", "missing image max_value", errors);
    if (!errors.has_error())
        bounds.max_value = max_value;
}
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Variance_stats::to_string(const std::string &prefix) {
    std::ostringstream os{};
    os << "stats: " << std::endl
       << prefix << "    " << std::setw(20) << std::left << "count " << count << std::endl
       << prefix << "    " << std::setw(20) << std::left << "mean " << get_mean() << std::endl
       << prefix << "    " << std::setw(20) << std::left << "variance " << get_variance() << std::endl
       << prefix << "    " << std::setw(20) << std::left << "sample variance " << get_sample_variance() << std::endl
       << prefix << "    " << std::setw(20) << std::left << "standard deviation " << get_standard_deviation()
       << std::endl
       << prefix << "    " << std::setw(20) << std::left << "min value " << bounds.min_value << std::endl
       << prefix << "    " << std::setw(20) << std::left << "max value " << bounds.max_value << std::endl;
    return os.str();
}

/**
 *  For a new value newValue, compute the new count, new mean, the new M2.
 *  mean accumulates the mean of the entire dataset
 *  M2 aggregates the squared distance from the mean
 *  count aggregates the number of samples seen so far
 * def update_input_value(existingAggregate, newValue):
 *     (count, mean, M2) = existingAggregate
 *     count += 1
 *     delta = newValue - mean
 *     mean += delta / count
 *     delta2 = newValue - mean
 *     M2 += delta * delta2
 *     return (count, mean, M2)
 * @param new_value
 */
void Variance_stats::update(double new_value) {
    count++;
    double delta = new_value - mean;
    mean += delta / count;
    double delta2 = new_value - mean;
    M2 += delta * delta2;
    bounds.update(new_value);
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Variance_stats::write(FILE *fp, Errors &errors) const {
    if (!errors.has_error())
        wb_utils::write_int(fp, count, "Variance_stats::write", "", "cannot write count", errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(mean), "Variance_stats::write", "", "cannot write mean",
                              errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(standard_deviation), "Variance_stats::write", "",
                              "cannot write standard_deviation", errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(bounds.min_value), "Histogram::write", "",
                              "cannot write min_value", errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(bounds.max_value), "Histogram::write", "",
                              "cannot write max_value", errors);
}
