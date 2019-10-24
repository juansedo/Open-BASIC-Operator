#pragma once

#ifndef HASH_TABLE
#define HASH_TABLE
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Variables {
private:
    vector<string> keys;
    float* values;
    int size;
    int hashFunction(string str);
public:
    Variables(int size = 100);
    void put(string k, float v);
    float get(string k);
};
#endif
