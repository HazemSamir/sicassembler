#include "AssemblerUtalities.h"

/**
 * namespace contains sic assembeler utalities functions
 */

namespace autalities {


/**
 * @param s
 * @brief (convert given string to lowercase)
 * @return string converted to lowercase
 */
string tolow(string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

/**
 * @param s
 * @brief (convert given string to uppercase)
 * @return string converted to uppercase
 */
string toUp(string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

string removeLeadingSpaces(string &s) {
    int ls = 0;
    for(; ls < s.size(); ++ls) {
        if (s[ls] != ' ')
            break;
    }
    return s.substr(ls);
}

/**
 * @param &s
 *          refernce to string
 * @brief (remove trialing spaces from end of givien string)
 */

void removeTrailingSpaces(string &s) {
    while (s.back() == ' ') {
        s.pop_back();
    }
}

/**
 * @param &s
 *          refernce to string
 * @brief (remove \r character at end of string if exists)
 *
 * if string is read from windows file the end of line char will be \r\n
 * and if read in linux it will read \r char which may cause unexpected behavior
 * so we remove it
 */
void dos2unix(string &s) {
    if (s.back() == '\r') {
        s.pop_back();
    }
}
/**
 * @param txt
 *            string of digit characters
 * @return int converted to number
 * @brief (convert given string to decimal integer)
 */

int toInteger(const string &txt) {
    int x = 0;
    for (int i = 0; i < txt.size(); i++) {
        x = x * 10 + txt[i] - '0';
    }
    return x;
}

/**
 * @param c
 *          hex char
 * @return int converted to decimal number
 * @brief (convert given hex char to decimal integer)
 */

int hexToInteger(const char c) {
    int digit = c - '0';
    return digit + (digit > 9 ? (10 + '0' - 'a') : 0);
}

/**
 * @param txt
 *          string hex chars
 * @return int converted to decimal number
 * @brief (convert given hex string to decimal integer)
 */

int hexToInteger(const string &txt) {
    int x = 0;
    int base = 16;
    for (int i = 0; i < txt.size(); i++) {
        x = x * base + hexToInteger(txt[i]);
    }
    return x;
}

/**
 * @param d
 *          int between 0 to 15
 * @return hex char
 * @brief (convert given int to char of hex value)
 */

char toHexChar(int d) {
    return (d > 9 ? ('a' - 10) : '0') + d;
}

/**
 * @param d
 * @return hex string
 * @brief (convert given int to string of hex chars with leading zeros)
 */

string toHex(int number) {
    string ans = "";
    while (number != 0) {
        ans += toHexChar(number % 16);
        number /= 16;
    }
    reverse(ans.begin(), ans.end());
    while (ans.size() < 4) {
        ans.insert(0, "0");
    }
    return ans;
}

}
