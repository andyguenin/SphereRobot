package com.spherebot.network;



/**
 * Creates a script that listens for network connections and then reports on various commands
 * @author Andy Guenin
 *
 */


import com.spherebot.SBModule;
import com.spherebot.logging.LogCollection;
import com.spherebot.logging.LoggerI;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;


public class NetworkListener extends Thread implements SBModule {
	
	private int port;
	private ArrayList<ReporterI> reports;
	private ServerSocket ss;
	private final int NUM_CONNECTIONS = 10;
	private LogCollection logs;
	
	/**
	 * Creates a Network Listener on the specified port
	 * @param port the port to listen on
	 */
	public NetworkListener(int port)
	{
		this.port = port;
		reports = new ArrayList<ReporterI>();
		clearLoggers();		
	}
	
	
	/**
	 * Adds a Reporter 
	 * @param r
	 */
	public void addReporter(ReporterI r)
	{
		synchronized(reports)
		{
			reports.add(r);
		}
	}
	
	
	public void run()
	{
		Socket connection;
		ObjectInputStream in;
		try
		{
			ss = new ServerSocket(port, NUM_CONNECTIONS);
			report("SphereServer running");
			connection = ss.accept();
			report("SphereServer received an incoming connection from: " + connection.getInetAddress().getHostAddress());
			in = new ObjectInputStream(connection.getInputStream());
		}
		catch(IOException e)
		{
			report("error: " + e.getMessage());
			return;
		}
		String message = "";
		while(!message.equals("quit"))
		{
			try {
					message = (String)in.readObject();
					report(message);
				} catch (ClassNotFoundException | IOException e) {
					report("error: " + e.getMessage());
				}
		}
	}
	
	
	
	private void report(String message)
	{
		Iterator<ReporterI> reportIt = reports.iterator();
		while(reportIt.hasNext())
		{
			reportIt.next().report(message);
		}
		
		Iterator<LoggerI> logIt = logs.iterator();
		while(logIt.hasNext())
		{
			logIt.next().logText(message);
		}
	}



	@Override
	public void setLoggers(LogCollection l) {
		logs = l;
		
	}


	@Override
	public void clearLoggers() {
		logs = new LogCollection();
		
	}


	@Override
	public LogCollection getLoggers() {
		return logs;
	}

}

