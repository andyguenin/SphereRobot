package com.spherebot.logging;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

public class FileLogger implements LoggerI{
	
	File f;
	FileWriter fw;
	
	public FileLogger(String path) throws IOException
	{
		long time = (new Date()).getTime();
		f = new File(path + File.separator + time + ".txt");
		fw = new FileWriter(f);
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
