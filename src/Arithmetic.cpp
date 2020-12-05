//
//  Arithmetic.cpp
//  pl
//
//  Created by 최용렬 on 2020/12/05.
//

#include "../header/Arithmetic.h"
#include "../header/Parser.h"
#include "../header/Lexer.h"
#include "../header/Exception.h"


List Arithmetic::add(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    Lexer lexer;
    vector< vector< pair<int, string> > > params;
    vector<double> sum_param;
    List result;
    
    for(int i = 1; i < token.size()-2; i++){
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
        else if(token[i].first == 10 || token[i].first == 12){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
        else{
            //산술연산의 파라미터는 number만 가능
            throw Exception(60);
        }
    }
    
    for(int i = 0; i < params.size(); i++){
        vector< pair<int, string> > param;
        if(params[i].size() == 1){// 파라미터가 변수이름, number일때
            if(params[i][0].first == 11){// 변수일때
                List param_list = parser.analyze(params[i], variables);
                if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                    sum_param.push_back(stod(param_list.getHead()->data));
                }
                else{//변수에 number가 아닌 list, array가 있을때
                    throw Exception(60);
                }
            }
            else if(params[i][0].first == 10 || params[i][0].first == 12){// number일때
                sum_param.push_back(stod(params[i][0].second));
            }
            else{//그 외
                throw Exception(60);
            }
        }
        else{// 파라미터의 길이가 1이 아닐때, 괄호로 묶인 함수가 나오는 경우
            List param_list = parser.analyze(params[0], variables);
            if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                sum_param.push_back(stod(param_list.getHead()->data));
            }
            else{//변수에 number가 아닌 list, array가 있을때
                throw Exception(60);
            }
        }
    }
    double sum = 0;
    for(auto &p : sum_param){
        sum += p;
    }
    string sum_str = to_string(sum);
    sum_str = lexer.removeZeroFloat(sum_str);

    if(sum_str[sum_str.length()-1] == '.'){
        sum_str.erase(sum_str.length()-1);
    }
    
    result.setFlag(0);
    result.add(sum_str);
    
    return result;
}

List Arithmetic::sub(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    Lexer lexer;
    vector< vector< pair<int, string> > > params;
    vector<double> sum_param;
    List result;
    
    for(int i = 1; i < token.size()-2; i++){
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
        else if(token[i].first == 10 || token[i].first == 12){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
        else{
            //산술연산의 파라미터는 number만 가능
            throw Exception(60);
        }
    }
    
    for(int i = 0; i < params.size(); i++){
        vector< pair<int, string> > param;
        if(params[i].size() == 1){// 파라미터가 변수이름, number일때
            if(params[i][0].first == 11){// 변수일때
                List param_list = parser.analyze(params[i], variables);
                if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                    sum_param.push_back(stod(param_list.getHead()->data));
                }
                else{//변수에 number가 아닌 list, array가 있을때
                    throw Exception(60);
                }
            }
            else if(params[i][0].first == 10 || params[i][0].first == 12){// number일때
                sum_param.push_back(stod(params[i][0].second));
            }
            else{//그 외
                throw Exception(60);
            }
        }
        else{// 파라미터의 길이가 1이 아닐때, 괄호로 묶인 함수가 나오는 경우
            List param_list = parser.analyze(params[0], variables);
            if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                sum_param.push_back(stod(param_list.getHead()->data));
            }
            else{//변수에 number가 아닌 list, array가 있을때
                throw Exception(60);
            }
        }
    }
    
    double sub = 0;
    for(auto &i: sum_param){
        sub -= i;
    }
    sub = sub + sum_param[0] + sum_param[0];
    
    string sum_str = to_string(sub);
    sum_str = lexer.removeZeroFloat(sum_str);

    if(sum_str[sum_str.length()-1] == '.'){
        sum_str.erase(sum_str.length()-1);
    }
    
    result.setFlag(0);
    result.add(sum_str);
    
    return result;
}

List Arithmetic::mul(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    Lexer lexer;
    vector< vector< pair<int, string> > > params;
    vector<double> sum_param;
    List result;
    
    for(int i = 1; i < token.size()-2; i++){
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
        else if(token[i].first == 10 || token[i].first == 12){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
        else{
            //산술연산의 파라미터는 number만 가능
            throw Exception(60);
        }
    }
    
    for(int i = 0; i < params.size(); i++){
        vector< pair<int, string> > param;
        if(params[i].size() == 1){// 파라미터가 변수이름, number일때
            if(params[i][0].first == 11){// 변수일때
                List param_list = parser.analyze(params[i], variables);
                if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                    sum_param.push_back(stod(param_list.getHead()->data));
                }
                else{//변수에 number가 아닌 list, array가 있을때
                    throw Exception(60);
                }
            }
            else if(params[i][0].first == 10 || params[i][0].first == 12){// number일때
                sum_param.push_back(stod(params[i][0].second));
            }
            else{//그 외
                throw Exception(60);
            }
        }
        else{// 파라미터의 길이가 1이 아닐때, 괄호로 묶인 함수가 나오는 경우
            List param_list = parser.analyze(params[0], variables);
            if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                sum_param.push_back(stod(param_list.getHead()->data));
            }
            else{//변수에 number가 아닌 list, array가 있을때
                throw Exception(60);
            }
        }
    }
    
    double mul = sum_param[0];
    for(int i = 1; i < sum_param.size(); i++){
        mul *= sum_param[i];
    }
    
    string sum_str = to_string(mul);
    sum_str = lexer.removeZeroFloat(sum_str);

    if(sum_str[sum_str.length()-1] == '.'){
        sum_str.erase(sum_str.length()-1);
    }
    
    result.setFlag(0);
    result.add(sum_str);
    
    return result;
}

List Arithmetic::div(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    Parser parser;
    Lexer lexer;
    vector< vector< pair<int,string> > > params;
    vector<double> sum_param;
    List result;
    
    for(int i = 1; i < token.size()-2; i++){
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
        else if(token[i].first == 10 || token[i].first == 12){
            vector< pair<int, string> > param;
            param.push_back(token[i]);
            params.push_back(param);
        }
        else{
            //산술연산의 파라미터는 number만 가능
            throw Exception(60);
        }
    }
    
    for(int i = 0; i < params.size(); i++){
        vector< pair<int, string> > param;
        if(params[i].size() == 1){// 파라미터가 변수이름, number일때
            if(params[i][0].first == 11){// 변수일때
                List param_list = parser.analyze(params[i], variables);
                if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                    sum_param.push_back(stod(param_list.getHead()->data));
                }
                else{//변수에 number가 아닌 list, array가 있을때
                    throw Exception(60);
                }
            }
            else if(params[i][0].first == 10 || params[i][0].first == 12){// number일때
                sum_param.push_back(stod(params[i][0].second));
            }
            else{//그 외
                throw Exception(60);
            }
        }
        else{// 파라미터의 길이가 1이 아닐때, 괄호로 묶인 함수가 나오는 경우
            List param_list = parser.analyze(params[0], variables);
            if(param_list.getFlag() == 0){//변수를 확인해서 변수에 number가 들어가 있을때
                sum_param.push_back(stod(param_list.getHead()->data));
            }
            else{//변수에 number가 아닌 list, array가 있을때
                throw Exception(60);
            }
        }
    }
    
    double div = sum_param[0];
    for(int i = 1; i < sum_param.size(); i++){
        if(sum_param[i] == 0){// 0으로 나눌 수 없음
            throw Exception(61);
        }
        div /= sum_param[i];
    }
    
    string sum_str = to_string(div);
    sum_str = lexer.removeZeroFloat(sum_str);

    if(sum_str[sum_str.length()-1] == '.'){
        sum_str.erase(sum_str.length()-1);
    }
    
    result.setFlag(0);
    result.add(sum_str);
    
    return result;
}
