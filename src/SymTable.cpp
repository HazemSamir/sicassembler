#include "SymTable.h"

/** @brief (empty constructor)
  */
SymTable::SymTable() {}

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
