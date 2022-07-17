#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <string>

//

char ascii2char(int n);
std::string char2string(char c);
std::string intToHex(unsigned long long i, int width = -1);
std::string intToText(int i, int width = -1);
bool isNumeric(std::string number);
std::string realToText(double i, int width = -1);
bool textHexToInt(std::string text, unsigned long long &value);
bool textToInt(std::string text, int &value);
bool textToReal(std::string text, double &value);

#endif // TEXTUTILS_H
