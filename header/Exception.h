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
            
            case 100:
                cout << "Invalid number of arguments."<< endl;
                break;
            
            case 101:
                cout << "The variable is unbound." << endl;
            
            default:
                break;
            }
        }
};