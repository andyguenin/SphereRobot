package com.spherebot;
import com.spherebot.logging.LogCollection;


public interface SBModule {
	
	
	void setLoggers(LogCollection l);
	void clearLoggers();
	LogCollection getLoggers();
	
	

}
