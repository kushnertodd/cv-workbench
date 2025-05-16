#include "operator_filter_smooth_gaussian.hpp"
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

Operator_filter_smooth_gaussian::~Operator_filter_smooth_gaussian() = default;
void Operator_filter_smooth_gaussian::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_smooth_gaussian::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_smooth_gaussian::run", "", "output data source required");

    int ncols{};
    int nrows{};
    double sigma_x{};
    double sigma_y{};
    Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "ncols", ncols,
                                      errors);
    Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "nrows", nrows,
                                      errors);
    Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "sigma-x", sigma_x,
                                       errors);
    Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "sigma-y", sigma_y,
                                       errors);
    Data_source_descriptor *input_data_source = input_data_sources.front();
    if (!errors.has_error()) {
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_smooth_gaussian::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_smooth_gaussian::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Kernel> gaussian_kernel_y(Kernel::create_gaussian_y(nrows, sigma_y));
            std::unique_ptr<Kernel> gaussian_kernel_x(Kernel::create_gaussian_x(ncols, sigma_x));
            std::unique_ptr<Image> output_pass1_image(gaussian_kernel_y->convolve_numeric(input_image.get(), errors));
            if (!errors.has_error()) {
                std::unique_ptr<Image> output_pass2_image(
                        gaussian_kernel_y->convolve_numeric(output_pass1_image.get(), errors));
                if (!errors.has_error())
                    for (Data_source_descriptor *output_data_store: output_data_stores)

                        output_data_store->write_operator_image(output_pass2_image.get(),
                                                                "Operator_filter_smooth_gaussian::run", errors);
                if (!errors.has_error())
                    output_pass2_image->log(log_entries);
            }
        }
    }
}
