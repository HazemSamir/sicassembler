#ifndef PASSTWO_H
#define PASSTWO_H
#include "Includes.h"
#include "SymTable.h"
#include "OpTable.h"
#include "IntermediateReader.h"
class PassTwo
{
    public:
        PassTwo();
        void pass();
    protected:
    private:
        void writeTextRecord(string start, string opCode);
        void writeTextRecord(string opCode);
        SymTable *symTab;
        OpTable *opTab;
        IntermediateReader *inReader;
        string fileName;
        void wordHandle();
        void byteHandle();
        void ORGHandle();
        void EQUHandle();
        string pc;
        string base;
        string generateOpCode(string operation, string address);
};

#endif // PASSTWO_H
