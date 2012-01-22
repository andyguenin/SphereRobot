package com.spherebot;

import java.io.IOException;

import com.spherebot.logging.FileLogger;
import com.spherebot.logging.LogCollection;
import com.spherebot.network.NetworkListener;
import com.spherebot.network.ReporterI;


public class Runner {

	public static void main(String[] args) throws IOException
	{
		NetworkListener nl = new NetworkListener(12351);
		nl.addReporter(new ReporterI() { public void report(String message) {System.out.println(message);}});
		FileLogger fl = new FileLogger(System.getProperty("user.dir"));
		System.out.println(System.getProperty("user.dir"));
		LogCollection lc = new LogCollection();
		lc.add(fl);
		nl.setLoggers(lc);
		nl.start();
		TestThread tt = new TestThread("127.0.0.1", 12351);
		tt.start();
	}
}
