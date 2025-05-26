#include "operator_filter_edge_laplacian.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_filter_edge_laplacian::~Operator_filter_edge_laplacian() = default;

/**
 * kernel:
 *     [-0.125, -0.125, -0.125], [-0.125, 1.0, -0.125], [-0.125, -0.125, -0.125]
 *
 * @param input_data_sources input binary or jpeg image
 * @param output_data_stores output binary, jpeg, or test images
 * @param operator_parameters parameters
 * @param errors any run errors
 */
void Operator_filter_edge_laplacian::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_edge_laplacian::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_laplacian::run", "", "output data sources required");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_laplacian::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_edge_laplacian::run", errors);
        if (!errors.has_error()) {
            Kernel *laplacian_kernel_ptr = nullptr;
            //       [-0.125, -0.125, -0.125], [-0.125, 1.0, -0.125], [-0.125, -0.125, -0.125]
            float coeffs_32F[] = {-0.125, -0.125, -0.125, -0.125, 1.0, -0.125, -0.125, -0.125, -0.125};
            laplacian_kernel_ptr = Kernel::create_32F(3, 3, coeffs_32F);
            std::unique_ptr<Kernel> laplacian_kernel(laplacian_kernel_ptr);
            std::unique_ptr<Image> output_image(laplacian_kernel->convolve_numeric(input_image.get(), errors));
            if (!errors.has_error())
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(), "Operator_filter_edge_laplacian::run",
                                                            errors);
            if (!errors.has_error())
                output_image->log(log_entries);
        }
    }
}
