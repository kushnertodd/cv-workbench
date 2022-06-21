//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "operator_filter_edge_sobel.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
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
                                     String_map &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    cout << "Operator_filter_edge_sobel::run parameters: "
         << Operator_utils::parameters_to_string(operator_parameters) << endl;
  }
  if (input_data_sources.size() == 0)
    errors.add("Operator_filter_edge_sobel::run missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_sobel::run too many input data sources");
  else if (output_data_stores.size() == 0)
    errors.add("Operator_filter_edge_sobel::run missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_sobel::run too many output data sources");
  else {
    int orientation;
    if (Operator_utils::get_int_parameter("Operator_filter_edge_sobel::run",
                                          operator_parameters, "orientation",
                                          orientation, errors)) {
      if (orientation != 0 && orientation != 1) {
        errors.add("Operator_filter_edge_sobel: invalid 'orientation' parameter not 0 or 1");
      } else {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = input_data_source->read_image(errors);
        int rows = input->get_rows();
        int cols = input->get_cols();
        int row_stride = input->get_row_stride();
        Image *output = new Image(rows, cols, input->get_components(), CV_32S);
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
}
