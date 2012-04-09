package com.revo.graphics;

import java.applet.Applet;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class RevoUI3 extends Applet implements Runnable, KeyListener
{
	private static final long serialVersionUID = 7135238528596404218L;

	Dimension dim;
	Image offscreen;
	Graphics g;
	Thread animator;
	int frame;
	private static final int FPS = 30;
	int delay = 1000/FPS;
	int height = 400;
	int width = 800;
	RevoControl cntl;
	
	public void init()
	{
		dim = new Dimension();
		dim.height = height;
		dim.width = width;
		
		offscreen = createImage(width, height);
		g = offscreen.getGraphics();
		setSize(dim);
		setName("Revo");
		addKeyListener(this);
		cntl = new RevoControl(FPS);
	}

	public void start() {
		animator = new Thread(this);
		animator.start();
	}
	
	
	public void paint(Graphics g)
	{
		if(offscreen != null)
			g.drawImage(offscreen, 0, 0, null);
		((Graphics2D)g).setRenderingHint( RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON );

	}
	

    public void run() {
    	// Remember the starting time
    	long tm = System.currentTimeMillis();
    	while (Thread.currentThread() == animator && cntl.cont()) {
    	    // Display the next frame of animation.
    	    repaint();

    	    // Delay depending on how far we are behind.
    	    try {
    		tm += delay;
    		Thread.sleep(Math.max(0, tm - System.currentTimeMillis()));
    	    } catch (InterruptedException e) {
    		break;
    	    }

    	    // Advance the frame
    	    frame++;
    	}
    	System.exit(0);
      }

	public void update(Graphics g)
	{
		cntl.step();	
		cntl.drawScene(offscreen);
		g.drawImage(offscreen, 0, 0, null);
	}
	
	public void stop() {
		animator = null;
	}


	
	public void keyPressed(KeyEvent e) {
		char c = e.getKeyChar();
		if(c!= KeyEvent.CHAR_UNDEFINED)
		{
			RevoKeyEvent ke = new RevoKeyEvent(c, RevoKeyEvent.PressType.DOWN);
			cntl.addKeyEvent(ke);
			e.consume();
		}
		
	}

	public void keyReleased(KeyEvent e) {	
		char c = e.getKeyChar();
		if(c!= KeyEvent.CHAR_UNDEFINED)
		{
			RevoKeyEvent ke = new RevoKeyEvent(c, RevoKeyEvent.PressType.UP);
			cntl.addKeyEvent(ke);
			e.consume();
		}		
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
