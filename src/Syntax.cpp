#include "../header/Syntax.h"
#include "../header/Basic.h"
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

bool Syntax::isNumber(string str){

    bool flag = true;

        for(int i = 0 ; i < str.size() ; i++){
            if(str[0] == '-' || str[0] == '+') continue;
            if(isdigit(str[i]) != 1){
                flag = false;
                break;
            }
        }
    return flag;
}

void Syntax::predicate_Function(vector< pair<int, string> > t){
    
    /* predicate 함수 기능 구현 */

    string functionName = t[0].second;

    string value = t[1].second; // value, *변수 안에 값도 이거로 받아온다고 가정*

    if(functionName.compare("ATOM") == 0){
        /* ATOM function
         * 얘는 어느정도 SETQ 윤곽이 잡히고 나서 만들기 */

    }else if(functionName.compare("NULL") == 0){
        /* NULL 
         * X가 NIL일 때만 참(true)을 반환함. */
        if(value.compare("NIL")) printf("T");
        else printf("NIL");

    }else if(functionName.compare("NUMBERP") == 0){
        /* NUMBERP
         * X가 숫자일 때만 참(true)을 반환함. */
 
        bool flag = isNumber(value);

        if(flag) printf("T");
        else printf("NIL");
        
    }else if(functionName.compare("ZEROP") == 0){
        /* ZEROP 
         * X가 0일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
        if(value.compare("0") == 0){
             printf("T");
             return;
        }
        else{
            bool flag = isNumber(value);

            if(flag) printf("NIL");
            else printf("ERROR");
        }

    }else if(functionName.compare("MINUSP") == 0){
        /* MINUSP 
         * X가 음수일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
        bool flag = isNumber(value);

        if(value[0] == '-' && flag){
            printf("T");
        }else if(flag){
            printf("NIL");
        }else{
            printf("ERROR");
        }

    }else if(functionName.compare("EQUAL") == 0){
        /* EQAUL 
         * X와 Y가 같으면 참(true)을 반환함. 아니면 NIL */
        string compared = t[2].second;
        
        if(value.compare(compared) == 0 ) printf("T");
        else printf("NIL");

    }else if(functionName.compare("<") == 0 || functionName.compare(">=") == 0){
        /* < 
         * X < Y 이면 참(true)을 반환함. 숫자가 아니면 error */
        string compared = t[2].second;
        if(isNumber(value) && isNumber(compared)){
            int operandA = atoi(value.c_str());
            int operandB = atoi(compared.c_str());
            
            if(functionName.compare("<") == 0){
                if(operandA < operandB) printf("T");
                else printf("NIL");
            }else if(functionName.compare(">=") == 0){
                if(operandA >= operandB) printf("T");
                else printf("NIL");
            }

        }else printf("ERROR");
        
    }else if(functionName.compare("STRINGP") == 0){
        
        /* STRINGP */
        // 변수일경우 안에 값 확인하고 (STRINGP X) (STRINGP "HI"), 근데 어차피 string은 " " 짝이 맞을때까지 받음
        if(value.front() == '"'){
            printf("T");
        }
        /*
        else if(변수 안에 값이 string 이면){
            printf("T");
        }
        */
       else{
           printf("NIL");
       }
    }
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

    }else{
        return "1";
    }

    return "0";
}
