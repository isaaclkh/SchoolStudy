//
//  stlstack.cpp
//  Solution
//
//  Created by Isaac on 30/09/2019.
//  Copyright © 2019 Isaac. All rights reserved.
//

#include "stlstack.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    stack <char> s;
    s.push('a');
    s.push('b');
    s.push('c');
    
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    
    return 0;
}
