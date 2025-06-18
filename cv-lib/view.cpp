#include "view.hpp"

/**
 * @brief
 */
View::~View() {}
/**
 * @brief
 */
View::View() = default;
/**
 * kludgy, any bool argument invokes. needed to honor legacy calls.
 * @brief
 * @param m_ncols
 * @param m_nrows
 */
View::View(int m_ncols, int m_nrows) : ncols(m_ncols), nrows(m_nrows) {}
/**
 * @brief
 * @return
 */
int View::get_ncols() const { return ncols; }
/**
 * @brief
 * @return
 */
int View::get_nrows() const { return nrows; }
