#include "PassOne.h"
#include "FreeFormatReader.h"
#include "FixedFormatReader.h"

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SymTable* PassOne::getSymTable() {

    return symTab;


}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void PassOne::pass() {

    int lineNumber = 1;
    string msg = "";
    int startRead = 0;
    while(input->hasNextLine() && input->isCommentLine()) {
        //maybe print the comments in the file
        outStream << lineNumber;
        outStream << "\t\t" ;
        outStream << input->getLine() ;
        outStream <<  "\n";
        lineNumber++;
    }
    string currentLine = input->getOperation();
    currentLine = autalities::tolow(currentLine);
    if(currentLine == "start") {
        locator = input->getOperand();
        startingAdress = locator;
        while(startingAdress.size() < 6)startingAdress = '0' + startingAdress;
        cout << locator << "\n";
        if(autalities::isHex(locator) && locator.size() <= 6){
            locator = startingAdress;
        }
        else{
            locator = "000000";
            msg += "\t\tinvalid relocatable address\n";
        }
    }
    startRead = 1;
    while(currentLine != "end") {
        if(input->isCommentLine()) {
            outStream << lineNumber;
            outStream << "\t" ;
            //outStream << locator;
            //outStream << "\t";
            outStream << input->getLine() ;
            outStream <<  "\n";
            lineNumber++;
        } else {
            string label = input->getLabel();
            label = autalities::tolow(label);
            //start label
            if(label != "") {
                if(symTab->hasLabel(label)) {
                    //set error flag duplicate symbol
                    msg = ("\t\t****Error:Symbol \'" + label + "\' already defined\n");
                } else {
                    symTab->insert(label, locator);
                }
            }
            //end label
            outStream << lineNumber;
            outStream << "\t" ;
            outStream << autalities::toUp(locator);
            outStream << "\t";
            outStream << input->getLine() ;
            outStream <<  "\n";
            lineNumber++;
            if(!autalities::checkLocator(locator)){
                msg += "\t\tlocator exceeds available memory\n";
                outStream << msg;
                outStream.close();
                return;
            }
            //start operation
            string operation = input->getOperation();
            operation = autalities::tolow(operation);
            if(operation != "") {
                if(opTab->hasOperation(operation)) {
                    int format = opTab->getFormat(operation);
                    if(format == 3 && input->isFormatFour())format = 4;
                    else if(input->isFormatFour()){
                        msg += "\t\tinvalid conversion to format 4\n";
                    }
                    locator = addToLocator(locator, format);
                    int numberOfOperand = opTab->getNumberOfOperands(operation);
                    string operand = input->getOperand() + " ";
                    if(numberOfOperand == 0) {  //RSUB
                        if(operand != " ") {
                            msg += "\t\twarning : rsub operand isn't empty\n";
                        }
                    } else if(numberOfOperand == 1) {
                        if(regex_match(operand, INDEXING_REGEX) || regex_match(operand, IMMEDIATE_INDIRECT_REGEX)
                                || regex_match(operand, OPERAND_REGEX) || regex_match(operand,IS_HEX_REGEX));
                        else {
                            msg += "\t\tinvalid operand\n";
                        }
                    } else {
                        if(!regex_match(operand, TWO_OPERANDS_REGEX)) {
                            msg += "\t\tinvalid register to register operand\n";
                        }
                    }
                } else if(operation == "word") {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    string operand = input->getOperand();
                    regex r("(#|@)?(-)?[0-9]+(,(-)?[0-9]+)*", regex_constants::ECMAScript);
                    regex r1("(#|@)?[A-Za-z][A-Za-z0-9]*(,[Xx])?",regex_constants::ECMAScript);
                    regex r2("(#|@)?((((-)?[0-9]+)|(0[0-9a-fA-F]*))((,(-)?[0-9]+)|(,0[0-9a-fA-F]*))*)",regex_constants::ECMAScript);
                    if(regex_match(operand, r) || regex_match(operand,r2)){
                        int comma = 0;
                        for(int i = 0 ; i < operand.size() ; i++){
                            if(operand[i] == ','){
                                comma++;
                            }
                        }
                        locator = addToLocator(locator, (comma+1)*3);
                    }
                    else if(regex_match(operand,r1))
                        locator = addToLocator(locator,3);
                    else msg += "\t\terror invalid word\n";
                } else if(operation == "resw") {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    string operand = input->getOperand();
                    regex r("[0-9]+", regex_constants::ECMAScript);
                    if(regex_match(operand, r)) {
                        int delta = input->getIncrement();
                        locator = addToLocator(locator, delta);
                    } else  msg += "\t\terror invalid resw value\n";
                } else if(operation == "resb") {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    string operand = input->getOperand();
                    regex r("[0-9]+", regex_constants::ECMAScript);
                    if(regex_match(operand, r)) {
                        int delta = input->getIncrement();
                        locator = addToLocator(locator, delta);
                    } else msg += "\t\terror invalid resb value\n";
                } else if(operation == "byte") {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    string operand = input->getOperand();
                    regex r1("[xX]\'[a-fA-F0-9]+\'", regex_constants::ECMAScript);
                    regex r2("[cC]\'[\\w\\W ]+\'", regex_constants::ECMAScript);
                    cout << operand << "\n";
                    if(regex_match(operand, r1) || regex_match(operand, r2)) {
                        int delta = input->getIncrement();
                        locator = addToLocator(locator, delta);
                    } else msg += "\t\t***error invalid byte string\n";

                } else if(dirTab->contains(operation) && dirTab->notSupported(operation)) {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    msg += "\t\t****warning not supported directive\n";
                } else if(dirTab->contains(operation)) {
                    if(input->isFormatFour()){
                        msg += "\t\tinvalid format 4 with directives\n";
                    }
                    if(autalities::tolow(operation) != "start"){           /// ??????
                        string operand = input->getOperand() + " ";
                        if(regex_match(operand, INDEXING_REGEX) || regex_match(operand, IMMEDIATE_INDIRECT_REGEX)
                                || regex_match(operand, OPERAND_REGEX) || regex_match(operand,IS_HEX_REGEX));
                        else {
                            msg += "\t\tinvalid relocatable address\n";
                        }
                    }
                    else if(autalities::tolow(operation) == "start"){
                        if(startRead > 1){
                            msg += "\t\tstart can't be written again\n";
                        }
                    }
                } else {
                    //set error flag
                    msg +=  "\t\t****invalid operation code\n";
                    //outStream << "\t\t****invalid operation code\n";
                }
            }
            //appendToFile(input.getLine());
            if(!input->isValid())msg += "\t\t" + input->getErrorMessage();
            if(msg != ""){
                msg = '*' + msg;
            }
            outStream << msg;
        }
        if(!input->hasNextLine()) {
            msg += "\t\tno end found\n";
            break;
        }
        currentLine = input->getOperation();
        currentLine = autalities::tolow(currentLine);
        msg = "";
        if(currentLine == "start"){
            startRead++;
        }
    }
    //appendToFile(input.getLine());
    if(msg != "")msg = '*' + msg;
    outStream << msg;
    outStream << lineNumber;
    outStream << "\t" ;
    outStream << autalities::toUp(locator);
    outStream << "\t";
    outStream << input->getLine() ;
    outStream <<  "\n";
    if(!autalities::checkLocator(locator)){
        msg += "*\t\tlocator exceeds available memory\n";
        outStream << msg;
        outStream.close();
        return;
    }
    outStream << "\t\t**********End of pass 1***********\n";

    ///Symbol table

    /**for(auto x : symTab->getSymtab()){
        string s = x.first;
        while(s.size() < 15){
            s += " ";
        }
        s += autalities::toUp(x.second);
        outStream << s << "\n";
    }**/
    outStream.close();
}


void PassOne::appendToFile(string line) {
    //write to file
    outStream << line + '\n';
}

string PassOne::addToLocator(string number, int delta) {
    int x = autalities::hexToInteger(number);
    cout << x << "\n";
    x += delta;
    cout << x << "\n";
    string temp = autalities::toHex(x);
    cout << temp << "\n";
    while(temp.size() < 6)temp = '0' + temp;
    return temp;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */

PassOne::PassOne(InputReader *reader, string outputFile) {
    input = reader;
    opTab = new OpTable();
    symTab = new SymTable();
    dirTab = new DirectivseTable();
    this->outputFile = outputFile;
    outStream.open(outputFile, ios_base::out);
}

PassOne::PassOne(string fileName, string outputFile) : PassOne::PassOne(new FreeFormatReader(fileName), outputFile) {}

string PassOne::getProgramLength(){
    return autalities::toHex(autalities::subtractHex(locator,startingAdress));
}
