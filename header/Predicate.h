#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Predicate{
    private:

    public:
        string atom(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string null(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string numberp(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string zerop(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string minusp(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string equal(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string isLess(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string isGreater(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string stringp(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        bool isNumber(string str);
};



#endif