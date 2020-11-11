#ifndef SYNTAX_H
#define SYNTAX_H 

#include <utility>
#include <vector>
#include <string>

using namespace std;

class Syntax {
    private:
        vector< pair<int, string> > token;
        /* syntax 판단 함수 */
        void check_Syntax();
        /* 산술 연산 */
        void arithmetic_Operation();
        /* 기본 함수 */
        void basic_Function();
        /* predicate 함수 */
        void predicate_Finction();
        /* 조건문 */
        void conditional();

    public:
        /* syntax 분석 */
        void analyze(vector< pair<int, string> > token);
}

#endif