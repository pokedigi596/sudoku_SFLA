#include "sudoku_board.h"
#include <queue>
#include <ctime>
#include <algorithm>
#include <vector>
#include <list>
#include <random>

using namespace std;

class Solver
{
    public:
    Solver();
    bool replace_function(string better_puzzle, int replace_size, Board* board, list<int> mylist);
    bool backtrack(int index, Board board);
    void constrain_propagation(Board& board);
    void random_solution(Board& board);
    bool Shuffled_Frog_Leaping_Algorithm(int memeplex, int n_frogs, Board* board, clock_t start);
    string getanswer();
    private:
    string answer;
    string original;
    queue<int> randnum;
};