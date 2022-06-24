//
// Created by kushn on 6/24/2022.
//

#include <cfloat>
#include <cmath>
#include <iostream>
#include <sstream>
#include "variance_stats.hpp"

using namespace std;

Variance_stats::Variance_stats() :
    count(0),
    mean(0.0),
    M2(0.0),
    variance(0.0),
    sample_variance(0.0),
    min_value(FLT_MAX),
    max_value(FLT_MIN) {}

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
  //cout << "before min_value " << min_value << " new_value " << new_value ;
  min_value = min(min_value, new_value);
  //cout << " after min_value " << min_value << " before max_value " << max_value << " new_value " << new_value;
  max_value = max(max_value, new_value);
  //cout << " after max_value " << max_value << endl;
}

/**
 * test if the result is valid
 */
bool Variance_stats::is_valid() {
  return (count >= 2);
}

/**
 * # Retrieve the mean, variance and sample variance from an aggregate
 * def finalize(existingAggregate):
 *     (count, mean, M2) = existingAggregate
 *     if count < 2:
 *         return float("nan")
 *     else:
 *         (mean, variance, sampleVariance) = (mean, M2 / count, M2 / (count - 1))
 *         return (mean, variance, sampleVariance)
 */
void Variance_stats::finalize() {
  if (!is_valid()) {
    throw "Variance_stats::finalize: count < 2";
  }
  variance = M2 / count;
  sample_variance = M2 / (count - 1);
}

int Variance_stats::get_count() { return count; }

double Variance_stats::get_min_value() { return min_value; }

double Variance_stats::get_max_value() { return max_value; }

double Variance_stats::get_mean() {
  finalize();
  return mean;
}

double Variance_stats::get_variance() {
  finalize();
  return variance;
}

double Variance_stats::get_sample_variance() {
  finalize();
  return sample_variance;
}

double Variance_stats::get_standard_deviation() {
  finalize();
  return sqrt(sample_variance);
}

string Variance_stats::to_string() {
  ostringstream os;
  os << "count " << get_count() << endl
     << "mean " << get_mean() << endl
     << "variance " << get_variance() << endl
     << "sample variance " << get_sample_variance() << endl
     << "standard deviation " << get_standard_deviation() << endl
     << "min value " << get_min_value() << endl
     << "max value " << get_max_value() << endl;
  return os.str();
}