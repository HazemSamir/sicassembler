#ifndef INPUTREADER_H
#define INPUTREADER_H
#include "Includes.h"

#ifndef REGEX_H
#include <regex>
#endif // REGEX_H

#ifndef ASSEMBLERUTALITIES_H
#include <AssemblerUtalities.h>
#endif // ASSEMBLERUTALITIES_H

const string LABEL_REGEX_STR = "([a-zA-Z][a-zA-Z0-9]*)?\\s*";
const regex LABEL_REGEX(LABEL_REGEX_STR, regex_constants::ECMAScript);
const int LABEL_MATCH_INDEX = 1;

const string OPERATION_REGEX_STR = "(\\+)?([a-zA-Z]+)\\s*";
const regex OPERATION_REGEX(OPERATION_REGEX_STR, regex_constants::ECMAScript);
const int OPERATION_MATCH_INDEX = 2;

const string TWO_OPERANDS_STR = "([AaSsTtLlxXBb],[AaSsTtLlxXBb])\\s*";
const regex TWO_OPERANDS_REGEX(TWO_OPERANDS_STR, regex_constants::ECMAScript);

const string INDEXING_STR = "(#)?([a-zA-Z][a-zA-Z0-9]*,[Xx])\\s*";
const regex INDEXING_REGEX(INDEXING_STR, regex_constants::ECMAScript);

const string OPERAND_REGEX_STR = "(([a-zA-Z0-9]+)|(\\*([\\+-][0-9]+)?)|(-)[0-9]+)\\s*"; // check for spaces
const regex OPERAND_REGEX(OPERAND_REGEX_STR, regex_constants::ECMAScript);
const int OPERAND_MATCH_INDEX = 1;

const string LITERAL_CHAR_REGEX_STR = "(=[Cc]\'[\\w\\W ]+\')\\s*";
const regex LITERAL_CHAR_REGEX(LITERAL_CHAR_REGEX_STR, regex_constants::ECMAScript);
const int LITERAL_CHAR_MATCH_INDEX = 1;

const string LITERAL_HEX_REGEX_STR = "(=[Xx]\'([a-fA-F0-9]+)\')\\s*";
const regex LITERAL_HEX_REGEX(LITERAL_HEX_REGEX_STR, regex_constants::ECMAScript);
const int LITERAL_HEX_MATCH_INDEX = 1;

const string IMMEDIATE_INDIRECT_REGEX_STR =
    "([@#](([a-zA-Z][a-zA-Z0-9]*)|[0-9]+|(\\*([\\+-][0-9]+)?)))\\s*"; //check for -ve values
const regex IMMEDIATE_INDIRECT_REGEX(IMMEDIATE_INDIRECT_REGEX_STR, regex_constants::ECMAScript);
const int IMMEDIATE_MATCH_INDEX = 1;

const string IS_HEX = "(([@#])?(0)[0-9a-fA-F]*)\\s*";
const regex IS_HEX_REGEX(IS_HEX,regex_constants::ECMAScript);
class InputReader {

public:
    InputReader(string fileName);
    //virtual ~InputReader();
    // Read a line return if there is more lines in the file
    virtual bool hasNextLine() = 0;
    // return empty string if there is not
    string getLabel();
    // return empty string if there is not
    string getOperation();
    // return empty string if there is not
    string getOperand();
    // return true if line is a Comment
    bool isCommentLine();
    // return if this instruction is a format 4 or not
    bool isFormatFour();
    // return the length to increment the location counter if is word or byte
    int getIncrement();
    //return the full current line
    string getLine();

    bool isValid();

    string getErrorMessage();

protected:
    bool validateLabel();
    bool validateOperation();
    bool validateOperand();

    void initVariables();
    void addToErrorMessage(string msg);

    ifstream in;
    string label, operand, operation;
    bool isComment;
    bool isFour;
    bool valid = true;
    string currentLine;
    string errorMessage;
};

#endif // INPUTREADER_H
