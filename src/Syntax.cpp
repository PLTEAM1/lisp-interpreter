#include "../header/Syntax.h"
#include "../header/Basic.h"
//#include "../header/Conditional.h"
#include <cctype>
//#include "../header/Lisplist.h"
#include "../header/Basic.h"
#include "../header/Predicate.h"
#include "../header/Exception.h"
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

string Syntax::check_Syntax(vector< pair<int, string> > t){

    /* Syntax 판별 기능 구현 */
    
    string ret_string;
    //넘어온 파라미터의 첫번째가 함수이면 (token.first == 22)
    if(t[0].first == 23){
        
        /*사칙연산, 파라미터로 넘어온 t가 + 5 3)이라고 가정, 어떤 전처리 없이 그대로 arithmetic_Operation에 파라미터로 전달
          사칙연산 : + , - , *, /
         */
        if(t[0].second == "+" || t[0].second == "-" || t[0].second == "*" || t[0].second == "/" ){
            //ret_string = arithmetic_Operation(t);
            return ret_string;
        }
        
        /*기본함수, 파라미터로 넘어온 t가 SETQ X (LIST (1 2 3))이라고 가정, 어떤 전처리 없이 그대로 basic_Operation에 파라미터로 전달
          기본함수 : SETQ, LIST, CAR, CDR, NTH, CONS, REVERSE, APPEND, LENGTH, MEMBER, ASSOC, REMOVE, SUBST
         */
        else if(t[0].second == "SETQ" || t[0].second == "LIST" ||t[0].second == "CAR" ||t[0].second == "CDR" ||t[0].second == "NTH" ||t[0].second == "CONS" ||t[0].second == "REVERSE" ||t[0].second == "APPEND" ||t[0].second == "LENGTH" ||t[0].second == "MEMBER" ||t[0].second == "ASSOC" ||t[0].second == "REMOVE" ||t[0].second == "SUBST"){
            //ret_string = basic_Function(t);
            return ret_string;
        }
        
        /*Predicate함수, 전처리 없이 그대로 predicate_Function에 파라미터로 전달
          Predicate함수 : ATOM, NULL, NUMBERP, ZEROP, MINUSP, EQUAL, <, >, <= >=, STRINGP
         */
        else if(t[0].second == "ATOM" ||t[0].second == "NULL" ||t[0].second == "NUMBERP" ||t[0].second == "ZEROP" ||t[0].second == "MINUSP" ||t[0].second == "MINUSP" ||t[0].second == "EQUAL" ||t[0].second == "<" ||t[0].second == ">" ||t[0].second == "<=" ||t[0].second == ">=" ||t[0].second == "STRINGP"||t[0].second == "="){
            //ret_string = predicate_Function(t);
            //return ret_string;
            return "TRUE";
        }
        
        /*조건문
          조건문 : IF,COND
         */
        else if(t[0].second == "IF" ||t[0].second == "COND"){
            
            /*for(auto &i : t){
                cout << i.second << " ";
            }
            cout << "\n";*/
            ret_string = conditional(t);
            cout << ret_string;
            return ret_string;
        }
        
    }
    
    //넘어온 파라미터의 첫번째가 세미콜론이면
    else if(t[0].first == 22){
        //그대로 종료?
        return ret_string = "SEMI";
    }
    //EOF이면
    else if(t[0].first == -1){
        cout << "\n check_Syntax EOF";
        return "";
    }
    else{
        return "invalid parameter";
    }
    return "error";
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

    List error;

    if(token[0].second != "("){
        for(int i = 0 ; i < (*variables).size() ; i++){
            if((*variables)[i].first == token[0].second){
                return (*variables)[i].second;
            }
        }
        
        throw Exception(2);
    }
    else{
        token.erase(token.begin());
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
            /* CADDR Function */
            if(function_Name.at(0) == 'C' && function_Name.at(1) == 'A'){
                vector< pair<int, string> > new_token;
                int count = 0;
                new_token.push_back(make_pair(20, "("));
                new_token.push_back(make_pair(23, "CAR"));
                for(int i=2;i<function_Name.length();i++){
                    if(function_Name.at(i) != 'D' && i != function_Name.length() - 1){
                        throw Exception(1);
                    }else{
                        if(i == function_Name.length() - 1){
                            if(function_Name.at(i) == 'R'){
                                token.erase(token.begin());
                                new_token.insert(new_token.end(), token.begin(), token.end());
                            }else{
                                throw Exception(1);
                            }
                        }else{
                            count++;
                            new_token.push_back(make_pair(20, "("));
                            new_token.push_back(make_pair(23, "CDR"));
                        }
                    }
                }

                while(count){
                    new_token.push_back(make_pair(21, ")"));
                    count--;
                }

                return analyze(new_token, variables);
            }

            throw Exception(1);
        }
    }
    throw Exception(1);
}
