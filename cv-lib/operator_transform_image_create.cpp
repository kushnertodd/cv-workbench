#include "operator_transform_image_create.hpp"
#include <iostream>
#include <regex>
#include "operator_utils.hpp"

extern bool debug;

/**
   create new image from an existing image

 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_image_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (input_data_sources.empty())
        errors.add("Operator_transform_image_create::run", "", "input data source required");
    else if (input_data_sources.size() > 1)
        errors.add("Operator_transform_image_create::run", "", "too many input data sources");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_image_create::run", "", "output data source required");
    else {
        int ncols;
        int nrows;
        double background = 0;
        double foreground = 255;
        bool saw_ncols = false;
        bool saw_nrows = false;
        if (Operator_utils::has_parameter(operator_parameters, "ncols")) {
            saw_ncols = true;
            Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "ncols",
                                              ncols, errors);
        }
        if (Operator_utils::has_parameter(operator_parameters, "nrows")) {
            saw_nrows = true;
            Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "nrows",
                                              nrows, errors);
        }
        if (Operator_utils::has_parameter(operator_parameters, "background"))
            Operator_utils::get_real_parameter("Operator_transform_image_create::run", operator_parameters,
                                               "background", background, errors);
        if (Operator_utils::has_parameter(operator_parameters, "foreground"))
            Operator_utils::get_real_parameter("Operator_transform_image_create::run", operator_parameters,
                                               "foreground", foreground, errors);
        if (!saw_ncols)
            errors.add("Operator_transform_image_create::run", "", "missing ncols parameter");
        if (!saw_nrows)
            errors.add("Operator_transform_image_create::run", "", "missing nrows parameter");
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data *input_ptr = nullptr;
        if (!errors.has_error())
            input_ptr = input_data_source->read_operator_data("Operator_transform_image_create::run", errors);
        Image *image = nullptr;
        if (!errors.has_error()) {
            image = new Image(ncols, nrows, 1, Image_depth::CV_8U, background);
            for (std::string line: input_ptr->lines) {
                std::vector<std::string> tokens = wb_utils::tokenize(line, " ");
                if (tokens.empty())
                    errors.add("Operator_transform_image_create::run", "", "invalid draw command: '" + line + "'");
                if (!errors.has_error()) {
                    if (tokens[0] == "P") {
                        std::vector<std::string> params = wb_utils::tokenize(tokens[1], ",");
                        if (params.size() != 2)
                            errors.add("Operator_transform_image_create::run", "", "invalid point command argument");
                        else {
                            int col;
                            int row;
                            if (!wb_utils::string_to_int(params[0], col))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid point parameter col value");
                            if (!wb_utils::string_to_int(params[1], row))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid point parameter row value");
                            if (!errors.has_error()) {
                                image->set(col, row, foreground);
                            }
                        }
                    } else if (tokens[0] == "L") {
                        std::vector<std::string> params = wb_utils::tokenize(tokens[1], ",");
                        if (params.size() != 4)
                            errors.add("Operator_transform_image_create::run", "", "invalid line command argument");
                        else {
                            int col1;
                            int row1;
                            int col2;
                            int row2;
                            if (!wb_utils::string_to_int(params[0], col1))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid line parameter col1 value");
                            if (!wb_utils::string_to_int(params[1], row1))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid line parameter row1 value");
                            if (!wb_utils::string_to_int(params[0], col2))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid line parameter col2 value");
                            if (!wb_utils::string_to_int(params[1], row2))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid line parameter row2 value");
                            if (!errors.has_error())
                                image->draw_line_segment(col1, row1, col2, row2, foreground);
                        }
                    } else if (tokens[0] == "R") {
                        std::vector<std::string> params = wb_utils::tokenize(tokens[1], ",");
                        if (params.size() != 4)
                            errors.add("Operator_transform_image_create::run", "",
                                       "invalid rectangle command argument");
                        else {
                            int col1;
                            int row1;
                            int col2;
                            int row2;
                            if (!wb_utils::string_to_int(params[0], col1))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid rectangle parameter col1 value");
                            if (!wb_utils::string_to_int(params[1], row1))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid rectangle parameter row1 value");
                            if (!wb_utils::string_to_int(params[0], col2))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid rectangle parameter col2 value");
                            if (!wb_utils::string_to_int(params[1], row2))
                                errors.add("Operator_transform_image_create::run", "",
                                           "invalid rectangle parameter row2 value");
                            if (!errors.has_error())
                                image->draw_rectangle(col1, row1, col2, row2, foreground);
                        }
                    }
                } else if (tokens[0] == "F") {
                    std::vector<std::string> params = wb_utils::tokenize(tokens[1], ",");
                    if (params.size() != 4)
                        errors.add("Operator_transform_image_create::run", "",
                                   "invalid filled rectangle command argument");
                    else {
                        int col1;
                        int row1;
                        int col2;
                        int row2;
                        if (!wb_utils::string_to_int(params[0], col1))
                            errors.add("Operator_transform_image_create::run", "",
                                       "invalid filled rectangle parameter col value");
                        if (!wb_utils::string_to_int(params[1], row1))
                            errors.add("Operator_transform_image_create::run", "",
                                       "invalid filled rectangle parameter row value");
                        if (!wb_utils::string_to_int(params[0], col2))
                            errors.add("Operator_transform_image_create::run", "",
                                       "invalid filled rectangle parameter col value");
                        if (!wb_utils::string_to_int(params[1], row2))
                            errors.add("Operator_transform_image_create::run", "",
                                       "invalid filled rectangle parameter row value");
                        if (!errors.has_error())
                            image->draw_rectangle_filled(col1, row1, col2, row2, foreground);
                    }
                } else
                    errors.add("Operator_transform_image_create::run", "", "invalid pixel parameter value");
            }
        }
        if (!errors.has_error())
            for (Data_source_descriptor *output_data_store: output_data_stores)
                output_data_store->write_operator_image(image, "Operator_transform_image_create::run", errors);
    }
}
