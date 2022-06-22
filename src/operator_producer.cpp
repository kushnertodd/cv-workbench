//
// Created by kushn on 6/14/2022.
//

#include "operator_filter_edge_prewitt.hpp"
#include "operator_filter_edge_sobel.hpp"
#include "operator_transform_intensity_map.hpp"
#include "operator_producer.hpp"

using namespace std;
extern bool debug;
Operator *Operator_producer::create_operator(string operator_name) {
  Operator *pOperator;
  if (debug)
    cout << "Operator_producer::create_operator operator_name '" << operator_name << "'" << endl;
  // Creator explicitly creates classes according to type
  if (operator_name == "filter-edge-prewitt")
    pOperator = new Operator_filter_edge_prewitt();
  else if (operator_name == "filter-edge-sobel")
    pOperator = new Operator_filter_edge_sobel();
  else if (operator_name == "transform-intensity-map")
    pOperator = new Operator_transform_intensity_map();
  else
    pOperator = nullptr;
  return pOperator;
}