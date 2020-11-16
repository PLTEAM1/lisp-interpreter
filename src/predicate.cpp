#include "../header/Predicate.h"
#include "../header/Syntax.h"

#include <iostream>

/* 예원 할 일 
    1. variable에서 참조해오는 것
    2. ATOM, NULL 에서 다양한 처리 
    3. 안에 함수 들었을 때 syntax.analyze 들어가도록
    4. (ATOM (LIST 1 2)) 시 LIST 반환값에서 '붙여서 판별하기 */
    
bool Predicate::isNumber(string str){
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

string Predicate::atom(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    // ATOM
    Syntax syntax;
    string value = token[1].second;
}

string Predicate::null(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* NULL 
        * X가 NIL일 때만 참(true)을 반환함. */
    Syntax syntax;
    string value = token[1].second;
    cout << value << endl;

    if(value == "NIL"){
        printf("T");
        return "true";
    } 
    else {
        printf("NIL");
        return "NIL";
    }
}

string Predicate::numberp(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* NUMBERP
         * X가 숫자일 때만 참(true)을 반환함. */
    Syntax syntax;
    string value = token[1].second;

    bool flag = isNumber(value);

        if(flag){
            printf("T");
            return "true";
        }
        else {
            printf("NIL");
            return "NIL";
        }
}

string Predicate::zerop(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* ZEROP 
         * X가 0일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    Syntax syntax;
    string value = token[1].second;

    if(value.compare("0") == 0){
             printf("T");
             return "true";
        }
        else{
            bool flag = isNumber(value);

            if(flag) {
                printf("NIL");
                return "NIL";
            }
            else{
                printf("ERROR");
                return "ERROR";
            }
        }
}

string Predicate::minusp(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* MINUSP 
         * X가 음수일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    Syntax syntax;
    string value = token[1].second;

    bool flag = isNumber(value);

        if(value[0] == '-' && flag){
            printf("T");
            return "true";
        }else if(flag){
            printf("NIL");
            return "NIL";
        }else{
            printf("ERROR");
            return "ERROR";
        }
}

string Predicate::equal(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* EQAUL 
         * X와 Y가 같으면 참(true)을 반환함. 아니면 NIL */
    Syntax syntax;
    string value = token[1].second;
    string compared = token[2].second;
        
        if(value.compare(compared) == 0 ){
            printf("T");
            return "true";
        }
        else{
            printf("NIL");
            return "NIL";
        }
}

string Predicate::isLess(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* < 
         * X < Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    Syntax syntax;
    string value = token[1].second;
    string compared = token[2].second;
    printf("hERRRL");
    if(isNumber(value) && isNumber(compared)){
            int operandA = atoi(value.c_str());
            int operandB = atoi(compared.c_str());
            
            if(operandA < operandB){
                printf("T");
                return "true";
            }
            else{
                printf("NIL");
                return "NIL";
            }
            
    }else{
        printf("ERROR");
        return "ERROR";
    } 
}

string Predicate::isGreater(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* >=
         * X >= Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    Syntax syntax;
    string value = token[1].second;
    string compared = token[2].second;

    if(isNumber(value) && isNumber(compared)){
            int operandA = atoi(value.c_str());
            int operandB = atoi(compared.c_str());
            
            if(operandA >= operandB){
                printf("T");
                return "true";
            }
            else{
                printf("NIL");
                return "NIL";
            }
            
            
    }else{
        printf("ERROR");
        return "ERROR";
    } 
}

string Predicate::stringp(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    /* STRINGP */
    Syntax syntax;
    string value = token[1].second;

    if(value.front() == '"'){
            printf("T");
            return "true";
        }
        /*
        else if(변수 안에 값이 string 이면){
            printf("T");
        }
        */
       else{
           printf("NIL");
           return "NIL";
       }
}
