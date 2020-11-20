#ifndef _SYNTAX_H
#define _SYNTAX_H

#include <utility>
#include <vector>
#include <string>
#include "./Lisplist.h"
#include "./Basic.h"

using namespace std;

class Syntax {
    private:
        vector< pair<int, string> > token;
        /* 괄호의 갯수 확인 함수 */
        bool is_valid_paren(vector< pair<int, string> > t);
        /* syntax 판단 함수 */
        string check_Syntax(vector< pair<int, string> > token);
        /* 산술 연산 */
        void arithmetic_Operation();
        /* 기본 함수 */
        void basic_Function(vector< pair<int, string> > token);
        /* predicate 함수 */
        bool isNumber(string str);
        void predicate_Function(vector< pair<int, string> > t);

        /* 조건문 */
        void conditional();

    public:
        /* syntax 분석 */
        List analyze(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};

#endif
