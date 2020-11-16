#include "../header/Syntax.h"
#include "../header/Basic.h"
#include "../header/Predicate.h"
#include <cctype>
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

void Syntax::conditional(){

    /* 조건문 구현 */
}

List Syntax::analyze(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    Basic basic;
    Predicate predicate;

    string function_Name = token[0].second;

    if(function_Name == "SETQ"){
        /* SETQ Function ex) SETQ X (1 2 3)); */
        return basic.setq(token, variables);

    }else if(function_Name == "LIST"){
        /* LIST Function */
        return basic.list(token, variables);

    }else if(function_Name == "CAR"){
        /* CAR Function */
        return basic.car(token, variables);

    }else if(function_Name == "CDR"){
        /* CDR Function */
        return basic.cdr(token, variables);

    }else if(function_Name == "CADDR"){
        /* CADDR Function */
        return basic.caddr(token, variables);

    }else if(function_Name == "NTH"){
        /* NTH Function */
        return basic.nth(token, variables);
      
    }else if(function_Name == "CONS"){
        /* CONS Function */
        return basic.cons(token, variables);

    }else if(function_Name == "REVERSE"){
        /* REVERSE Function */
        return basic.reverse(token, variables);

    }else if(function_Name == "APPEND"){
        /* APPEND Function */
        return basic.append(token, variables);

    }else if(function_Name == "LENGTH"){
        /* LENGTH Function */
        return basic.length(token, variables);

    }else if(function_Name == "MEMBER"){
        /* MEMBER Function */
        return basic.member(token, variables);

    }else if(function_Name == "ASSOC"){
        /* ASSOC Function */
        return basic.assoc(token, variables);

    }else if(function_Name == "REMOVE"){
        /* REMOVE Function */
        return basic.remove(token, variables);

    }else if(function_Name == "SUBST"){
        /* SUBST Function */
        return basic.subst(token, variables);

    }else if(function_Name == "ATOM"){
        return predicate.atom(token, variables);

    }else if(function_Name == "NULL"){
        return predicate.null(token, variables);

    }else if(function_Name == "NUMBERP"){
        return predicate.numberp(token, variables);

    }else if(function_Name == "ZEROP"){
        return predicate.zerop(token, variables);

    }else if(function_Name == "MINUSP"){
        return predicate.minusp(token, variables);

    }else if(function_Name == "EQUAL"){
        return predicate.equal(token, variables);

    }else if(function_Name == "<"){
        return predicate.isLess(token, variables);

    }else if(function_Name == ">="){
        return predicate.isGreater(token, variables);

    }else if(function_Name == "STRINGP"){
        return predicate.stringp(token, variables);

    }else{
        return List();
    }

    return List();
}
