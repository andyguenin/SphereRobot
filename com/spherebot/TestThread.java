package com.spherebot;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;


public class TestThread extends Thread{
	
	private int c;
	String ip;
	int port;
	ObjectOutputStream out;
	ObjectInputStream in;
	Socket requestSocket;
	public TestThread(String ip, int port)
	{
		c = 0;
		this.ip = ip;
		this.port = port;
		
	}
	
	public void run()
	{
		
		
		
		try{
			//1. creating a socket to connect to the server
			requestSocket = new Socket(ip, port);
			System.out.println("Connected to " + ip + " in port " + port);
			//2. get Input and Output streams
			out = new ObjectOutputStream(requestSocket.getOutputStream());
			out.flush();
			
			//3: Communicating with the server
			String m = "send";
			
			do{
				if(c == 2)
				{
					m = "quit";
				}
				sendMessage(m);
				try {
					synchronized(this)
					{
						wait(2000);
					}
					c++;
				} catch (InterruptedException e) {
					System.out.println("nnnnnnnnnnnnnnnnnnnnnn");
					return;
				}
				
			}while(!m.equals("quit"));
		}
		catch(UnknownHostException unknownHost){
			System.err.println("You are trying to connect to an unknown host!");
		}
		catch(IOException ioException){
			ioException.printStackTrace();
		}
		finally{
			//4: Closing connection
			try{
				out.close();
				requestSocket.close();
			}
			catch(IOException ioException){
				ioException.printStackTrace();
			}
		}
	}
	
	void sendMessage(String msg)
	{
		try{
			out.writeObject(msg);
			out.flush();
		}
		catch(IOException ioException){
			ioException.printStackTrace();
		}
	}


}
