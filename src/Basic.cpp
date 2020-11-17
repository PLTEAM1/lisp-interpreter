#include "../header/Basic.h"
#include "../header/Syntax.h"
#include <iostream>

string Basic::setq(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    string name;
    string value;
    Syntax syntax;

    for(int i=1;i<token.size();i++){
        if(token[i].first == 11){
            name = token[i].second;
        }else if(token[i].first == 10){
            value = "";
            value = token[i].second;

            variables->push_back(make_pair(name, value));
            name  = "";
        }else if(token[i].second == "\'"){
            value = "";
            for(int j=i+1;j<token.size();j++){
                if(token[j].first != 21){
                    i+=1;
                    if(value.length() == 0){
                        value = token[j].second;
                    }else if(value.length() == 1){
                        value += token[j].second;
                    }else{
                        value += " " + token[j].second;
                    }
                }else{
                    value += token[j].second;

                    variables->push_back(make_pair(name, value));
                    i += 1;
                    name  = "";
                    break;
                }
            }
        }else{
            if(token[i].first == 20){
                vector< pair<int, string> > new_token;

                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }
                value = syntax.analyze(new_token, variables);

                variables->push_back(make_pair(name, value));
                name = "";

                for(int j=0;j<new_token.size();j++){
                    if(new_token[j].first != 21){
                        i+=1;
                    }else{
                        i+=1;
                        break;
                    }
                }
            }else if(token[i].first == 21 || token[i].first == -1){
                break;
            }else{
                value = "error";
                break;
            }
        }
    }

    return value;
}

string Basic::list(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    string value = "(";

    for(int i=1; token.size();i++){
        if(token[i].first == 10 || token[i].first == 12){
            if(value.length() == 1){
                value += token[i].second;
            }else{
                value += " " + token[i].second;
            }
        }else if(token[i].second == "\'"){
            i += 1;
            if(value.length() == 1){
                value += token[i].second;
            }else{
                value += " " + token[i].second;
            }
        }else if(token[i].first == 11){
            int check = 0;
            for(int j=0; variables->size(); j++){
                if((*variables)[i].first == token[i].second){
                    check = 1;
                    string temp = (*variables)[i].second;

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
                            }
                        }
                    }else{
                        if(value.length() == 1){
                            value += temp;
                        }else{
                            value += " " + temp;
                        }
                    }
                }
            }

            if(check == 0){
                value = "error";
                break;
            }
        }else if(token[i].first == 21){
            value += ")";
            break;
        }else{
            value = "error";
            break;
        }
    }

    return value;
}
string Basic::car(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
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
                            string temp = (*variables)[i].second;

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
                vector< pair<int, string> > new_token;
                string function_result;
                for(int j=i+1;j<token.size();j++){
                    new_token.push_back(token[j]);
                }

                function_result = syntax.analyze(new_token, variables);

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

    return value;

}
string Basic::cdr(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::caddr(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::nth(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::cons(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::reverse(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::append(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::length(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}

string Basic::member(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::assoc(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::remove(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}
string Basic::subst(vector< pair<int, string> > token, vector< pair<string, string> > *variables){
    return "1";

}