#include "operator_transform_image_copy.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_transform_image_copy::~Operator_transform_image_copy() = default;
/**
 * @brief
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_transform_image_copy::run(std::list<Data_source_descriptor *> &input_data_sources,
                                        std::list<Data_source_descriptor *> &output_data_stores,
                                        String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                        Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_transform_image_copy::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_image_copy::run", "", "at least one output data source required");
    int min_col{};
    int min_row{};
    int max_col{};
    int max_row{};
    bool saw_ncols = false;
    bool saw_nrows = false;
    bool saw_min_col{};
    bool saw_min_row{};
    bool saw_max_col{};
    bool saw_max_row{};
    if (Operator_utils::has_parameter(operator_parameters, "min-col")) {
        saw_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_copy::run", operator_parameters, "min-col", min_col,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "min-row")) {
        saw_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_copy::run", operator_parameters, "min-row", min_row,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "max-col")) {
        saw_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_copy::run", operator_parameters, "max-col", max_col,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "max-row")) {
        saw_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_copy::run", operator_parameters, "max-row", max_row,
                                          errors);
    }
    Data_source_descriptor *input_data_source = input_data_sources.front();
    if (!errors.has_error()) {
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_prewitt::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_edge_prewitt::run", errors);
        if (!errors.has_error()) {
            int in_ncols = input_image->get_ncols();
            int in_nrows = input_image->get_nrows();
            if (!saw_min_col)
                min_col = 0;
            if (!saw_min_row)
                min_row = 0;
            if (!saw_max_col)
                max_col = in_ncols - 1;
            if (!saw_max_row)
                max_row = in_nrows - 1;
            std::unique_ptr<Image> output_image(input_image->copy(min_col, min_row, max_col, max_row, errors));
            if (!errors.has_error()) {
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(), "Operator_transform_image_copy::run",
                                                            errors);
                if (!errors.has_error())
                    input_image->log(log_entries);
            }
        }
    }
}
