package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;

public class Main {
	
	static boolean onlyParser = false; // for -p option
	
	public static void main(String[] args) {
		
		// This is just an example code. Use args to get -p option and actual code from CLI
		//String exampleCode = "{- {+ 2 {+ {+ 4 5} 4}} {+ 1 2}}";
		
		// expected argument length 1 or 2
		if(args.length > 2 || args.length == 0) // unexpected argument : more than 2 expression or none was entered
			System.out.println("Unexpected Argument. Enter option(optional) with the expression");
		
		else { // 2 expression or 1 expression would come to argument (with option or not)
			
			// Parser
			Parser parser = new Parser();
			
			if(args.length == 2) { // with option -p
				AST ast = parser.parse(args[1]);
				
				if(ast == null)
					System.out.println("Syntax Error!");
				
				//if(onlyParser)
				System.out.println(ast.getASTCode());
			}
			
			else {
				AST ast = parser.parse(args[0]);
				
				if(ast == null)
					System.out.println("Syntax Error!");
				
				// interpreter
				Interpreter interpreter = new Interpreter();
				
				String result = interpreter.interp(ast);
				
				System.out.println(result);
			}
			
		} // else
		
	}
}
