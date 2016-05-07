//
// Created by Tarek on 5/6/2016.
//

#include "PassTwo.h"

const int MAX_PC = 2047, MIN_PC = -2048, MAX_BASE = 4096, MAX_MEMORY = (1 << 20);

PassTwo::PassTwo(string fileName, SymTable *symtabel, LiteralPool *literalPool, string length) {
    intermediateFile = fileName;
    input = new IntermediateReader(intermediateFile);
    opTab = new OpTable();
    symTab = symtabel;
    dirTab = new DirectivseTable();
    opwriter = new ObjectWriter(objectFile);
    this -> length = length;
}

void PassTwo::pass() {
    string msg = "";

    /// loop till end statement or no line remains
    while (input->hasNextLine()) {
        if (!input->isCommentLine()) { // not a comment line
            string operation = input->getOperation();
            string label = input->getLabel();
            string operand = input->getOperand();
            auto args = input->getArgs(); // operand subfields
            locator = input->getLocator();

            if (operation == "start") {
                handelStart(args, label, msg);
            } else if (opTab->hasOperation(operation)) { // valid operation
                handelOperation(args, msg, operation, input->isFormatFour());
            } else if (operation == "word") {
                handelWord(args, msg);
            } else if (operation == "byte") {
                handelByte(args, msg);
            } else if (operation == "resw") {
                handelResw(args, msg);
            } else if (operation == "resb") {
                handelResb(args, msg);
            } else if (operation == "base") {
                base = args[0].operand;
            } else if (operation == "nobase") {
                base = "";
            }
        }
        if (errorCounter > 0) {
            break;
        }
    }
    input->close();

    opwriter->writeEnd(startingAdress);

    ofstream outStream;
    outStream.open(intermediateFile, std::ios_base::app | std::ios_base::out);
    outStream << "\n************* \tpass 2 report *************\n\n";
    outStream << msg << "\n";
    outStream.close();
}

void PassTwo::handelStart(vector<OperandValidator::Operand> args, string label, string &msg) {
    startingAdress = locator = args[0].operand;

    if (label.length() > 6) {
        addErrorMessage(msg, "program name too long");
    }
    opwriter->writeHeader(locator, label, length);
}

void PassTwo::handelOperation(vector<OperandValidator::Operand> args, string &msg, string &operation,
                              bool isFormatFour) {
    string opCode = opTab->getOpcode(operation);
    int numberOfArgs = opTab->getNumberOfOperands(operation);
    int format = isFormatFour ? 4 : opTab->getFormat(operation);
    string flags = "000000";
    if(format == 2) {
        string address = autalities::normalize(evaluateOperand(args[0], msg), 1);
        if(numberOfArgs == 2) {
            address += autalities::normalize(evaluateOperand(args[1], msg), 1);
        }
        address = autalities::normalize(address, 2);
        opwriter->writeTextRecord(opCode + address);
    } else {
        locator = addToLocator(locator, format);
        flags[0] = args[0].isInDirect ? '1' : '0';
        flags[1] = args[0].isImmediate ? '1' : '0';
        if (!args[0].isInDirect && !args[0].isImmediate) {
            flags[0] = flags[1] = '1';
        }
        flags[2] = args[0].isIndexed ? '1' : '0';
        flags[5] = isFormatFour ? '1' : '0';
        string address = evaluateOperand(args[0], msg);
        if (!args[0].isImmediate && format == 3) {
            int disp = autalities::subtractHex(address, locator);
            if (disp > MAX_PC || disp < MIN_PC) {
                if(base.empty()) {
                    addErrorMessage(msg, "displacement is out of bounds of pc relative - can not use base");
                    return;
                } else {
                    disp = autalities::subtractHex(address, base);
                    if (disp < 0 || disp > MAX_BASE) {
                        addErrorMessage(msg, "displacement is out of bounds for both pc and base");
                        return;
                    }
                }
                flags[3] = '1'; // base
            } else {
                flags[4] = '1'; // pc
            }
            address = autalities::intToHex(disp);
        } else if (format == 4 && autalities::hexToInteger(address) > MAX_MEMORY) {
            addErrorMessage(msg, "out of memory bounds");
        }
        address = autalities::normalize(address, format == 3 ? 3 : 5);
        opwriter->writeTextRecord(opCode, flags, address);
    }
}

void PassTwo::handelByte(vector<OperandValidator::Operand> args, string &msg) {
    opwriter->writeTextRecord(locator, args[0].toHex());
}

void PassTwo::handelResw(vector<OperandValidator::Operand> args, string &msg) {
    int arrSize = autalities::toInteger(args[0].operand) * 3;
    opwriter->startNewRecord(addToLocator(locator, arrSize));
}

void PassTwo::handelResb(vector<OperandValidator::Operand> args, string &msg) {
    int arrSize = autalities::toInteger(args[0].operand);
    opwriter->startNewRecord(addToLocator(locator, arrSize));
}

void PassTwo::handelWord(vector<OperandValidator::Operand> args, string &msg) {
    opwriter->startNewRecord(locator);
    for(auto arg : args) {
        opwriter->writeTextRecord(autalities::intToWord(arg.operand));
    }
    opwriter->startNewRecord(addToLocator(locator, args.size() * 3));
}

void PassTwo::addToMessage(string &msg, string toBeAdded) {
    msg += "****\t" + toBeAdded + "\n";
}

string PassTwo::addToLocator(string number, int delta) {
    int x = autalities::hexToInteger(number);
    return autalities::intToWord(x + delta); // of size 6
}

void PassTwo::addErrorMessage(string &msg, string toBeAdded) {
    errorCounter++;
    addToMessage(msg, "error: " + toBeAdded);
}

string PassTwo::evaluateOperand(OperandValidator::Operand &operand, string &msg) {
    if(operand.type == OperandValidator::OperandType::LABEL || operand.type == OperandValidator::OperandType::REGESTER) {
        if (symTab->hasLabel(operand.operand)) {
            return symTab->getLocator(operand.operand);
        } else {
            addErrorMessage(msg, "undefined sympol " + operand.operand + " before address " + locator);
            return "000000";
        }
    } else if (operand.isNumber()) {
        return autalities::intToWord(operand.operand);
    } else if (operand.isLiteral()) {
        return "00";
    }
    return "00";
}
