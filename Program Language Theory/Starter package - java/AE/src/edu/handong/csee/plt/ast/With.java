package edu.handong.csee.plt.ast;

public class With extends AST{
	char id;
	AST lhs = new AST();
	AST rhs = new AST();
	
	public With(char id, AST lhs, AST rhs) {
		this.id = id;
		this.lhs = lhs;
		this.rhs = rhs;
	}
	
	public AST getLhs() {
		return lhs;
	}

	public AST getRhs() {
		return rhs;
	}

	public String getASTCode() {
		return "(sub " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}
}
