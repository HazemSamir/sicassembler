//
// Created by Tarek on 5/6/2016.
//

#include "ObjectWriter.h"

ObjectWriter::ObjectWriter(string fileName) {

}

void ObjectWriter::writeHeader(string start, string programName, string programLength) {

}

void ObjectWriter::writeTextRecord(string opCode, string flags, string address) {

}

void ObjectWriter::writeTextRecord(string start, string opCode, string flags, string address) {
    startNewRecord(start);
    writeTextRecord(opCode, flags, address);
}

void ObjectWriter::writeTextRecord(string start, string filed) {
    startNewRecord(start);
    writeTextRecord(opCode, filed);
}

void ObjectWriter::writeEnd(string start) {

}

void ObjectWriter::writeTextRecord(string field) {

}

void ObjectWriter::startNewRecord(string start) {

}
