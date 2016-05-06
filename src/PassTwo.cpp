//
// Created by Tarek on 5/6/2016.
//

#include "PassTwo.h"

PassTwo::PassTwo(string fileName) {
    input = new IntermediateReader(fileName);
    opTab = new OpTable();
    symTab = new SymTable();
    dirTab = new DirectivseTable();
    this->outputFile = outputFile;
    outStream.open(outputFile, ios_base::out);
}

void PassTwo::pass() {

}

void PassTwo::handelStart(vector<OperandValidator::Operand> args, string &msg) {

}

void PassTwo::handelOperation(vector<OperandValidator::Operand> args, string &msg, string &operation) {

}

void PassTwo::handelByte(vector<OperandValidator::Operand> args, string &msg) {

}

void PassTwo::addToMessage(string &msg, string toBeAdded) {

}

void PassTwo::addWarningMessage(string &msg, string toBeAdded) {

}

void PassTwo::printSymTable() {

}

string PassTwo::addToLocator(string number, int delta) {
    return std::basic_string<char, char_traits<char>, allocator<char>>();
}

void PassTwo::appendToFile(string line) {

}

void PassTwo::addErrorMessage(string &msg, string toBeAdded) {

}

void PassTwo::handelRes(vector<OperandValidator::Operand> args, string &msg, string &operation) {

}

void PassTwo::handelWord(vector<OperandValidator::Operand> args, string &msg) {

}





















