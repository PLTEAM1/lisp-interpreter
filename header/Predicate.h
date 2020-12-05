#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include <cctype>

#include "./Parser.h"
#include "./Lisplist.h"

using namespace std;

class Predicate{
    private:
        void delVar(vector< pair<string, List> > *variables, int count);
        bool isNumber(string str);
        List getValue(vector< pair<string, List> > *variables, string isSymbol);
        List getArr(int& index, vector< pair<int, string> > token);
    public:
        List atom(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List null(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List numberp(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List zerop(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List minusp(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List equal(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List isLess(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List isGreater(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List stringp(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};



#endif