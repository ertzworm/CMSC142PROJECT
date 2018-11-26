import java.util.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Project {

  public static void main(String[] args) {

    JFrame frame1 = new JFrame();
    frame1.setSize(800,600);
    JFrame frame2 = new JFrame();
    frame2.setSize(800,600);
    
    ImagePanel panel1 = new ImagePanel(
    new ImageIcon("wordscapes1.png").getImage());
    //panel1.setSize(800, 600);

    JButton startButton = new JButton();
    startButton.setPreferredSize(new Dimension(100, 50));
    startButton.setBackground(Color.LIGHT_GRAY);
    startButton.setBounds(60, 400, 220, 30);

    startButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent ae) {
            frame1.setVisible(false);
            ImagePanel panel2 = new ImagePanel(
            new ImageIcon("background.jpg").getImage());

            JLabel level1Label = new JLabel("L E V E L  1");    
            level1Label.setForeground(Color.WHITE);

            panel2.add(level1Label);
            frame2.getContentPane().add(panel2);
            frame2.pack();
            frame2.setVisible(true);
        }
    });





    JLabel startLabel = new JLabel (" P L A Y ", JLabel.CENTER); 
    startLabel.setForeground(Color.WHITE);
    startButton.add(startLabel);

    //panel1.add(panel2);

    panel1.setLayout( new GridBagLayout() );
    panel1.add(startButton, new GridBagConstraints());
    //panel1.setLayout(new BorderLayout());
    // panel1.add(startButton,BorderLayout.SOUTH);

   

    frame1.getContentPane().add(panel1);
    frame1.pack();
    frame1.setVisible(true);
    //==========================================================

    

  }
}


class ImagePanel extends JPanel {

  private Image bg;
 

  public ImagePanel(String bg) {
    this(new ImageIcon(bg).getImage());
  }

  public ImagePanel(Image bg) {
    this.bg = bg;
    Dimension size = new Dimension(bg.getWidth(null), bg.getHeight(null));
    setPreferredSize(size);
    setSize(size);
    setLayout(null);
  }

  public void paintComponent(Graphics g) {
    g.drawImage(bg, 0, 0, null);
  }

}

