#include "../header/Lexer.h"
#include "../header/Lisplist.h"
#include "../header/Parser.h"
#include "../header/Exception.h"
#include <iostream>
#include <string>

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

            
                for(int i=0;i<variables.size();i++){
                    cout << variables[i].first << " : ";

                    variables[i].second.traverse(variables[i].second.getHead());

                    cout << endl;
                }
                
                cout << "ret : ";
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
