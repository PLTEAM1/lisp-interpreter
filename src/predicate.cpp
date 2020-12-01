
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
    int index = 0;
    int count = 0;
    
    int isSetq = 0;

    //count는 다 셌는데, 할당이 문제임 한개는 괜찮은데 두개부터가..
    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);
            //index++;

            if(token[i].second=="("){
                leftCount++;
                check++;
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
                    check--;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(check == 0){

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
    int index = 0;
    int count = 0;
    
    int isSetq = 0;

    //count는 다 셌는데, 할당이 문제임 한개는 괜찮은데 두개부터가..
    for(int i = 1 ; i < token.size(); i++){

            newToken.push_back(token[i]);
            //index++;

            if(token[i].second=="("){
                leftCount++;
                check++;
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
                    check--;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(check == 0){

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
                    /*
                    else if(){
                        //문자일 때
                        item.add("IS CHAR");
                    }
                    아래는 else로 묶기
                    */
                    item.add(token[i].second);
                    newToken.clear();
                    count++;
                }

            }
            
    }
    //cout << "here: " << newToken.back().second << endl;
    //cout << "new : ";
    //item.traverse(item.getHead());
    //cout << endl;
    //temp.getHead();
   
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
        if(temp.isList() == 0)  ret.add("T"); // var에 저장되어있었다는건 어떤 symbol이라는 뜻
        else    ret.add("NIL");
    }
    return ret;
    
    /*
    Syntax syntax;
    List ret;
    string value;
    List temp;

    vector< pair<int, string> > newToken;
    int leftCount = 0;
    int check = 0;
    int index = 0;

    for(int i = 1 ; i < token.size(); i++){
        //cout << token[i].second << endl;
        if(check < 1){
            check++;
            newToken.push_back(token[i]);
            if(token[i].second=="("){
                leftCount++;
            }
            
            if(token[i].second==")"){
                if(leftCount == 1 ){
                    i += index;
                    //cout << "i : " << i << endl;
                    //cout << token[i].second << endl;
                    temp = syntax.analyze(newToken, variables);
                    //temp.traverse(temp.getHead());
                    newToken.clear();
                    //check = 1;
                }else{
                    leftCount--;
                }
            }
        }else{
            throw Exception(100);
        }
        
    }
    
    Syntax syntax;
    List ret;
    string value;

    List temp;
    if(token[1].second =="("){
        //함수일 때
        token.erase(token.begin());
        temp = syntax.analyze(token, variables);
    }else{
        value = token[1].second;
        if(value == "NIL"){
            ret.add("T");
            return ret;
        }
        if(value == "#" || value =="\'"){
            ret.add("NIL");
            return ret;
        }

        temp = numberp(token, variables);
        if(temp.getHead()->data =="T"){
                ret.add("NIL");
                return ret;
        }
        
        temp = getValue(variables, token[1].second);

        //변수가 존재하지 않을 때
        if(temp.getHead()==NULL){
            ret.add("No variable 4");
            return ret;
        }
    }
    if(temp.isList() == 0){
        if(temp.getHead()->data =="NIL"){
            ret.add("T");
            return ret;
        }else{
            ret.add("NIL");
            return ret;
        }
         
    }else{
        ret.add("NIL");
        return ret;
    }
*/
}

List Predicate::numberp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* NUMBERP
         * X가 숫자일 때만 참(true)을 반환함. */
    Syntax syntax;
    List ret;
    string value;
    bool flag;

    List temp;

    if(token[1].second =="("){
        //함수일 때
        token.erase(token.begin());
        temp = syntax.analyze(token, variables);
    }else{

        value = token[1].second;

        flag = isNumber(value);

        if(flag){
            ret.add("T");
            return ret;
        }else{
            // 쌩 값이 아니라면 변수 참조 = 함수일 때
            temp = getValue(variables, token[1].second);

            //변수가 존재하지 않을 때
            if(temp.getHead()==NULL){
                ret.add("No variable 3");
                return ret;
            }
        }
    }
    
    if(temp.isList() == 0){

        flag = isNumber(temp.getHead()->data);

        if(flag){
            ret.add("T");
            return ret;
        }else{
            ret.add("NIL");
            return ret;
        }
    }else{
        ret.add("NIL");
        return ret;
    }
        
}

List Predicate::zerop(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* ZEROP 
         * X가 0일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    Syntax syntax;
    List ret;
    string value;
    bool flag;

    List temp;

    if(token[1].second =="("){
        //함수일 때
        token.erase(token.begin());
        temp = syntax.analyze(token, variables);
    }else{

        value = token[1].second;
        flag = isNumber(value);

        if(flag){
            if(value == "0"){
                ret.add("T");
                return ret;
            }else{
                ret.add("NIL");
                return ret;
            }
        }else{
            // 쌩 값이 아니라면 변수 참조
            if(value == "#" || value =="\'"){
                ret.add("Not a number");
                return ret;
            }
            temp = getValue(variables, token[1].second);

            //변수가 존재하지 않을 때
            if(temp.getHead()==NULL){
                ret.add("No variable 2");
                return ret;
            }
        }
    }
    if(temp.isList() == 0){
        
        flag = isNumber(temp.getHead()->data);
        if(flag){
            if(temp.getHead()->data == "0"){
                ret.add("T");
                return ret;
            }else{
                ret.add("NIL");
                return ret;
            } 
        }else{
            ret.add("Not a number");
            return ret;
        }
    }else{
        ret.add("Not a Number");
        return ret;
    }

}

//****op 어쩌구 지워야대 다시 생각 고~~~*********

List Predicate::minusp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* MINUSP 
         * X가 음수일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    Syntax syntax;
    List ret;
    string value;
    bool flag;
    
    List temp;

    if(token[1].second =="("){
        //함수일 때
        token.erase(token.begin());
        temp = syntax.analyze(token, variables);
    }else{
       
        value = token[1].second;

        flag = isNumber(value);

        if(flag){
            if( value[0] == '-'){
                ret.add("T");
                return ret;
            }else{
                ret.add("NIL");
                return ret;
            }
        }else{
            // 쌩 값이 아니라면 변수 참조 = 함수일 때
            if(value == "#" || value =="\'"){
                ret.add("Not a number");
                return ret;
            }

            temp = getValue(variables, token[1].second);

            //변수가 존재하지 않을 때
            if(temp.getHead()==NULL){
                ret.add("No variable 1");
                return ret;
            }
        }
    }
    if(temp.isList() == 0){
        
        flag = isNumber(temp.getHead()->data);
        if(flag){
            if( temp.getHead()->data[0] == '-'){
                ret.add("T");
                return ret;
            }else{
                ret.add("NIL");
                return ret;
            }
        }else{
            ret.add("Not a number");
            return ret;
        }
    }else{
        ret.add("Not a Number");
        return ret;
    }

}

List Predicate::equal(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* EQAUL 
         * X와 Y가 같으면 참(true)을 반환함. 아니면 NIL */
    //Syntax syntax;
    //string value = token[1].second;
    //string compared = token[2].second;

}

List Predicate::isLess(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* < 
         * X < Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    Syntax syntax;
    string value = token[1].second;
    string compared = token[2].second;
    
}

List Predicate::isGreater(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* >=
         * X >= Y 이면 참(true)을 반환함. 숫자가 아니면 error */
    Syntax syntax;
    string value = token[1].second;
    string compared = token[2].second;
  
}

List Predicate::stringp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* STRINGP */
    Syntax syntax;
    List ret;
    string value;
    bool flag;
    
    List temp;

    if(token[1].second =="("){
        //함수일 때
        token.erase(token.begin());
        temp = syntax.analyze(token, variables);
    }else{
        if(token[1].first == 12){
            ret.add("T");
            return ret;
        }else{
            temp = atom(token, variables);
            if(temp.getHead()->data == "T" || temp.getHead()->data == "NIL"){
                ret.add("NIL");
                return ret;
            }

            temp = getValue(variables, token[1].second);

            //변수가 존재하지 않을 때
            if(temp.getHead()==NULL){
                ret.add("No variable 1");
                return ret;
            }
        }
    }
    if(temp.isList() == 0){
        
        string var = temp.getHead()->data;
        if(var[0] == '"' && var[temp.getSize()-1] == '"'){
            ret.add("T");
            return ret;
        }else{
            ret.add("NIL");
            return ret;
        }
    }else{
        ret.add("NIL");
        return ret;
    }
}
