//
//  Arithmetic.hpp
//  pl
//
//  Created by 최용렬 on 2020/12/05.
//

#ifndef Arithmetic_hpp
#define Arithmetic_hpp

#include <string>
#include <vector>
#include "./Lisplist.h"

using namespace std;

class Arithmetic {
public:
    /* Add */
    List add(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
    /* Sub */
    List sub(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
    /* Mul */
    List mul(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
    /* Div */
    List div(vector< pair<int, string> > token, vector< pair<string, List> > *variables);
};


#endif /* Arithmetic_hpp */
