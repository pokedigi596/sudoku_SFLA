#include "../inc/num_set.h"

NumSet::NumSet()
{

}

NumSet::NumSet(int order)
{
    set = set >> (64 - order * order);
    mask = mask >> (64 - order * order);
    length = order * order;
}

int NumSet::size()
{
    return length;
}

string NumSet::validnum()
{
    unsigned long long temp = set;
    string pos_num = "";
    for (int i = 0; i < length; i++)
    {
        if (temp % 2 == 1) pos_num += ('0' + (i + 1));
        temp = temp >> 1;
    }
    return pos_num;
}

void NumSet::setzero()
{
    set = 0;
}

bool NumSet::empty()
{
    return (set == 0);
}

bool NumSet::fixed()
{
    return ((unsigned long long)1 << index() == set);
}

int NumSet::index()
{
    return msb(set);
}

int NumSet::count()
{
    return popcnt(set);
}

bool NumSet::contains(NumSet &other)
{
    return (set & other.set) != 0;
}

NumSet NumSet::operator + (NumSet& other)
{
    return Union(other);
}

NumSet NumSet::operator - (NumSet& other)
{
    return Difference(other);
}

NumSet NumSet::operator ~ ()
{
    return Complement();
}

void NumSet::operator ^= (NumSet& other)
{
    set &= other.set;
}

void NumSet::operator += (NumSet& other)
{
    set |= other.set;
}

void NumSet::operator <<= (int shift)
{
	set <<= shift;
}

NumSet NumSet::Union(NumSet& other)
{
    NumSet newset = NumSet(sqrt(length));
    newset.setzero();
    newset.set = set | other.set;
    return newset;
}

NumSet NumSet::Difference(NumSet& other)
{
    NumSet newset = NumSet(sqrt(length));
    newset.setzero();
    newset.set = mask & (set & ~other.set);
    return newset;
}

NumSet NumSet::Complement()
{
    NumSet newset = NumSet(sqrt(length));
    newset.setzero();
    newset.set = mask & (~set);
    return newset;
}