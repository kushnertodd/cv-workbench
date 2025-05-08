#include "operator_filter_smooth_average.hpp"
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

Operator_filter_smooth_average::~Operator_filter_smooth_average() = default;
void Operator_filter_smooth_average::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
    if (input_data_sources.empty())
        errors.add("Operator_filter_smooth_average::run", "", "input data source required");
    if (input_data_sources.size() > 1)
        errors.add("Operator_filter_smooth_average::run", "", "too many input data sources");
    if (output_data_stores.empty())
        errors.add("Operator_filter_smooth_average::run", "", "output data source required");
    if (output_data_stores.size() > 1)
        errors.add("Operator_filter_smooth_average::run", "", "too many output data sources");
    int ncols;
    Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "ncols", ncols,
                                      errors);
    int nrows;
    Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "nrows", nrows,
                                      errors);
    Data_source_descriptor *input_data_source = input_data_sources.front();
    Data_source_descriptor *output_data_store = output_data_stores.front();
    Image *input = nullptr;
    if (!errors.has_error())
        input = input_data_source->read_operator_image("Operator_filter_smooth_average::run", errors);
    if (!errors.has_error() && input != nullptr)
        input->check_grayscale("Operator_filter_smooth_average::run", errors);
    // TODO: implement separable filter
    if (!errors.has_error() && input != nullptr) {
        auto *coeffs_32F = new pixel_32F[ncols * nrows];
        double correction = 1.0 / (ncols * nrows);
        for (int i = 0; i < ncols * nrows; i++)
            coeffs_32F[i] = wb_utils::double_to_float(correction);
        std::unique_ptr<Kernel> average_kernel(Kernel::create_32F(ncols, nrows, coeffs_32F));
        Image *output = average_kernel->convolve_numeric(input, errors);
        if (!errors.has_error() && output != nullptr)
            output_data_store->write_operator_image(output, "Operator_filter_smooth_average::run", errors);
        if (!errors.has_error() && output != nullptr) {
            output->log(log_entries);
        }
        delete[] coeffs_32F;
        delete output;
    }
    delete input;
}
