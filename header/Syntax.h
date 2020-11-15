#ifndef SYNTAX_H
#define SYNTAX_H 

#include <utility>
#include <vector>
#include <string>
//#include "./Basic.h"

using namespace std;

class Syntax {
    private:
        //vector< pair<string, string> > variables;
        //Basic basic;

        /* syntax 판단 함수 */
        string check_Syntax(vector< pair<int, string> > token);
        /* 산술 연산 */
        void arithmetic_Operation();
        /* 기본 함수 */
        void basic_Function(vector< pair<int, string> > token);
        /* predicate 함수 */
        void predicate_Finction();
        /* 조건문 */
        void conditional();

    public:
        /* syntax 분석 */
        string analyze(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
};

#endif