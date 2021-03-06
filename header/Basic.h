#ifndef _BASIC_H
#define _BASIC_H

#include <string>
#include <vector>
#include "./Lisplist.h"
#include "./Parser.h"
using namespace std;

/** 
 * Class that performs the basic functions of the interpreter.
 * 
 * @date 2020.11.29
 * @version 1.0
 */
class Basic{
    private:
        int addQuoteList(vector< pair<int, string> > token, int index, class List& origin);
        List getValue(vector< pair<string, List> > *variables, string isSymbol);
        List getArr(int& index, vector< pair<int, string> > token);
        void delVar(vector< pair<string, List> > *variables, int count);
    public:
        List setq(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List list(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List car(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List cdr(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List nth(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List cons(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List reverse(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List append(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List length(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List member(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List assoc(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List remove(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List subst(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};

#endif