//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "operator_filter_edge_sobel.hpp"
#include "wb_utils.hpp"

using namespace std;

extern bool debug;

Operator_filter_edge_sobel::Operator_filter_edge_sobel() {}

/**
 * orientation:
 *      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
 *     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_sobel::run(list<Data_source_descriptor *> &input_data_sources,
                                     list<Data_source_descriptor *> &output_data_stores,
                                     map<string, string> &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    cout << "operator_filter_edge_sobel: '" << endl << "   parameters " << endl;
    map<string, string>::iterator it;
    for (it = operator_parameters.begin(); it != operator_parameters.end(); it++) {
      cout << "      '" << it->first    // string (key)
           << "': '"
           << it->second   // string's value
           << "'" << endl;
    }
  }
  if (input_data_sources.size() == 0)
    errors.add("Experiment_step::run filter-edge-Sobel: missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Experiment_step::run filter-edge-Sobel: too many input data sources");
  else if (output_data_stores.size() == 0)
    errors.add("Experiment_step::run filter-edge-Sobel: missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Experiment_step::run filter-edge-Sobel: too many output data sources");
  else if (operator_parameters.find("orientation") == operator_parameters.end()) {
    errors.add("operator_filter_edge_sobel: missing 'orientation' parameter");
  } else {
    int orientation;
    string orientation_str = operator_parameters["orientation"];
    if (!string_to_int(orientation_str, orientation)) {
      errors.add("operator_filter_edge_sobel: invalid 'orientation' parameter: '" + orientation_str + "'");
    } else {
      Data_source_descriptor *input_data_source = input_data_sources.front();
      Data_source_descriptor *output_data_store = output_data_stores.front();
      cout << "sobeling! orientation " << orientation << endl;
      Image *input = input_data_source->read_image(errors);
      int rows = input->get_rows();
      int cols = input->get_cols();
      int row_stride = input->get_row_stride();
      Image *output = new Image(rows, cols, input->get_components(), CV_8U);
      // Image *output = output_data_store->read_image(errors);
      cout << "still sobeling!" << endl;
      int ptr = 0;
      for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
          if (col < cols - 1) {
            output->buf_8U[row * row_stride + col] =
                255 - abs(input->buf_8U[row * row_stride + col] -
                    input->buf_8U[row * row_stride + col + 1]);
          }
          ptr++;
        }
      }
      output->write_jpeg("sobel.jpg", errors);
    }
  }
}
