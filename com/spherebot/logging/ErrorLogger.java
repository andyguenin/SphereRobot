package com.spherebot.logging;

import java.io.IOException;

/**
 * Class for logging only errors to a file
 * @author Andy Guenin
 * @version 01/24/2012
 *
 */
public class ErrorLogger extends FileLogger{

	/**
	 * Creates a new error logger
	 * @param path the path to the directory where the log should be stored
	 * @throws IOException
	 */
	public ErrorLogger(String path) throws IOException {
		super(path, "error");
	}

	@Override
	public void logText(String text) {
		return;	
	}
}
