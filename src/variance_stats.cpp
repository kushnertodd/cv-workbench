//
// Created by kushn on 6/24/2022.
//

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include "wb_utils.hpp"
#include "variance_stats.hpp"

//

Variance_stats::Variance_stats() :
    count(0),
    mean(0.0),
    M2(0.0),
    variance(0.0),
    sample_variance(0.0),
    standard_deviation(0.0) {}

/**
 * # Retrieve the mean, variance and sample variance from an aggregate
 * def finalize(existingAggregate):
 *     (count, mean, M2) = existingAggregate
 *     if count < 2:
 *         return double("nan")
 *     else:
 *         (mean, variance, sampleVariance) = (mean, M2 / count, M2 / (count - 1))
 *         return (mean, variance, sampleVariance)
 */
void Variance_stats::finalize() {
  assert(is_valid());
  variance = M2 / count;
  sample_variance = M2 / (count - 1);
  standard_deviation = sqrt(sample_variance);
}

double Variance_stats::get_max_value() const { return bounds.get_max_value(); }

double Variance_stats::get_mean() {
  finalize();
  return mean;
}

double Variance_stats::get_min_value() const { return bounds.get_min_value(); }

double Variance_stats::get_sample_variance() {
  finalize();
  return sample_variance;
}

double Variance_stats::get_standard_deviation() {
  finalize();
  return standard_deviation;
}

double Variance_stats::get_variance() {
  finalize();
  return variance;
}

/**
 * test if the result is valid
 */
bool Variance_stats::is_valid() const {
  return (count >= 2);
}

std::string Variance_stats::to_string() {
  std::ostringstream os;
  os << "count " << count
     << " mean " << get_mean()
     << " variance " << get_variance()
     << " sample variance " << get_sample_variance()
     << " standard deviation " << get_standard_deviation()
     << " min value " << bounds.min_value
     << " max value " << bounds.max_value;
  return os.str();
}

/**
 *  For a new value newValue, compute the new count, new mean, the new M2.
 *  mean accumulates the mean of the entire dataset
 *  M2 aggregates the squared distance from the mean
 *  count aggregates the number of samples seen so far
 * def update(existingAggregate, newValue):
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

void Variance_stats::write(FILE *fp, const std::string &path, Errors &errors) const {
  if (errors.error_ct == 0)
    wb_utils::write_int(fp, count, "Variance_stats::write", "", "cannot write count to '" + path + "'", errors);
  if (errors.error_ct == 0)
    wb_utils::write_double(fp, mean, "Variance_stats::write", "", "cannot write mean to '" + path + "'", errors);
  if (errors.error_ct == 0)
    wb_utils::write_double(fp,
                           variance,
                           "Variance_stats::write",
                           "",
                           "cannot write variance to '" + path + "'",
                           errors);
  if (errors.error_ct == 0)
    wb_utils::write_double(fp,
                           sample_variance,
                           "Variance_stats::write",
                           "",
                           "cannot write sample_variance to '" + path + "'",
                           errors);
  if (errors.error_ct == 0)
    wb_utils::write_double(fp,
                           standard_deviation,
                           "Variance_stats::write",
                           "",
                           "cannot write standard_deviation to '" + path + "'",
                           errors);
  if (errors.error_ct == 0)
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(bounds.min_value),
                          "Histogram::write", "", "cannot write min_value to '" + path + "'",
                          errors);
  if (errors.error_ct == 0)
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(bounds.max_value),
                          "Histogram::write", "", "cannot write max_value to '" + path + "'",
                          errors);
}
