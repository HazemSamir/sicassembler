#ifndef PASSONE_H
#define PASSONE_H
#include "Includes.h"
#include "InputReader.h"
#include "FixedFormatReader.h"
#include "OpTable.h"
#include "SymTable.h"
#include "DirectivseTable.h"

#ifndef ASSEMBLERUTALITIES_H
#include <AssemblerUtalities.h>
#endif // ASSEMBLERUTALITIES_H

class PassOne {
public:
    PassOne(string fileName, string outputFile);
    PassOne(InputReader *reader, string outputFile);
    //virtual ~PassOne();
    void pass();
    SymTable *getSymTable();
    string getProgramLength();

private:
    InputReader *input;
    OpTable *opTab;
    SymTable *symTab;
    string startingAdress = "000000";
    string locator = "000000";
    string outputFile;
    ofstream outStream;
    DirectivseTable *dirTab;

    string addToLocator(string number, int delta);
    void appendToFile(string line);
};

#endif // PASSONE_H
