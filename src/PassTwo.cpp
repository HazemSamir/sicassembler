//
// Created by Tarek on 5/6/2016.
//

#include "PassTwo.h"

const int MAX_PC = 2047, MIN_PC = -2048, MAX_BASE = 4096, MAX_MEMORY = (1 << 20);

PassTwo::PassTwo(string fileName, SymTable *symtabel, LiteralPool *literalPool, string length) {
    input = new IntermediateReader(fileName);
    opTab = new OpTable();
    symTab = symtabel;
    dirTab = new DirectivseTable();
    opwriter = new ObjectWriter("op.txt");
    this->outputFile = outputFile;
    this -> length = length;
    outStream.open(outputFile, ios_base::out);
}

void PassTwo::pass() {
    string msg = "";
    bool started = false, noStart = true, noEnd = true;

    /// loop till end statement or no line remains
    while (input->hasNextLine()) {
        // lineNumber++;
        if (noEnd && !input->isCommentLine()) { // not a comment line
            /// handel start statement
            string operation = input->getOperation();
            string operand = input->getOperand();
            string label = input->getLabel();
            locator = input->getLocator();
            auto args = input->getArgs(); // operand subfields

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
            } else if (operation == "end") {
                noEnd = true;
                opwriter->writeEnd(startingAdress);
            }
        }
        // write to log file
        if (errorCounter > 0) {
            // exit
        }
    }
    // write msg to log file
}

void PassTwo::handelStart(vector<OperandValidator::Operand> args, string label, string &msg) {
    startingAdress = locator = args[0].operand;
    opwriter->writeHeader(locator, label, length);
}

void PassTwo::handelOperation(vector<OperandValidator::Operand> args, string &msg, string &operation,
                              bool isFormatFour) {
    string opCode = opTab->getOpcode(operation);
    int numberOfArgs = opTab->getNumberOfOperands(operation);
    int format = isFormatFour ? 4 : opTab->getFormat(operation);
    string flags = "000000";
    if(format == 2) {
        string address = evaluateOperand(args[0], msg);
        if(numberOfArgs == 2) {
            address += evaluateOperand(args[2], msg);
        }
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
                    addErrorMessage(msg, "");
                    return;
                } else {
                    disp = autalities::subtractHex(address, base);
                    if (disp < 0 || disp > MAX_BASE) {
                        addErrorMessage(msg, "");
                        return;
                    }
                }
                flags[3] = '1'; // base
            } else {
                flags[4] = '1'; // pc
            }
            address = autalities::toHex(disp);
        } else if (format == 4 && autalities::toInteger(address) > MAX_MEMORY) {
            addErrorMessage(msg, "out of memory bounds");
        }
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
        opwriter->writeTextRecord(autalities::toWord(arg.operand));
    }
    opwriter->startNewRecord(addToLocator(locator, args.size() * 3));
}


void PassTwo::addToMessage(string &msg, string toBeAdded) {
    msg += toBeAdded;
}

string PassTwo::addToLocator(string number, int delta) {
    return std::basic_string<char, char_traits<char>, allocator<char>>();
}

void PassTwo::addErrorMessage(string &msg, string toBeAdded) {
    errorCounter++;
    addToMessage(msg, "error: " + toBeAdded);
}

string PassTwo::evaluateOperand(OperandValidator::Operand &operand, string &msg) {
    if(operand.type == OperandValidator::OperandType::LABEL) {
        if (symTab->hasLabel(operand.operand)) {
            return symTab->getLocator(operand.operand);
        } else {
            addErrorMessage(msg, "undefined sympol");
        }
    } else if (operand.isNumber()) {
        return autalities::toWord(operand.operand);
    } else if (operand.isLiteral()) {
        /*if (symTab->hasLabel(operand.operand)) {
            return symTab->getLocator(operand.operand);
        } else {
            addErrorMessage(msg, "");
        }*/
    }
}
