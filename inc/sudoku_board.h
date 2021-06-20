#include <iostream>
#include <cmath>
#include <set>
#include "num_set.h"

using namespace std;

class Board
{
    public:
    Board();
    ~Board();
    Board(string puzzle_string, int aa);
    void PrintPossibaleValue();
    void constrain_cell(int index);
    void set_cell(int index, NumSet set);
    int fitness();
    string getpuzzle();
    void setpuzzle(string answer);
    NumSet at(int index);
    void remove(int index, int val);
    void setfail(int num);
    void release_memory();
    private:
    NumSet* numset = nullptr;
    string puzzle;
    int size = 0;
    int invalid = 0;
    int aaa;
};