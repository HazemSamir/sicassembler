#ifndef INTERMEDIATEREADER_H
#define INTERMEDIATEREADER_H
#include "Includes.h"
#include "FreeFormatReader.h"
class IntermediateReader: FreeFormatReader
{
    public:
        IntermediateReader(string fileName): FreeFormatReader(fileName) {}
        string getLocator();
        bool hasNextLine();

    protected:
    private:
        string locator;
};

#endif // INTERMEDIATEREADER_H
