
#include "../header/Predicate.h"
#include "../header/Lexer.h"
#include "../header/Exception.h"
#include <iostream>

/* 예원 할 일 
    1. variable에서 참조해오는 것 // 완료 : numberp, zerop ,,, 마이너스 받아오기 에바 - 가 토큰임 
    2. ATOM, NULL 에서 다양한 처리 
    3. 안에 함수 들었을 때 syntax.analyze 들어가도록
    4. (ATOM (LIST 1 2)) 시 LIST 반환값에서 '붙여서 판별하기 */
    
// 주의점! 기본적으로 값 판별 -> 이후 변수테이블로 들어가기
// 쌩값인 경우에 어떤 식으로 나올 지 가늠이 안가므로 따로 뺴준거라고 볼 수 있음 / 함수를 콜하면 형식이 딱 딱 맞을 거니까...

bool Predicate::isNumber(string str){
    bool flag = true;
        for(int i = 0 ; i < str.size() ; i++){
            if(str[0] == '-' || str[0] == '+' || str[i] == '.') continue;
            if(isdigit(str[i]) != 1){
                flag = false;
                break;
            }
        }
    return flag;
}

List Predicate::getValue(vector< pair<string, List> > *variables, string isSymbol){
    int check = 0;

    for(int i = 0 ; i < (*variables).size() ; i++){
        if((*variables)[i].first == isSymbol){
            return (*variables)[i].second;
        }
    }
    return List();
}

List Predicate::getArr(int& index, vector< pair<int, string> > token){
    int leftCount = 0;
    List ret;

    for(int i = index ; i < token.size() ; i++){
        ret.add(token[i].second);

        if(token[i].second == "("){
            leftCount++;
        }
        if(token[i].second==")"){
            if(leftCount==1){
                index = i;
                return ret;
            }else{
                leftCount--;
            }
        }
    }
}

void Predicate::delVar(vector< pair<string, List> > *variables, int count){
    for(int k = 0 ; k < count ;k++){
        cout << "pop" << endl;
        variables->pop_back();
    }
}  


List Predicate::atom(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    // ATOM
    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;

    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12){
                        item.add("IS NUMBER");
                    }
                    else if(token[i].first == 13){
                        //문자일 때
                        item.add("IS CHAR");
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
   
    if(check == 0 ){
        string value = item.getHead()->data;
        if(value == "'") ret.add("NIL"); //리스트
        else if(value == "#") ret.add("T"); //배열
        else if(value == "IS NUMBER") ret.add("T");
        else if(value == "IS CHAR") ret.add("T");
        else if(value =="NIL") ret.add("T");
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.isList() == 0)  ret.add("T"); // var에 저장되어있었다는건 어떤 symbol이라는 뜻
            else    ret.add("NIL");
        }
    }else{
        if(item.isList()) ret.add("NIL");
        else ret.add("T");
    }
    
    return ret;
}

List Predicate::null(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* NULL 
        * X가 NIL일 때만 참(true)을 반환함. / 변수가 아니면 error */
    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);
            //index++;

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10 || token[i].first == 12){
                        item.add("IS NUMBER");
                    }else if(token[i].first == 13){
                        item.add("IS CHAR");
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
   
    if(check ==0 ){
        string value = item.getHead()->data;
        if(value == "'") ret.add("NIL");
        else if(value == "#") ret.add("NIL");
        else if(value == "IS NUMBER") ret.add("NIL");
        else if(value == "IS CHAR") ret.add("NIL");
        else if(value =="NIL") ret.add("T");
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.getHead()->data == "NIL")  ret.add("T"); // var에 저장되어있었다는건 어떤 symbol이라는 뜻
            else    ret.add("NIL");
        }
    }else{
        if(item.getHead()->data == "NIL") ret.add("T");
        else ret.add("T");
    }
    
    return ret;
}

List Predicate::numberp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* NUMBERP
         * X가 숫자일 때만 참(true)을 반환함. */

    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10 || token[i].first == 12){
                        item.add("IS NUMBER");
                    }else if(token[i].first == 13){
                        item.add("IS CHAR");
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }

    string value = item.getHead()->data;

    if(check ==0 ){
        if(value == "'") ret.add("NIL");
        else if(value == "#") ret.add("NIL");
        else if(value == "IS NUMBER") ret.add("T");
        else if(value == "IS CHAR") ret.add("NIL");
        else if(value =="NIL") ret.add("NIL");
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
    
            string num = temp.getHead()->data;
            if(num[0] == '-' || isdigit(num[0])) ret.add("T");
            else    ret.add("NIL");
        }
    }else{
        if(item.isList()){
            //배열일 때도 마찬가지
            ret.add("NIL");
        }
        else if(isNumber(item.getHead()->data)) ret.add("T");
        else ret.add("NIL");
    }
    
    return ret;
        
}

List Predicate::zerop(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* ZEROP 
         * X가 0일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount== 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10){
                        //일반 정수
                        if(token[i].second == "0") item.add("IS ZERO");
                        else item.add("IS NUMBER");

                    }else if(token[i].first == 12){
                        //실수
                        if(token[i].second[0] == '0' && token[i].second[2]== '0' && token[i].second.length() ==3 ) item.add("IS ZERO");
                        else item.add("IS NUMBER");

                    }else if(token[i].first == 13){
                        item.add("IS CHAR");
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
   
    if(check == 0 ){
        string value = item.getHead()->data;
        if(value == "IS ZERO") ret.add("T");
        else if(value == "IS NUMBER") ret.add("NIL");
        else if(value == "'") throw Exception(102);
        else if(value == "#") throw Exception(102);
        else if(value == "IS CHAR") throw Exception(102);
        else if(value =="NIL") throw Exception(102);
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            
            //정수 실수의 판별이 필요합니다..
            string num = temp.getHead()->data;
            if(num[0] == '0'){
                if(num[1]=='.' && num[2]== '0' && num.length() == 3) ret.add("T");
                else if(num.length()==1) ret.add("T");
            }else if(isNumber(num)) ret.add("NIL");
            else throw Exception(102);
        
        }
    }else{
        string funcVal = item.getHead()->data;
        if(item.isList()){
            //배열일 때에도!
            throw Exception(102);
        }
        else if(funcVal[0] == '0'){
                if(funcVal[1]=='.' && funcVal[2]== '0' && funcVal.length() == 3) ret.add("T");
                else if(funcVal.length()==1) ret.add("T");
        }else if(isNumber(funcVal)) ret.add("NIL");
        else throw Exception(102);

    }
    
    return ret;

}

List Predicate::minusp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* MINUSP 
         * X가 음수일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;
    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10 || token[i].first == 12){
                        if(token[i].second[0]== '-') item.add("IS MINUS");
                        else    item.add("IS NUMBER");
                    }else if(token[i].first == 13){
                        item.add("IS CHAR");
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
   
    if(check == 0 ){
        string value = item.getHead()->data;
        if(value == "IS MINUS") ret.add("T");
        else if(value == "IS NUMBER") ret.add("NIL");
        else if(value == "'") throw Exception(102);
        else if(value == "#") throw Exception(102);
        else if(value == "IS CHAR") throw Exception(102);
        else if(value =="NIL") throw Exception(102);
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
    
            string num = temp.getHead()->data;
            if(num[0] == '-') ret.add("T");
            else if(isNumber(num)) ret.add("NIL");
            else throw Exception(102);
        }
    }else{
        string funcVal = item.getHead()->data;
        if(item.isList()){
            //배열일 때에도!
            throw Exception(102);
        }
        else if(funcVal[0] == '-'){
            ret.add("T");
        }else if(isNumber(funcVal)) ret.add("NIL");
        else throw Exception(102);
    }
    return ret;
}

List Predicate::equal(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* EQAUL 
         * X와 Y가 같으면 참(true)을 반환함. 아니면 NIL */
    List ret;

    Syntax syntax;
    List item;
    List compared;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }
                   
                    if(item.getSize()==0) item = syntax.analyze(newToken, variables);
                    else compared = syntax.analyze(newToken, variables);
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0) item = getArr(i, token);
                    else compared = getArr(i, token);

                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    if(item.getSize()==0) item.add(token[i].second);
                    else compared.add(token[i].second);

                    newToken.clear();
                    count++;
                }

            }
            
    }    

    if(item.compare(item.getHead(), compared.getHead())) ret.add("T");
    else ret.add("NIL");
    
    return ret;
}

List Predicate::isLess(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* < 
         * X < Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    List ret;

    Syntax syntax;
    List item;
    List compared;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }
          
                    if(item.getSize()==0) item = syntax.analyze(newToken, variables);
                    else compared = syntax.analyze(newToken, variables);
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0) item = getArr(i, token);
                    else compared = getArr(i, token);

                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    if(item.getSize()==0) item.add(token[i].second);
                    else compared.add(token[i].second);

                    newToken.clear();
                    count++;
                }

            }
            
    }    

    if(item.getSize() != 1) throw Exception(103);
    else if(item.getSize() != 1) throw Exception(104);
    else{
        string pnum= item.getHead()->data;
        string qnum = compared.getHead()->data;

        if(!isNumber(pnum)) throw Exception(103);
        else if(!isNumber(qnum)) throw Exception(104);

        if(stof(pnum) < stof(qnum)) ret.add("T");
        else ret.add("NIL");

    }

    return ret;
    
}

List Predicate::isGreater(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* >=
         * X >= Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    List ret;

    Syntax syntax;
    List item;
    List compared;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }
          
                    if(item.getSize()==0) item = syntax.analyze(newToken, variables);
                    else compared = syntax.analyze(newToken, variables);
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0) item = getArr(i, token);
                    else compared = getArr(i, token);

                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    if(item.getSize()==0) item.add(token[i].second);
                    else compared.add(token[i].second);

                    newToken.clear();
                    count++;
                }

            }
            
    }    

    if(item.getSize() != 1) throw Exception(103);
    else if(item.getSize() != 1) throw Exception(104);
    else{
        string pnum= item.getHead()->data;
        string qnum = compared.getHead()->data;

        if(!isNumber(pnum)) throw Exception(103);
        else if(!isNumber(qnum)) throw Exception(104);

        if(stof(pnum) >= stof(qnum)) ret.add("T");
        else ret.add("NIL");

    }

    return ret;
  
}

List Predicate::stringp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* STRINGP */
    List ret;

    Syntax syntax;
    List item;
    vector< pair<int, string> > newToken;

    int leftCount = 0;
    int check = 0;
    int count = 0;
    
    int isSetq = 0;

    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);

            if(token[i].second=="("){
                leftCount++;
            }
            else if(token[i].second==")"){
                if(leftCount == 1){
                    
                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(newToken[1].second == "SETQ"){
                        isSetq++;
                    }

                    item = syntax.analyze(newToken, variables);
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if(token[i].second =="#" || token[i].second == "'" ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 30) item.add("IS STRING");
                    else if(token[i].first == 10 || token[i].first == 12) item.add("IS NUMBER");
                    else if(token[i].first == 13) item.add("IS CHAR");
                    else item.add(token[i].second);
                    
                    newToken.clear();
                    count++;
                }

            }
            
    }
   
    if(check == 0 ){
        string value = item.getHead()->data;
        if(value == "IS STRING") ret.add("T");
        else if(value == "'") ret.add("NIL"); //리스트
        else if(value == "#") ret.add("NIL"); //배열
        else if(value == "IS NUMBER") ret.add("NIL");
        else if(value == "IS CHAR") ret.add("NIL");
        else if(value =="NIL") ret.add("NIL");
        else{
            //변수인지 확인
            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.getHead()->data == "\"") ret.add("T");
            else ret.add("NIL");
        }
    }else{
        if(item.getHead()->data == "\"") ret.add("T");
        else ret.add("NIL");
    }
    
    return ret;
}
