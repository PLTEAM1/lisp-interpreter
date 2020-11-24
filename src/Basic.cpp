#include "../header/Basic.h"
#include <iostream>

/**********************************************************/
/* addQuoteList - a function to add quote list '(1 2 (3 4))
            returns next token index                      */
/**********************************************************/
int Basic::addQuoteList(vector< pair<int, string> > token, int index, class List& origin){
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

        }else if(token[i].second == ")"){
            return i;
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
        //error
        return List();
    }

    for(int i=2;i<token.size();i++){
        List variable;
        if(token[i].first == 10){
            if(name != ""){
                variable.add(token[i].second);

                variables->push_back(make_pair(name, variable));
                return_Variable = variable;
                name = "";
            }else{
                //error
                return List();
            }
        }else if(token[i].first == 11){
            if(name != ""){
                variable.add(token[i].second);

                variables->push_back(make_pair(name, variable));
                return_Variable = variable;
                name = "";
            }else{
                name = token[i].second;
            }
        }else if(token[i].second == "\'"){
            if(name != ""){
                i += 1;
                vector< pair<int, string> > new_token;
                
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                i += addQuoteList(new_token, 0, variable);

                variables->push_back(make_pair(name, variable));
                return_Variable = variable;
                name = "";
            }else{
                //error
                return List();
            }
        }else{
            if(token[i].first == 20){
                if(name != ""){
                    vector< pair<int, string> > new_token;
                    int left_count = 0;
                    int check =0;
                    int index = 0;

                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                        index++;
                        if(token[j].first == 20){
                            left_count++;
                        }

                        if(token[j].first == 21){
                            if(left_count == 0 && check == 0){
                                i+=index;
                                check = 1;
                            }else{
                                left_count--;
                            }
                        }
                    }

                    List newList;

                    newList = syntax.analyze(new_token, variables);

                    if(newList.getSize() == 1){
                        variable.add(newList.back());
                    }else{
                        variable.addList(newList);
                    }

                    return_Variable = variable;
                }else{
                    //error
                    return List();
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                return List();
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

    for(int i=1; token.size(); i++){
        if(token[i].first == 10 || token[i].first == 12){
            variable.add(token[i].second);
        }else if(token[i].second == "\'"){
            ++i;
            variable.add(token[i].second);
        }else if(token[i].first == 11){
            int check = 0;
            for(int j=0; variables->size();j++){
                if((*variables)[j].first == token[i].second){
                    check = 1;

                    List temp = (*variables)[j].second;

                    if(temp.getSize() == 1){
                        variable.add(temp.back());
                    }else{
                        variable.addList(temp);
                    }

                    break;
                }
            }

            if(check == 0){
                //error
                return List();
            }
        }else if(token[i].first == 21){
            break;
        }else{
            //error
            return List();
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
            if(head->data != "dummy"){
                variable.add(head->data);
            }else{
                head->next = NULL;

                variable.setHead(head);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;

                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }

                    if(token[j].first == 21){
                        if(left_count == 0 && check == 0){
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
                if(head->data != "dummy"){
                    variable.add(head->data);
                }else{
                    head->next = NULL;

                    variable.setHead(head);
                }
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;

                        List temp = (*variables)[j].second;

                        NODE *head = temp.getHead();
                        if(head->data != "dummy"){
                            variable.add(head->data);
                        }else{
                            head->next = NULL;

                            variable.setHead(head);
                        }

                        break;
                    }
                }

                if(check == 0){
                    //error
                    return List();
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                return List();
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

                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }

                    if(token[j].first == 21){
                        if(left_count == 0 && check == 0){
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
                    return List();
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                return List();
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
    int index = 0;
    Syntax syntax;

    if(token[1].first == 10){
        index = stoi(token[1].second);
    }else{
        return List();
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

            NODE *head = quote_result.getHead()->next;

            for(int j=0;j<index;j++){
                if(head->next != NULL){
                    head = head->next;
                }else{
                    return List();
                }
            }

            if(head->data != "dummy"){
                variable.add(head->data);
            }else{
                head->next = NULL;

                variable.setHead(head);
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;
                int left_count = 0;
                int check =0;
                int index = 0;

                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                    index++;
                    if(token[j].first == 20){
                        left_count++;
                    }

                    if(token[j].first == 21){
                        if(left_count == 0 && check == 0){
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

                for(int j=0;j<index;j++){
                    if(head->next != NULL){
                        head = head->next;
                    }else{
                        return List();
                    }
                }

                if(head->data != "dummy"){
                    variable.add(head->data);
                }else{
                    head->next = NULL;

                    variable.setHead(head);
                }
            }else if(token[i].first == 11){
                int check = 0;
                for(int j=0; variables->size();j++){
                    if((*variables)[j].first == token[i].second){
                        check = 1;

                        List temp = (*variables)[j].second;

                        NODE *head = temp.getHead()->next;

                        for(int k=0;k<index;k++){
                            if(head->next != NULL){
                                head = head->next;
                            }else{
                                return List();
                            }
                        }

                        if(head->data != "dummy"){
                            variable.add(head->data);
                        }else{
                            head->next = NULL;

                            variable.setHead(head);
                        }

                        break;
                    }
                }

                if(check == 0){
                    //error
                    return List();
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                return List();
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
    return List();

}

/**********************************************************/
/* reverse - a function to reverse the order of list elements
        returns List - all elements                       */
/**********************************************************/
List Basic::reverse(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

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