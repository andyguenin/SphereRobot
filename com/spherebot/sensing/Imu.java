package com.spherebot.sensing;

import com.spherebot.SBModule;
import com.spherebot.logging.LogCollection;

public class Imu implements SBModule{
	LogCollection logCollection;
	
	
	
	
	@Override
	public void setLoggers(LogCollection logCollection) {
		this.logCollection = logCollection;
		
	}

	@Override
	public void clearLoggers() {
		logCollection = new LogCollection();
		
	}

	@Override
	public LogCollection getLoggers() {
		return logCollection;
	}

}
