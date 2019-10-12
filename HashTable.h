#ifndef HASH_TABLE
#define HASH_TABLE
#include <iostream>
#include <cmath>

using namespace std;

class Variables {
private:
    //string key;
    float* values;
    int size;

    int hashFunction(string str) {
        int sum = 0;
        for(int i = 0; i < sizeof(str)/sizeof(string); i++) {
            sum += ((int)str.at(i))*i + pow(10,i);
        }
        return sum % size;
    }
public:
    Variables(int size = 100) {
        this->size = size;
        values = new float[size];
    }

    void put(string k, float v) {
        values[hashFunction(k)] = v;
    }
    
    float get(string k) {
        return values[hashFunction(k)];
    }
};
#endif
