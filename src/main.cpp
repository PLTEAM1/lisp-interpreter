#include "../header/Lexer.h"
#include "../header/Lisplist.h"
#include "../header/Syntax.h"
#include "../header/Exception.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

    Lexer lexer;
    Syntax syntax;
    vector< pair<string, List> > variables;
    List result;

    try{
        vector< pair<int, string> > token = lexer.get_Token();

        result = syntax.analyze(token, &variables);

        for(int i=0;i<variables.size();i++){
            cout << variables[i].first << " : ";

            variables[i].second.traverse(variables[i].second.getHead());

            cout << endl;
        }

        result.traverse(result.getHead());

    }catch(Exception e){
        e.print();
    }

    return 0;
}
