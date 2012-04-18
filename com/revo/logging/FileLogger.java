package com.revo.logging;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

/**
 * Class that logs status updates, warning, and errors to a file
 * @author Andy Guenin
 * @version 01/24/2012
 *
 */
public class FileLogger implements LoggerI{
	
	File f;
	FileWriter fw;
	
	public FileLogger(String path)
	{
		initFileLogger(path, ((Long)(new Date()).getTime()).toString());	
		
	}


	public FileLogger(String path, String fname)
	{
		initFileLogger(path, fname);
	}
	
	private void initFileLogger(String path, String fname)
	{
		try
		{
			
			(new File(path)).mkdirs();
			f = new File(path + fname + ".txt");
			//f.createNewFile();
			fw = new FileWriter(f);
			
		}
		catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	private void write(String text, String preText)
	{
		Calendar c = Calendar.getInstance();
		String log = preText + c.get(Calendar.HOUR) + ":" + c.get(Calendar.MINUTE) + ":" + c.get(Calendar.SECOND) + ":" + c.get(Calendar.MILLISECOND) + " - " + (c.get(Calendar.MONTH) + 1) +"/" + c.get(Calendar.DATE) + "/" + c.get(Calendar.YEAR) + " -- " + text + "\n";
		try {
			fw.append(log.substring(0));
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			fw.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void logText(String text)
	{
		write(text, "");		
	}
	
	public void logWarning(String text)
	{
		write(text, "Warning:::");
	}
	
	public void logError(String text)
	{
		write(text, "::::::::ERROR::::::::\n");
	}

	public void logStackTrace(StackTraceElement[] element)
	{
		StringBuffer b = new StringBuffer();
		b.append("Stack Trace:\n");
		for(int i = 0; i < element.length; i++)
		{
			b.append(element[i].toString());
			b.append("\n");
		}
		write(b.toString(), "Stack Trace");
	}
}
