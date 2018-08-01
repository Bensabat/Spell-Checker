#pragma once

#include <iostream>

using namespace std;

class PatriciaTrie
{
    public:
        int getValue() const;
        void setValue(int value);

    private:
        int _value;
};