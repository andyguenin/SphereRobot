/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.revo.graphics;

import java.awt.Color;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author andy
 */
public class RevoCommunicator extends Thread{
    private int port;
    private String ipAddress;
    private ObjectOutputStream out;
    private RevoUI r;
    
    private volatile String messageToSend ="";
    private volatile boolean readyToSend = false;
    
    
    Socket requestSocket;
    
    private volatile boolean contRun;
    
    public RevoCommunicator(String ip, int startport, RevoUI r)
    {
        this.port = startport;
        ipAddress = ip;
        requestSocket = null;
        this.r = r;
        contRun = true;
        readyToSend = false;
    }
    
    public void halt()
    {
        sendMessage("quit");
        synchronized(this)
        {
            contRun = false;
        }
    }

    public void run()
    {
        boolean success = false;
        int tempPort = port;
        r.addToConsole("Pinging REVO...");
        do
        {
            success = true;
            try {
                requestSocket = new Socket();
                requestSocket.connect(new InetSocketAddress(ipAddress, port-1));
                
            } catch (UnknownHostException ex) {
                try {
                    requestSocket.close();
                } catch (IOException ex1) {
                    Logger.getLogger(RevoCommunicator.class.getName()).log(Level.SEVERE, null, ex1);
                }
                success = false;
            } catch (IOException ex) {
                try {
                    requestSocket.close();
                } catch (IOException ex1) {
                    Logger.getLogger(RevoCommunicator.class.getName()).log(Level.SEVERE, null, ex1);
                }
                success = false;
            }
        }while(!success);
        
        r.addToConsole("REVO online");
        r.addToConsole("Attempting to connect to REVO @ " + ipAddress + " on port " + port);

        do
        {
            success = true;
            try {
                requestSocket = new Socket();
                requestSocket.connect(new InetSocketAddress(ipAddress, tempPort), 1000);
                
            } catch (UnknownHostException ex) {
                try {
                    requestSocket.close();
                } catch (IOException ex1) {
                    Logger.getLogger(RevoCommunicator.class.getName()).log(Level.SEVERE, null, ex1);
                }
                success = false;
                tempPort++;
            } catch (IOException ex) {
                try {
                    requestSocket.close();
                } catch (IOException ex1) {
                    Logger.getLogger(RevoCommunicator.class.getName()).log(Level.SEVERE, null, ex1);
                }
                success = false;
                tempPort++;
            }
        }while(!success);
        
        
        r.addToConsole("Connected to " + ipAddress + ":" + port);
        r.StatusLabel.setText("connected");
        r.StatusLabel.setForeground(Color.GREEN);
        try {
            out = new ObjectOutputStream(requestSocket.getOutputStream());
            out.flush();
        } catch (IOException ex) {
            Logger.getLogger(RevoCommunicator.class.getName()).log(Level.SEVERE, null, ex);
        }
        r.addToConsole("Created output stream. Opened communications.");
        while(contRun)
        {
            if(readyToSend)
            {
                synchronized(this)
                {
                    readyToSend = false;
                    sendMessageToBeagle(messageToSend);
                }
            }
        }
        try {
            sendMessageToBeagle("quit");
            out.close();
            requestSocket.close();
        } catch (IOException ex) {
            r.addToConsole("IOError: " + ex.getMessage());
        }
        

        
    }
    
    
    public void sendMessage(String text)
    {
        while(!readyToSend)
        {
            synchronized(this)
            {
                messageToSend = text;
                readyToSend = true;
            }
        }
    }
    
    private void sendMessageToBeagle(String msg)
    {
            try{
                    out.writeObject(msg);
                    out.flush();
                    r.addToConsole("sent message: " + msg);
            }
            catch(IOException ioException){
                    ioException.printStackTrace();
            }
    }

    
}
