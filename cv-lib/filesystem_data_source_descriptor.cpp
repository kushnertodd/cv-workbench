#include "filesystem_data_source_descriptor.hpp"
#include <iostream>
#include <sstream>
#include "data_source_descriptor.hpp"
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_json_utils.hpp"
#include "wb_repository_types.hpp"

extern bool debug;

/**
 * @brief
 * @param m_id
 * @param m_data_type
 * @param m_data_format
 */
Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id, WB_data_type::Data_type m_data_type,
                                                                     WB_data_format::Data_format m_data_format) :
    Data_source_descriptor(m_id, m_data_type, m_data_format, WB_repository_types::Repository_type::FILESYSTEM) {}
/**
 * @brief
 * @param json_data_source_descriptor
 * @param id
 * @param data_type
 * @param data_format
 * @param errors
 * @return
 */
Filesystem_data_source_descriptor *
Filesystem_data_source_descriptor::from_json(json_object *json_data_source_descriptor, int id,
                                             WB_data_type::Data_type data_type, WB_data_format::Data_format data_format,
                                             Errors &errors) {
    if (debug)
        std::cout << "Filesystem_data_source_descriptor::from_json: id '" << id << "' type " << std::endl;
    auto *filesystem_data_source_descriptor = new Filesystem_data_source_descriptor(id, data_type, data_format);

    // parse: ' "directory": ... `
    json_object *json_directory = get_json_object("Filesystem_data_source_descriptor::from_json",
                                                  json_data_source_descriptor, "directory", json_type_string, errors);
    if (errors.has_error()) {
        delete filesystem_data_source_descriptor;
        return nullptr;
    }
    if (json_directory != nullptr)
        filesystem_data_source_descriptor->directory = json_object_get_string(json_directory);
    else
        filesystem_data_source_descriptor->directory = ".";

    // parse: ' "filename": ... `
    json_object *json_filename = get_json_object("Filesystem_data_source_descriptor::from_json",
                                                 json_data_source_descriptor, "filename", json_type_string, errors);
    if (errors.has_error()) {
        delete filesystem_data_source_descriptor;
        return nullptr;
    }
    if (json_filename != nullptr)
        filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);
    else
        errors.add("Filesystem_data_source_descriptor::from_json", "", "missing required filename");

    // parse: ' "ext": ... `
    json_object *json_ext = get_json_object("Filesystem_data_source_descriptor::from_json", json_data_source_descriptor,
                                            "ext", json_type_string, errors, true);
    if (errors.has_error()) {
        delete filesystem_data_source_descriptor;
        return nullptr;
    }
    if (json_ext != nullptr)
        filesystem_data_source_descriptor->ext = json_object_get_string(json_ext);
    else
        filesystem_data_source_descriptor->ext = WB_data_format::to_ext(filesystem_data_source_descriptor->data_format);
    return filesystem_data_source_descriptor;
}
/**
 * @brief
 * @param errors
 * @return
 */
Data *Filesystem_data_source_descriptor::read_data(Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::string data_filename = wb_filename.to_text();
    return Data::read_text(data_filename, errors);
}
/**
 * @brief
 * @param errors
 * @return
 */
Histogram *Filesystem_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
/**
 * @brief
 * @param errors
 * @return
 */
Hough *Filesystem_data_source_descriptor::read_hough(Errors &errors) {
    std::string path = to_path_noext();
    Hough *hough = Hough::read(path, errors);
    return hough;
}
/**
 * @brief
 * @param errors
 * @return
 */
Image *Filesystem_data_source_descriptor::read_image(Errors &errors) {
    std::string path = to_path_noext();
    Image *image = Image::read(path, errors);
    return image;
}
/**
 * @brief
 * @param errors
 * @return
 */
Image *Filesystem_data_source_descriptor::read_image_jpeg(Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::JPEG);
    std::string data_filename = wb_filename.to_jpeg();
    return Image::read_jpeg(data_filename, errors);
}
/**
 * @brief
 * @param errors
 * @return
 */
Image *Filesystem_data_source_descriptor::read_image_text(Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::string data_filename = wb_filename.to_text();
    return Image::read_text(data_filename, errors);
}
/**
 * @brief
 * @param errors
 * @return
 */
std::string Filesystem_data_source_descriptor::read_json(Errors &errors) { return ""; }
/**
 * @brief
 * @param ifs
 * @param errors
 * @return
 */
Hough *Filesystem_data_source_descriptor::read_text(std::ifstream &ifs, Errors &errors) { return nullptr; }
/**
 * @brief
 * @return
 */
std::string Filesystem_data_source_descriptor::to_path() const { return to_path_noext() + "." + ext; }
/**
 * @brief
 * @return
 */
std::string Filesystem_data_source_descriptor::to_path_noext() const {
    return (directory.empty() ? "" : directory + "/") + filename;
}
/**
 * @brief
 * @return
 */
std::string Filesystem_data_source_descriptor::to_string() {
    std::ostringstream os;
    os << Data_source_descriptor::to_string() << " file format '" << WB_data_format::to_string(data_format)
       << "' directory '" << directory << "' filename '" << filename << "' ext '" << ext << "'";
    return os.str();
}
/**
 * @brief
 * @param histogram
 * @param errors
 */
void Filesystem_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_hist();
    FILE *fp = file_utils::open_file_write(data_filename, errors);
    if (fp) {
        histogram->write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param histogram
 * @param errors
 */
void Filesystem_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::string data_filename = wb_filename.to_hist_text();
    histogram->write_text(data_filename, "\t", errors);
}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Filesystem_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_hough();
    FILE *fp = file_utils::open_file_write(data_filename, errors);
    if (fp) {
        hough->write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Filesystem_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::string data_filename = wb_filename.to_hough_text();
    std::ofstream ofs = file_utils::open_file_write_text(data_filename, errors);
    if (!errors.has_error()) {
        hough->write_text(ofs, "\t", errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Filesystem_data_source_descriptor::write_hough_peaks(Hough *hough, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_peaks();
    FILE *fp = file_utils::open_file_write(data_filename, errors);
    if (fp) {
        hough->write_peak_lines(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param hough
 * @param errors
 */
void Filesystem_data_source_descriptor::write_hough_peaks_text(Hough *hough, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::string data_filename = wb_filename.to_peaks_text();
    std::ofstream ofs = file_utils::open_file_write_text(data_filename, errors);
    if (!errors.has_error()) {
        hough->write_peak_lines_text(ofs, "\t", errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param image
 * @param errors
 */
void Filesystem_data_source_descriptor::write_image(Image *image, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_bin();
    FILE *fp = file_utils::open_file_write(data_filename, errors);
    if (fp) {
        image->write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param image
 * @param errors
 */
void Filesystem_data_source_descriptor::write_image_text(Image *image, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_text();
    std::ofstream ofs = file_utils::open_file_write_text(data_filename, errors);
    if (!errors.has_error()) {
        image->write_text(ofs, "\t", errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param image
 * @param errors
 */
void Filesystem_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {
    std::string path = to_path_noext();
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
    std::string data_filename = wb_filename.to_jpeg();
    image->write_jpeg(data_filename, errors);
}
/**
 * @brief
 * @param json
 * @param errors
 */
void Filesystem_data_source_descriptor::write_json(std::string &json, Errors &errors) {}
