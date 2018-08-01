#include "patricia_trie.hh"

int PatriciaTrie::getValue() const
{
    return _value;
}

void PatriciaTrie::setValue(int value)
{
    _value = value;
}