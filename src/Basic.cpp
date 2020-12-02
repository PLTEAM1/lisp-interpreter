#include "../header/Basic.h"
#include "../header/Exception.h"
#include <iostream>

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
            List newList;
            int ret = addQuoteList(token, i, newList);
            origin.addList(newList);
            i = ret;

        }else if(token[i].first == 26){
            i+=2;
            List newList;
            int ret = addQuoteList(token, i, newList);
            newList.setFlag(2);
            origin.addList(newList);
            i = ret;

        }else if(token[i].second == ")"){
            return i + 1;
        }else{
            origin.add(token[i].second);
        }
    }

    return token.size();
}

/**********************************************************/
/* setq - a function to set variable(symbol and list) 
            returns List - linked list
                    symbol also a list with one node      */
/**********************************************************/
List Basic::setq(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    string name = "";
    List return_Variable;
    Syntax syntax;

    if(token[1].first == 11){
        name = token[1].second;
    }else{
        //variable name error
        throw Exception(1);
    }

    for(int i=2;i<token.size();i++){
        List variable;
        if(token[i].first == 10 || token[i].first == 12){
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
            }else{
                name = token[i].second;
            }
        }else if(token[i].second == "\'"){
            if(name != ""){
                if(token[i+1].first == 20){
                    i += 1;
                    vector< pair<int, string> > new_token;
                    
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, variable);

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

                        i += addQuoteList(new_token, 0, variable);

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
                }else if(token[i+1].first == 11 || token[i+1].first == 10 || token[i].first == 12){
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

                    i += addQuoteList(new_token, 0, variable);

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

                    variable = syntax.analyze(new_token, variables);

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
    //yae
    variable.setFlag(1); // set this variable is list

    for(int i=1; token.size(); i++){
        if(token[i].first == 10 || token[i].first == 12){
            variable.add(token[i].second);
        }else if(token[i].second == "\'"){
            ++i;
            if(token[i].first == 10 || token[i].first == 11 || token[i].first == 12){
                variable.add(token[i].second);
            }else if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                List newList;

                i += addQuoteList(new_token, 0, newList);

                variable.addList(newList);
            }
        }else if(token[i].first == 11){
            int check = 0;
            for(int j=0; variables->size();j++){
                if((*variables)[j].first == token[i].second){
                    check = 1;

                    List temp = (*variables)[j].second;

                    if(temp.getFlag() == 0){
                        variable.add(temp.back());
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
        }else if(token[i].first == 21){
            break;
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
    Syntax syntax;;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            List quote_result;
            i += 1;
            vector< pair<int, string> > new_token;
                
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }

            i += addQuoteList(new_token, 0, quote_result);

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

                newList = syntax.analyze(new_token, variables);

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
                    throw Exception(2);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                throw Exception(6);
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
    Syntax syntax;;

    variable.setFlag(1);

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            List quote_result;
            i += 1;
            vector< pair<int, string> > new_token;
                
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }

            i += addQuoteList(new_token, 0, quote_result);

            NODE *head = quote_result.getHead()->next;

            variable.setHead(head);
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

                newList = syntax.analyze(new_token, variables);

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
                    throw Exception(2);
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                throw Exception(7);
            }
            
        }
    }

    return variable;

}

/**********************************************************/
/* caddr -  
        returns List -               */
/**********************************************************/
List Basic::caddr(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}

/**********************************************************/
/* nth - a function to returns the n'th element of a list 
        returns List - one element of a list              */
/**********************************************************/
List Basic::nth(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    List variable;
    int nthIndex = 0;
    Syntax syntax;

    if(token[1].first == 10){
        nthIndex = stoi(token[1].second);
    }else{
        /* 변수가 들어오면 변수에 담긴 값을 보고 판단해야함을 발견 - 수정 필요 */
        throw Exception(9);
    }

    for(int i=2;i<token.size();i++){
        if(token[i].second == "\'"){
            List quote_result;
            i += 1;
            vector< pair<int, string> > new_token;
                
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }

            i += addQuoteList(new_token, 0, quote_result);

            NODE *head = quote_result.getHead();

            for(int j=0;j<nthIndex;j++){
                if(head->next != NULL){
                    head = head->next;
                }else{
                    return List();
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

                newList = syntax.analyze(new_token, variables);

                NODE *head = newList.getHead();

                for(int j=0;j<nthIndex;j++){
                    if(head->next != NULL){
                        head = head->next;
                    }else{
                        //리스트 index를 넘어가는 경우 NIL 반환 - 수정 필요
                        return List();
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
                                //리스트 index를 넘어가는 경우 NIL 반환 - 수정 필요
                                return List();
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
    Syntax syntax;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            i += 1;
            if(token[i].first == 11 || token[i].first == 10){
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

                    i += addQuoteList(new_token, 0, insert_variable);

                }else if(variable.getSize() == 0){
                    vector< pair<int, string> > new_token;

                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    i += addQuoteList(new_token, 0, variable);

                    variable.insertList(insert_variable, 0);
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
                    insert_variable = syntax.analyze(new_token, variables);
                }else if(variable.getSize() == 0){
                    variable = syntax.analyze(new_token, variables);

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

            }else if(token[i].first == 10){
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
    Syntax syntax;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            i += 1;
            vector< pair<int, string> > new_token;
                
            for(int j=i+1;j<token.size();j++){
                new_token.push_back(token[j]);
            }

            i += addQuoteList(new_token, 0, variable);
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

                newList = syntax.analyze(new_token, variables);

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

List Basic::append(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::length(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}

List Basic::member(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::assoc(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::remove(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::subst(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}