/**
 On my honour, I pledge that I have neither received nor provided improper assistance
 in the completion of this assignment.
 Signed: Keonho Lim        Section:01       Student Number: 21800612
 */
// infixall.cpp :
//
// The program evaluates a given infix expression which is fully parenthesized. 
// It uses Dijkstra¡¯s two-stack algorithm. For simplicity of coding, however,
// the expression is to be fully parenthesized. 
// For example: ((3 - 1 ) * 5) + 4, 2 * ((34 - 4) * 2), 1 + (((12 * 2) / 4) - 1)
// 
// Author: idebtor@gmail.com
// 2019.09.20	Creation
// 
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

// Stay tuned since we are going to use C++ Template to make them into 
// one or a generic function.
// prints stack items from botton to top recursively.

template <typename T>
void printStack(T s){
    T temp;
    
    while(!(s.empty())){
        temp.push(s.top());
        s.pop();
    }
    
    while(!(temp.empty())){
        cout << temp.top() << " ";
        s.push(temp.top());
        temp.pop();
    }
}

// performs arithmetic operations. 
int apply_op(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
    case '^': return pow(a,b);
	}
	cout << "Unsupported operator encountered: " << op << endl;
	return 0;
}

int compute(stack<int>& va_stack, stack<char>& op_stack) {
	int rigt = va_stack.top(); va_stack.pop();     // right operand first
	int left = va_stack.top(); va_stack.pop();
	char op = op_stack.top(); op_stack.pop();
    
	int ans = apply_op(left, rigt, op);
	DPRINT(cout << " va/op_stack.pop: " << left << op << rigt << " = " << ans << endl;);
	return ans;
}

int order(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '(') return 0;
    else return 2;
}

// returns value of expression after evaluation. 
int evaluate(string tokens) {
	DPRINT(cout << ">evaluate: tokens=" << tokens << endl;);
	stack<int>  va_stack;                 // stack to store operands or values
	stack<char> op_stack;                 // stack to store operators.

	for (int i = 0; i < tokens.length(); i++) {
		DPRINT(cout << " tokens[" << i << "]=" << tokens[i] << endl;);

		// current token is a whitespace or an opening brace, skip it. 
		if (tokens[i] == ' ') continue;
        
        if (tokens[i] == '(') op_stack.push(tokens[i]);

		// current token is a value(or operand), push it to va_stack. 
		if (isdigit(tokens[i])) { 
			int va = 0;
            int tem = 0;
            int count = 1;
			
            // add the code to handle multi-digits value(operand)
			va = tokens[i] - '0';
            
            if(isdigit(tokens[i+1])){
                for(;isdigit(tokens[i+1]);){
                    tem = tokens[i+1] - '0';
                    va = tem + (pow(10,count) * va);
                    i++;
                }
            }
            
            va_stack.push(va);
			DPRINT(cout << " va_stack.push: " << va << endl;);
		} // closing brace encountered; compute it and push the result to va_stack. 
		else if (tokens[i] == ')') {
            
            while(op_stack.top() != '('){
                int answer = compute(va_stack, op_stack);
                va_stack.push(answer);
            }
            op_stack.pop();
			DPRINT(cout << " va_stack.push: " << answer << endl;);
		}
        
		else { // current token is an operator; push it to op_stack.
            
            while (!op_stack.empty() && order(tokens[i]) <= order(op_stack.top())){
                if(op_stack.top() == '(') {
                    op_stack.pop();
                    break;
                }
                int answer = compute(va_stack, op_stack);
                va_stack.push(answer);
            }
            op_stack.push(tokens[i]);
			DPRINT(cout << " op_stack.push: " << tokens[i] << endl;);
		}
	}

	printStack(va_stack);
	printStack(op_stack);
    
    cout << "\nanswer : ";

	DPRINT(cout << " Parsing finished...clear va_stack and op_stack if any." << endl;);
	
    // The whole expression has been parsed at this point,
	// apply remaining op_stack to remaining va_stack. 
	
    while (!op_stack.empty()) {
        if(op_stack.top()=='(') op_stack.pop();
        
        int answer = compute(va_stack, op_stack);
        va_stack.push(answer);
        DPRINT(cout << " va_stack.push: " << answer << endl;);
	}

	DPRINT(cout << "<evaluate" << endl;);
	// va_stack top contains the result, return it. 
	return va_stack.top();
}

