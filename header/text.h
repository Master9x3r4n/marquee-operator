#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> getArgs(string input) 
{
    vector<string> args;
    string word = "";
    istringstream stream(input);
    
    // split string into vector
    while (stream >> word)
        args.push_back(word);


    return args;
}       

int parseString(string input)
{
    return 0;
}