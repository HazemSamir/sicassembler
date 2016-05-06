#ifndef ASSEMBLERUTALITIES_H
#define ASSEMBLERUTALITIES_H

#ifndef INCLUDES_H

#include "Includes.h"

#endif // INCLUDES_H

using namespace std;

namespace autalities {

    string tolow(string s);

    string toUp(string s);

    void removeTrailingSpaces(string &s);

    string removeLeadingSpaces(string &s);

    void dos2unix(string &s);

    int toInteger(const string &txt);

    int hexToInteger(const string &txt);

    int hexToInteger(const char c);

    char toHexChar(int d);

    string toByte(string decimal);

    string toByte(int decimal);

    string toWord(string decimal);

    string toWord(int decimal);

    string toHex(int number);

    int binToInteger(string a);

    int subtractHex(string a, string b);
}
#endif // ASSEMBLERUTALITIES_H
