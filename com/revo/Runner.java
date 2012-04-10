package com.revo;

import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;

import com.revo.logging.*;
import com.revo.network.*;


public class Runner {

	public static void main(String[] args) throws IOException
	{

		
		NetworkListener netListener = new NetworkListener(59430);
		netListener.addReporter(new ReporterI() { public void report(String message) {System.out.println(message);}});
		String logPath = System.getProperty("user.dir")+File.separator+"logs"+File.separator;
		FileLogger statusLogger = new FileLogger(logPath+"status"+File.separator);
		FileLogger errorLogger = new ErrorLogger(logPath+"error"+File.separator);
		LogCollection logs = new LogCollection();
		logs.add(statusLogger);
		logs.add(errorLogger);
		netListener.setLoggers(logs);
		logs.logText("Waiting for ping on port 59429...");

		netListener.start();
	}
}
