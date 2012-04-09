package com.revo.graphics;

public class RevoKeyEvent {

	public static enum PressType { DOWN, UP };
	
	private char k;
	private PressType p;
	public RevoKeyEvent(Character k, PressType p)
	{
		this.k = k.charValue();
		this.p = p;
	}
	
	public PressType getPressType()
	{
		return p;
	}
	
	public char getChar()
	{
		return k;
	}
	
}
