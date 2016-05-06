//
// Created by Tarek on 5/6/2016.
//

#ifndef ASSEMBLER_OBJECTWRITER_H
#define ASSEMBLER_OBJECTWRITER_H

#include "Includes.h"

class ObjectWriter {
public:

    void writeHeader(string start, string programName, string programLength);

    /**
     * @brief: append to the current text record
     * @param : opCode -> hex string from the opTable
     * @param: flags: binary string containing all the instruction flags such i, n, x, pc, b, e
     * @param: address: displacement , immediate value or absolute address
    */
    void writeTextRecord(string opCode, string flags, string address);

    /**
     * @brief: start new text record starting from the start parameter
     * @param: start hex string indicating the starting value
     * @param : opCode -> hex string from the opTable
     * @param: flags: binary string containing all the instruction flags such i, n, x, pc, b, e
     * @param: address: displacement , immediate value or absolute address
    */

    void writeTextRecord(string start, string opCode, string flags, string address);

    /**
     * @brief: start new text record starting from the start parameter
     * @param: start hex string indicating the starting value
     * @param: field : hex object to be writen in memory ex: 'test string' but convert it first to hex
    */

    void writeTextRecord(string start, string filed);

    /**
     * @brief: append to the text record
     * @param: field : hex object to be writen in memory ex: 'test string' but convert it first to hex
    */

    void writeTextRecord(string field);

    /**
     * @brief: append to the text record
     * @param: field : hex object to be writen in memory ex: 'test string' but convert it first to hex
    */

    void writeEnd(string start);
};


#endif //ASSEMBLER_OBJECTWRITER_H
