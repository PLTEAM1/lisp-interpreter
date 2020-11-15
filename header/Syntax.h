#ifndef SYNTAX_H
#define SYNTAX_H 

#include <utility>
#include <vector>
#include <string>

using namespace std;

class Syntax {
    private:
        vector< pair<int, string> > token;
        /* 괄호의 갯수 확인 함수 */
        bool is_valid_paren(vector<pair<int,string>>);
        /* syntax 판단 함수 */
        string check_Syntax(vector<pair<int, string>> t);
        /* 산술 연산 */
        void arithmetic_Operation();
        /* 기본 함수 */
        void basic_Function();
        /* predicate 함수 */
        void predicate_Finction();
        /* 조건문 */
        void conditional(vector< pair<int, string> > t);

    public:
        /* syntax 분석 */
        void analyze(vector< pair<int, string> > token);
};

#endif
