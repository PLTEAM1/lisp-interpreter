#include "../header/Syntax.h"

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

    while(!token.empty()){
        check_Syntax();
    }
}