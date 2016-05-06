#include "OpTable.h"


/** @brief (return number of operands this operation takes)
  * 0, 1 or 2 operands
  */
int OpTable::getNumberOfOperands(string operation) {
    return opTab[operation].numOfOperation;
}

/** @brief (return opject code of given operation)
  */
string OpTable::getOpcode(string operation) {
    return opTab[operation].opCode;
}

/** @brief (get supported format of givien instruction)
  * 2 or 3
  */
int OpTable::getFormat(string operation) {
    return opTab[operation].format;
}

/** @brief (true if contains this operation)
  */
bool OpTable::hasOperation(string operation) {
    return opTab.find(operation) != opTab.end();
}

/** @brief (initialize table from the given file)
  */
OpTable::OpTable(string fileName) {
    ifstream in;
    in.open(fileName);
    string s;
    while(getline(in, s)) {
        stringstream ss(s);
        string Operation;
        int numberofoper;
        string opcod;
        int format;
        Instruction ins;
        ss >> Operation;
        ss >> numberofoper;
        ss >> format ;
        ss >> opcod ;
        ins.format = format;
        ins.numOfOperation = numberofoper;
        ins.opCode = opcod;
        opTab[Operation] = ins;
    }
    in.close();
}

