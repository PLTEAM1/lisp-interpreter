#include "../header/Syntax.h"
#include "../header/Basic.h"

string Syntax::check_Syntax(vector< pair<int, string> > token){

    /* Syntax 판별 기능 구현 */

    return "1";
}

void Syntax::arithmetic_Operation(){

    /* 산술 연산 기능 구현 */
}

void Syntax::basic_Function(vector< pair<int, string> > token){

    /* 기본 함수 기능 구현 */
        
}

void Syntax::predicate_Finction(){

    /* predicate 함수 기능 구현 */
}

void Syntax::conditional(){

    /* 조건문 구현 */
}

string Syntax::analyze(vector< pair<int, string> > token, vector< pair<string, string> > *variables){

    Basic basic;

    string function_Name = token[0].second;

    if(function_Name == "SETQ"){
        /* SETQ Function ex) SETQ X (1 2 3)); */
        return basic.setq(token, variables);

    }else if(function_Name == "LIST"){
        /* LIST Function */
        return basic.list(token, variables);

    }else if(function_Name == "CAR"){
        /* CAR Function */
        return basic.car(token);

    }else if(function_Name == "CDR"){
        /* CDR Function */
        return basic.cdr(token);

    }else if(function_Name == "CADDR"){
        /* CADDR Function */
        return basic.caddr(token);

    }else if(function_Name == "NTH"){
        /* NTH Function */
        return basic.nth(token);

    }else if(function_Name == "CONS"){
        /* CONS Function */
        return basic.cons(token);

    }else if(function_Name == "REVERSE"){
        /* REVERSE Function */
        return basic.reverse(token);

    }else if(function_Name == "APPEND"){
        /* APPEND Function */
        return basic.append(token);

    }else if(function_Name == "LENGTH"){
        /* LENGTH Function */
        return basic.length(token);

    }else if(function_Name == "MEMBER"){
        /* MEMBER Function */
        return basic.member(token);

    }else if(function_Name == "ASSOC"){
        /* ASSOC Function */
        return basic.assoc(token);

    }else if(function_Name == "REMOVE"){
        /* REMOVE Function */
        return basic.remove(token);

    }else if(function_Name == "SUBST"){
        /* SUBST Function */
        return basic.subst(token);

    }else{
        return "1";
    }

    return "0";
}