package com.spherebot.logging;

import java.io.IOException;

public class ErrorLogger extends FileLogger{

	public ErrorLogger(String path) throws IOException {
		super(path, "error");
	}

	@Override
	public void logText(String text) {
		return;	
	}
}
