#include "SymTable.h"

/** @brief (empty constructor)
  */
SymTable::SymTable() {

//register names
    symTab["a"] = "0";
    symTab["x"] = "1";
    symTab["l"] = "2";
    symTab["b"] = "3";
    symTab["s"] = "4";
    symTab["t"] = "5";
    symTab["f"] = "6";
    symTab["pc"] = "8";//maybe no use
    symTab["sw"] = "9";//maybe no use
}

/** @brief (return location counter of the given lable)
  */
string SymTable::getLocator(string label) {
    return symTab[label];
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
