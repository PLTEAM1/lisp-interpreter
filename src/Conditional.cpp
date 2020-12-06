//
//  conditional.cpp
//  pl
//
//  Created by 최용렬 on 2020/11/17.
//

#include "../header/Conditional.h"
#include "../header/Parser.h"
#include "../header/Lisplist.h"
#include "../header/Exception.h"
#include <iostream>

/*
    IF함수 (조건문) (수행문) 으로 이루어져 있다.
    조건문에서 NIL이 아닌, 변수, 리스트, 배열 등은 모두 참이라고 간주한다.
    파라미터가 2개인 경우 참이면 수행문 수행, 거짓이면 NIL 반환
    ex) (IF (> X 3) (+ X 3))
    파라미터가 3개인 경우 참이면 첫번째 수행문 수행, 거짓이면 두번째 수행문 수행
    ex) (IF (> X 3) (+ X 3) (+ X 4))
 */
List Conditional::_IF(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    vector< vector< pair<int, string> > > params;
    List result;

    for(int i = 1; i < token.size(); i++){//파라미터들을 벡터에넣는 작업
        int Paren = 0;
        
        if(token[i].second == "("){
            Paren++;
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            for(int j = i+1; j < token.size(); j++){
                if(Paren == 0){
                    i = j-1;
                    break;
                }
                else
                    param.push_back(token[j]);
                
                if(token[j].second == "(")
                    Paren++;
                else if(token[j].second == ")")
                    Paren--;
            }
            params.push_back(param);
        }
        else if(token[i].first == 11){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
    }
    
    if(!(params.size() == 2 || params.size() == 3)){
        //error 파라미터 개수는 2개 또는 3개만 가능
        throw Exception(56);
    }
    
    //cout << "param size : " << params.size() << endl;
    List condition;
    condition = parser.analyze(params[0], variables);
    
    if(params.size() == 2){ // 파라미터의 개수가 2개일때
        if(condition.getFlag() == 0){ // 심볼이면서 값이 "NIL"일때
            if(condition.getHead()->data == "NIL"){
                //NIL을 출력
                result.add("NIL");
            }
            else{ // 그 외의 경우
                result = parser.analyze(params[1], variables);
            }
        }
        else{ // 그 외의 경우
            result = parser.analyze(params[1], variables);
        }
    }
    else if(params.size() == 3){ // 파라미터의 개수가 3개일때
        if(condition.getFlag() == 0){ // 심볼이면서 값이 "NIL"일때
            if(condition.getHead()->data == "NIL"){
                //NIL일때의 statement실행
                result = parser.analyze(params[2], variables);
            }
            else{ // 그 외의 경우
                result = parser.analyze(params[1], variables);
            }
        }
        else{ // 그 외의 경우
            result = parser.analyze(params[1], variables);
        }
    }
    return result;
}

/*
    COND함수는 ((조건문 1) (수행문 1) ...) ((조건문 2) (수행문 2) ...) ...)
    으로 이루어져 있다. 조건문의 개수는 정해져 있지 않으며, 조건문이 참이면 그 조건문에 맞는 수행문을 모두 수행한다.
    조건문은 앞에서 부터 검사를 하고 참이면 즉시 반환한다.
    모든 조건문을 검사 했을, 전부 거짓이면 NIL을 반환한다.
 
    ex) (COND ((> X 0) (+ X 1))  ; X 가 0보다 크면 X 값에 1을 더함
              ((= X 0) (+ X 2))  ; X 가 0이면 X 값에 2을 더함
              ((< X 0) (+ X 3)))
 */
List Conditional::_COND(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    vector< vector< pair<int, string> > > params;
    List result;
    int nil_check = 0;

    for(int i = 0; i < token.size(); i++){//파라미터들을 벡터에넣는 작업, (조건문, 수행문...)쌍
        int Paren = 0;
        
        if(token[i].second == "("){
            Paren++;
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            for(int j = i+1; j < token.size(); j++){
                if(Paren == 0){
                    i = j-1;
                    break;
                }
                else
                    param.push_back(token[j]);
                
                if(token[j].second == "(")
                    Paren++;
                else if(token[j].second == ")")
                    Paren--;
            }
            params.push_back(param);
        }
        else if(token[i].first == 11){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
    }
    
    for(int i = 0; i < params.size(); i++){// (조건문, 수행문...)쌍을 각각 나누어서 temp에 추가
        vector< pair<int, string> > condition;
        vector< vector< pair<int, string> > > temp, statement;
        
        for(int j = 1; j < params[i].size(); j++){
            int Paren = 0;
            
            if(params[i][j].second == "("){
                Paren++;
                vector< pair<int, string> > param;
                param.push_back(params[i][j]);
                for(int k = j+1; j < params[i].size(); k++){
                    if(Paren == 0){
                        j = k-1;
                        break;
                    }
                    else
                        param.push_back(params[i][k]);
                    
                    if(params[i][k].second == "(")
                        Paren++;
                    else if(params[i][k].second == ")")
                        Paren--;
                }
                temp.push_back(param);
            }
            else if(params[i][j].first == 11){
                vector< pair<int, string> > param;
                param.push_back(params[i][j]);
                temp.push_back(param);
            }
        }
        condition = temp[0]; // temp에서 첫번째는 무조건 조건문
        for(int i = 1; i < temp.size(); i++){// 두번째 부터 모두 수행문
            statement.push_back(temp[i]);
        }
        List con_list = parser.analyze(condition, variables);

        if(con_list.getFlag() == 0){ // 심볼이면서 값이 "NIL"일때
            if(con_list.getHead()->data == "NIL"){
                //NIL을 출력
            }
            else{ // 그 외의 경우
                for(int i = 0; i < statement.size(); i++){
                    result = parser.analyze(statement[i], variables);
                    if(i == statement.size()-1)
                        result = parser.analyze(statement[i], variables);
                }
                nil_check++;
                break;
            }
        }
        else{ // 그 외의 경우
            for(int i = 0; i < statement.size(); i++){
                parser.analyze(statement[i], variables);
                if(i == statement.size()-1)
                    result = parser.analyze(statement[i], variables);
            }            nil_check++;
            break;
        }
    }
    if(nil_check == 0){
        result.add("NIL");
    }
    
    return result;
}
