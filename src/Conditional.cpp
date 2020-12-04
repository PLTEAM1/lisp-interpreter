////
////  conditional.cpp
////  pl
////
////  Created by 최용렬 on 2020/11/17.
////
//
//#include "../header/Conditional.h"
//#include "../header/Syntax.h"
//#include "../header/Lisplist.h"
//#include <iostream>
//
///*  IF또는 COND를 봤을때 넘어온다고 가정
//    ex) IF (> X 3) (PRINT X))
//    ex) COND ((> X 0) (+ X 1))  ; X 가 0보다 크면 X 값에 1을 더함
//            ((= X 0) (+ X 2))  ; X 가 0이면 X 값에 2을 더함
//            ((< X 0) (+ X 3)))
// */
//string Conditional::_IF(vector< pair<int, string> > t,vector< pair<string, List> > *variables){
//    Syntax syntax;
//
//    /* IF */
//
//    /* 파라미터로 넘어온 토큰중 조건문, 수행문을 괄호에 맞춰서 스택에 넣는 작업
//        ex) token = (> X 3) // syntax_check를 위해서 pair<int,string>으로 추가
//        ex) stack[0] = (> X 3) <- token의 형식(즉, pair<int,string>
//            stack[1] = (+ X 1)
//     */
//    vector<pair<int,string>> token;
//    vector<vector<pair<int,string>>> stack;
//
//    for(int i = 0; i < t.size(); i++){
//        if(t[i].second == "("){
//            for(int j = i; j < t.size(); j++){
//                if(t[j].second == ")"){
//                    token.push_back(t[j]);
//                    stack.push_back(token);
//                    token.clear();
//                    i = j;
//                    break;
//                }//if ) end
//                token.push_back(t[j]);
//            }//for loop end
//        }//if ( end
//        else if(t[i].second == ")"){
//            break;
//        }//else if ) end
//    }//for loop end
//
//    //넘겨줄때는 > X 0)을 넘겨줌
//    stack[0].erase(stack[0].begin());
//
//    //파라미터가 2개일때, 즉 참이면 수행문, 거짓이면 NIL 출력
//    if(stack.size() == 2){
//        cout << "\n파라미터 2개";
//        if(syntax.analyze(stack[0], variables) == "TRUE"){
//            cout << "조건문 TRUE\n";
//            stack[1].erase(stack[1].begin());
//            syntax.analyze(stack[1], variables);
//        }//if true end
//        else if(syntax.analyze(stack[0], variables) == "FALSE"){
//            cout << "NIL\n";
//        }//else if false end
//    }//파라미터가 2개일때 if end
//
//    //파라미터가 3개일때, 즉 참이면 참 수행문, 거짓이면 거짓 수행문
//    else if(stack.size() == 3){
//        cout << "파라미터 3개\n";
//        if(syntax.analyze(stack[0], variables) == "TRUE"){
//            cout << "조건문 TRUE\n";
//            stack[1].erase(stack[1].begin());
//            syntax.analyze(stack[1], variables);
//        }//if true end
//        else if(syntax.analyze(stack[0], variables) == "FALSE"){
//            cout << "조건문 FALSE\n";
//            stack[2].erase(stack[2].begin());
//            syntax.analyze(stack[2], variables);
//        }//else if false end
//    }//파라미터가 3개일때 else if end
//
//    return "";
//}
//
//string Conditional::_COND(vector< pair<int, string> > t,vector< pair<string, string> > *variables){
//
//    /* COND */
//    Syntax syntax;
//
//    /* 파라미터로 넘어온 토큰중 조건문, 수행문을 괄호에 맞춰서 스택에 넣는 작업
//        ex) token = (> X 3) // syntax_check를 위해서 pair<int,string>으로 추가
//        ex) stack[0] = (> X 3) <- token의 형식(즉, pair<int,string>
//            stack[1] = (+ X 1)
//        ex) stack_COND[0] = (> X 0) (+ X 1) <- stack_COND[0][0] = (> X 0), stack_COND[0][1] = (+ X 1)
//            stack_COND[1] = (= X 0) (+ X 2)
//            stack_COND[2] = (< X 0) (+ X 3)
//     */
//    vector<pair<int,string>> token;
//    vector<vector<pair<int,string>>> stack;
//    vector<vector<vector<pair<int,string>>>> stack_COND;
//
//    for(int i = 0; i < t.size(); i++){
//        if(t[i].second == "("){
//            for(int j = i; j < t.size(); j++){
//                if(t[j].second == ")"){
//                    token.push_back(t[j]);
//                    stack.push_back(token);
//                    token.clear();
//                    i = j;
//                    break;
//                }//if ) end
//                token.push_back(t[j]);
//            }//for loop end
//        }//if ( end
//        else if(t[i].second == ")"){
//            if(t[i+1].second == "("){
//                stack[0].erase(stack[0].begin());
//                stack_COND.push_back(stack);
//                stack.clear();
//            }//if ( end
//            else if(t[i+1].second == ")"){
//                stack[0].erase(stack[0].begin());
//                stack_COND.push_back(stack);
//                break;
//            }//if ) end
//        }//else if ) end
//    }//for loop end
//
//    for(int i = 0; i <= stack_COND.size(); i++){
//        if(i == stack_COND.size()){
//            cout << "맞는 조건이 없음 return 은 생각 해봐야함\n";
//            return "CONDITIONAL ERROR";
//            break;
//        }//if stack_COND.size() end
//        stack_COND[i][0].erase(stack_COND[i][0].begin());
//        if(syntax.analyze(stack_COND[i][0], variables) == "TRUE"){
//            stack_COND[i][1].erase(stack_COND[i][1].begin());
//            syntax.analyze(stack_COND[i][1], variables);// 수행문 실행
//            break;
//        }//if TRUE end
//    }//for loop end
//    return "";
//}
//
