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
                if((*variables)[i].first == token[i].second){
                    check = 1;

                    List temp = (*variables)[i].second;

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

List Basic::car(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    string value;
    Syntax syntax;

    for(int i=1;i<token.size();i++){
        if(token[i].second == "\'"){
            i+=2;
            value = token[i].second;

            if(value == "("){
                // CAR '((X) Y Z))
                for(int j=i+1;j<token.size();j++){
                    if(token[j].first != 21){
                        if(value.length() == 1){
                            value += token[j].second;
                        }else{
                            value += " " + token[j].second;
                        }
                    }else{
                        value += ")";
                        break;
                    }
                }
            }else if(value == "\'"){
                // CAR '('X Y Z))
                i+=1;
                value = token[i].second;
            }else{
                if(token[i].first == 11){
                    int check = 0;
                    for(int j=0; variables->size(); j++){
                        if((*variables)[i].first == token[i].second){
                            check = 1;
                            //string temp = (*variables)[i].second;
                            string temp;
                            
                            if(temp[0] == '('){
                                string s;
                                for(int k=1; k<temp.length(); k++){
                                    //string s;
                                    if(temp[k] != ' ' && temp[k] != ')'){
                                        s.append(1, temp[k]);
                                    }else{
                                        if(value.length() == 1){
                                            value += s;
                                        }else{
                                            value += " " + s;
                                        }

                                        s = "";
                                        break;
                                    }
                                }
                            }else{
                                value = "error";
                                break;
                            }
                        }
                    }

                    if(check == 0){
                        value = "error";
                        break;
                    }
                }
            }

            break;
        }else {
            if(token[i].first == 20){
                //CAR (CAR ((1 2) 4 5 6))
                vector< pair<int, string> > new_token;
                string function_result;
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                //function_result = syntax.analyze(new_token, variables); // "(1 2)"

                if(function_result[0] == '('){
                    if(function_result[1] == '('){
                        for(int j=1; function_result.length();j++){
                            if(function_result[j] != ')'){
                                value.append(1, function_result[j]);
                            }else{
                                value.append(1, ')');
                                break;
                            }
                        }
                    }else{
                        for(int j=1;function_result.length();j++){
                            if(function_result[j] != ' '){
                                value.append(1, function_result[j]);
                            }else{
                                break;
                            }
                        }
                    }
                }else{
                    value = "error";
                }

                break;
            }else{
                value = "error";
                break;
            }
        }
    }

    return List();

}
List Basic::cdr(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::caddr(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
List Basic::nth(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    string value;
    string index;
    Syntax syntax;
    vector<string> v;

    if(token[1].first == 10){
        index = token[1].second;
    }else{
        value ="error";

        return List();
    }

    for(int i=2;i<token.size();i++){
            if(token[i].second == "\'"){
                i+=2;
                string s;
                if(token[i].first == 20){
                    for(int j=i;j<token.size();j++){
                        i += 1;
                        if(token[j].first != 21){
                            if(s.length() < 2){
                                s += token[j].second;
                            }else{
                                s += " " + token[j].second;
                            }
                        }else{
                            s += ")";
                            break;
                        }
                    }

                    v.push_back(s);
                }else{
                    if(token[i].first != 21){
                        v.push_back(token[i].second);
                    }else{
                        break;
                    }
                }

            }else{
                if(token[i].first == 20){
                    vector< pair<int, string> > new_token;
                    string function_result;
                    for(int j=i+1;j<token.size();j++){
                        new_token.push_back(token[j]);
                    }

                    //function_result = syntax.analyze(new_token, variables);

                    if(function_result[0] == '('){

                        for(int j=1; function_result.length();j++){
                            if(function_result[j] == '('){
                                for(int k=j; function_result.length();k++){
                                    j += 1;
                                    if(function_result[k] != ')'){
                                        value.append(1, function_result[k]);
                                    }else{
                                        value.append(1, ')');
                                        break;
                                    }
                                }

                                v.push_back(value);
                                value = "";
                            }else{
                                for(int k=j;function_result.length();k++){
                                    j += 1;
                                    if(function_result[k] != ' '){
                                        value.append(1, function_result[j]);
                                    }else{
                                        break;
                                    }
                                }

                                v.push_back(value);
                                value = "";
                            }
                        }
                    }else{
                        value = "error";
                    }

                    break;
                }else{
                    value = "error";
                    break;
                }
            }
    }

    cout <<"value : " << value << endl;
    cout << "vector" << endl;

    for(int i=0;i<v.size();i++){
        cout << v[i] << endl;
    }

    if(stoi(index) < v.size() && value != "error"){
        value = v[stoi(index)];
    }else{
        value = "error";
    }

    return List();

}
List Basic::cons(vector< pair<int, string> > token, vector< pair<string, List> > *variables){
    return List();

}
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