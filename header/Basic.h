#ifndef BASIC_H
#define BASIC_H 

#include <string>
#include <vector>
//#include "Syntax.h"

using namespace std;

class Basic{
    private:
        //Syntax syntax;
    public:
        string setq(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string list(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string car(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string cdr(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string caddr(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string nth(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string cons(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string reverse(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string append(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string length(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string member(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string assoc(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string remove(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
        string subst(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
};

#endif