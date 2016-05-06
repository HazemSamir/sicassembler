#include "IntermediateReader.h"



bool IntermediateReader::hasNextLine() {
    string line;
    bool isTrue = getline(in, line);
    initVariables();
    currentLine = line;
    if(isTrue) {
        stringstream ss(line);
        string tmp;
        ss >> tmp ;
        ss >> line;
        if(line[0] == '.') {
            isComment = true;
            return isTrue;
        } else {
            ss >> locator;
            getline(ss, line);
            parse(line);
        }
    }
    return isTrue;
}
