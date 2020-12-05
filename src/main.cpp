#include "../header/Lexer.h"
#include "../header/Lisplist.h"
#include "../header/Parser.h"
#include "../header/Exception.h"
#include <iostream>
#include <string>

#include <list>
using namespace std;

int main(){
    
    Lexer lexer;
    Parser parser;
    vector< pair<string, List> > variables;
    List result;


    while(1){
        try{
            vector< pair<int, string> > token = lexer.get_Token();

            if(parser.is_valid_paren(token)){
                result = parser.analyze(token, &variables);
                
                cout << "> ";
                result.traverse(result.getHead());
                cout << endl;
            }else{
                throw Exception(15);
            }
        }catch(Exception e){
            e.print();
        }
    }
    
    return 0;
}
