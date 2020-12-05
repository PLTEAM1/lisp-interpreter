
#include "../header/Predicate.h"
#include "../header/Lexer.h"
#include "../header/Exception.h"
#include <iostream>

/**********************************************************/
/* isNumber, getValue, getArr, delVar
   - Sub functions to helping predicate's functions.  */
/**********************************************************/

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
    return ret;
}

void Predicate::delVar(vector< pair<string, List> > *variables, int count){
    for(int k = 0 ; k < count ;k++){
        variables->pop_back();
    }
}  

/**********************************************************/
/* atom - returns T when the variable is symbol  
            returns NIL when the variable is a list   */
/**********************************************************/
List Predicate::atom(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
 
    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;

    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if( (token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    symbolFlag = 1;
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==13  || token[i].first == 30 || token[i].second =="NIL"){
                        symbolFlag =1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
    }

    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "'") ret.add("NIL");
            else ret.add("T");
        }else{

            List temp;
            temp = getValue(variables, value);
            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.getFlag() == 1)  ret.add("NIL"); 
            else    ret.add("T");
        }
    }else{
        if(item.getFlag()==1) ret.add("NIL");
        else ret.add("T");
    }
    
    return ret;
}

/**********************************************************/
/* null - return T when the variable is NIL */
/**********************************************************/
List Predicate::null(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    symbolFlag = 1;
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==13  || token[i].first == 30 || token[i].second =="NIL"){
                        symbolFlag =1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }
                
            }
            
    }
    
    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "NIL") ret.add("T"); 
            else ret.add("NIL");
        }else{

            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.getHead()->data == "NIL")  ret.add("T");
            else    ret.add("NIL");
        }
    }else{

        if(item.getHead()->data == "NIL") ret.add("T");
        else ret.add("NIL");
    }
    
    return ret;
}

/**********************************************************/
/* numberp - return T when the variable is number 
        return NIL when the parameter is not a number */
/**********************************************************/
List Predicate::numberp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* NUMBERP
         * X가 숫자일 때만 참(true)을 반환함. */

    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    symbolFlag = 1;
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10 || token[i].first == 12){
                        symbolFlag = 1;
                        item.add("IS NUMBER");
                    }else if(token[i].first == 13 || token[i].first == 30 || token[i].second == "NIL"){
                        symbolFlag =1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }

    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "IS NUMBER") ret.add("T");
            else ret.add("NIL");
        }else{

            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            string num = temp.getHead()->data;
            if(temp.getFlag() == 1 || temp.getFlag()== 2) ret.add("NIL");
            else if(num[0] == '-' || isdigit(num[0])) ret.add("T");
            else    ret.add("NIL");
        }
    }else{
        if(item.getFlag()== 1 || item.getFlag()== 2){
            ret.add("NIL");
        }
        else if(isNumber(item.getHead()->data)) ret.add("T");
        else ret.add("NIL");
    }
    
    return ret;
        
}

/**********************************************************/
/* null - return T when the variable is ZERO(0)
        return error when the parameter is not a number */
/**********************************************************/
List Predicate::zerop(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* ZEROP 
         * X가 0일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount== 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    symbolFlag = 1;
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10){
                        symbolFlag = 1;
                        if(token[i].second == "0") item.add("IS ZERO");
                        else item.add("IS NUMBER");

                    }else if(token[i].first == 12){
                        symbolFlag = 1;
                        if(token[i].second[0] == '0' && token[i].second[2]== '0' && token[i].second.length() ==3 ) item.add("IS ZERO");
                        else item.add("IS NUMBER");

                    }else if(token[i].first == 13 || token[i].first == 30 || token[i].second == "NIL"){
                        symbolFlag = 1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
    
    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "IS ZERO") ret.add("T"); 
            else if(value == "IS NUMBER") ret.add("NIL");
            else throw Exception(102);
        }else{

            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            string num = temp.getHead()->data;

            if(temp.getFlag() == 1 || temp.getFlag()== 2) throw Exception(102);
            else if(num[0] == '0'){
                if(num[1]=='.' && num[2]== '0' && num.length() == 3) ret.add("T");
                else if(num.length()==1) ret.add("T");
            }else if(isNumber(num)) ret.add("NIL");
            else throw Exception(102);

        }
    }else{
        if(item.getFlag()== 1 || item.getFlag()== 2){
            throw Exception(102);
        }

        string num = item.getHead()->data;
        if(num[0] == '0'){
                if(num[1]=='.' && num[2]== '0' && num.length() == 3) ret.add("T");
                else if(num.length()==1) ret.add("T");
        }else if(isNumber(num)) ret.add("NIL");
        else throw Exception(102);
    }
    
    return ret;
}

/**********************************************************/
/* minusp - return T when the variable is negative
        return error when the parameter is not a number */
/**********************************************************/
List Predicate::minusp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    /* MINUSP 
         * X가 음수일 때만 참(true)을 반환함. X가 숫자가 아니면 ERROR 발생. */
    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;
    
    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    item = getArr(i, token);
                    symbolFlag = 1;
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(token[i].first == 10 || token[i].first == 12){
                        symbolFlag = 1;
                        if(token[i].second[0]== '-') item.add("IS MINUS");
                        else    item.add("IS NUMBER");
                    }else if(token[i].first == 13 || token[i].first == 30 || token[i].second == "NIL"){
                        symbolFlag = 1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
            
    }
    
    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "IS MINUS") ret.add("T"); 
            else if(value == "IS NUMBER") ret.add("NIL");
            else throw Exception(102);
        }else{

            List temp;
            temp = getValue(variables, value);

            if(temp.getHead()==NULL) throw Exception(101);
            string num = temp.getHead()->data;

            if(temp.getFlag() == 1 || temp.getFlag()== 2) throw Exception(102);
            else if(num[0] == '-') ret.add("T");
            else if(isNumber(num)) ret.add("NIL");
            else throw Exception(102);

        }
    }else{
        if(item.getFlag()== 1 || item.getFlag()== 2){
            throw Exception(102);
        }

        string num = item.getHead()->data;
        if(num[0] == '-') ret.add("T");
        else if(isNumber(num)) ret.add("NIL");
        else throw Exception(102);
    }
    return ret;
    
}


/**********************************************************/
/* equal - return T when first and second parameter is same
        return NIL when they are different  */
/**********************************************************/
List Predicate::equal(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    List ret;

    Parser parser;
    List item;
    List compared;
    vector< pair<int, string> > newToken;

    int itemFlag = 0;
    int comparedFlag = 0;

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
                   
                    if(item.getSize()==0){
                        itemFlag = 1;
                        item = parser.analyze(newToken, variables);
                    } 
                    else{
                        comparedFlag =1;
                        compared = parser.analyze(newToken, variables);
                    }
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item = getArr(i, token);
                        
                    } 
                    else{
                        comparedFlag =1;
                        compared = getArr(i, token);
                    } 

                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item.add(token[i+1].second);
                        i++;
                        newToken.clear();
                    } 
                    else{
                        comparedFlag =1;
                        compared.add(token[i+1].second);
                        i++;
                    } 
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==30 ||token[i].first == 13 || token[i].second == "NIL"){
                        if(item.getSize()==0){
                            itemFlag = 1;
                            item.add(token[i].second);
                        } 
                        else{
                            comparedFlag = 1;
                            compared.add(token[i].second);
                        }
                    }else{
                        if(item.getSize()==0) item.add(token[i].second);
                        else compared.add(token[i].second);
                        
                    }

                    newToken.clear();
                    count++;
                }

            }
            
    }    
   
    if(count <= 1){
        delVar(variables, isSetq);
        throw Exception(100);
    }

    if(itemFlag == 1 && comparedFlag ==1){
        if(item.compare(item.getHead(), compared.getHead())) ret.add("T");
        else ret.add("NIL");
    }else if(itemFlag == 0 & comparedFlag == 1){
        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);

        if(item.getHead()==NULL) throw Exception(105);
        
        if(item.getFlag() == 1){
            item.insertValue("'", 0);
            item.insertValue("(", 1);
            item.insertValue(")", item.getSize());
        }
        else if(item.getFlag()==2){
            item.insertValue("#", 0);
            item.insertValue("(", 1);
            item.insertValue(")", item.getSize());
        }

        if(item.compare(item.getHead(), compared.getHead())) ret.add("T");
        else ret.add("NIL");

    }else if(itemFlag == 1 & comparedFlag == 0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);

        if(compared.getHead()==NULL) throw Exception(106);

        if(compared.getFlag() == 1){
            compared.insertValue("'", 0);
            compared.insertValue("(", 1);
            compared.insertValue(")", item.getSize());
        }
        else if(compared.getFlag()==2){
            compared.insertValue("#", 0);
            compared.insertValue("(", 1);
            compared.insertValue(")", compared.getSize());
        }

        if(item.compare(item.getHead(), compared.getHead())) ret.add("T");
        else ret.add("NIL");
    }else if(itemFlag == 0 & comparedFlag == 0){

        string itemData = item.getHead()->data;
        string comparedData = compared.getHead()->data;

        item = getValue(variables, itemData);
        compared = getValue(variables, comparedData);

        if(item.getHead()==NULL) throw Exception(105);      
        if(compared.getHead()==NULL) throw Exception(106);

        if(item.getFlag() != compared.getFlag()) ret.add("NIL");
        else if(item.compare(item.getHead(), compared.getHead())) ret.add("T");
        else ret.add("NIL"); 
    }
    
    return ret;
}

/**********************************************************/
/* < - return T when first param is less than second one.
        return NIL when they are not. 
        return error when they are not a number.   */
/**********************************************************/
List Predicate::isLess(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    List ret;

    Parser parser;
    List item;
    List compared;
    vector< pair<int, string> > newToken;

    // 0 = not symbol, 1 = symbol
    int itemFlag = 0;
    int comparedFlag = 0;

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
                   
                    if(item.getSize()==0){
                        itemFlag = 1;
                        item = parser.analyze(newToken, variables);
                    } 
                    else{
                        comparedFlag =1;
                        compared = parser.analyze(newToken, variables);
                    }
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item = getArr(i, token);
                        
                    } 
                    else{
                        comparedFlag =1;
                        compared = getArr(i, token);
                    } 

                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item.add(token[i+1].second);
                        i++;
                        
                    } 
                    else{
                        comparedFlag =1;
                        compared.add(token[i+1].second);
                        i++;
                    } 
                    count++;
                    newToken.clear();
                }
                else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==30 ||token[i].first == 13 || token[i].second == "NIL"){
                        if(item.getSize()==0){
                            itemFlag = 1;
                            item.add(token[i].second);
                        } 
                        else{
                            comparedFlag = 1;
                            compared.add(token[i].second);
                        }
                    }else{
                        if(item.getSize()==0) item.add(token[i].second);
                        else compared.add(token[i].second);
                        
                    }

                    newToken.clear();
                    count++;
                }

            }
            
    }    
    if(count <= 1){
        delVar(variables, isSetq);
        throw Exception(100);
    }

    if(itemFlag == 1 && comparedFlag ==1){
        
    }else if(itemFlag == 0 & comparedFlag == 1){

        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);

        if(item.getHead()==NULL) throw Exception(105);


    }else if(itemFlag == 1 & comparedFlag == 0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);

        if(compared.getHead()==NULL) throw Exception(106);

    }else if(itemFlag == 0 & comparedFlag == 0){
        string itemData = item.getHead()->data;
        string comparedData = compared.getHead()->data;

        item = getValue(variables, itemData);
        compared = getValue(variables, comparedData);

        if(item.getHead()==NULL) throw Exception(105);      
        if(compared.getHead()==NULL) throw Exception(106);
    }

    string pnum= item.getHead()->data;
    string qnum = compared.getHead()->data;

    if(!isNumber(pnum)) throw Exception(103);
    else if(!isNumber(qnum)) throw Exception(104);

    if(stof(pnum) < stof(qnum)) ret.add("T");
    else ret.add("NIL");

    return ret;
    
}

/**********************************************************/
/* >= - return T when first param is greater than second one.
        return NIL when they are not. 
        return error when they are not a number.   */
/**********************************************************/
List Predicate::isGreater(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    List ret;

    Parser parser;
    List item;
    List compared;
    vector< pair<int, string> > newToken;

    int itemFlag = 0;
    int comparedFlag = 0;

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
                   
                    if(item.getSize()==0){
                        itemFlag = 1;
                        item = parser.analyze(newToken, variables);
                    } 
                    else{
                        comparedFlag =1;
                        compared = parser.analyze(newToken, variables);
                    }
                    

                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){
                
                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item = getArr(i, token);
                        
                    } 
                    else{
                        comparedFlag =1;
                        compared = getArr(i, token);
                    } 

                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item.add(token[i+1].second);
                        i++;
                        
                    } 
                    else{
                        comparedFlag =1;
                        compared.add(token[i+1].second);
                        i++;
                    } 
                    newToken.clear();
                    count++;
                }else if(token[i].second!="EOF"){

                    if(count >= 2 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==30 ||token[i].first == 13 || token[i].second == "NIL"){
                        if(item.getSize()==0){
                            itemFlag = 1;
                            item.add(token[i].second);
                        } 
                        else{
                            comparedFlag = 1;
                            compared.add(token[i].second);
                        }
                    }else{
                        if(item.getSize()==0) item.add(token[i].second);
                        else compared.add(token[i].second);
                        
                    }

                    newToken.clear();
                    count++;
                }

            }
            
    }    

    if(count <= 1){
        delVar(variables, isSetq);
        throw Exception(100);
    }

    if(itemFlag == 1 && comparedFlag ==1){
        
    }else if(itemFlag == 0 & comparedFlag == 1){

        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);

        if(item.getHead()==NULL) throw Exception(105);


    }else if(itemFlag == 1 & comparedFlag == 0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);

        if(compared.getHead()==NULL) throw Exception(106);

    }else if(itemFlag == 0 & comparedFlag == 0){
        string itemData = item.getHead()->data;
        string comparedData = compared.getHead()->data;

        item = getValue(variables, itemData);
        compared = getValue(variables, comparedData);

        if(item.getHead()==NULL) throw Exception(105);      
        if(compared.getHead()==NULL) throw Exception(106);
    }

    string pnum= item.getHead()->data;
    string qnum = compared.getHead()->data;

    if(!isNumber(pnum)) throw Exception(103);
    else if(!isNumber(qnum)) throw Exception(104);

    if(stof(pnum) >= stof(qnum)) ret.add("T");
    else ret.add("NIL");

    return ret;
  
}


/**********************************************************/
/* stringp - return T when the variable is string.
        return NIL when they are not.   */
/**********************************************************/
List Predicate::stringp(vector< pair<int, string> > token, vector< pair<string, List> > *variables){

    List ret;

    Parser parser;
    List item;
    vector< pair<int, string> > newToken;

    int leftCount = 0;
    int check = 0;
    int count = 0;
    int symbolFlag = 0;
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

                    item = parser.analyze(newToken, variables);
                    symbolFlag = 1;
                    newToken.clear();
        
                    count++;
                    check++;
                    leftCount--;
                }else{
                    leftCount--;
                }
            }else if(leftCount == 0){

                if((token[i].second =="#" &&token[i+1].second =="(") || (token[i].second == "'" &&token[i+1].second =="(" ) ){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    symbolFlag = 1;
                    item = getArr(i, token);
                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){

                    symbolFlag = 1;
                    item.add(token[i+1].second);
                    i++;
                    newToken.clear();    
                    count++;
                }
                else if(token[i].second!="EOF"){

                    if(count >= 1 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    if(token[i].first == 30){
                        symbolFlag =1;
                        item.add("IS STRING");
                    }
                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==13 || token[i].second =="NIL"){
                        symbolFlag =1;
                        item.add(token[i].second);
                    }else{
                        item.add(token[i].second);
                    }
                    newToken.clear();
                    count++;
                }

            }
    }

    if(check == 0){
        string value = item.getHead()->data;
        if(symbolFlag){
            if(value == "IS STRING") ret.add("T"); 
            else ret.add("NIL");
        }else{

            List temp;
            temp = getValue(variables, value);
            if(temp.getHead()==NULL) throw Exception(101);
            if(temp.getHead()->data[0] == '\"')  ret.add("T"); 
            else    ret.add("NIL");
        }
    }else{
        if(item.getHead()->data == "\"") ret.add("T");
        else ret.add("NIL");
    }
    
    return ret;
}
