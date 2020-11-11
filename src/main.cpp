#include "../header/Lexer.h"
#include "../header/Syntax.h"
#include <iostream>

using namespace std;

int main(){

    Lexer lexer;
    Syntax syntax;

    vector< pair<int, string> > token = lexer.get_Token();

    syntax.analyze(token);

    return 0;
}