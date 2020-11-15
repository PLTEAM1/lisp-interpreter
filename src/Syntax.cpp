#include "../header/Syntax.h"
#include <iostream>

bool Syntax::is_valid_paren(vector<pair<int, string> > t){
    
    int Left_paren_count = 0;
    int Right_paren_count = 0;
    
    for(auto &item : t){

        if(item.second == "("){
            Left_paren_count++;
        }
        else if(item.second == ")"){
            Right_paren_count++;
        }
    }
    
    if(Left_paren_count == Right_paren_count) return true;
    else return false;
}

void Syntax::check_Syntax(){

    /* Syntax 판별 기능 구현 */
}

void Syntax::arithmetic_Operation(){

    /* 산술 연산 기능 구현 */
}

void Syntax::basic_Function(){

    /* 기본 함수 기능 구현 */
}

void Syntax::predicate_Finction(){

    /* predicate 함수 기능 구현 */
}

void Syntax::conditional(){

    /* 조건문 구현 */
}

void Syntax::analyze(vector< pair<int, string> > t){

    token = t;

    
    if(is_valid_paren(t)){
        cout << "\nvalid";
    }
    else{
        cout << "\nparen error";
    }
    
    while(!token.empty()){
        check_Syntax();
    }
}
