package com.spherebot;
import com.spherebot.logging.LogCollection;

/**
 * This interface is implemented by all modules within the spherebot for easy reporting
 * @author Andy Guein
 * @version 01/24/2012
 */
public interface SBModule {
	
	/**
	 * Sets all of the loggers for the module.
	 * @param logCollection
	 */
	void setLoggers(LogCollection logCollection);
	
	/**
	 * Clears all of the loggers
	 */
	void clearLoggers();
	
	/**
	 * Returns the collection of loggers
	 * @return the collection of loggers
	 */
	LogCollection getLoggers();
	
	

}
