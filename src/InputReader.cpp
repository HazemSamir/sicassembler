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


/** @brief (return increament of location counter in case of memory directive)
  * memory directives :
  * byte : return number of bytes = (number of chars in case of C'..' or number of hex_digits/2 in case of X'..')
  * word : return 3
  * resb : return number of bytes in operand
  * resw : return number of words in operand * 3
  *
  * this function assumed to be called after required validation to both operation and operand feild so there is no validation goes here
  */
int InputReader::getIncrement() {
    if(autalities::tolow(operation) == "resb") {
        return autalities::toInteger(operand);
    } else if (autalities::tolow(operation) == "resw") {
        return 3 * autalities::toInteger(operand);
    } else if (autalities::tolow(operation) == "byte") {
        int len = operand.size() - 3;
        if(tolower(operand[0]) == 'x') {
            if(len % 2) {
                valid = false;
                addToErrorMessage("Odd number of hexadecimal digits");
            }
        }
        return (tolower(operand[0]) == 'c' ? len : len / 2);
    } else if (autalities::tolow(operation) == "word") {
        return 3;
    }
    return 0;
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
        return true;
    }
    label = "";
    valid = false;
    addToErrorMessage("wrong label operand field");
    return false;
}

/** @brief (validate operation field with regex)
  * match operation with operation regex and extract operation from string
  * if operation starts with + marks it as formate four
  * if does not match make operation field empty and generate error message
  */
bool InputReader::validateOperation() {
    smatch sm;
    cout << "validate1 " <<  operation << "\n";
    if (regex_match(operation, sm, OPERATION_REGEX)) {
        operation = sm[OPERATION_MATCH_INDEX];
        isFour = (sm[OPERATION_MATCH_INDEX - 1] == "+");
        cout << isFour << "\n";
        cout << "validate2 " <<  operation << "\n";
        return true;
    }
    operation = "";
    valid = false;
    addToErrorMessage("wrong format operation field");
    return false;
}


/** @brief (validate operation field with regex)
  * match operand with different operand regexes and extract operand from string
  * if does not match make operand field empty and generate error message
  */
bool InputReader::validateOperand() {
    if(autalities::tolow(operation) == "word"){
        autalities::removeTrailingSpaces(operand);
        return true;
    }
    smatch sm;
    regex r1("[xX]\'[a-fA-F0-9]+\'\\s*", regex_constants::ECMAScript);
    regex r2("[cC]\'(\\w|\\W)+\'\\s*", regex_constants::ECMAScript);
    if(regex_match(operand, r1) || regex_match(operand, r2)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if (regex_match(operand, sm, OPERAND_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if (regex_match(operand, sm, IMMEDIATE_INDIRECT_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if (regex_match(operand, sm, TWO_OPERANDS_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if (regex_match(operand, sm, LITERAL_CHAR_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if(regex_match(operand, sm, LITERAL_HEX_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if(regex_match(operand, sm, INDEXING_REGEX)) {
        autalities::removeTrailingSpaces(operand);
        return true;
    } else if(regex_match(operand , sm, IS_HEX_REGEX)){
        autalities::removeTrailingSpaces(operand);
        return true;
    }
    operand = "";
    valid = false;
    addToErrorMessage("wrong format operand field");
    //cout << operand << "\n";
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

vector<OperandValidator::Operand> InputReader::getArgs() {
    return args;
}

