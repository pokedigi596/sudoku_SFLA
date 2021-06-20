#include "../inc/sudoku_board.h"

Board::Board()
{

}

Board::~Board()
{
    /*cout << "delete " << aaa << endl;
    delete[] numset;*/
}

Board::Board(string puzzle_string, int aa)
{
    aaa = aa;
    puzzle = puzzle_string;
    numset = new NumSet[puzzle_string.length()];
    size = sqrt(puzzle_string.length());
    int order = sqrt(size);
    for (int i = 0; i < puzzle_string.length(); i++) numset[i] = NumSet(order);
    for (int i = 0; i < puzzle_string.length(); i++)
    {
        if (puzzle_string[i] == '.')
        {
            int start_point = 0;
            for (int j = 0; j < size; j++)
            {
                // Row Judge
                start_point = i / size * size;
                if (puzzle_string[start_point + j] != '.') numset[i].delnum(puzzle_string[start_point + j] - '0');
                // Column Judge
                start_point = i % size;
                if (puzzle_string[start_point + size * j] != '.') numset[i].delnum(puzzle_string[start_point + size * j] - '0');
                // Box Judge
                start_point = i / size / order * order * size + i % size / order * order;
                if (puzzle_string[start_point + j / order * size + j % order] != '.') numset[i].delnum(puzzle_string[start_point + j / order * size + j % order] - '0');
            }
        }
        else
        {
            numset[i].setzero();
            numset[i].addnum(puzzle_string[i] - '0');
        }
    }
}

void Board::PrintPossibaleValue()
{
    for (int i = 0; i < size * size; i++)
    {
        cout << numset[i].validnum() << endl;
    }
}

void Board::constrain_cell(int index)
{
    if (numset[index].fixed() || numset[index].empty()) return;
    int start_point;
    int size = sqrt(puzzle.length());
    int order = sqrt(size);
    NumSet row(order), col(order), box(order), frow(order), fcol(order), fbox(order);

    row.setzero(); col.setzero(); box.setzero(); frow.setzero(); fcol.setzero(); fbox.setzero();

    for (int i = 0; i < size; i++)
    {
        start_point = index / size / order * order * size + index % size / order * order;
        if (index != start_point + i / order * size + i % order)
        {
            if (numset[start_point + i / order * size + i % order].fixed()) fbox += numset[start_point + i / order * size + i % order];
            box += numset[start_point + i / order * size + i % order];
        }
        start_point = index % size;
        if (index != start_point + size * i)
        {
            if (numset[start_point + size * i].fixed()) fcol += numset[start_point + size * i];
            col += numset[start_point + size * i];
        }
        start_point = index / size * size;
        if (index != start_point + i)
        {
            if (numset[start_point + i].fixed()) frow += numset[start_point + i];
            row += numset[start_point + i];
        }
    }

    NumSet temp = ~(frow + fcol + fbox);

    if (temp.fixed())
    {
        puzzle[index] = temp.index() + 1 + '0';
        set_cell(index, temp);
    }
    else
    {
        numset[index] ^= temp;
        if ((numset[index] - row).fixed()) set_cell(index, (numset[index] - row));
        else if ((numset[index] - col).fixed()) set_cell(index, (numset[index] - col));
        else if ((numset[index] - box).fixed()) set_cell(index, (numset[index] - box));
    }
}

void Board::set_cell(int index, NumSet set)
{
    if (numset[index].fixed()) return;
    numset[index] = set;

    int start_point;
    int size = sqrt(puzzle.length());
    int order = sqrt(size);
    for (int i = 0; i < size; i++)
    {
        start_point = index / size * size;
        if (index != start_point + i)
        {
            constrain_cell(start_point + i);
        }
        start_point = index % size;
        if (index != start_point + size * i)
        {
            constrain_cell(start_point + size * i);
        }
        start_point = index / size / order * order * size + index % size / order * order;
        if (index != start_point + i / order * size + i % order)
        {
            constrain_cell(start_point + i / order * size + i % order);
        }
    }
}

int Board::fitness()
{
    return invalid;
}

string Board::getpuzzle()
{
    return puzzle;
}
void Board::setpuzzle(string answer)
{
    puzzle = answer;
}

NumSet Board::at(int index)
{
    return numset[index];
}

void Board::remove(int index, int val)
{
    numset[index].delnum(val);
}

void Board::setfail(int num)
{
    invalid = num;
}

void Board::release_memory()
{
    delete[] numset;
    puzzle = "";
}