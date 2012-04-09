package com.revo.graphics;

import java.awt.Image;


public class RevoControl {
	
	private double fps;
	public static enum KeyEvent{ Left, Right, Forward, Backward, Stop, Config};
	private byte[] status = {0,0,0,0};
	private boolean cont;
	public RevoControl(double fps)
	{
		this.fps = fps;
		cont = true;
	}
	
	public void addKeyEvent(RevoKeyEvent ke)
	{
		switch(ke.getChar())
		{
		case 'q':
			cont = false;
			break;
		}
	}
	
	public void step()
	{
		
	}
	
	public void drawScene(Image offscreen)
	{
		
	}
	
	public boolean cont()
	{
		return cont;
	}

}
