#include "../header/Lexer.h"
#include "../header/Syntax.h"
#include <iostream>

using namespace std;

int main(){

    Lexer lexer;
    Syntax syntax;
    vector< pair<string, string> > variables;
    string result;

    vector< pair<int, string> > token = lexer.get_Token();

    result = syntax.analyze(token, &variables);

    cout << endl << "result : " << result << endl << endl;

    for(int i=0;i<variables.size();i++){
        cout << variables[i].first << " : " << variables[i].second << endl;
    }

    return 0;
}
