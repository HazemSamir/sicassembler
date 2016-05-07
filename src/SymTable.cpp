#include "SymTable.h"

/** @brief (empty constructor)
  */
SymTable::SymTable() {
    registers["a"] = "0";
    registers["x"] = "1";
    registers["l"] = "2";
    registers["b"] = "3";
    registers["s"] = "4";
    registers["t"] = "5";
    registers["f"] = "6";
    registers["pc"] = "8";
    registers["sw"] = "9";
}

/** @brief (return location counter of the given lable)
  */
string SymTable::getLocator(string label) {
    return registers[label];
}

/** @brief (insert label and its location counter)
  */
void SymTable::insert(string label, string locator) {
    symTab[label] = locator;
}

/** @brief (return true if it contains the given label)
  */
bool SymTable::hasLabel(string label) {
    return symTab.find(label) != symTab.end();
}

string SymTable::getRegister(string r) {
    return registers[r];
}
