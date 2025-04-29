#include "operator_filter_smooth_gaussian.hpp"
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

Operator_filter_smooth_gaussian::~Operator_filter_smooth_gaussian() = default;
void Operator_filter_smooth_gaussian::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (input_data_sources.empty())
        errors.add("Operator_filter_smooth_gaussian::run", "", "input data source required");
    if (input_data_sources.size() > 1)
        errors.add("Operator_filter_smooth_gaussian::run", "", "too many input data sources");
    if (output_data_stores.empty())
        errors.add("Operator_filter_smooth_gaussian::run", "", "output data source required");
    if (output_data_stores.size() > 1)
        errors.add("Operator_filter_smooth_gaussian::run", "", "too many output data sources");
    int nrows;
    int ncols;
    double sigma_x;
    double sigma_y;
    Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "nrows", nrows,
                                      errors);
    Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "ncols", ncols,
                                      errors);
    Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "sigma-x", sigma_x,
                                       errors);
    Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run", operator_parameters, "sigma-y", sigma_y,
                                       errors);
    Data_source_descriptor *input_data_source = input_data_sources.front();
    Data_source_descriptor *output_data_store = output_data_stores.front();
    Image *input = nullptr;
    if (!errors.has_error())
        input = input_data_source->read_operator_image("Operator_filter_smooth_gaussian::run", errors);
    if (!errors.has_error() && input != nullptr)
        input->check_grayscale("Operator_filter_smooth_gaussian::run", errors);
    if (!errors.has_error() && input != nullptr) {
        Kernel *gaussian_kernel_y_ptr = Kernel::create_gaussian_y(nrows, sigma_y);
        Kernel *gaussian_kernel_x_ptr = Kernel::create_gaussian_x(ncols, sigma_x);
        std::unique_ptr<Kernel> gaussian_kernel_y(gaussian_kernel_y_ptr);
        std::unique_ptr<Kernel> gaussian_kernel_x(gaussian_kernel_x_ptr);
        Image *output_pass1 = gaussian_kernel_y->convolve_numeric(input, errors);
        Image *output_pass2 = nullptr;
        if (!errors.has_error() && output_pass1 != nullptr)
            output_pass2 = gaussian_kernel_x->convolve_numeric(output_pass1, errors);
        if (!errors.has_error() && output_pass2 != nullptr)
            output_data_store->write_operator_image(output_pass2, "Operator_filter_smooth_gaussian::run", errors);
        if (!errors.has_error() && output_pass2 != nullptr) {
            output_pass2->log(log_entries);
        }
        delete output_pass1;
        delete output_pass2;
        delete input;
    }
}
