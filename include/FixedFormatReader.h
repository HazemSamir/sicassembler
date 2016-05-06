#ifndef FIXEDFORMATREADER_H
#define FIXEDFORMATREADER_H

#include <InputReader.h>

class FixedFormatReader : public InputReader {
public:
    FixedFormatReader(string fileName): InputReader(fileName) {};
    bool hasNextLine() override;
private:
    bool trailSpaces(string & s, int n);
};

#endif // FIXEDFORMATREADER_H
