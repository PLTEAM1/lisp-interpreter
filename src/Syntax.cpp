#include "../header/Syntax.h"
#include "../header/Basic.h"
//#include "../header/Conditional.h"
#include <cctype>
//#include "../header/Lisplist.h"
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

/*  IF또는 COND를 봤을때 넘어온다고 가정
    ex) IF (> X 3) (PRINT X))
    ex) COND ((> X 0) (+ X 1))  ; X 가 0보다 크면 X 값에 1을 더함
            ((= X 0) (+ X 2))  ; X 가 0이면 X 값에 2을 더함
            ((< X 0) (+ X 3)))
 */
string Syntax::conditional(vector< pair<int, string> > t){

    /* 조건문 구현 */
    
    //파라미터를 전부 지우고 check_Syntax를 해야함.
    int param_size = 0;
    
    /* IF */
    if(t[0].second == "IF"){
        
        /* 파라미터로 넘어온 토큰중 조건문, 수행문을 괄호에 맞춰서 스택에 넣는 작업
            ex) token = (> X 3) // syntax_check를 위해서 pair<int,string>으로 추가
            ex) stack[0] = (> X 3) <- token의 형식(즉, pair<int,string>
                stack[1] = (+ X 1)
         */
        
        vector<pair<int,string>> token;
        vector<vector<pair<int,string>>> stack;
        
        for(int i = 0; i < t.size(); i++){
            if(t[i].second == "("){
                for(int j = i; j < t.size(); j++){
                    if(t[j].second == ")"){
                        token.push_back(t[j]);
                        stack.push_back(token);
                        token.clear();
                        i = j;
                        break;
                    }//if ) end
                    token.push_back(t[j]);
                }//for loop end
            }//if ( end
            else if(t[i].second == ")"){
                break;
            }//else if ) end
        }//for loop end
        
        //넘겨줄때는 > X 0)을 넘겨줌
        stack[0].erase(stack[0].begin());
        
        //파라미터가 2개일때, 즉 참이면 수행문, 거짓이면 NIL 출력
        if(stack.size() == 2){
            cout << "\n파라미터 2개";
            if(check_Syntax(stack[0]) == "TRUE"){
                cout << "조건문 TRUE\n";
                stack[1].erase(stack[1].begin());
                check_Syntax(stack[1]);
            }//if true end
            else if(check_Syntax(stack[0]) == "FALSE"){
                cout << "NIL\n";
            }//else if false end
        }//파라미터가 2개일때 if end
        
        //파라미터가 3개일때, 즉 참이면 참 수행문, 거짓이면 거짓 수행문
        else if(stack.size() == 3){
            cout << "파라미터 3개\n";
            if(check_Syntax(stack[0]) == "TRUE"){
                cout << "조건문 TRUE\n";
                stack[1].erase(stack[1].begin());
                check_Syntax(stack[1]);
            }//if true end
            else if(check_Syntax(stack[0]) == "FALSE"){
                cout << "조건문 FALSE\n";
                stack[2].erase(stack[2].begin());
                check_Syntax(stack[2]);
            }//else if false end
        }//파라미터가 3개일때 else if end
    }//IF end
        
    /* COND */
    else if(t[0].second == "COND"){
        /* 파라미터로 넘어온 토큰중 조건문, 수행문을 괄호에 맞춰서 스택에 넣는 작업
            ex) token = (> X 3) // syntax_check를 위해서 pair<int,string>으로 추가
            ex) stack[0] = (> X 3) <- token의 형식(즉, pair<int,string>
                stack[1] = (+ X 1)
            ex) stack_COND[0] = (> X 0) (+ X 1) <- stack_COND[0][0] = (> X 0), stack_COND[0][1] = (+ X 1)
                stack_COND[1] = (= X 0) (+ X 2)
                stack_COND[2] = (< X 0) (+ X 3)
         */
        
        vector<pair<int,string>> token;
        vector<vector<pair<int,string>>> stack;
        vector<vector<vector<pair<int,string>>>> stack_COND;
        
        for(int i = 0; i < t.size(); i++){
            if(t[i].second == "("){
                for(int j = i; j < t.size(); j++){
                    if(t[j].second == ")"){
                        token.push_back(t[j]);
                        stack.push_back(token);
                        param_size += token.size();
                        for(auto &i : token){
                            cout << i.second << " ";
                        }
                        cout << "\n";
                        token.clear();
                        i = j;
                        break;
                    }//if ) end
                    token.push_back(t[j]);
                }//for loop end
            }//if ( end
            else if(t[i].second == ")"){
                if(t[i+1].second == "("){
                    stack[0].erase(stack[0].begin());
                    stack_COND.push_back(stack);
                    param_size++;
                    stack.clear();
                }//if ( end
                else if(t[i+1].second == ")"){
                    stack[0].erase(stack[0].begin());
                    stack_COND.push_back(stack);
                    break;
                }//if ) end
            }//else if ) end
        }//for loop end
        
        //cout << "stack_COND size : "<<stack_COND.size() << "\n";
        
        /*
        for(int i = 0; i < stack_COND.size(); i++){
            for(int j = 0; j < stack_COND[i].size(); j++){
                for(int k = 0; k < stack_COND[i][j].size(); k++){
                    cout << stack_COND[i][j][k].second << " ";
                }
            }
            cout << "\n";
        }*/
        
        for(int i = 0; i <= stack_COND.size(); i++){
            if(i == stack_COND.size()){
                //cout << "맞는 조건이 없음 return 은 생각 해봐야함\n";
                cout << "\nParam_size : "<< param_size;
                return "CONDITION ERROR";
                break;
            }//if stack_COND.size() end
            stack_COND[i][0].erase(stack_COND[i][0].begin());
            if(check_Syntax(stack_COND[i][0]) == "TRUE"){
                stack_COND[i][1].erase(stack_COND[i][1].begin());
                check_Syntax(stack_COND[i][1]); // 수행문 실행
                break;
            }//if TRUE end
        }//for loop end
        param_size += stack_COND.size();
    }//COND end
    
    cout << "\nParam_size : "<< param_size;
    t.erase(t.begin(), t.begin()+param_size);
    cout << "after erase" << "\n";
    for(int i = 0; i < t.size(); i++){
        cout << t[i].second << " ";
    }
    check_Syntax(t);
    return "DONE";
}//conditional end

List Syntax::analyze(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Basic basic;

    string function_Name = token[0].second;

    if(function_Name == "SETQ"){
        /* SETQ Function ex) SETQ X (1 2 3)); */
        return basic.setq(token, variables);

    }else if(function_Name == "LIST"){
        /* LIST Function */
        /*try{
            return basic.list(token, variables);
        }catch(int a){
            cout << a;
        }*/
        
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
        return List();
    }

    return List();
}
