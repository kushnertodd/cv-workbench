#include "operator_filter_smooth_average.hpp"
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

Operator_filter_smooth_average::~Operator_filter_smooth_average() = default;
void Operator_filter_smooth_average::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_smooth_average::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_smooth_average::run", "", "output data source required");
    int ncols{};
    Operator_utils::get_int_parameter("Operator_filter_smooth_average::run", operator_parameters, "ncols", ncols,
                                      errors);
    int nrows{};
    Operator_utils::get_int_parameter("Operator_filter_smooth_average::run", operator_parameters, "nrows", nrows,
                                      errors);
    Data_source_descriptor *input_data_source = input_data_sources.front();
    if (!errors.has_error()) {
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_smooth_average::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_smooth_average::run", errors);
        // TODO: implement separable filter
        if (!errors.has_error()) {
            std::unique_ptr<pixel_32F[]> coeffs_32F = std::make_unique<pixel_32F[]>(ncols * nrows);
            double correction = 1.0 / (ncols * nrows);
            for (int i = 0; i < ncols * nrows; i++)
                coeffs_32F[i] = wb_utils::double_to_float(correction);
            std::unique_ptr<Kernel> average_kernel(Kernel::create_32F(ncols, nrows, coeffs_32F.get()));
            std::unique_ptr<Image> output_image(average_kernel->convolve_numeric(input_image.get(), errors));
            if (!errors.has_error())
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(), "Operator_filter_smooth_average::run",
                                                            errors);
            if (!errors.has_error())
                output_image->log(log_entries);
        }
    }
}
