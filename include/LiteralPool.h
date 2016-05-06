//
// Created by Tarek on 5/6/2016.
//

#ifndef ASSEMBLER_LITERALPOOL_H
#define ASSEMBLER_LITERALPOOL_H

#include "Includes.h"

class LiteralPool {
public:
    void insert(string literal, string locator);

    void insert(string literal);

    string getLocator(string literal);

    bool hasLiteral(string literal);

    // @return the size of the current pool
    int getIncrement();

    map<string, string> getLiteralPool() {
        return literalPool;
    }

private:
    map<string, string> literalPool;
};


#endif //ASSEMBLER_LITERALPOOL_H
