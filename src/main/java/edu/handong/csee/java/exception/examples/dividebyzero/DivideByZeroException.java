package edu.handong.csee.java.exception.examples.dividebyzero;

public class DivideByZeroException extends Exception {

	public DivideByZeroException ()
	{
		super ("Dividing by Zero!");
	}

	public DivideByZeroException (String message)
	{
		super (message);
	}
}
