#ifndef LITERALPOOL_H
#define LITERALPOOL_H
#include "Includes.h"

class LiteralPool {
public:
    LiteralPool();
    bool contains(string name);
    void insert(string name);
protected:
private:
    unordered_map<string, string> pool;
};

#endif // LITERALPOOL_H
