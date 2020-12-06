
#include "../header/Lexer.h"
#include "../header/Parser.h"
#include "../header/Exception.h"
#include <fstream>

/******************************************
 * lookup - a function to lookup operators
 * and parentheses and return the token
 ******************************************/
int Lexer::lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case ';':
           addChar();
           nextToken = SEMI;
           break;
        case '+':
           addChar();
           nextToken = ARITHMETIC;
           break;
        case '-':
           addChar();
           nextToken = ARITHMETIC;
           break;
        case '*':
           addChar();
           nextToken = FUNCTION;
           break;
        case '/':
           addChar();
           nextToken = FUNCTION;
           break;
        case '\'':
            addChar();
            nextToken = FUNCTION;
            break;
        case '\\':
            addChar();
            nextToken = BACKSLASH;
            break;
        case '#':
            addChar();
            nextToken = SHARP;
            break;
        case '.': // float point error
            throw Exception(69);
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/**
 * 사칙연산     : + , - , *, /
 * 기본 함수    : SETQ, LIST, CAR, CDR, NTH, CONS, REVERSE, APPEND, LENGTH, MEMBER, ASSOC, REMOVE, SUBST
 *          ATOM, NULL, NUMBERP, ZEROP, MINUSP, EQUAL, <, >, <= >=, STRINGP, IF, COND
 */

int Lexer::is_Function(){
   if(!strcasecmp(lexeme, "SETQ") || !strcasecmp(lexeme, "LIST") ||!strcasecmp(lexeme, "CAR") ||!strcasecmp(lexeme, "CDR") ||!strcasecmp(lexeme, "NTH") ||!strcasecmp(lexeme, "CONS") ||!strcasecmp(lexeme, "REVERSE") ||!strcasecmp(lexeme, "APPEND") ||!strcasecmp(lexeme, "LENGTH") ||!strcasecmp(lexeme, "MEMBER") ||!strcasecmp(lexeme, "ASSOC") ||!strcasecmp(lexeme, "REMOVE") ||!strcasecmp(lexeme, "SUBST") ||!strcasecmp(lexeme, "ATOM") ||!strcasecmp(lexeme, "NULL") ||!strcasecmp(lexeme, "NUMBERP") ||!strcasecmp(lexeme, "ZEROP") ||!strcasecmp(lexeme, "MINUSP") ||!strcasecmp(lexeme, "EQUAL") ||!strcasecmp(lexeme, "<=") ||!strcasecmp(lexeme, ">=")||!strcasecmp(lexeme, ">")||!strcasecmp(lexeme, "<") ||!strcasecmp(lexeme, "STRINGP") ||!strcasecmp(lexeme, "IF") ||!strcasecmp(lexeme, "COND")){
      return FUNCTION;
   }
   else if(!strcmp(lexeme,"\'")){
       return FUNCTION;
   }
   else return IDENT;
}

/**************************************************/
/* addChar - a function to add nextChar to lexeme */
/**************************************************/
void Lexer::addChar() {
    if (lexLen <= 98) {  // max length of Lexeme is 99
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0; // '\0'
    } else { // lexeme size error
        throw Exception(65);
    }
}

/*****************************************************/
/* getChar - a function to get the next character
          of input and determine its character class */
/*****************************************************/
void Lexer::getChar() {
    
    if (input.size() != 0) {
        
        nextChar = input.front();
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if(nextChar == '>' || nextChar == '<' || nextChar == '=')
            charClass = OPERATOR;
        else if(nextChar == '"')
            charClass = QUOTE;
        else if(nextChar == '#')
            charClass = SHARP;
        else if(nextChar == '\\')
            charClass = BACKSLASH;
        else if(nextChar == '-')
            charClass = ARITHMETIC;
        else
            charClass = UNKNOWN;

        if(input.size() == 0){
            input = '\0';
            charClass = EOF;
        }else{
            input = input.substr(1, input.length() - 1);
        }
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
           returns a non-whitespace character        */
/*****************************************************/
void Lexer::getNonBlank() {
    while (isspace(nextChar))
      getChar();
}

/**
    remove ZeroInt
    0001등 정수에서 앞에 쓸모없는 0을 제거해주는 함수
 */

string Lexer::removeZeroInt(string str){
    int i = stoi(str);
        
    return to_string(i);
}

/**
    remove ZeroFloat
    00.10000등 실수자료에서 쓸모없는 0을 제거하는 함수
    ex) 0.0, 6.0000이 들어오면 0.0, 6.0으로 변환한다.
 */

string Lexer::removeZeroFloat(string str){
    double i = stod(str);
    string ret =to_string(i);
    
    while(ret[ret.length()-1] == '0'){
        ret.erase(ret.length()-1);
    }
    if(ret[ret.length()-1] == '.'){
        //ret.erase(ret.length()-1);
        ret += "0";
    }
    return ret;
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions                                 */
/*****************************************************/
int Lexer::lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = is_Function();
            break;
            
        case OPERATOR:
            addChar();
            getChar();
            
            while(charClass == OPERATOR){
                addChar();
                getChar();
            }
            nextToken = is_Function();
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();

            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            if(nextChar == '.'){
                addChar();
                getChar();
                while (charClass == DIGIT) {
                    addChar();
                    getChar();
                }
                nextToken = FLOAT;
            }
            else
                nextToken = INT_LIT;
            break;

        /* Parse Strings */
        case QUOTE:
            addChar();
            getChar();
            
            while(charClass == LETTER || charClass == DIGIT || nextChar == ' '){
                addChar();
                getChar();
            }
            if(nextChar == '"'){
                addChar();
                getChar();
            }else{
                throw Exception(66);
            }
           
            nextToken = STRING;
            break;
            
        /* SHARP CASE */
        case SHARP:
            
            addChar();
            getChar();
            
            if(charClass == BACKSLASH){
                addChar();
                getChar();
                int i = 0;
                while(charClass == LETTER){
                    addChar();
                    getChar();
                    i++;
                }
                if(i == 0){
                    throw Exception(67);
                }
                nextToken = SHARP_LETTER;
                break;
            }
            else if(nextChar == '('){
                nextToken = SHARP;
                break;
            }
            else{
                throw Exception(68);
            }
            
        /* Integer, floating point number */
        case ARITHMETIC:
            addChar();
            getChar();
            while(charClass == DIGIT){
                addChar();
                getChar();
            }
            if(nextChar == ' ' && lexLen == 1){
                nextToken = FUNCTION;
            }
            else if(nextChar == '.'){
                addChar();
                getChar();
                while (charClass == DIGIT) {
                    addChar();
                    getChar();
                }
                nextToken = FLOAT;
            }
            else
                nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */


    string str(lexeme);
    
    if(nextToken == 10)
        str = removeZeroInt(str);
    else if(nextToken == 12)
        str = removeZeroFloat(str);
    
    //printf("Next token is: %d, Next lexeme is %s\n", nextToken, str.c_str);
    //cout << "Next token is: " << nextToken << ", Next lexeme is " << str << endl;
    ret.push_back(make_pair(nextToken, str));

    return nextToken;
}

vector<pair<int, string> > Lexer::get_Token(){

    ret.clear();
    cout << "* ";
    getline(cin, input);
    
    getChar();

    do{
        lex();
    } while (nextToken != EOF);
    
    /* Find semicolon and remove after semi
        세미콜론 이후의 토큰은 모두 주석 처리가 되어 analyze되지 않아야 한다.
        먼저 세미콜론의 위치를 찾는다. 그리고 그 뒤의 토큰들을 모두 제거한다.
     */
    int semi_index = 101;
    for(int i = 0; i < ret.size(); i++){
        if(ret[i].first == SEMI){
            semi_index = i;
            break;
        }
    }

    if(semi_index != 101){
        ret.erase(ret.begin()+semi_index, ret.end());
        if(ret.size() == 0){ // 입력( ;something) 와 같이 세미콜론 이전에 어떤 입력도 없을때, EOF를 추가해준다.
            ret.push_back(make_pair(nextToken, "EOF"));
        }
    }
    
    /*
     대소문자 구별이 없게 하기 위해, 모든 토큰의 스트링을 전부 대문자로 바꿔준다.
     */
    for(auto it = ret.begin(); it != ret.end(); it++){
        transform(it->second.begin(), it->second.end(), it->second.begin(), ::toupper);
    }

    return ret;
}
