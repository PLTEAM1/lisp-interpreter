#include "../header/Syntax.h"
#include <iostream>

bool Syntax::is_valid_paren(vector<pair<int, string>> t){
    
    /* 괄호의 갯수가 맞는지 확인하는 함수 */
    
    int Left_paren_count = 0;
    int Right_paren_count = 0;
    
    for(auto &item : t){
        if(item.second == "("){
            Left_paren_count++;
        }//if end
        else if(item.second == ")"){
            Right_paren_count++;
        }//else if end
    }//for loop end
    
    if(Left_paren_count == Right_paren_count) return true;
    else return false;
}//is_valid_paren func end

string Syntax::check_Syntax(vector<pair<int, string>> t){

    /* Syntax 판별 기능 구현 */
    //넘어온 파라미터의 첫번째가 함수 또는 세미콜론이면
    if(t[0].first == 22 || t[0].first == 23){
        if(t[0].second == "<"){
            return "FALSE";
        }
    }
    else{
        return "invalid parameter";
    }
    return "";
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

/*  IF또는 COND를 봤을때 넘어온다고 가정
    ex) IF (> X 3) (PRINT X))
    ex) COND ((> X 0) (+ X 1))  ; X 가 0보다 크면 X 값에 1을 더함
            ((= X 0) (+ X 2))  ; X 가 0이면 X 값에 2을 더함
            ((< X 0) (+ X 3)))
 */
void Syntax::conditional(vector< pair<int, string> > t){

    /* 조건문 구현 */
    
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
        
        cout << "in COND\n";
        
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
                cout << "맞는 조건이 없음 return 은 생각 해봐야함";
                break;
            }//if stack_COND.size() end
            stack_COND[i][0].erase(stack_COND[i][0].begin());
            if(check_Syntax(stack_COND[i][0]) == "TRUE"){
                stack_COND[i][1].erase(stack_COND[i][1].begin());
                check_Syntax(stack_COND[i][1]); // 수행문 실행
                break;
            }//if TRUE end
        }//for loop end
    }//COND end
}

void Syntax::analyze(vector< pair<int, string> > t){

    token = t;

    
    
    if(is_valid_paren(t)){
        cout << "valid paren\n";
    }
    else{
        cout << "invaild paren error\n";
    }
    
    t.erase(t.begin());
    conditional(t);
    
    /*
    while(!token.empty()){
        check_Syntax();
    }*/
    
    //check_Syntax();
}
