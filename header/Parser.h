#ifndef _PARSER_H
#define _PARSER_H

#include <utility>
#include <vector>
#include <string>
#include "./Lisplist.h"
#include "./Basic.h"

using namespace std;

class Parser {
    public:
        /* 괄호의 갯수 확인 함수 */
        bool is_valid_paren(vector< pair<int, string> > t);
        /* syntax 분석 */
        List analyze(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};

#endif
