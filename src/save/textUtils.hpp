#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <string>

using namespace std;

char ascii2char(int n);
string char2string(char c);
string intToHex(unsigned long long i, int width = -1);
string intToText(int i, int width = -1);
bool isNumeric(string number);
string realToText(double i, int width = -1);
bool textHexToInt(string text, unsigned long long &value);
bool textToInt(string text, int &value);
bool textToReal(string text, double &value);

#endif // TEXTUTILS_H
