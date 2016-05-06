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


class PassTwo {
public:
    PassTwo(string fileName);

    void pass();

private:
    InputReader *input;
    OpTable *opTab;
    SymTable *symTab;
    string startingAdress = "000000";
    string locator = "000000";
    string outputFile;
    ofstream outStream;
    DirectivseTable *dirTab;
    int errorCounter = 0;
    string base = "";

    void handelStart(vector<OperandValidator::Operand> args, string &msg);

    void handelOperation(vector<OperandValidator::Operand> args, string &msg, string &operation);

    void handelWord(vector<OperandValidator::Operand> args, string &msg);

    void handelByte(vector<OperandValidator::Operand> args, string &msg);

    void handelRes(vector<OperandValidator::Operand> args, string &msg, string &operation);

    void addToMessage(string &msg, string toBeAdded);

    void addErrorMessage(string &msg, string toBeAdded);

    void addWarningMessage(string &msg, string toBeAdded);

    void printSymTable();

    string addToLocator(string number, int delta);

    void appendToFile(string line);
};


#endif //ASSEMBLER_PASSTWO_H
