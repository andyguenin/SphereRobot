package com.revo.network;



/**
 * Creates a script that listens for network connections and then reports on various commands
 * @author Andy Guenin
 * @version 01/24/2012
 */


import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;

import com.revo.SBModule;
import com.revo.logging.LogCollection;


public class NetworkListener extends Thread implements SBModule {
	
	private int port;
	private ArrayList<ReporterI> reports;
	private ServerSocket ss;
	private final int NUM_CONNECTIONS = 10;
	private LogCollection logs;
	private boolean cont;
	
	/**
	 * Creates a Network Listener on the specified port
	 * @param port the port to listen on
	 */
	public NetworkListener(int port)
	{
		this.port = port;
		reports = new ArrayList<ReporterI>();
		clearLoggers();		
		cont = true;
	}
	
	
	/**
	 * Adds a Reporter 
	 * @param r the reporter to add
	 */
	public void addReporter(ReporterI r)
	{
		synchronized(reports)
		{
			reports.add(r);
		}
	}
	
	/**
	 * This should contain the code that is executed when the thread is to be run.
	 * NOTE: Call NetworkListener.start(), NOT this method
	 */
	public void run()
	{

			report("Waiting for ping on port 59429");
			ServerSocket pingServer;
			try {
				pingServer = new ServerSocket(59429,1);
				pingServer.accept();
				pingServer.close();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	
			report("Ping received");
			

			Socket connection = null;
			ObjectInputStream in = null;
			do
			{
				// Tries to listen to new connections on the port specified in the constructor
				try
				{
					ss = new ServerSocket(port, NUM_CONNECTIONS);
					// The port has successfully been opened
					report("SphereServer running");
					report("Listening on port " + port);
					connection = ss.accept();
					// A remote client has successfully connected on this port
					report("SphereServer received an incoming connection from: " + connection.getInetAddress().getHostAddress() + ":" + port);
					in = new ObjectInputStream(connection.getInputStream());
				}
				catch(IOException e)
				{
					reportError(e.getMessage(), e.getStackTrace());
					
					// If the flow of execution reaches this point, there is no way to control the robot, and therefore the program
					// must stop.
					
				}
			}while(in == null);
				
			String message = "";
			while(!message.equals("quit"))
			{
				try {
						// Listens for a message to be sent
						message = (String)in.readObject();
						report(message);
					} catch (ClassNotFoundException | IOException e) {
						reportError(e.getMessage(), e.getStackTrace());
						break;
						
					}
			}
			try {
				connection.close();
				in.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				reportError(e.getMessage(), e.getStackTrace());
			}
		}
	
	
	/**
	 * Sends a report to all ReporterI and LoggerI.
	 * @param message the message to report.
	 */
	private void report(String message)
	{
		Iterator<ReporterI> reportIt = reports.iterator();
		while(reportIt.hasNext())
		{
			reportIt.next().report(message);
		}
		
		logs.logText(message);
	}
	
	/**
	 * Sends an error message to all ReporterI and LoggerI
	 * @param message the error message
	 * @param ste the stack trace, from Exception.getStackTrace()
	 */
	private void reportError(String message, StackTraceElement[] ste)
	{
		Iterator<ReporterI> reportIt = reports.iterator();
		while(reportIt.hasNext())
		{
			reportIt.next().report(message);
		}
		
		logs.logError(message);
		logs.logStackTrace(ste);
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

