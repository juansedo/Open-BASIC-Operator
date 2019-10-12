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

    int hashFunction(string str) {
        int hash = 7;
        for (int i = 0; i < str.size(); i++) {
            hash = hash*31 + str.at(i);
        }
        return hash % size;
    }
public:
    Variables(int size = 100) {
        this->size = size;
        values = new float[size];
    }

    void put(string k, float v) {
        values[hashFunction(k)] = v;
        keys.push_back(k);
    }
    
    float get(string k) {
        for (auto i = keys.begin(); i != keys.end(); i++) {
            if(k.compare(*i)) {
                return values[hashFunction(k)];
            }
        }
        throw "Error: key does not exist";
    }

};
#endif
