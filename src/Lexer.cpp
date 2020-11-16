
#include "../header/Lexer.h"

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
           nextToken = FUNCTION;
           break;
        case '-':
           addChar();
           nextToken = FUNCTION;
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
       //printf("quote");
       return FUNCTION;
   }
   else return IDENT;
}

/**************************************************/
/* addChar - a function to add nextChar to lexeme */
/**************************************************/
void Lexer::addChar() {
    if (lexLen <= 98) {  // max length of Lexime is 99
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0; // '\0'
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character
          of input and determine its character class */
/*****************************************************/
void Lexer::getChar() {
    /*
    if ((nextChar = getc(stdin)) != EOF){
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if(nextChar == '>' || nextChar == '<' || nextChar == '=')
            charClass = OPERATOR;
        else
            charClass = UNKNOWN;
    }
    else{
        charClass = EOF;
    }*/
    
    
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
            nextToken = INT_LIT;
            break;

        /* Parse Strings */
        case QUOTE:
            addChar();
            getChar();
            
            while(charClass == LETTER || charClass == DIGIT){
                addChar();
                getChar();
            }
            if(nextChar == '"'){
                addChar();
                getChar();
            }else{
                printf("Error - String is NOT completed\n");
            }
           
            nextToken = STRING;
            break;

        /* Parentheses and operators */
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

    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);

    string str(lexeme);

    ret.push_back(make_pair(nextToken, lexeme));

    return nextToken;
}

vector<pair<int, string> > Lexer::get_Token(){

    getline(cin, input);
    
    getChar();

    do{
        lex();
    } while (nextToken != EOF);
     
    return ret;
}
