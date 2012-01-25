package com.spherebot;

import java.io.File;
import java.io.IOException;

import com.spherebot.logging.*;
import com.spherebot.network.*;


public class Runner {

	public static void main(String[] args) throws IOException
	{
		NetworkListener netListener = new NetworkListener(12351);
		netListener.addReporter(new ReporterI() { public void report(String message) {System.out.println(message);}});
		String logPath = System.getProperty("user.dir")+File.separator+"logs"+File.separator;
		FileLogger statusLogger = new FileLogger(logPath+"status"+File.separator);
		FileLogger errorLogger = new ErrorLogger(logPath+"error"+File.separator);
		LogCollection logs = new LogCollection();
		logs.add(statusLogger);
		logs.add(errorLogger);
		netListener.setLoggers(logs);
		
		
		netListener.start();
		
		TestThread tt = new TestThread("127.0.0.1", 12351);
		tt.start();
	}
}
