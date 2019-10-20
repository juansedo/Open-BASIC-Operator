#include "HashTable.h"

int Variables::hashFunction(string str)
{
    int hash = 7;
    for (int i = 0; i < str.size(); i++)
    {
        hash = hash * 31 + str.at(i);
    }
    return hash % size;
}

Variables::Variables(int size = 100)
{
    this->size = size;
    values = new float[size];
}

void Variables::put(string k, float v)
{
    values[hashFunction(k)] = v;
    keys.push_back(k);
}

float Variables::get(string k)
{
    for (auto i = keys.begin(); i != keys.end(); i++)
    {
        if (k.compare(*i) == 0)
        {
            return values[hashFunction(k)];
        }
    }
    throw "Error: key does not exist";
}