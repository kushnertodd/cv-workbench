//
// Created by kushn on 6/14/2022.
//

#include "operator_filter_edge_kirsch.hpp"
#include "operator_filter_edge_laplacian.hpp"
#include "operator_filter_edge_prewitt.hpp"
#include "operator_filter_edge_roberts.hpp"
#include "operator_filter_edge_sobel.hpp"
#include "operator_filter_image_morphology.hpp"
#include "operator_filter_smooth_average.hpp"
#include "operator_filter_smooth_gaussian.hpp"
#include "operator_filter_smooth_median.hpp"
#include "operator_histogram_hough_create.hpp"
#include "operator_histogram_image_create.hpp"
#include "operator_histogram_peak_detect.hpp"
#include "operator_hough_draw_line.hpp"
#include "operator_hough_image_create.hpp"
#include "operator_hough_peak_detect.hpp"
#include "operator_transform_image_combine.hpp"
#include "operator_transform_image_copy.hpp"
#include "operator_transform_image_create.hpp"
#include "operator_transform_intensity_map.hpp"
#include "operator_dispatcher.hpp"

extern bool debug;
Operator *Operator_dispatcher::create_operator(const std::string &operator_name) {
  Operator *pOperator = nullptr;
  if (debug)
    std::cout << "Operator_dispatcher::create_operator operator_name '" << operator_name << "'" << std::endl;
  // Creator explicitly creates classes according to type
  if (operator_name == "filter-edge-kirsch") pOperator = new Operator_filter_edge_kirsch();
  else if (operator_name == "filter-edge-laplacian") pOperator = new Operator_filter_edge_laplacian();
  else if (operator_name == "filter-edge-prewitt") pOperator = new Operator_filter_edge_prewitt();
  else if (operator_name == "filter-edge-roberts") pOperator = new Operator_filter_edge_roberts();
  else if (operator_name == "filter-edge-sobel") pOperator = new Operator_filter_edge_sobel();
  else if (operator_name == "filter-image-morphology") pOperator = new Operator_filter_image_morphology();
  else if (operator_name == "filter-smooth-average") pOperator = new Operator_filter_smooth_average();
  else if (operator_name == "filter-smooth-gaussian") pOperator = new Operator_filter_smooth_gaussian();
  else if (operator_name == "filter-smooth-median") pOperator = new Operator_filter_smooth_median();
  else if (operator_name == "histogram-hough-create") pOperator = new Operator_histogram_hough_create();
  else if (operator_name == "histogram-image-create") pOperator = new Operator_histogram_image_create();
  else if (operator_name == "histogram-peak-detect") pOperator = new Operator_histogram_peak_detect();
  else if (operator_name == "hough-draw-line") pOperator = new Operator_hough_draw_line();
  else if (operator_name == "hough-image-create") pOperator = new Operator_hough_image_create();
  else if (operator_name == "hough-peak-detect") pOperator = new Operator_hough_peak_detect();
  else if (operator_name == "transform-image-combine") pOperator = new Operator_transform_image_combine();
  else if (operator_name == "transform-image-copy") pOperator = new Operator_transform_image_copy();
  else if (operator_name == "transform-image-create") pOperator = new Operator_transform_image_create();
  else if (operator_name == "transform-intensity-map") pOperator = new Operator_transform_intensity_map();
  return pOperator;
}
