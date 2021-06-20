#include <iostream>
#include <fstream>
#include <cmath>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>


using namespace std;

float split(string s)
{
    string s1, s2;
    float result;
    sscanf(s.c_str(), "%s %f %s", &s1, &result, &s2);
    return result;
}

int main(int argc, char* argv[])
{
    _setmode(_fileno(stdout), 0x00020000);
    if (argc == 1) return 1;
    fstream file;
    file.open(argv[1], ios::in);
    string data;
    int success = 0, fail = 0;
    float sum = 0.0;
    float second[100];
    int i = 0;
    while (getline(file, data))
    {
        if (data == "Timeout")
        {
            fail++;
        }
        else
        {
            success++;
            second[i] = split(data);
            sum += second[i];
            i++;
        }
    }
    file.close();

    float average = sum / (success + fail);
    float sd = 0;
    for (int i = 0; i < success; i++)
    {
        sd += pow(second[i] - average, 2);
    }
    sd = sqrt(sd / (success + fail - 1));
    wcout << L"Solution Rate: " << (float)success * 100 / (success + fail) << endl;
    wcout << L"Solution Time: " << average << L"±" << sd << endl;

    return 0;
}