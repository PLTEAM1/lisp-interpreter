#include "../header/Basic.h"
#include "../header/Exception.h"
#include <iostream>
#include <string>

/**********************************************************/
/* addQuoteList - a function to add quote list '(1 2 (3 4))
 returns next token index                      */
/**********************************************************/
int Basic::addQuoteList(vector< pair<int, string> > token, int index, class List& origin){
    origin.setFlag(1);
    for(int i = index; i < token.size() ; i++){
        if(token[i].second == "("){
            List newList;
            int ret = addQuoteList(token, i+1, newList);
            origin.addList(newList);
            i = ret;
            
        }else if(token[i].second == "\'"){
            List newList1, newList2;
            newList1.add(token[i].second);

            int ret = addQuoteList(token, i+2, newList2);
            newList1.addList(newList2);
            newList1.setFlag(1);
            origin.addList(newList1);
            i = ret;
            
        }else if(token[i].first == 26){
            i+=2;
            List newList;
            int ret = addQuoteList(token, i, newList);
            newList.setFlag(2);
            origin.addList(newList);
            i = ret;
            
        }else if(token[i].second == ")"){
            return i;
        }else{
            origin.add(token[i].second);
        }
    }
    
    return token.size();
}

/**********************************************************/
/* getValue, getArr, delVar
     - a sub function for helping ASSOC, REMOVE, SUBST */
/**********************************************************/
List Basic::getValue(vector< pair<string, List> > *variables, string isSymbol){
    int check = 0;
    
    for(int i = 0 ; i < (*variables).size() ; i++){
        if((*variables)[i].first == isSymbol){
            return (*variables)[i].second;
        }
    }
    return List();
}

List Basic::getArr(int& index, vector< pair<int, string> > token){
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
                break;
            }else{
                leftCount--;
            }
        }
    }

    return ret;
}


void Basic::delVar(vector< pair<string, List> > *variables, int count){
    for(int k = 0 ; k < count ;k++){
        variables->pop_back();
    }
}  

/**********************************************************/
/* setq - a function to set variable(symbol and list) 
 returns List - linked list
 symbol also a list with one node      */
/**********************************************************/
List Basic::setq(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    string name = "";
    List return_Variable;
    Parser parser;

    if(token[1].first == 11){
        if(token[1].second == "NIL"){
            throw Exception(17);
        }else if(token[1].second == "T"){
            throw Exception(18);
        }else{
            name = token[1].second;
        }
    }else{
        //variable name error
        throw Exception(1);
    }
    
    for(int i=2;i<token.size();i++){
        List variable;
        if(token[i].first == 10 || token[i].first == 12 || token[i].first == 30 || token[i].first == 13){
            if(name != ""){
                variable.add(token[i].second);
                
                int check = 0;
                for(int j=0;j<variables->size();j++){
                    if((*variables)[j].first == name){
                        (*variables)[j].second = variable;
                        
                        return_Variable = variable;
                        check = 1;
                        name = "";
                        
                        break;
                    }
                }
                
                if(check == 0){
                    variables->push_back(make_pair(name, variable));
                    return_Variable = variable;
                    name = "";
                }
            }else{
                //variable name error
                throw Exception(1);
            }
        }else if(token[i].first == 11){
            if(name != ""){
                if(token[i].second == "NIL" || token[i].second == "T"){
                    int check = 0;
                    if(token[i].second == "NIL"){
                        variable.add("NIL");
                    }else{
                        variable.add("T");
                    }

                    check = 0;

                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;

                            return_Variable = variable;
                            check = 1;
                            name = "";

                            break;
                        }
                    }

                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                }else{
                    int check = 0;
                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == token[i].second){
                            variable = (*variables)[j].second;

                            check = 1;

                            break;
                        }
                    }

                    if(check == 0){
                        //unbound variable
                        throw Exception(2);
                    }

                    check = 0;

                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;

                            return_Variable = variable;
                            check = 1;
                            name = "";

                            break;
                        }
                    }

                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                }
            }else{
                if(token[i].second == "NIL"){
                    throw Exception(17);
                }else if(token[i].second == "T"){
                    throw Exception(18);
                }else{
                    name = token[i].second;
                }
            }
        }else if(token[i].second == "\'"){
            if(name != ""){
                if(token[i+1].first == 20){
                    i += 1;
                    vector< pair<int, string> > new_token;
                    
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, variable) + 1;

                    int check = 0;
                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;
                            
                            return_Variable = variable;
                            check = 1;
                            name = "";
                            
                            break;
                        }
                    }
                    
                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                    
                }else if(token[i+1].first == 26){
                    i += 1;
                    if(token[i+1].first == 20){
                        i += 1;
                        vector< pair<int, string> > new_token;
                        
                        for(int j=i+1;j<token.size();j++){
                            new_token.push_back(token[j]);
                        }

                        i += addQuoteList(new_token, 0, variable) + 1;

                        variable.setFlag(2);
                        
                        int check = 0;
                        for(int j=0;j<variables->size();j++){
                            if((*variables)[j].first == name){
                                (*variables)[j].second = variable;
                                
                                return_Variable = variable;
                                check = 1;
                                name = "";
                                
                                break;
                            }
                        }
                        
                        if(check == 0){
                            variables->push_back(make_pair(name, variable));
                            return_Variable = variable;
                            name = "";
                        }
                    }else{
                        //array format error
                        throw Exception(14);
                    }
                }else if(token[i+1].first == 11 || token[i+1].first == 10 || token[i].first == 12  || token[i].first == 13 || token[i].first == 30){
                    i += 1;
                    variable.add(token[i].second);
                    
                    int check = 0;
                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;
                            
                            return_Variable = variable;
                            check = 1;
                            name = "";
                            
                            break;
                        }
                    }
                    
                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                }else{
                    //quote format error
                    throw Exception(3);
                }
            }else{
                //variable name error
                throw Exception(1);
            }
        }else if(token[i].first == 26){
            if(name != ""){
                if(token[i+1].first == 20){
                    i += 1;
                    vector< pair<int, string> > new_token;
                    
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, variable) +1;

                    variable.setFlag(2);
                    
                    int check = 0;
                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;
                            
                            return_Variable = variable;
                            check = 1;
                            name = "";
                            
                            break;
                        }
                    }
                    
                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                    
                }else{
                    //array format error
                    throw Exception(14);
                }
            }else{
                //variable name error
                throw Exception(1);
            }
        }else{
            if(token[i].first == 20){
                if(name != ""){
                    vector< pair<int, string> > new_token;
                    int left_count = 0;
                    int check =0;
                    int index = 0;
                    
                    for(int j=i;j<token.size();j++){
                        new_token.push_back(token[j]);
                        index++;
                        if(token[j].first == 20){
                            left_count++;
                        }
                        
                        if(token[j].first == 21){
                            if(left_count == 1 && check == 0){
                                i+=index;
                                check = 1;
                            }else{
                                left_count--;
                            }
                        }
                    }

                    variable = parser.analyze(new_token, variables);

                    check = 0;
                    for(int j=0;j<variables->size();j++){
                        if((*variables)[j].first == name){
                            (*variables)[j].second = variable;
                            
                            return_Variable = variable;
                            check = 1;
                            name = "";
                            
                            break;
                        }
                    }
                    
                    if(check == 0){
                        variables->push_back(make_pair(name, variable));
                        return_Variable = variable;
                        name = "";
                    }
                }else{
                    //variable name error
                    throw Exception(1);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                //SETQ format error
                throw Exception(4);
            }
        }
    }
    
    return return_Variable;
}

/**********************************************************/
/* list - a function to create list  
 returns List - linked list                    */
/**********************************************************/
List Basic::list(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable;
    Parser parser;

    variable.setFlag(1);

    for(int i=1; token.size(); i++){
        if(token[i].first == 10 || token[i].first == 12  || token[i].first == 13 || token[i].first == 30){
            variable.add(token[i].second);
        }else if(token[i].second == "\'"){
            ++i;
            if(token[i].first == 10 || token[i].first == 11 || token[i].first == 12  || token[i].first == 13 || token[i].first == 30){
                variable.add(token[i].second);
            }else if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }
                
                List newList;

                i += addQuoteList(new_token, 0, newList) + 1;

                variable.addList(newList);
            }
        }else if(token[i].first == 11){
            int check = 0;
            for(int j=0; j < variables->size();j++){
                if((*variables)[j].first == token[i].second){
                    check = 1;
                    
                    List temp = (*variables)[j].second;
                    
                    if(temp.getFlag() == 0){
                        variable.add(temp.front());
                    }else{
                        variable.addList(temp);
                    }
                    
                    break;
                }
            }
            
            if(check == 0){
                //error
                throw Exception(2);
            }
        }else if(token[i].first == 26){
            if(token[i+1].first == 20){
                i += 1;
                vector< pair<int, string> > new_token;
                    
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                List new_list;

                i += addQuoteList(new_token, 0, new_list) +1;

                new_list.setFlag(2);
                
                variable.addList(new_list);
                
            }else{
                //array format error
                throw Exception(14);
            }

        }else if(token[i].first == 21 || token[i].first == -1){
            break;
        }else if(token[i].first == 20){
            vector< pair<int, string> > new_token;
            int left_count = 0;
            int check = 0;
            int index = 0;

            for(int j=i;j<token.size();j++){
                new_token.push_back(token[j]);
                index++;
                if(token[j].first == 20){
                    left_count++;
                }

                if(token[j].first == 21){
                    if(left_count == 1 && check == 0){
                        i+=index - 1;
                        check = 1;
                    }else{
                        left_count--;
                    }
                }
            }

            List newList;

            newList = parser.analyze(new_token, variables);

            if(newList.getFlag() == 0){
                variable.add(newList.back());
            }else{
                variable.addList(newList);
            }
        }else{
            //error
            throw Exception(5);
        }
    }
    
    return variable;
}

/**********************************************************/
/* car - a function to return the first element of a list 
 returns List - firtst element                 */
/**********************************************************/
List Basic::car(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable;
    Parser parser;;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            if(token[i+1].first == 20){
                List quote_result;
                i += 1;
                vector< pair<int, string> > new_token;
                    
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                i += addQuoteList(new_token, 0, quote_result) + 1;

                NODE *head = quote_result.getHead();

                if(head->data == variable.getListCheck()){
                    NODE *tempNode = head->list;

                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }

                        tempNode = tempNode->next;
                    }

                    variable.setFlag(1);
                }else if(head->data == variable.getArrayCheck()){
                    NODE *tempNode = head->list;

                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }

                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(2);
                }else{
                    variable.add(head->data);
                }
            }else{
                throw Exception(80);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;
                
                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }
                
                List newList;

                newList = parser.analyze(new_token, variables);

                NODE *head = newList.getHead();
                
                if(head->data == variable.getListCheck()){
                    NODE *tempNode = head->list;
                    
                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }
                        
                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(1);
                }else if(head->data == variable.getArrayCheck()){
                    NODE *tempNode = head->list;
                    
                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }
                        
                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(2);
                }else{
                    variable.add(head->data);
                }
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;
                        
                        List temp = (*variables)[j].second;
                        
                        NODE *head = temp.getHead();
                        
                        if(head->data == variable.getListCheck()){
                            NODE *tempNode = head->list;
                            
                            while(tempNode != NULL){
                                if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                                    variable.addNode(tempNode);
                                }else{
                                    variable.add(tempNode->data);
                                }
                                
                                tempNode = tempNode->next;
                            }
                            
                            variable.setFlag(1);
                        }else if(head->data == variable.getArrayCheck()){
                            NODE *tempNode = head->list;
                            
                            while(tempNode != NULL){
                                if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                                    variable.addNode(tempNode);
                                }else{
                                    variable.add(tempNode->data);
                                }
                                
                                tempNode = tempNode->next;
                            }
                            
                            variable.setFlag(2);
                        }else{
                            variable.add(head->data);
                        }
                        
                        break;
                    }
                }
                
                if(check == 0){
                    //error
                    if(token[i].second == "NIL"){
                        variable.add("NIL");
                    }else{
                        throw Exception(2);
                    }
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                throw Exception(80);
            }
            
        }
    }
    
    return variable;
}

/**********************************************************/
/* cdr - a function to return the all elements 
 except the first element of a list
 returns List - all elements
 except the first element          */
/**********************************************************/
List Basic::cdr(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable;
    Parser parser;;

    variable.setFlag(1);
    
    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            if(token[i+1].first == 20){
                List quote_result;
                i += 1;
                vector< pair<int, string> > new_token;
                    
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                i += addQuoteList(new_token, 0, quote_result) + 1;

                NODE *head = quote_result.getHead()->next;

                variable.setHead(head);
            }else{
                throw Exception(80);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;
                
                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }
                
                List newList;

                newList = parser.analyze(new_token, variables);

                NODE *head = newList.getHead()->next;
                
                variable.setHead(head);
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;
                        
                        List temp = (*variables)[j].second;
                        
                        NODE *head = temp.getHead()->next;
                        
                        variable.setHead(head);
                        
                        break;
                    }
                }
                
                if(check == 0){
                    //error
                    if(token[i].second == "NIL"){
                        variable.add("NIL");
                    }else{
                        throw Exception(2);
                    }
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                throw Exception(80);
            }
            
        }
    }
    
    return variable;
    
}

/**********************************************************/
/* nth - a function to returns the n'th element of a list 
 returns List - one element of a list              */
/**********************************************************/
List Basic::nth(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable;
    int nthIndex = 0;
    Parser parser;

    if(token[1].first == 10){
        nthIndex = stoi(token[1].second);
    }else{
        /* 변수가 들어오면 변수에 담긴 값을 보고 판단해야함을 발견 - 수정 필요 */
        throw Exception(9);
    }
    
    for(int i=2;i<token.size();i++){
        if(token[i].second == "\'"){
            if(token[i+1].first == 20){
                List quote_result;
                i += 1;
                vector< pair<int, string> > new_token;
                    
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                i += addQuoteList(new_token, 0, quote_result) + 1;

                NODE *head = quote_result.getHead();

                for(int j=0;j<nthIndex;j++){
                    if(head->next != NULL){
                        head = head->next;
                    }else{
                        List nil;
                        nil.add("NIL");
                        return nil;
                    }
                }

                if(head->data == variable.getListCheck()){
                    NODE *tempNode = head->list;

                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }

                        tempNode = tempNode->next;
                    }

                    variable.setFlag(1);
                }else if(head->data == variable.getArrayCheck()){
                    NODE *tempNode = head->list;

                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }

                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(2);
                }else{
                    variable.add(head->data);
                }
            }else{
                throw Exception(80);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;
                
                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }
                
                List newList;

                newList = parser.analyze(new_token, variables);

                NODE *head = newList.getHead();
                
                for(int j=0;j<nthIndex;j++){
                    if(head->next != NULL){
                        head = head->next;
                    }else{
                        List nil;
                        nil.add("NIL");
                        return nil;
                    }
                }
                
                if(head->data == variable.getListCheck()){
                    NODE *tempNode = head->list;
                    
                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }
                        
                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(1);
                }else if(head->data == variable.getArrayCheck()){
                    NODE *tempNode = head->list;
                    
                    while(tempNode != NULL){
                        if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                            variable.addNode(tempNode);
                        }else{
                            variable.add(tempNode->data);
                        }
                        
                        tempNode = tempNode->next;
                    }
                    
                    variable.setFlag(2);
                }else{
                    variable.add(head->data);
                }
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;
                        
                        List temp = (*variables)[j].second;
                        
                        NODE *head = temp.getHead();
                        
                        for(int k=0;k<nthIndex;k++){
                            if(head->next != NULL){
                                head = head->next;
                            }else{
                                List nil;
                                nil.add("NIL");
                                return nil;
                            }
                        }
                        
                        if(head->data == variable.getListCheck()){
                            NODE *tempNode = head->list;
                            
                            while(tempNode != NULL){
                                if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                                    variable.addNode(tempNode);
                                }else{
                                    variable.add(tempNode->data);
                                }
                                
                                tempNode = tempNode->next;
                            }
                            
                            variable.setFlag(1);
                        }else if(head->data == variable.getArrayCheck()){
                            NODE *tempNode = head->list;
                            
                            while(tempNode != NULL){
                                if(tempNode->data == variable.getListCheck() || tempNode->data == variable.getArrayCheck()){
                                    variable.addNode(tempNode);
                                }else{
                                    variable.add(tempNode->data);
                                }
                                
                                tempNode = tempNode->next;
                            }
                            
                            variable.setFlag(2);
                        }else{
                            variable.add(head->data);
                        }
                        
                        break;
                    }
                }
                
                if(check == 0){
                    //error
                    throw Exception(2);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                throw Exception(10);
            }
        }
        
    }
    
    return variable;
}

/**********************************************************/
/* cons - a function to add a new element
 to the beginning of the list.
 returns List - all elements                       */
/**********************************************************/
List Basic::cons(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    // (CONS 'A '(B C D))
    List insert_variable;
    List variable;
    Parser parser;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            i += 1;
            if(token[i].first == 11 || token[i].first == 10  || token[i].first == 12  || token[i].first == 13 || token[i].first == 30){
                if(insert_variable.getSize() == 0){
                    insert_variable.add(token[i].second);
                    
                }else if(variable.getSize() == 0){
                    variable.add(token[i].second);
                    
                    if(insert_variable.getSize() == 1){
                        variable.insertValue(insert_variable.front(), 0);
                    }else{
                        variable.insertList(insert_variable, 0);
                    }
                }else{
                    //invalid number of arguments
                    throw Exception(11);
                }
            }else if(token[i].first == 20){
                if(insert_variable.getSize() == 0){
                    vector< pair<int, string> > new_token;
                    
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, insert_variable) + 1;

                }else if(variable.getSize() == 0){
                    vector< pair<int, string> > new_token;
                    
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }
                    
                    i += addQuoteList(new_token, 0, variable);

                    if(insert_variable.getSize() == 1){
                        variable.insertValue(insert_variable.front(), 0);
                    }else{
                        variable.insertList(insert_variable, 0);
                    }
                }else{
                    //error
                    throw Exception(11);
                }
            }else{
                //error
                throw Exception(3);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;
                
                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }
                
                if(insert_variable.getSize() == 0){
                    insert_variable = parser.analyze(new_token, variables);
                }else if(variable.getSize() == 0){
                    variable = parser.analyze(new_token, variables);

                    if(insert_variable.getSize() == 1){
                        variable.insertValue(insert_variable.front(), 0);
                    }else{
                        variable.insertList(insert_variable, 0);
                    }
                }else{
                    //error
                    throw Exception(11);
                }
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;
                        
                        if(insert_variable.getSize() == 0){
                            insert_variable = (*variables)[j].second;
                            
                            break;
                        }else if(variable.getSize() == 0){
                            variable = (*variables)[j].second;
                            
                            if(insert_variable.getSize() == 1){
                                variable.insertValue(insert_variable.front(), 0);
                            }else{
                                variable.insertList(insert_variable, 0);
                            }
                            
                            break;
                        }else{
                            //error
                            throw Exception(11);
                        }
                    }
                }
                
                if(check == 0){
                    //error
                    throw Exception(2);
                }
                
            }else if(token[i].first == 10 || token[i].first == 12 || token[i].first == 13 || token[i].first == 30){
                if(insert_variable.getSize() == 0){
                    insert_variable.add(token[i].second);
                    
                }else if(variable.getSize() == 0){
                    variable.add(token[i].second);
                    
                    if(insert_variable.getSize() == 1){
                        variable.insertValue(insert_variable.front(), 0);
                    }else{
                        variable.insertList(insert_variable, 0);
                    }
                }else{
                    //error
                    throw Exception(11);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                //error
                throw Exception(12);
            }
        }
    }
    
    return variable;
}
/**********************************************************/
/* reverse - a function to reverse the order of list elements
 returns List - all elements                       */
/**********************************************************/
List Basic::reverse(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable, result;
    Parser parser;
    result.setFlag(1);

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            if(token[i+1].first == 20){
                i += 1;
                vector< pair<int, string> > new_token;
                    
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                i += addQuoteList(new_token, 0, variable) + 1;

            }else{
                throw Exception(80);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;
                
                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }
                
                List newList;

                newList = parser.analyze(new_token, variables);

                variable = newList;
                
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;
                        
                        List temp = (*variables)[j].second;
                        
                        variable = temp;
                        
                        break;
                    }
                }
                
                if(check == 0){
                    //error
                    throw Exception(2);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                //error
                throw Exception(13);
            }
        }
    }
    
    variable.reverse(result, variable.getHead());
    
    return result;
    
}

/*
 주어진 여러개의 리스트를 하나의 리스트로 만드는 함수
 (APPEND '(A C) '(B D) '(E F))
 > (A C B D E F)
 append 할때
 (append '(1 2) #(3 4))
 > (1 2 . #(3 4))
 로나옴 이유 모름
 */
List Basic::append(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable, result;
    Parser parser;
    
    for(int i = 1; i < token.size(); i++){
        if(token[i].second == "\'"){
            i += 1;
            vector< pair<int, string> > new_token;
            
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }
            
            i += addQuoteList(new_token, 0, variable) + 1;
        }//if end
        else if(token[i].first == 11){
            int check = 0;
            for(int j=0; variables->size();j++){
                if((*variables)[j].first == token[i].second){
                    check = 1;
                    
                    List temp = (*variables)[j].second;
                    
                    if(temp.getFlag() == 0){
                        //단순 변수일때
                        throw Exception(52);
                        //variable.add(temp.back());
                    }else if(temp.getFlag() == 1){
                        //변수가 리스트일때
                        NODE* get = temp.getHead();
                        
                        while(get != NULL){
                            List newList;
                            variable.add(get->data);
                            newList.setHead(get->list);
                            newList.traverse(newList.getHead());
                            get = get->next;
                        }
                    }
                    else if(temp.getFlag() == 2){
                        //변수가 배열일때 어떻게 처리?
                        
                    }
                    break;
                }
            }
            
            if(check == 0){
                //error
                throw Exception(2);
            }
        }//else if end
        else if(token[i].first == 10 || token[i].first == 12 || token[i].first == 26){
            throw Exception(52);
        }
        else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 1;
                int index = 0;
                
                new_token.push_back(token[i]);
                for(int j=i+1;j<token.size();j++){
                    if(left_count == 0){
                        i += index;
                        break;
                    }
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }
                    
                    if(token[j].first == 21){
                        left_count--;
                    }
                }
                List newList;
                
                newList = parser.analyze(new_token, variables);
                
                NODE *head = newList.getHead();
                
                for(int k = 0;k < newList.getSize(); k++){
                    variable.add(head->data);
                    head = head->next;
                }
            }//if end
        }//else end
    }
    result = variable;
    return result;
}

List Basic::length(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable, result;
    Parser parser;
    int ret = 0;
    int check = 0;
    for(int i = 1; i < token.size(); i++){
        
        if(token[i].second == "\'"){
            if(check != 0){
                //error throw
                throw Exception(50);
            }
            check++;
            i += 1;
            vector< pair<int, string> > new_token;
            
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }
            
            i += addQuoteList(new_token, 0, variable) + 1;
            ret += variable.getSize();
        }
        else if(token[i].first == 11){
            if(check != 0){
                //error throw
                throw Exception(50);
            }
            check++;
            for(int j=0; variables->size();j++){
                if((*variables)[j].first == token[i].second){
                    
                    List temp = (*variables)[j].second;
                    
                    if(temp.getFlag() == 0){
                        //단순 변수일때
                        ret++;
                    }else{
                        //변수가 리스트일때
                        NODE* get = temp.getHead();
                        
                        while(get != NULL){
                            List newList;
                            ret++;
                            newList.setHead(get->list);
                            newList.traverse(newList.getHead());
                            get = get->next;
                        }
                    }
                    break;
                }
            }
            
            if(check == 1){
                //error
                throw Exception(2);
            }
        }
        else if(token[i].first == 26){
            if(token[i+1].first == 20){
                i += 1;
                vector< pair<int, string> > new_token;
                
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }
                
                i += addQuoteList(new_token, 0, variable) + 1;
                ret += variable.getSize();
            }else{
                //array format error
                throw Exception(14);
            }
        }//else if end
        else if(token[i].first == 20){
            if(check != 0){
                //error throw
                throw Exception(50);
            }
            check++;
            vector< pair<int, string> > new_token;
            int left_count = 0;
            int check =0;
            int index = 0;
            
            new_token.push_back(token[i]);
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
                index++;
                if(token[j].first == 20){
                    left_count++;
                }
                
                if(token[j].first == 21){
                    if(left_count == 1 && check == 0){
                        i+=index;
                        check = 1;
                    }else{
                        left_count--;
                    }
                }
            }
            List newList;
            
            newList = parser.analyze(new_token, variables);
            
            if(newList.getFlag() == 1 || newList.getFlag() == 2){
                NODE* get = newList.getHead();
                
                while(get != NULL){
                    List newList;
                    ret++;
                    newList.setHead(get->list);
                    newList.traverse(newList.getHead());
                    get = get->next;
                }
            }
            else{
                //함수를 콜 하고 리턴이 리스트가 아님 에러
                Exception(51);
            }
        }//else end
    }
    result.add(to_string(ret));
    result.setFlag(0);
    
    return result;
}

/**********************************************************/
/* member - a function to returns a list from the found data
             to the last element 
        returns List - a list from the found data
                        to the last element               */
/**********************************************************/
List Basic::member(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List data;
    List nilCheck;
    List variable;
    Parser parser;

    for(int i=1; i< token.size(); i++){
        if(token[i].second == "\'"){
            if(token[i+1].first == 20){
                if(data.getSize() == 0){
                    i += 1;
                    List newList;
                    vector< pair<int, string> > new_token;
                        
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, newList) + 1;
                    
                    data.add("NIL");
                    nilCheck.add("NIL");
                }else if(variable.getSize() == 0){
                    i += 1;
                    List newList;
                    vector< pair<int, string> > new_token;
                        
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, newList) + 1;

                    string find_Data = data.front();
                    NODE *head = newList.getHead();

                    while(head != NULL){
                        if(head->data != find_Data){
                            head = head->next;
                        }else{
                            variable.setHead(head);
                            variable.setFlag(1);
                            break;
                        }
                    }

                    if(head == NULL){
                        if(nilCheck.getSize()==0){
                            nilCheck.add("NIL");
                        }
                    }
                }else{
                    throw Exception(11);
                }
            }else{
                i+=1;
                if(data.getSize() == 0){
                    data.add(token[i].second);
                }else{
                    throw Exception(80);
                }
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;

                for(int j=i;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }

                    if(token[j].first == 21){
                        if(left_count == 1 && check == 0){
                            i+=index;
                            check = 1;
                        }else{
                            left_count--;
                        }
                    }
                }

                List newList;

                newList = parser.analyze(new_token, variables);

                if(data.getSize() == 0){
                    if(newList.getFlag() == 0){
                        data = newList;
                    }else{
                        data.add("NIL");
                        nilCheck.add("NIL");
                    }
                }else if(variable.getSize() == 0){
                    if(newList.getFlag() == 1){
                        string find_Data = data.front();
                        NODE *head = newList.getHead();

                        while(head != NULL){
                            if(head->data != find_Data){
                                head = head->next;
                            }else{
                                variable.setHead(head);
                                variable.setFlag(1);
                                break;
                            }
                        }

                        if(head == NULL){
                            if(nilCheck.getSize()==0){
                                nilCheck.add("NIL");
                            }
                        }
                    }else{
                        throw Exception(80);
                    }
                }else{
                    throw Exception(11);
                }
            }else if(token[i].first == 11){
                int check = 0;
                List newList;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;

                        newList = (*variables)[j].second;

                        break;
                    }
                }

                if(check == 0){
                    //error
                    throw Exception(2);
                }

                if(data.getSize() == 0){
                    if(newList.getFlag() == 0){
                        data = newList;
                    }else{
                        data.add("NIL");
                        nilCheck.add("NIL");
                    }
                }else if(variable.getSize() == 0){
                    if(newList.getFlag() == 1){
                        string find_Data = data.front();
                        NODE *head = newList.getHead();

                        while(head != NULL){
                            if(head->data != find_Data){
                                head = head->next;
                            }else{
                                variable.setHead(head);
                                variable.setFlag(1);
                                break;
                            }
                        }

                        if(head == NULL){
                            if(nilCheck.getSize() == 0){
                                nilCheck.add("NIL");
                            }
                        }
                    }else{
                        throw Exception(80);
                    }
                }else{
                    throw Exception(11);
                }

            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                if(data.getSize() == 0){
                    data.add(token[i].second);
                }else{
                    throw Exception(80);
                }
            }
        }
    }

    if(nilCheck.getSize() == 1){
        return nilCheck;
    }else{
        return variable;
    }
}

/**********************************************************/
/* assoc - a function to returns a list when the second variable 
    in the function has the same first element in the list.  */
/**********************************************************/
List Basic::assoc(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    

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
                    if(token[i].second == "'"){
                        i = addQuoteList(token, i+2, item);
                    }
                    else item = getArr(i, token);
                    
                }
                else{
                    comparedFlag =1;
                    if(token[i].second == "'"){
                        i = addQuoteList(token, i+2, compared);
                    }
                    else compared = getArr(i, token);
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
                        item = parser.analyze(newToken, variables);
                    } 
                    else{
                        comparedFlag =1;
                        compared = parser.analyze(newToken, variables);
                    }
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
                        if(token[i].second == "'"){ 
                            i = addQuoteList(token, i+2, item);
                        }           
                        else item = getArr(i, token);
         
                    } 
                    else{
                        comparedFlag =1;
                        if(token[i].second == "'"){
                            i = addQuoteList(token, i+2, compared);
                        }         
                        else compared = getArr(i, token);   
                    } 

                    newToken.clear();
                    count++;
                }else if(token[i].second == "\'"){
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
                
                newToken.clear();
                count++;
            }
            
        }
        
    }
    
    if(count <= 1){
        delVar(variables, isSetq);
        throw Exception(100);
    }
    
    
    if(itemFlag == 0){
        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);
        if(item.getHead()==NULL) throw Exception(105);
        
    }
    if(comparedFlag==0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);
        
        if(compared.getHead()==NULL) throw Exception(106);
        
    }
    if(compared.getFlag() != 1) throw Exception(80);
    if(!compared.isListIn()) throw Exception(81);
    
    if(item.getSize() != 1 ) ret.add("NIL");
    else{
        string retList = compared.getAssoc(item.getHead()->data);
        ret.add(retList);
    }
    
    return ret;
    
}

/****************************************************************************/
/* remove - remove a variable that is in the list which is second parameter.*/
/****************************************************************************/
List Basic::remove(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
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
                        if(token[i].second == "'"){ 
                            i = addQuoteList(token, i+2, item);
                            item.setFlag(1);
                        }           
                        else item = getArr(i, token);
         
                    } 
                    else{
                        comparedFlag =1;
                        if(token[i].second == "'"){
                            i = addQuoteList(token, i+2, compared);
                            compared.setFlag(1);
                        }         
                        else compared = getArr(i, token);   
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
  
    if(itemFlag == 0){
        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);
        if(item.getHead()==NULL) throw Exception(105);

    }
    if(comparedFlag==0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);

        if(compared.getHead()==NULL) throw Exception(106);
       
    }

    if(item.getSize() != 1 ) return compared;
    else{
        ret = compared.getRemove(item.getHead()->data);
    }
    return ret;

}


/*****************************************************************/
/* subst - a function to find a second variable 
    in the third variable and replace it with first parameter.  */
/****************************************************************/
List Basic::subst(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List ret;

    Parser parser;
    List item;
    List compared;
    List change;
    vector< pair<int, string> > newToken;


    // 0 = not symbol, 1 = symbol
    int itemFlag = 0;
    int comparedFlag = 0;
    int changeFlag = 0;

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
                    
                    if(count >= 3 ){
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
                    else if(compared.getSize()==0){
                        comparedFlag =1;
                        compared = parser.analyze(newToken, variables);
                    }else{
                        changeFlag =1;
                        change = parser.analyze(newToken, variables);
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

                    if(count >= 3 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        if(token[i].second == "'"){ 
                            i = addQuoteList(token, i+2, item);
                            item.setFlag(1);
                        }           
                        else item = getArr(i, token);
         
                    }else if(compared.getSize()==0){
                        comparedFlag =1;
                        if(token[i].second == "'"){
                            i = addQuoteList(token, i+2, compared);
                            compared.setFlag(1);
                        }         
                        else compared = getArr(i, token);   
                    }else{
                        changeFlag=1;
                        if(token[i].second == "'"){
                            i = addQuoteList(token, i+2, change);
                            change.setFlag(1);
                        }         
                        else change = getArr(i, token);

                    
                    } 

                    newToken.clear();
                    count++;
                }else if(token[i].second == "'"){
                    
                    if(item.getSize()==0){ 
                        itemFlag = 1;
                        item.add(token[i+1].second);
                        i++;
                        
                    }else if(compared.getSize()==0){
                        comparedFlag =1;
                        compared.add(token[i+1].second);
                        i++;
                    }else{
                        changeFlag =1;
                        change.add(token[i+1].second);
                        i++;
                    } 
                    count++;
                    newToken.clear();
                }else if(token[i].second!="EOF"){

                    if(count >= 3 ){
                        delVar(variables, isSetq);
                        throw Exception(100);
                    }

                    if(token[i].first == 10 || token[i].first == 12 || token[i].first ==30 ||token[i].first == 13 || token[i].second == "NIL"){
                        if(item.getSize()==0){
                            itemFlag = 1;
                            item.add(token[i].second);
                        }else if(compared.getSize()==0){
                            comparedFlag = 1;
                            compared.add(token[i].second);
                        }else{
                            changeFlag =1;
                            change.add(token[i].second);
                        }
                    }else{
                        if(item.getSize()==0) item.add(token[i].second);
                        else if(compared.getSize()==0) compared.add(token[i].second);
                        else change.add(token[i].second);
                    }

                    newToken.clear();
                    count++;
                }

            }
            
    }    
    
    if(count <= 2){
        delVar(variables, isSetq);
        throw Exception(100);
    }

    if(itemFlag == 0){
        string itemData = item.getHead()->data;
        item = getValue(variables, itemData);
        if(item.getHead()==NULL) throw Exception(105);

    }
    if(comparedFlag==0){
        string comparedData = compared.getHead()->data;
        compared = getValue(variables, comparedData);

        if(compared.getHead()==NULL) throw Exception(106);
       
    }
    if(changeFlag==0){
        string changeData = change.getHead()->data;
        change = getValue(variables, changeData);

        if(change.getHead()==NULL) throw Exception(106);
    }


    if(change.getFlag() ==2 || change.getHead()->data == "#") return change;
    if(compared.getSize() != 1) return change;

    ret.add(change.find(compared.getHead()->data, item));

    return ret;
}
