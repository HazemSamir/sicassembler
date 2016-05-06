//
// Created by Tarek on 5/6/2016.
//

#ifndef ASSEMBLER_PASSTWO_H
#define ASSEMBLER_PASSTWO_H

#include "Includes.h"
#include "OpTable.h"
#include "DirectivseTable.h"
#include "SymTable.h"
#include "InputReader.h"
#include "IntermediateReader.h"
#include "LiteralPool.h"
#include "ObjectWriter.h"
#include "OperandValidator.h"
class PassTwo {
public:
    PassTwo(string fileName, SymTable *symtabel, LiteralPool *literalPool, string length);

    void pass();

private:
    IntermediateReader *input;
    OpTable *opTab;
    SymTable *symTab;
    ObjectWriter *opwriter;
    string startingAdress = "000000";
    string locator = "000000";
    string outputFile;
    string length;
    ofstream outStream;
    DirectivseTable *dirTab;
    int errorCounter = 0;
    string base = "";

    void handleStart(vector<OperandValidator::Operand> args, string label, string &msg);

    void handleOperation(vector<OperandValidator::Operand> args, string &msg, string &operation, bool isFormatFour);

    void handleWord(vector<OperandValidator::Operand> args, string &msg);

    void handleByte(vector<OperandValidator::Operand> args, string &msg);

    void handleResw(vector<OperandValidator::Operand> args, string &msg);

    void handleResb(vector<OperandValidator::Operand> args, string &msg);

    void addToMessage(string &msg, string toBeAdded);

    void addErrorMessage(string &msg, string toBeAdded);

    string addToLocator(string number, int delta);

    string evaluateOperand(OperandValidator::Operand &operand, string &msg);

};


#endif //ASSEMBLER_PASSTWO_H
