#include "OperandValidator.h"

namespace OperandValidator {

bool Operand::ofType(char c) {
    if(c == OperandTypeGroup::NUMBER) {
        return isNumber() && isPlain();
    } else if (c == OperandTypeGroup::HEX) {
        return isHex() && isPlain();
    } else if (c == OperandTypeGroup::LITERAL) {
        return isLiteral();
    } else if (c == OperandTypeGroup::MEMORY) {
        return isMemory();
    } else if (c == OperandTypeGroup::POSNUMBER) {
        return isPosNumber() && isPlain();
    } else if (c == OperandTypeGroup::REGESTER) {
        return type == OperandType::REGESTER;
    }
    return false;
}

bool Operand::isPlain() {
    return !(isImmediate || isIndexed || isInDirect);
}


bool Operand::isMemory() {
    return isPosNumber() || (isNumber() && isImmediate)
           || (type == OperandType::LABEL) || isLiteral()
           || (type == OperandType::EXPRESION) || isHex();
}

bool Operand::isLiteral() {
    return (type == OperandType::CLITERAL || type == OperandType::XLITERAL);
}

bool Operand::isNumber() {
    return (type == OperandType::NUMBER);
}

bool Operand::isPosNumber() {
    return (isNumber() && operand[0] != '-');
}

bool Operand::isHex() {
    return (type == OperandType::HEX || isPosNumber());
}

vector<string> splitAtComma(string field) {
    vector<string> ret;
    if(field.empty())
        return ret;
    bool speratedWithComma = regex_match(field, COMMA_REGEX);
    if(regex_match(field, CBYTES_REGEX) || regex_match(field, CBYTES_REGEX) || !speratedWithComma) {
        ret.push_back(field);
    } else if (speratedWithComma) {
        replace(field.begin(), field.end(), ',', ' ');
        stringstream ss(field);
        string tmp;
        while(ss >> tmp) {
            ret.push_back(tmp);
        }
    }
    return ret;
}


string Operand::stringType() {
    return "";
}

string Operand::toHex() {
    string ret = "";
    if (isHex() || type == OperandType::XBYTES || type == OperandType::XLITERAL) {
        return operand;
    } else if (type == OperandType::CBYTES || type == OperandType::CLITERAL) {
        for(char c : operand) {
            ret += autalities::intToByte((int) c);
        }
    } else if (isNumber()) {
        return autalities::intToWord(operand);
    }
    return ret;
}

/** @brief (evaluate expression and return its hex value and type (absolute or realocatble))
  * @return
  *        Sympol object if there is an error then return empty string
  */

Sympol evaluateExpression(Operand expression, string locator, SymTable *symTab) {
    smatch sm;
    Sympol symp;
    if(regex_match(expression.operand, sm, EXPERSION_REGEX)) {
        vector<string> terms;
    }
    return symp;
}

vector<Operand> getOperands(string field) {
    return getOperands(splitAtComma(field));
}

vector<Operand> getOperands(vector<string> args) {
    vector<Operand> operandList;
    for(string arg : args) {
        Operand tmp;
        tmp.operand = autalities::tolow(arg);
        smatch sm;
        if (regex_match(arg, RIGESTER_REGEX)) {
            tmp.type = OperandType::REGESTER;
        } else if(regex_match(arg, sm, XBYTES_REGEX)) {
            tmp.type = OperandType::XBYTES;
            tmp.operand = autalities::tolow(sm[1]);
        } else if(regex_match(arg, sm, CBYTES_REGEX)) {
            tmp.type = OperandType::CBYTES;
            tmp.operand = sm[1];
        } else if(regex_match(arg, sm, XLITERAL_REGEX)) {
            tmp.type = OperandType::XLITERAL;
            tmp.operand = autalities::tolow(sm[1]);
        } else if(regex_match(arg, sm, CLITERAL_REGEX)) {
            tmp.type = OperandType::CLITERAL;
            tmp.operand = sm[1];
        } else if(regex_match(arg, sm, LABEL_REGEX)) {
            tmp.type = OperandType::LABEL;
            tmp.operand = autalities::tolow(sm[2]);
            tmp.isImmediate = (sm[1] == "#");
            tmp.isInDirect = (sm[1] == "@");
        } else if(regex_match(arg, sm, NUM_REGEX)) {
            tmp.type = OperandType::NUMBER;
            tmp.operand = sm[2];
            tmp.isImmediate = (sm[1] == "#");
            tmp.isInDirect = (sm[1] == "@");
        } else if(regex_match(arg, HEX_REGEX)) {
            tmp.type = OperandType::HEX;
        } else if(regex_match(arg, EXPERSION_REGEX)) {
            tmp.type = OperandType::EXPRESION;
            tmp.operand = autalities::tolow(sm[0]);
        }
        if(tmp.type == OperandType::REGESTER
                && tmp.operand == "x"
                && !operandList.empty() && operandList.back().ofType(OperandTypeGroup::MEMORY)) {

            operandList.back().isIndexed = true;
        } else {
            operandList.push_back(tmp);
        }
    }
    return operandList;
}

}
