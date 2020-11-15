#include "../header/Syntax.h"

void Syntax::check_Syntax(){

    /* Syntax 판별 기능 구현 */
}

void Syntax::arithmetic_Operation(){

    /* 산술 연산 기능 구현 */
}

void Syntax::basic_Function(vector< pair<int, string> > token){

    /* 기본 함수 기능 구현 */
    string function_Name = token[0].second;

    if(function_Name == "SETQ"){
        /* SETQ Function ex) SETQ X 3); */

    }else if(function_Name == "LIST"){
        /* LIST Function */

    }else if(function_Name == "CAR"){
        /* CAR Function */

    }else if(function_Name == "CDR"){
        /* CDR Function */

    }else if(function_Name == "CADDR"){
        /* CADDR Function */

    }else if(function_Name == "NTH"){
        /* NTH Function */

    }else if(function_Name == "CONS"){
        /* CONS Function */

    }else if(function_Name == "REVERSE"){
        /* REVERSE Function */

    }else if(function_Name == "APPEND"){
        /* APPEND Function */

    }else if(function_Name == "LENGTH"){
        /* LENGTH Function */

    }else if(function_Name == "MEMBER"){
        /* MEMBER Function */

    }else if(function_Name == "ASSOC"){
        /* ASSOC Function */

    }else if(function_Name == "REMOVE"){
        /* REMOVE Function */

    }else{
        /* SUBST Function */
    }
    
}

void Syntax::predicate_Finction(){

    /* predicate 함수 기능 구현 */
}

void Syntax::conditional(){

    /* 조건문 구현 */
}

void Syntax::analyze(vector< pair<int, string> > token){

    //token = t;

    /*while(!token.empty()){
        check_Syntax();
    }*/

    basic_Function(token);
}