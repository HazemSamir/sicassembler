#ifndef ASSEMBLERUTALITIES_H
#define ASSEMBLERUTALITIES_H

#ifndef BITS_H
#include <bits/stdc++.h>
#endif // BITS_H

using namespace std;

namespace autalities {

    string tolow(string s);
    string toUp(string s);
    void removeTrailingSpaces(string &s);
    void dos2unix(string &s);

    int toInteger(const string &txt);
    int hexToInteger(const string &txt);
    int hexToInteger(const char c);
    char toHexChar(int d);
    string toHex(int number);
    bool isHex(const string &txt);
    bool checkLocator(string &txt);
}
#endif // ASSEMBLERUTALITIES_H
