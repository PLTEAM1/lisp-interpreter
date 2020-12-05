#include <iostream>

using namespace std;

class Exception{
private:
    int code;
public:
    Exception(int code){
        this->code = code;
    }
    
    void print(){
        switch (code)
        {
            case 1:
                /* Variable name error */
                cout << "Variable name is not a symbol." << endl;
                break;
                
            case 2:
                /* Unbound-variable*/
                cout << "The variable is unbound" << endl;
                break;
                
            case 3:
                /* quote format error */
                cout << "Quote format error" << endl;
                break;
                
            case 4:
                /* SETQ format error */
                cout << "SETQ format error" << endl;
                break;
                
            case 5:
                /* LIST format error */
                cout << "LIST format error" << endl;
                break;
                
            case 6:
                /* CAR format error */
                cout << "CAR format error" << endl;
                break;
                
            case 8:
                /* CDR format error */
                cout << "CDR format error" << endl;
                break;
                
            case 9:
                /*  NTH index error */
                cout << "NTH index error" << endl;
                break;
                
            case 10:
                /* NTH format error */
                cout << "NTH format error" << endl;
                break;
                
            case 11:
                /* invalid number of arguments */
                cout << "Invalid number of arguments" << endl;
                break;
                
            case 12:
                /* CONS format error */
                cout << "CONS format error" << endl;
                break;
                
            case 13:
                /* REVERSE format error */
                cout << "REVERSE format error" << endl;
                break;
                
            case 14:
                /* REVERSE format error */
                cout << "Array(#) format error" << endl;
                break;

            case 15:
                /* paren count error */
                cout << "Left, Right paren count is not matched" << endl;
                break;
            
            case 16:
                /* undefined function error */
                cout << "Undefined function, check input function name" << endl;
                break;

            case 17:
                /* NIL is a constant */
                cout << "NIL is a constant and thus can't be set." << endl;
                break;

            case 18:
                /* T is a constant */
                cout << "T is a constant and thus can't be set." << endl;
                break;

                
            //용열 50 ~ basic for append, length
            case 50:
                /* LENGTH function param error*/
                cout << "Only 1 parameter is allowed for the LENGTH function." << endl;
                break;
                
            case 51:
                cout << "Only list or array parameters are allowed for the LENGTH function." << endl;
                break;
                
            case 52:
                cout << "Only list parameters are allowed for APPEND function." << endl;
                break;
                
            //용열 55 ~ conditional exception
            case 55:
                cout << "Only T or NIL can be included in the conditional statement." << endl;
                break;
                
            case 56:
                cout << "IF function must have 2 parameters." << endl;
                break;
                
            case 57:
                cout << "" << endl;
                break;
                
            case 58:
                cout << "" << endl;
                break;
                
            //용열 60 ~ Arithmetic error
            case 60:
                cout << "Only Number can be included in the add/sub/mul/div Function." << endl;
                break;
                
            case 61:
                cout << "Error - divide by zero" << endl;
                break;
                
            case 62:
                cout << "" << endl;
                break;
                
            //용열 65 ~ lexer
            case 65:
                cout << "Error - lexeme is too long." << endl;
                break;
                
            case 66:
                cout << "Error - String is NOT completed" << endl;
                break;
                
            case 67:
                cout << "Lexer error only #\\" << endl;
                break;
                
            case 68:
                cout << "Error - Wrong char after #" << endl;
                break;
                
            case 69:
                cout << "Error - floating point error" << endl;
                break;
                
            case 70:
                cout << "" << endl;
                break;
                
            case 80:
                cout << "Right variable is not a LIST." << endl;
                break;
                
            case 81:
                cout << "There is no LIST variable in LIST." << endl;
                break;
                
            case 100:
                cout << "Invalid number of arguments."<< endl;
                break;
                
            case 101:
                cout << "The variable is unbound" << endl;
                break;
                
            case 102:
                cout << "Argument is not a number." << endl;
                break;
                
            case 103:
                cout << "Left argument is not a REAL." << endl;
                break;
                
            case 104:
                cout << "Right argument is not a REAL." << endl;
                break;
                
            case 105:
                cout << "Left variable is unbound." << endl;
                break;
                
            case 106:
                cout << "Right variable is ubound." << endl;
                break;
            default:
                break;
        }
    }
};
