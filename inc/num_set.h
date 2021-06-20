#include <iostream>
#include <cmath>

using namespace std;

class NumSet
{
    public:
    NumSet();

    NumSet(int order);

    inline void addnum(int val) { set = set | (1 << (val - 1)); }
    inline void delnum(int val) { set = set & mask & ~(1 << (val - 1)); }
    string validnum();
    int size();
    void setzero();
    bool empty();
    bool fixed();
    int index();
    int count();
    bool contains(NumSet &other);
    NumSet operator + (NumSet& other);
    NumSet operator - (NumSet& other);
    NumSet operator ~ ();
    void operator ^= (NumSet& other);
    void operator += (NumSet& other);
    void operator <<= (int shift);
    NumSet Union(NumSet& other);
    NumSet Difference(NumSet& other);
    NumSet Complement();
    private:
    unsigned long long set = 0xFFFFFFFFFFFFFFFF;
    unsigned long long mask = 0xFFFFFFFFFFFFFFFF;
    int length = 0;
    inline int msb(unsigned long long x) const
    {
        double dx = (double)x;
		return ( *(unsigned long long*)(&dx) - 0x3FF0000000000000)>>52;
    }
#define MU0 0x5555555555555555
#define MU1 0x3333333333333333
#define MU2 0x0f0f0f0f0f0f0f0f
#define A 0x0101010101010101
    inline int popcnt(unsigned long long x) const
	{
		unsigned long long y = x - ((x>>1)&MU0);
		y = (y&MU1) + ( (y>>2)&MU1);
		y = (y + (y>>4))&MU2;
		return (A*y) >> 56;
	}
};