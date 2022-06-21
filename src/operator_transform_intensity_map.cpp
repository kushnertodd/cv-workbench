//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "operator_transform_intensity_map.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

using namespace std;

extern bool debug;

Operator_transform_intensity_map::Operator_transform_intensity_map() {}

/**
 * parameters:
    float lower_in
    float upper_in
    float lower_out                                            
    float upper_out
    enum depth
        CV_8U   unsigned byte
        CV_32S  int
        CV_32F  float
    map pixels values:
       pixel_in <= in_lower -> 
         out_lower
       pixel_in >= in_upper -> 
         out_upper;
       t ->       
         out_lower + (pixel_in-in_lower) * (out_upper-out_lower) / (in_upper-in_lower) 
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_intensity_map::run(list<Data_source_descriptor *> &input_data_sources,
                                     list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    cout << "Operator_transform_intensity_map::run parameters: "
         <<    Operator_utils::parameters_to_string(operator_parameters)<< endl;
  }
  if (input_data_sources.size() == 0)
    errors.add("Experiment_step::run transform-intensity-map: missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Experiment_step::run transform-intensity-map: too many input data sources");
  else if (output_data_stores.size() == 0)
    errors.add("Experiment_step::run transform-intensity-map: missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Experiment_step::run transform-intensity-map: too many output data sources");
  else if (operator_parameters.find("orientation") == operator_parameters.end()) {
    errors.add("operator_filter_edge_sobel: missing 'orientation' parameter");
  } else {
    int orientation;
    string orientation_str = operator_parameters["orientation"];
    if (!Workbench_utils::string_to_int(orientation_str, orientation)) {
      errors.add("operator_filter_edge_sobel: invalid 'orientation' parameter: '" + orientation_str + "'");
    } else if (orientation != 0 && orientation != 1) {
      errors.add("operator_filter_edge_sobel: invalid 'orientation' parameter not 0 or 1: '"
                     + orientation_str + "'");
      /**
       lower_in
       upper_in
       lower_out
       upper_out

      if (Operator_utils::has_parameter(operator_parameters, "lower_in")){
    } else {
          */
      Data_source_descriptor *input_data_source = input_data_sources.front();
      Data_source_descriptor *output_data_store = output_data_stores.front();
      cout << "sobeling! orientation " << orientation << endl;
      Image *input = input_data_source->read_image(errors);
      int rows = input->get_rows();
      int cols = input->get_cols();
      int row_stride = input->get_row_stride();
      Image *output = new Image(rows, cols, input->get_components(), CV_32S);
      // Image *output = output_data_store->read_image(errors);
      cout << "still sobeling!" << endl;
      for (int row = 1; row < rows - 1; row++) {
        for (int col = 1; col < cols - 1; col++) {
          int ulc = (row - 1) * row_stride + col;
          int cl = row * row_stride + col;
          int llc = (row + 1) * row_stride + col;
          int center = cl + 1;
          int sum = 0;
          if (orientation == 0) {
            /*
             * orientation 0
             *     [-1,  0,  1]
             *     [-2,  0,  2]
             *     [-1,  0,  1]
             */
            sum += 0
                + input->buf_8U[ulc] * -1
                + input->buf_8U[cl] * -2
                + input->buf_8U[llc] * -1
                + input->buf_8U[ulc + 2] * 1
                + input->buf_8U[cl + 2] * 2
                + input->buf_8U[llc + 2] * 1;
          } else if (orientation == 1) {
            /*
             * orientation 90
             *     [ 1,  2,  1]
             *     [ 0,  0,  0]
             *     [-1, -2, -1]
             */
            sum += 0
                + input->buf_8U[ulc] * 1
                + input->buf_8U[ulc + 1] * 2
                + input->buf_8U[ulc + 2] * 1
                + input->buf_8U[llc] * -1
                + input->buf_8U[llc + 1] * -2
                + input->buf_8U[llc + 2] * -1;
          }
          output->buf_32S[center] = sum;
        }
      }
      //output->write_jpeg("sobel.jpg", errors);
      output_data_store->write_image(output, errors);
    }
  }
}
