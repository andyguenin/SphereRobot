package com.spherebot.logging;

/**
 * Interface describing what a logger should do
 * @author Andy
 *
 */
public interface LoggerI {
	
	/**
	 * Logs normal text statuses
	 * @param text the text to log
	 */
	void logText(String text);
	
	/**
	 * Logs warning text
	 * @param text the text to log
	 */
	void logWarning(String text);
	
	/**
	 * Logs errors
	 * @param text the text to log
	 */
	void logError(String text);
	
	/**
	 * Logs an entire stack trace
	 * @param st the stack trace to log
	 */
	void logStackTrace(StackTraceElement[] st);

}
