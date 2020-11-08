#include "../header/Lexer.h"
//#include <vector>
#include <iostream>
using namespace std;

int main(){

    Lexer lexer;

    vector< pair<int, string> > token = lexer.get_Token();

    cout <<"end"<<endl;

    return 0;
}