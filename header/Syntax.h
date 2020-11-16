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
        bool is_valid_paren(vector<pair<int,string> >);
        /* syntax 판단 함수 */
        string check_Syntax(vector< pair<int, string> > token);
        /* 산술 연산 */
        void arithmetic_Operation();
        /* 기본 함수 */
        void basic_Function(vector< pair<int, string> > token);

        /* 조건문 */
        void conditional();

    public:
        /* syntax 분석 */
        string analyze(vector< pair<int, string> > token, vector< pair<string, string> > *variables);
};

#endif
