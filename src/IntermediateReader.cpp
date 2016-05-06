#include <IntermediateReader.h>

bool IntermediateReader::hasNextLine() {
    string line;
    bool isTrue;
    do {
        isTrue = getline(in, line);
        line = autalities::removeLeadingSpaces(line);
    } while(isTrue && line.empty());
    initVariables();
    currentLine = line;
    if(isTrue) {
        stringstream ss(line);
        string tmp;
        ss >> tmp;
        if(tmp[0] != '*') {
            ss >> locator;
            getline(ss, line);
            if(line[0] == '.') {
                isComment = true;
            } else {
                parse(line);
            }
        }
    }
    return isTrue;
}
