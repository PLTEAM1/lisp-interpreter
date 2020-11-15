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
        string car(vector< pair<int, string> > token);
        string cdr(vector< pair<int, string> > token);
        string caddr(vector< pair<int, string> > token);
        string nth(vector< pair<int, string> > token);
        string cons(vector< pair<int, string> > token);
        string reverse(vector< pair<int, string> > token);
        string append(vector< pair<int, string> > token);
        string length(vector< pair<int, string> > token);
        string member(vector< pair<int, string> > token);
        string assoc(vector< pair<int, string> > token);
        string remove(vector< pair<int, string> > token);
        string subst(vector< pair<int, string> > token);
};

#endif