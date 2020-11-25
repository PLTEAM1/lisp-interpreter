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
                /* code */
                cout << "SETQ variable error." << endl;
                break;

            case 2:
                /* code */
                cout << "code2" << endl;
                break;

            case 3:
                /* code */
                cout << "code3" << endl;
                break;

            case 4:
                /* code */
                cout << "code4" << endl;
                break;
            
            default:
                break;
            }
        }
};