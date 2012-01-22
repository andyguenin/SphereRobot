package com.spherebot.logging;

public interface LoggerI {
	
	void logText(String text);
	void logWarning(String text);
	void logError(String text);
	void logStackTrace(StackTraceElement[] element);

}
