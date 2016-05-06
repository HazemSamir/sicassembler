#include "FreeFormatReader.h"
#include "Includes.h"
#include "OpTable.h"
#include "DirectivseTable.h"
bool FreeFormatReader::hasNextLine() {
    string line;
    bool isTrue = getline(in, line);
    initVariables();
    currentLine = line;
    if(isTrue) {
        if(line[0] == '.') {
            isComment = true;
            return isTrue;
        } else {
            parse(line);
        }
    }
    return isTrue;
}
void FreeFormatReader::parse(string &line){
// split string with spaces
            smatch sm ;
            string literal = "";
            regex r1("(=)?[Cc]\'[ \\w\\W]+\'",regex_constants::ECMAScript);
            if(regex_search(line,sm,r1)){
                literal = sm[0];
            }
            string withoutSpaceLiteral = "";
            stringstream kf(literal);
            string s;
            while(kf >> s){
                withoutSpaceLiteral += s;
            }
            stringstream ss(line);
            vector<string> vStrings;
            while(ss >> line) {
                if(line[0] == '.') break;
                if(line.size() >= 2){
                    if(tolower(line[0]) == 'c' && line[1] == '\'' && literal != ""){
                        vStrings.push_back(literal);
                        cout << literal << "\n";
                        s = line;
                        while(ss>>line){
                            s += line;
                            if(s == withoutSpaceLiteral){
                                break;
                            }
                        }
                        continue;
                    }
                }
                else if(line.size() >= 3){
                    if(line[0] == '=' && tolower(line[1]) == 'c' && line[2] == '\'' && literal != ""){
                        vStrings.push_back(literal);
                        cout << literal << "\n";
                        s = line;
                        while(ss>>line){
                            s += line;
                            if(s == withoutSpaceLiteral){
                                break;
                            }
                        }
                        continue;
                    }
                }
                vStrings.push_back(line);
            }
            // if line has more than three fields
            if(vStrings.size() > 3) {
                addToErrorMessage("Line is too long");
                valid = false;
            } else if(vStrings.size() == 3) { // label operation operand
                label = vStrings[0];
                operation = vStrings[1];
                operand = vStrings[2];
                validateLabel();
                validateOperation();
                validateOperand();
            } else if(vStrings.size() == 2) { //operation operand
                OpTable *opTable = new OpTable();
                DirectivseTable *dir = new DirectivseTable();
                string first = vStrings[0];
                string second = vStrings[1];
                if(opTable->hasOperation(autalities::tolow(first)) || first[0] == '+') {
                    operation = first;
                    operand = second;
                    validateOperation();
                    validateOperand();
                } else if(dir->contains(autalities::tolow(first))) {
                    operation = first;
                    operand = second;
                    validateOperand();
                } else {
                    label = first;
                    validateLabel();
                    operation = second;
                    validateOperation();
                }
            } else if(vStrings.size() == 1) {
                operation = vStrings[0];
                validateOperation();
            } else {
                isComment = true;
            }
}

