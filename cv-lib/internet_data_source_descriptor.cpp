#include "internet_data_source_descriptor.hpp"
#include <iostream>
#include <sstream>
#include "data_source_descriptor.hpp"
#include "wb_json_utils.hpp"

extern bool debug;
/**
 * @brief
 * @param m_id
 * @param m_data_type
 * @param m_data_format
 */
Internet_data_source_descriptor::Internet_data_source_descriptor(int m_id, WB_data_type::Data_type m_data_type,
                                                                 WB_data_format::Data_format m_data_format) :
    Data_source_descriptor(m_id, m_data_type, m_data_format, WB_repository_types::Repository_type::INTERNET) {}
/**
 * @brief
 * @param errors
 * @return
 */
Histogram *Internet_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
Hough *Internet_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
Image *Internet_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
Image *Internet_data_source_descriptor::read_image_jpeg(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
Image *Internet_data_source_descriptor::read_image_text(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
std::string Internet_data_source_descriptor::read_json(Errors &errors) { return ""; }
/**
 * @brief
 * @param histogram
 * @param errors
 */
void Internet_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
/**
 * @brief
 * @param histogram
 * @param errors
 */
void Internet_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Internet_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Internet_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Internet_data_source_descriptor::write_hough_peaks(Hough *hough, Errors &errors) {}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Internet_data_source_descriptor::write_hough_peaks_text(Hough *hough, Errors &errors) {}
/**
 * @brief
 * @param image
 * @param errors
 */
void Internet_data_source_descriptor::write_image(Image *image, Errors &errors) {}
/**
 * @brief
 * @param image
 * @param errors
 */
void Internet_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {}
/**
 * @brief
 * @param image
 * @param errors
 */
void Internet_data_source_descriptor::write_image_text(Image *image, Errors &errors) {}
/**
 * @brief
 * @param json
 * @param errors
 */
void Internet_data_source_descriptor::write_json(std::string &json, Errors &errors) {}
/**
 * @brief
 * @param json_data_source_descriptor
 * @param id
 * @param data_type
 * @param data_format
 * @param errors
 * @return
 */
Internet_data_source_descriptor *Internet_data_source_descriptor::from_json(json_object *json_data_source_descriptor,
                                                                            int id, WB_data_type::Data_type data_type,
                                                                            WB_data_format::Data_format data_format,
                                                                            Errors &errors) {
    if (debug)
        std::cout << "Internet_data_source_descriptor::from_json: id '" << id << "' type " << std::endl;
    auto *internet_data_source_descriptor = new Internet_data_source_descriptor(id, data_type, data_format);
    json_object *json_url = get_json_object("Internet_data_source_descriptor::from_json", json_data_source_descriptor,
                                            "url", json_type_string, errors);
    if (json_url != nullptr)
        internet_data_source_descriptor->url = json_object_get_string(json_url);
    json_object *json_depth = get_json_object("Internet_data_source_descriptor::from_json", json_data_source_descriptor,
                                              "depth", json_type_string, errors);
    if (json_depth != nullptr)
        internet_data_source_descriptor->depth = json_object_get_string(json_depth);
    json_object *json_columns = get_json_object("Internet_data_source_descriptor::from_json",
                                                json_data_source_descriptor, "ncol", json_type_int, errors);
    if (json_columns != nullptr)
        internet_data_source_descriptor->ncols = json_object_get_int(json_columns);
    json_object *json_rows = get_json_object("Internet_data_source_descriptor::from_json", json_data_source_descriptor,
                                             "nrows", json_type_int, errors);
    if (json_rows != nullptr)
        internet_data_source_descriptor->nrows = json_object_get_int(json_rows);
    return internet_data_source_descriptor;
}
/**
 * @brief
 * @return
 */
std::string Internet_data_source_descriptor::to_string() {
    std::ostringstream os;
    os << Data_source_descriptor::to_string() << " url " << url << " depth " << depth << " ncols " << ncols << " nrows "
       << nrows;
    return os.str();
}
