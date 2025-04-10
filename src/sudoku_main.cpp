#include <iostream>
#include <fstream>
#include <string>
#include "../inc/sudoku_solver.h"
#include "../inc/timer.h"

using namespace std;

string readpuzzle(string fileName)
{
	char* puzString;
	fstream file;
	file.open(fileName);
	if (file.is_open())
	{
		int order, idum;
		file >> order;
		int numCells = order*order*order*order;
		file >> idum;
		puzString = new char[numCells+1];
		for (int i = 0; i < numCells; i++)
		{
			int val;
			file >> val;
			if (val == -1) puzString[i] = '.';
			else puzString[i] = '0' + val;
		}
		puzString[numCells] = 0;
		file.close();
		string retVal = string(puzString);
		delete [] puzString;
		return retVal;
	}
	else
	{
		cerr << "could not open file: " << fileName << endl;
		return string();
	}
}

bool solution_check(string answer)
{
	for (int i = 0; i < answer.length(); i++)
	{
		int start_point;
		int size = sqrt(answer.length());
		int order = sqrt(size);
		for (int j = 0; j < size; j++)
		{
			start_point = i / size * size;
			if ((i != start_point + j) && answer[i] == answer[start_point + j]) return false;
			start_point = i % size;
			if ((i != start_point + size * j) && answer[i] == answer[start_point + size * j]) return false;
			start_point = i / size / order * order * size + i % size / order * order;
			if ((i != start_point + j / order * size + j % order) && answer[i] == answer[start_point + j / order * size + j % order]) return false;
		}
	}
	return true;
}

void printpuzzle(string puzzle)
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

int main(int argc, char* argv[])
{
    string puzzle = readpuzzle(argv[1]);
	int memeplex = atoi(argv[2]);
	int n_frogs = atoi(argv[3]);
	// Allocate Board
	Board* board = new Board[memeplex * n_frogs];
	Solver solver;
	bool check = false;
	bool timeout;
	string answer;
	clock_t start;
	Timer timer;
	while (!check)
	{
		for (int i = 0; i < memeplex * n_frogs; i++)
		{
			Board* temp = new Board(puzzle);
			board[i] = *temp;
			temp->release_memory();
			delete temp;
		}
		timer.Reset();
		timeout = solver.Shuffled_Frog_Leaping_Algorithm(memeplex, n_frogs, board, start);
		if (!timeout) break;
		answer = solver.getanswer();
		check = solution_check(answer);
	}
	// Deallocate Board
	for (int i = 0; i < memeplex * n_frogs; i++) board[i].release_memory();
	float execute_time = timer.Elapsed();
	delete[] board;

	if (argv[4] == NULL)
	{
		printpuzzle(answer);
		if (!timeout) 
		{
			string result = "Timeout";
			cout << result << endl;
		}
		else
		{
			string result = "Time: " + to_string(execute_time) + " second";
			cout << result << endl;
		}
	}
	else
	{
		fstream file;
		file.open(argv[4], ios::app);
		if (!timeout) 
		{
			string result = "Timeout\n";
			file.write(result.c_str(), result.length());
		}
		else
		{
			string result = "Time: " + to_string(execute_time) + " second\n";
			file.write(result.c_str(), result.length());
		}
		file.close();
	}

    return 0;
}