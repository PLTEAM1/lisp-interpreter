#ifndef _SYNTAX_H
#define _SYNTAX_H

#include <utility>
#include <vector>
#include <string>
#include "./Lisplist.h"
#include "./Basic.h"

using namespace std;

class Syntax {
    public:
        /* 괄호의 갯수 확인 함수 */
        bool is_valid_paren(vector< pair<int, string> > t);
        /* syntax 분석 */
        List analyze(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};

#endif
