package com.revo.com;

import com.revo.logging.*;

public class I2CCom
{
	private LoggerI l;
	private I2CCom com;
	
	native void sc(char address, char command, char amount);
	native int gr(char address, char command);
	static {
		System.load("/usr/lib/revo/libi2ccom.so");
	}

	public I2CCom(LoggerI l)
	{
		this.l = l;
	}
	
	public void sendCommand(char address, char command, char amount)
	{
		l.logText("sending command " + (int)(command) + " : " + (int)(amount) + " to " + (int)(address));
		sc(address, command, amount);
	}
	
	public int getRequest(char address, char command)
	{
		l.logText("sending request " + (int)(command) + " to " + (int)(address));
		int response = gr(address, command);
		l.logText("Responded with: " + response);
		return response;
		
	}
}
