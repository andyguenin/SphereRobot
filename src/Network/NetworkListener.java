package Network;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Creates a script that listens for network connections and then reports on various commands
 * @author Andy Guenin
 *
 */

public class NetworkListener extends Thread {
	
	private int port;
	private ArrayList<ReporterI> reports;
	private ServerSocket ss;
	private final int NUM_CONNECTIONS = 10;
	
	public NetworkListener(int port)
	{
		this.port = port;
		reports = new ArrayList<ReporterI>();
	}
	
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
		while(true)
		{
			try {
					String message = (String)in.readObject();
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
	}

}
