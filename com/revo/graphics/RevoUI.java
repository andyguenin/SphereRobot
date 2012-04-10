/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.revo.graphics;
import java.awt.Color;
import java.awt.event.KeyEvent;
import javax.swing.JScrollBar;


/**
 *
 * @author andy
 */
public class RevoUI extends javax.swing.JFrame {

    private String ipAddress;
    RevoCommunicator rc;

    
    /**
     * Creates new form RevoUI
     */
    
    public RevoUI() {
        initComponents();
        ipAddress = "192.168.1.200";
        connect();
        IPAddressTextField.setVisible(false);
        IPAddressLabel.setText(ipAddress);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        StatusTextLabel = new javax.swing.JLabel();
        StatusLabel = new javax.swing.JLabel();
        IPAddressTextField = new javax.swing.JTextField();
        IPAddressLabel = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        ConsoleText = new javax.swing.JTextArea();
        DisconnectButton = new javax.swing.JButton();
        jSeparator1 = new javax.swing.JSeparator();
        button1 = new java.awt.Button();
        button2 = new java.awt.Button();
        button3 = new java.awt.Button();
        button4 = new java.awt.Button();

        jScrollPane1.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

        jTextArea1.setColumns(20);
        jTextArea1.setRows(5);
        jScrollPane1.setViewportView(jTextArea1);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("REVO");
        setPreferredSize(new java.awt.Dimension(800, 500));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosed(java.awt.event.WindowEvent evt) {
                formWindowClosed(evt);
            }
        });
        addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                formKeyPressed(evt);
            }
            public void keyReleased(java.awt.event.KeyEvent evt) {
                formKeyReleased(evt);
            }
        });

        StatusTextLabel.setText("Status:");
        StatusTextLabel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                StatusTextLabelMouseClicked(evt);
            }
        });

        StatusLabel.setForeground(new java.awt.Color(255, 51, 51));
        StatusLabel.setText("disconnected");

        IPAddressTextField.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                IPAddressTextFieldFocusLost(evt);
            }
        });
        IPAddressTextField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                IPAddressTextFieldKeyPressed(evt);
            }
        });

        IPAddressLabel.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        IPAddressLabel.setText("192.168.1.200");
        IPAddressLabel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                IPAddressLabelMouseClicked(evt);
            }
        });

        jLabel1.setText("MEAM445/446 2012 Senior Design: Andy Guenin, Christine Kappeyne, Andrew McAleer, Marin McDeromott, Ian Stephens");

        jScrollPane2.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

        ConsoleText.setColumns(20);
        ConsoleText.setEditable(false);
        ConsoleText.setLineWrap(true);
        ConsoleText.setRows(5);
        ConsoleText.setWrapStyleWord(true);
        ConsoleText.setDoubleBuffered(true);
        jScrollPane2.setViewportView(ConsoleText);

        DisconnectButton.setText("Connect");
        DisconnectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                DisconnectButtonMousePressed(evt);
            }
        });

        button1.setLabel("Forward");
        button1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                forwardMouseClicked(evt);
            }
        });

        button2.setLabel("Right");
        button2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                rightMouseClicked(evt);
            }
        });

        button3.setLabel("Left");
        button3.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                leftMouseClicked(evt);
            }
        });

        button4.setLabel("Backward");
        button4.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                backwardMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jSeparator1)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(StatusTextLabel)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(StatusLabel)
                                .addGap(10, 10, 10)
                                .addComponent(IPAddressLabel)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(IPAddressTextField)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(DisconnectButton))
                            .addComponent(jScrollPane2, javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(0, 236, Short.MAX_VALUE)
                                .addComponent(jLabel1)))
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addComponent(button3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(111, 111, 111)
                                .addComponent(button2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(320, 320, 320))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(button4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(button1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(377, 377, 377))))))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(StatusTextLabel)
                    .addComponent(StatusLabel)
                    .addComponent(IPAddressTextField)
                    .addComponent(IPAddressLabel)
                    .addComponent(DisconnectButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 226, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel1)
                .addGap(24, 24, 24)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(button1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(button2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(button3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(13, 13, 13)
                .addComponent(button4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(79, 79, 79))
        );

        pack();
    }// </editor-fold>

    private void IPAddressLabelMouseClicked(java.awt.event.MouseEvent evt) {                                            
        IPAddressLabel.setVisible(false);
        IPAddressTextField.setVisible(true);
        IPAddressTextField.requestFocus();
        IPAddressTextField.setText(ipAddress);
        IPAddressTextField.selectAll();
    }                                           

    private void IPAddressTextFieldFocusLost(java.awt.event.FocusEvent evt) {                                             
        submitIPAddress();
    }                                            

    private void IPAddressTextFieldKeyPressed(java.awt.event.KeyEvent evt) {                                              
        if(evt.getKeyCode() == 10)
            submitIPAddress();
            
    }                                             

    private void StatusTextLabelMouseClicked(java.awt.event.MouseEvent evt) {                                             

    }                                            

    private void formWindowClosed(java.awt.event.WindowEvent evt) {
        synchronized(this)
        {
            disconnect();
        }
    }

    private void DisconnectButtonMousePressed(java.awt.event.MouseEvent evt) {
        if(StatusLabel.getText().equals("connected"))
        {    
            DisconnectButton.setText("Connect");
            disconnect();
        }
        else
        {
            DisconnectButton.setText("Disconnect");
            connect();
        }
    }

    private void formKeyPressed(java.awt.event.KeyEvent evt) {
        switch(evt.getKeyCode())
        {
        case(KeyEvent.VK_UP):
        	forward(true);
        	break;
        case(KeyEvent.VK_DOWN):
        	backward(true);
        	break;
        case(KeyEvent.VK_LEFT):
        	left(true);
        	break;
        case(KeyEvent.VK_RIGHT):
        	right(true);
        	break;
        case(KeyEvent.VK_Q):
        	disconnect();
        	break;
        default:
        	break;
        
        }
    }

    private void formKeyReleased(java.awt.event.KeyEvent evt) {
                switch(evt.getKeyCode())
        {
        case(KeyEvent.VK_UP):
        	forward(false);
        	break;
        case(KeyEvent.VK_DOWN):
        	backward(false);
        	break;
        case(KeyEvent.VK_LEFT):
        	left(false);
        	break;
        case(KeyEvent.VK_RIGHT):
        	right(false);
        	break;
        default:
        	break;
        
        }
    }

    private void rightMouseClicked(java.awt.event.MouseEvent evt) {
        right(true);
    }

    private void forwardMouseClicked(java.awt.event.MouseEvent evt) {
        forward(true);
    }

    private void backwardMouseClicked(java.awt.event.MouseEvent evt) {
        backward(true);
    }

    private void leftMouseClicked(java.awt.event.MouseEvent evt) {
        left(true);
    }

    public void addToConsole(String text)
    {
        JScrollBar vbar = jScrollPane2.getVerticalScrollBar();
        boolean autoScroll = ((vbar.getValue() + vbar.getVisibleAmount() + 30) >= vbar.getMaximum());

        ConsoleText.append(text + "\n");
        
        if(autoScroll)
            ConsoleText.setCaretPosition(ConsoleText.getDocument().getLength());
        
        
    }
    private void submitIPAddress()
    {
        String newIP = IPAddressTextField.getText();
        if(!newIP.equals(ipAddress))
        {
            disconnect();
            ipAddress = newIP;
            IPAddressLabel.setText(ipAddress);
            connect();
        }
        IPAddressLabel.setVisible(true);
        IPAddressTextField.setVisible(false);
    }
    
    
    private void forward(boolean enabled)
    {
    	if(enabled)
    		rc.sendMessage("f1");
    	else
    		rc.sendMessage("f0");
    }
    
    private void backward(boolean enabled)
    {
    	if(enabled)
    		rc.sendMessage("b1");
    	else
    		rc.sendMessage("b0");
    }
    
    private void left(boolean enabled)
    {
    	if(enabled)
    		rc.sendMessage("l1");
    	else
    		rc.sendMessage("l0");
    }
    
    private void right(boolean enabled)
    {
    	if(enabled)
    		rc.sendMessage("r1");
    	else
    		rc.sendMessage("r0");
    }
    
    private void connect()
    {
        rc = new RevoCommunicator(ipAddress, 59430, this);
        rc.start();
    }
    
    private void disconnect()
    {
        StatusLabel.setText("disconnected");
        StatusLabel.setForeground(Color.RED);
        rc.halt();
        
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /*
         * Set the Nimbus look and feel
         */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /*
         * If Nimbus (introduced in Java SE 6) is not available, stay with the
         * default look and feel. For details see
         * http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(RevoUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(RevoUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(RevoUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(RevoUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /*
         * Create and display the form
         */
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                new RevoUI().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify
    private javax.swing.JTextArea ConsoleText;
    private javax.swing.JButton DisconnectButton;
    private javax.swing.JLabel IPAddressLabel;
    private javax.swing.JTextField IPAddressTextField;
    public javax.swing.JLabel StatusLabel;
    private javax.swing.JLabel StatusTextLabel;
    private java.awt.Button button1;
    private java.awt.Button button2;
    private java.awt.Button button3;
    private java.awt.Button button4;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JTextArea jTextArea1;
    // End of variables declaration
}
