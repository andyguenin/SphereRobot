package com.revo.graphics;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class RevoUI extends JPanel implements ActionListener, WindowListener, ChangeListener
{
	private static final long serialVersionUID = 7135238528596404218L;

	public static void main(String[] args)
	{
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				showGUI();
			}
		});
	}
	
	private static void showGUI() {
		JFrame frame = new JFrame("Revo Control");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		RevoUI r = new RevoUI();
		
		frame.add(r, BorderLayout.CENTER);
		
		frame.pack();
		frame.setSize(800, 400);
		frame.setVisible(true);

	}
	public RevoUI()
	{
		setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		JPanel statusPanel = new JPanel();
		statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.X_AXIS));
		//statusPanel.setPreferredSize(new Dimension(800,300));
		statusPanel.setAlignmentX(LEFT_ALIGNMENT);
		JLabel statusTextLabel = new JLabel("Status: ",SwingConstants.LEFT);
		JLabel statusLabel = new JLabel("not connected");
		statusPanel.add(statusTextLabel);
		statusPanel.add(statusLabel);		
		
		JPanel remarksPanel = new JPanel();
		JTextArea textArea = new JTextArea();
		JScrollPane sp = new JScrollPane(textArea);
		sp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		sp.setPreferredSize(new Dimension(780, 200));
		textArea.setEditable(false);
		textArea.setLineWrap(true);
		textArea.setWrapStyleWord(true);
		remarksPanel.add(sp);
		
		
		
		add(statusPanel);
		add(remarksPanel);
		//setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));*/
		
		//add(statusPanel);

	}

	@Override
	public void stateChanged(ChangeEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
