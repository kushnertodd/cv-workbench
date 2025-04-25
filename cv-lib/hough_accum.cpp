//
// Created by kushn on 6/27/2022.
//

#include "hough_accum.hpp"
#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"

extern bool debug;

Hough_accum::~Hough_accum() {
    delete polar_trig;
    delete rho_theta_counts;
}

Hough_accum::Hough_accum() = default;

Hough_accum::Hough_accum(int m_ncols, int m_nrows, int m_rho_inc, int m_theta_inc) {
    polar_trig = new Polar_trig(m_ncols, m_nrows, m_rho_inc, m_theta_inc);
    nbins = get_nrhos() * get_nthetas();
    rho_theta_counts = new int[nbins];
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++)
            set(rho_index, theta_index, 0);
    }
}

Hough_accum *Hough_accum::create_image(Image *image, int m_rho_inc, int m_theta_inc, int pixel_threshold) {
    auto *hough_accum = new Hough_accum(image->get_ncols(), image->get_nrows(), m_rho_inc, theta_inc);
    hough_accum->initialize(image, pixel_threshold);
    return hough_accum;
}

void Hough_accum::find_peaks(std::list<Polar_line> &lines, double threshold) {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            int count = get(rho_index, theta_index);
            if (count > threshold) {
                Polar_line line(rho_index, polar_trig->to_rho(rho_index), theta_index, Polar_trig::to_cos(theta_index),
                                Polar_trig::to_sin(theta_index), count);
                lines.push_back(line);
            }
        }
    }
}
int Hough_accum::get(int rho_index, int theta_index) {
    int index = rho_theta_to_index(rho_index, theta_index);
    return rho_theta_counts[index];
}
int Hough_accum::get_ncols() const { return polar_trig->get_ncols(); }
int Hough_accum::get_nrhos() const { return polar_trig->get_nrhos(); }
int Hough_accum::get_nthetas() const { return polar_trig->get_nthetas(); }
int Hough_accum::get_nrows() const { return polar_trig->get_nrows(); }
int Hough_accum::get_rho_inc() const { return polar_trig->get_rho_inc(); }
int Hough_accum::get_theta_inc() const { return polar_trig->get_theta_inc(); }
/**
 * initialize_image accumulator
 *
 * @param image_theshold
 */
void Hough_accum::initialize(Image *image, int image_theshold) {
    for (int row = 0; row < get_nrows(); row++) {
        for (int col = 0; col < get_ncols(); col++) {
            double value = std::abs(image->get(row, col));
            if (value > image_theshold) {
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    int rho_index = polar_trig->col_row_theta_to_rho(row, col, theta_index);
                    update(rho_index, theta_index, wb_utils::double_to_int_round(value));
                }
            }
        }
    }
    update_accumulator_stats();
}

Hough_accum *Hough_accum::read(FILE *fp, Errors &errors) {
    int rho_inc = 0; // TODO: define
    int theta_inc = 0; // TODO: define
    wb_utils::read_int(fp, theta_inc, "Hough_accum::read", "", "missing hough accumulator theta_inc", errors);
    int nrows;
    if (!errors.has_error())
        wb_utils::read_int(fp, nrows, "Hough_accum::read", "", "missing hough accumulator get_nrows()", errors);
    int ncols;
    if (!errors.has_error())
        wb_utils::read_int(fp, ncols, "Hough_accum::read", "", "missing hough accumulator get_ncols()", errors);
    if (errors.has_error())
        return nullptr;
    else {
        auto *hough_accum = new Hough_accum(ncols, nrows, rho_inc, theta_inc);
        wb_utils::read_int_buffer(fp, hough_accum->rho_theta_counts, hough_accum->nbins, "Hough_accum::read", "",
                                  "cannot read hough accumulator data", errors);
        if (errors.has_error()) {
            delete hough_accum;
            return nullptr;
        }
        hough_accum->update_accumulator_stats();
        return hough_accum;
    }
}

// NRFPT
Hough_accum *Hough_accum::read_text(std::ifstream &ifs, Errors &errors) {
    auto *hough_accum = new Hough_accum();
    std::string line;
    while (getline(ifs, line)) {
        std::vector<std::string> values = wb_utils::string_split(line);
        for (const std::string &value_str: values) {
            int value;
            if (!wb_utils::string_to_int(value_str, value)) {
                errors.add("Hough_accum::read_text", "", "invalid value '" + value_str + "'");
                delete hough_accum;
                return nullptr;
            }
        }
    }
    return hough_accum;
}
int Hough_accum::rho_theta_to_index(int rho_index, int theta_index) { return rho_index * get_nthetas() + theta_index; }
void Hough_accum::set(int rho_index, int theta_index, int value) {
    int index = rho_theta_to_index(rho_index, theta_index);
    rho_theta_counts[index] = value;
}

void Hough_accum::update(int rho_index, int theta_index, int value) {
    int index = rho_theta_to_index(rho_index, theta_index);
    rho_theta_counts[index] += value;
}

void Hough_accum::update_accumulator_stats() {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            accumulator_stats.update(get(rho_index, theta_index));
        }
    }
}

void Hough_accum::write(FILE *fp, Errors &errors) const {
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough_accum::write", "", "cannot write Hough accumulator theta_inc");
        return;
    }
    int nrows = get_nrows();
    fwrite(&nrows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough_accum::write", "", "cannot write Hough accumulator get_nrows()");
        return;
    }
    int ncols = get_ncols();
    fwrite(&ncols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough_accum::write", "", "cannot write Hough accumulator get_ncols()");
        return;
    }
    size_t newLen;
    newLen = fwrite(rho_theta_counts, sizeof(int), nbins, fp);
    if (ferror(fp) != 0 || newLen != nbins) {
        errors.add("Hough_accum::write", "", "cannot write Hough accumulator data ");
        return;
    }
}

void Hough_accum::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) {
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
