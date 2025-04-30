#include "hough.hpp"
#include <cstring>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
#include "wb_window.hpp"

extern bool debug;

Hough::~Hough() = default;
Hough::Hough() = default;
/**
 * @brief
 * @param m_image
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_pixel_threshold
 */
Hough::Hough(Image *m_image, int m_rho_inc, int m_theta_inc, int m_pixel_threshold) :
    Hough(m_image->get_ncols(), m_image->get_nrows(), m_rho_inc, m_theta_inc, m_pixel_threshold) {
    initialize(m_image, pixel_threshold);
}
Hough::Hough(int ncols, int nrows, int m_rho_inc, int m_theta_inc, int m_pixel_threshold) :
    polar_trig(std::make_unique<Polar_trig>(ncols, nrows, m_rho_inc, m_theta_inc)), nbins(get_nrhos() * get_nthetas()),
    pixel_threshold(m_pixel_threshold),
    // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
    image_frame(std::make_unique<Image_frame>(ncols, nrows)), accumulator(std::make_unique<int[]>(nbins)) {}
/**
 * @brief
 */
void Hough::clear() {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++)
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++)
            set(rho_index, theta_index, 0);
}
/**
 * @brief
 * @param lines
 * @param threshold
 */
void Hough::find_peaks(std::list<Polar_line> &lines, double threshold) {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            int count = get(rho_index, theta_index);
            if (count > threshold) {
                Polar_line line(rho_index, theta_index);
                lines.push_back(line);
            }
        }
    }
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @return
 */
int Hough::get(int rho_index, int theta_index) {
    int index = rho_theta_to_index(rho_index, theta_index);
    return accumulator[index];
}
/**
 * @brief
 * @return
 */
int Hough::get_ncols() const { return image_frame->get_ncols(); }
/**
 * @brief
 * @return
 */
int Hough::get_nrhos() const { return polar_trig->get_nrhos(); }
/**
 * @brief
 * @return
 */
int Hough::get_nrows() const { return image_frame->get_nrows(); }
/**
 * @brief
 * @return
 */
int Hough::get_nthetas() const { return polar_trig->get_nthetas(); }
/**
 * @brief
 * @return
 */
int Hough::get_rho_inc() const { return polar_trig->get_rho_inc(); }
/**
 * @brief
 * @return
 */
int Hough::get_theta_inc() const { return polar_trig->get_theta_inc(); }
/**
 * @brief
 * @param image_theshold
 */
void Hough::initialize(Image *image, int image_theshold) {
    clear();
    for (int col = 0; col < image->get_ncols(); col++) {
        for (int row = 0; row < image->get_nrows(); row++) {
            double value = std::abs(image->get(col, row));
            if (value > image_theshold) {
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    Point point;
                    image_frame->to_point(point, col, row);
                    int rho_index = polar_trig->point_theta_to_rho(col, row, theta_index);
                    update(rho_index, theta_index, wb_utils::double_to_int_round(value));
                }
            }
        }
    }
    update_accumulator_stats();
}
/*
void Hough::find_lines(int ncols, int nrows, int nrhos, int nthetas) {
  lines_to_line_segments(ncols, nrows, nrhos, nthetas);
}

void Hough::lines_to_line_segments(int nrows, int ncols, int nrhos, int nthetas) {
  for (Polar_line line: lines) {
    Line_segment line_segment;
      if (WB_window::clip_window(nrows, ncols, nrhos, nthetas,line_segment, line))
      line_segments.push_back(line_segment);
  }
}
*/
int Hough::pixel_theta_index_to_rho_index(int col, int row, int theta_index) const {
    Point point;
    image_frame->to_point(point, col, row);
    return polar_trig->point_theta_index_to_rho(point, theta_index);
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Hough *Hough::read(const std::string &path, Errors &errors) {
    FILE *fp = file_utils::open_file_read(path, errors);
    Hough *hough = nullptr;
    if (fp) {
        hough = Hough::read(fp, errors);
        fclose(fp);
    }
    return hough;
}
/**
 * @brief
 * @param fp
 * @param errors
 * @return
 */
Hough *Hough::read(FILE *fp, Errors &errors) {
    int rho_inc = 0; // TODO: define
    int theta_inc = 0; // TODO: define
    wb_utils::read_int(fp, theta_inc, "Hough::read", "", "missing hough accumulator theta_inc", errors);
    int nrows;
    if (!errors.has_error())
        wb_utils::read_int(fp, nrows, "Hough::read", "", "missing hough accumulator get_nrows()", errors);
    int ncols;
    if (!errors.has_error())
        wb_utils::read_int(fp, ncols, "Hough::read", "", "missing hough accumulator get_ncols()", errors);
    if (errors.has_error())
        return nullptr;
    else {
        auto *hough = new Hough(ncols, nrows, rho_inc, theta_inc);
        wb_utils::read_int_buffer(fp, hough->accumulator.get(), hough->nbins, "Hough::read", "",
                                  "cannot read hough accumulator data", errors);
        if (errors.has_error()) {
            delete hough;
            return nullptr;
        }
        hough->update_accumulator_stats();
        return hough;
    }
}
/**
 * @brief
 * @param ifs
 * @param errors
 * @return
 */
Hough *Hough::read_text(std::ifstream &ifs, Errors &errors) {
    auto *hough_accum = new Hough();
    std::string line;
    while (getline(ifs, line)) {
        std::vector<std::string> values = wb_utils::string_split(line);
        for (const std::string &value_str: values) {
            int value;
            if (!wb_utils::string_to_int(value_str, value)) {
                errors.add("Hough::read_text", "", "invalid value '" + value_str + "'");
                delete hough_accum;
                return nullptr;
            }
        }
    }
    return hough_accum;
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @return
 */
int Hough::rho_theta_to_index(int rho_index, int theta_index) const { return rho_index * get_nthetas() + theta_index; }
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @param value
 */
void Hough::set(int rho_index, int theta_index, int value) {
    int index = rho_theta_to_index(rho_index, theta_index);
    accumulator[index] = value;
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @param value
 */
void Hough::update(int rho_index, int theta_index, int value) const {
    int index = rho_theta_to_index(rho_index, theta_index);
    accumulator[index] += value;
}
/**
 * @brief
 */
void Hough::update_accumulator_stats() {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            accumulator_stats.update(get(rho_index, theta_index));
        }
    }
}
/**
 * @brief
 * @param path
 * @param errors
 */
void Hough::write(const std::string &path, Errors &errors) const {
    FILE *fp = file_utils::open_file_write(path, errors);
    if (fp) {
        write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write(FILE *fp, Errors &errors) const {
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator theta_inc");
        return;
    }
    int nrows = get_nrows();
    fwrite(&nrows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_nrows()");
        return;
    }
    int ncols = get_ncols();
    fwrite(&ncols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_ncols()");
        return;
    }
    size_t newLen;
    newLen = fwrite(accumulator.get(), sizeof(int), nbins, fp);
    if (ferror(fp) != 0 || newLen != nbins) {
        errors.add("Hough::write", "", "cannot write Hough accumulator data ");
        return;
    }
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Hough::write_text(const std::string &path, const std::string &delim, Errors &errors) {
    std::ofstream ofs = file_utils::open_file_write_text(path, errors);
    if (ofs) {
        write_text(ofs, "\t", errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Hough::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) {
    for (int rho_index = 0; rho_index <= get_nrhos(); rho_index++)
        ofs << polar_trig->to_rho(rho_index) << delim;
    ofs << std::endl;
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        ofs << polar_trig->to_theta(theta_index) << delim;
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            ofs << get(rho_index, theta_index) << delim;
        }
        ofs << std::endl;
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write_peak_lines(FILE *fp, Errors &errors) const {
    size_t npeaks = lines.size();
    fwrite(&npeaks, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough peak line count");
        return;
    }
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough theta_inc  ");
        return;
    }
    int nrhos = get_nrhos();
    fwrite(&nrhos, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough nrhos ");
        return;
    }
    for (Polar_line line: lines) {
        line.write(fp, errors);
        if (errors.has_error())
            break;
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Hough::write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    for (Polar_line line: lines) {
        line.write_text(ofs, delim, errors);
        if (errors.has_error())
            break;
    }
}
