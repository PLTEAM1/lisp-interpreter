//
//  conditional.hpp
//  pl
//
//  Created by 최용렬 on 2020/11/17.
//

#ifndef Conditional_h
#define Conditional_h

#include <string>
#include <vector>
#include "./Lisplist.h"

using namespace std;

/** 
 * Class that performs the conditional functions of the interpreter.
 * 
 * @date 2020.11.29
 * @version 1.0
 */
class Conditional{
    private:
    
    public:
        List _IF(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
        List _COND(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};

#endif /* conditional_hpp */
