#include "InputReader.h"

/** @brief (parse givien file)
  * constractor
  */
InputReader::InputReader(string fileName) {
    //dtor
    in.open(fileName);
}

/** @brief (return true if this line a comment)
  * comment starts with '.' char
  */
bool InputReader::isCommentLine() {
    return isComment;
}

/** @brief (return operand field)
  */
string InputReader::getOperand() {
    return operand;
}

/** @brief (return operation field)
  */
string InputReader::getOperation() {
    return autalities::tolow(operation);
}

/** @brief (return label field)
  */
string InputReader::getLabel() {
    return autalities::tolow(label);
}

vector<OperandValidator::Operand> InputReader::getArgs() {
    return args;
}

/** @brief (return true if line contains no errors)
  */
bool InputReader::isValid() {
    return valid;
}

/** @brief (return error messages generated during parsing)
  */
string InputReader::getErrorMessage() {
    return errorMessage;
}

/** @brief (add given message to error message)
  */
void InputReader::addToErrorMessage(string msg) {
    errorMessage += msg + "\n";
}

/** @brief (return currentline that has been read)
  */
string InputReader::getLine() {
    return currentLine;
}

/** @brief (return true if operation is a format four (has +))
  */
bool InputReader::isFormatFour() {
    return isFour;
}


/** @brief (validate label field with regex)
  * match label with label regex and extract label from string
  * if does not match make label field empty and generate error message
  */
bool InputReader::validateLabel() {
    smatch sm;
    if (regex_match(label, sm, LABEL_REGEX)) {
        label = sm[LABEL_MATCH_INDEX];
        if(!regex_match(label, sm, OperandValidator::RIGESTER_REGEX)) {
            return true;
        } else {
            addToErrorMessage("label cannot be a register name");
        }
    }
    label = "";
    valid = false;
    addToErrorMessage("wrong label field");
    return false;
}

/** @brief (validate operation field with regex)
  * match operation with operation regex and extract operation from string
  * if operation starts with + marks it as formate four
  * if does not match make operation field empty and generate error message
  */
bool InputReader::validateOperation() {
    smatch sm;
    if (regex_match(operation, sm, OPERATION_REGEX)) {
        operation = sm[OPERATION_MATCH_INDEX];
        isFour = (sm[OPERATION_MATCH_INDEX - 1] == "+");
        return true;
    }
    operation = "";
    valid = false;
    addToErrorMessage("wrong operation field");
    return false;
}

/** @brief (initalize object string to be empty and boolean variables)
  */
void InputReader::initVariables() {
    currentLine = "";
    label = "";
    operation = "";
    operand = "";
    errorMessage = "";
    valid = true;
    isComment = false;
    isFour = false;
    args.clear();
}
