#include <algorithm>
#include <iostream>
#include <iomanip>
#include "textUtils.hpp"

using namespace std;

namespace miscutils {

/**
 * determine character for Ascii code
 * @param n to convert
 * @return C char
 */
char ascii2char(int n) {
  return char(n);
}

/**
 * convert C char to string
 * @param c to convert
 * @return c++ string
 */
string char2string(char c) {
  string s(1, c);
  return s;
}

/**
 * convert int to hex string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string intToHex(unsigned long long i, int width) {
  ostringstream os;
  if (width == -1) {
    os << setbase(16) << i;
  } else {
    os << setbase(16) << setw(width) << i;
  }
  return os.str();
}

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string intToText(int i, int width) {
  ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << setw(width) << i;
  }
  return os.str();
}

/**
 * verify string is numeric
 * a [+-]\d+
 * b [+-]\d+.
 * c [+-].\d+
 * d [+-]\d+.\d+
 * possibilites:
 *  1 [+-]                 false
 *  2 [+-]\D               false
 *  3 [+-]\d+              a      intdigits
 *  4   [+-]\d+\D          false
 *  5   [+-]\d+.           b      intdigits
 *  6     [+-]\d+.\D       false
 *  7     [+-]\d+.\d+      d      intdigits, fracdigits
 *  8       [+-]\d+.\d+\D  false
 *  9 [+-].                false
 * 10  [+-].\D             false
 * 11  [+-].\d+            c      fracdigits
 * 12    [+-].\d+\D        false
 * @param number
 * @return
 */
bool isNumeric(string number) {
  int len = number.size();
  int pos = 0;
  // look for [+-]
  if (pos < len && (number[pos] == '+' || number[pos] == '-'))
    pos++;
  bool sawIntDigits = false;
  bool sawFracDigits = false;
  bool sawPeriod = false;
  for (; pos < len && isdigit(number[pos]); pos++) {
    sawIntDigits = true; // a, b
  }
  if (pos >= len)
    return sawIntDigits; // a, b, d
  if (number[pos] == '.') {
    sawPeriod = true; // 5-12
    pos++;
    for (; pos < len && isdigit(number[pos]); pos++) {
      sawFracDigits = true; // 7, 8, 11, 12
    }
  }
  if (pos >= len)
    return sawIntDigits || (sawPeriod && sawFracDigits); // 3, 5, 7, 11
  return false; // 1-2, 4, 6, 8-10, 12
}

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string realToText(double i, int width) {
  ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << setw(width) << i;
  }
  return os.str();
}

/**
 * decode hex string to integer
 * @param arg
 * @param value
 * @return
 */
bool textHexToInt(string arg, unsigned long long &value) {
  stringstream ss;
  ss << std::hex << arg;
  if (ss >> value) {
    return true;
  } else
    return false;
}

/**
* parse integer argument
* throws if invalid
* @param arg integer
* @param message to print on failure
* @return int from argument
*/
bool textToInt(string arg, int &value) {
  stringstream ss(arg);
  if (ss >> value) return true;
  else return false;
}

bool textToReal(string arg, double &value) {
  stringstream ss(arg);
  if (ss >> value) return true;
  else return false;
}

