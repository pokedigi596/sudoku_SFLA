#include "../inc/sudoku_solver.h"

int run = 0;

void debug(string puzzle)
{
	int size = sqrt(puzzle.length());
	int order = sqrt(size);
	for (int i = 0; i < 3 * (size + order) + 1; i++) cout << '=';
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		printf("%c", '|');
		for (int j = 0; j < size; j++)
		{
			if (puzzle[i * size + j] != '.') printf("%3d", puzzle[i * size + j] - '0');
            else printf("%3c", puzzle[i * size + j]);
			if (j % order == order - 1) printf("%3c", '|');
		}
		cout << endl;
		if (i % order == order - 1)
		{
			for (int i = 0; i < 3 * (size + order) + 1; i++) cout << '=';
			cout << endl;
		}
	}
}

bool compare(Board a, Board b)
{
    return a.fitness() < b.fitness();
}

int RandomNum(queue<int>& myque)
{
    int num = myque.front();
    myque.pop();
    myque.push(rand());
    return num;
}

bool safenumber(int num, int index, string puzzle_string)
{
    int size = sqrt(puzzle_string.length());
    int start_point;
    // Row
    start_point = index / size;
    for (int i = 0; i < size; i++)
    {
        if (puzzle_string[start_point * size + i] - '0' == num) return false;
    }
    // Column
    start_point = index % size;
    for (int i = 0; i < size; i++)
    {
        if (puzzle_string[start_point + size * i] - '0' == num) return false;
    }
    // Box
    start_point = index / size / (int)pow(size, 0.5) * (int)pow(size, 0.5) * size + index % size / (int)pow(size, 0.5) * (int)pow(size, 0.5);
    for (int i = 0; i < pow(size, 0.5); i++)
    {
        for (int j = 0; j < pow(size, 0.5); j++)
        {
            if (puzzle_string[start_point + i * size + j] - '0' == num) return false;
        }
    }

    return true;
}

Solver::Solver()
{
    srand(time(NULL));    
    for (int i = 0; i < 1000; i++)
    {
        int num = rand();
        randnum.push(num);
    }
}

bool Solver::replace_function(string& better_puzzle, int replace_size, Board& board)
{
    bool success = false;
    for (int j = 0; j < original.length() / 20; j++)
    {
        int start_point = rand() % better_puzzle.length();
        string new_puzzle(better_puzzle.length(), '.');
        for (int k = 0; k < new_puzzle.length(); k++)
        {
            if (k < replace_size)
            {
                new_puzzle[(start_point + k) % new_puzzle.length()] = better_puzzle[(start_point + k) % new_puzzle.length()];
            }
            else
            {
                new_puzzle[(start_point + k) % new_puzzle.length()] = original[(start_point + k) % new_puzzle.length()];
            }
        }
        Board tmp = Board(new_puzzle);
        random_solution(tmp);

        if (tmp.fitness() < board.fitness())
        {
            success = true;
            board = tmp;
            tmp.release_memory();
            break;
        }
        else tmp.release_memory();
    }
    return success;
}

/*bool Solver::backtrack(int index, Board board)
{
    if (index == 0) answer = board.getpuzzle();
    if (index == board.getpuzzle().length()) return true;
    if (answer[index] == '.')
    {
        string grid = board.at(index);
        for (int i = 0; i < grid.length(); i++)
        {
            if (safenumber(grid[i] - '0', index, answer))
            {
                answer[index] = grid[i];
                bool solve = backtrack(index + 1, board);
                if (solve) return true;
                else answer[index] = '.';
            }
        }
        return false;
    }
    else return backtrack(index + 1, board);
}*/

void Solver::random_solution(Board& board)
{
    int failcell = 0;
    int first = rand() % board.getpuzzle().length();
    answer = board.getpuzzle();
    for (int i = 0; i < answer.length(); i++)
    {
        int point = (first + i) % answer.length();
        if (answer[point] == '.')
        {
            NumSet grid = board.at(point);
            NumSet choice = NumSet(sqrt(sqrt(answer.length())));
            NumSet* fixnum = new NumSet[(int)sqrt(answer.length())];
            choice.setzero(); choice.addnum(1);
            if (grid.empty())
            {
                failcell++;
                delete[] fixnum;
                continue;
            }
            int numChoices = 0;
            for (int j = 0; j < sqrt(answer.length()); j++)
            {
                if (grid.contains(choice))
                {
                    fixnum[numChoices] = choice;
                    ++numChoices;
                }
                choice <<= 1;
            }
            int index = rand() % numChoices;
            answer[point] = fixnum[index].index() + 1 + '0';
            board.setpuzzle(answer);
            board.set_cell(point, fixnum[index]);
            answer = board.getpuzzle();
            delete[] fixnum;
        }
    }
    board.setfail(failcell);
}

bool Solver::Shuffled_Frog_Leaping_Algorithm(int memeplex, int n_frogs, Board* board, clock_t start)
{
    clock_t end;
    original = board[0].getpuzzle();
    for (int i = 0; i < memeplex * n_frogs; i++) random_solution(board[i]);
    sort(board, board + memeplex * n_frogs, compare);
    /*** Build triangular probability distribution ***/
    float* acc = new float[n_frogs];
    acc[0] = 2.0 / (n_frogs + 1);
    for (int j = 1; j < n_frogs; j++)
    {
        acc[j] = acc[j - 1] + (2.0 * (n_frogs - j) / (n_frogs * (n_frogs + 1)));
    }
    /*** Build triangular probability distribution ***/
    bool solve = false;
    while (!solve)
    {
        if (board[0].fitness() == 0)
        {
            answer = board[0].getpuzzle();
            return true;
        }
        int replace = original.length() / 5 + (rand() % (original.length() * 3 / 5));
        int submemeplex = 2;
        for (int i = 0; i < memeplex; i++)
        {
            list<int> mylist;
            while(mylist.size() != submemeplex)
            {
                float var = (float)rand() / (RAND_MAX + 1.0);
                for (int j = 0; j < n_frogs; j++)
                {
                    if (var < acc[j])
                    {
                        mylist.push_back(j * memeplex + i);
                        break;
                    }
                }
                mylist.sort();
                mylist.unique();
            }
            string best_puzzle;
            if (mylist.front() == i) best_puzzle = board[i + memeplex].getpuzzle();
            else best_puzzle = board[i].getpuzzle();
            string better_puzzle = board[mylist.front()].getpuzzle();
            bool flag = replace_function(better_puzzle, replace, board[mylist.back()]);
            if (!flag) flag = replace_function(best_puzzle, replace, board[mylist.back()]);
            if (!flag)
            {
                for (int j = 0; j < original.length() / 20; j++)
                {
                    Board tmp = Board(original);
                    random_solution(tmp);
                    if (tmp.fitness() == 0) 
                    {
                        tmp.release_memory();
                        delete[] acc;
                        return true;
                    }
                    if (tmp.fitness() < board[mylist.back()].fitness())
                    {
                        board[mylist.back()] = tmp;
                        tmp.release_memory();
                        break;
                    }
                    else
                    {
                        tmp.release_memory();
                    }
                }
            }
            mylist.clear();
        }
        sort(board, board + memeplex * n_frogs, compare);
        end = clock();
        if ((double)(end - start) / CLOCKS_PER_SEC > 450.0) break;
    }
    delete[] acc;
    return false;
}

string Solver::getanswer()
{
    return answer;
}



