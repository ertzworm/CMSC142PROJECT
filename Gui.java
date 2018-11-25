import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


class Gui{
    public static void main(String args[]){
       JFrame frame = new JFrame("My First GUI");
       frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       frame.setSize(400,400);

       JTextField fullWord = new JTextField(10);
       JTextField withUnderscore = new JTextField(10);
       JTextArea textArea = new JTextArea(19, 36);
       JLabel label = new JLabel("This is a label!");
       JButton button = new JButton("Generate");
	   JScrollPane scroll = new JScrollPane(textArea);
	   
	   JPanel mainPanel = new JPanel();
       JPanel top = new JPanel();
       JPanel center = new JPanel();
       mainPanel.setLayout(new BorderLayout());
       top.setLayout(new FlowLayout());
       
       mainPanel.add(top, BorderLayout.PAGE_START);
       mainPanel.add(center, BorderLayout.CENTER);
       top.add(fullWord);
       top.add(withUnderscore);
       top.add(button);
       // center.add(textArea);
       center.add(scroll);

       button.addActionListener(new ActionListener(){
		    public void actionPerformed(ActionEvent ae){
		    	String fullWordText = fullWord.getText();
		    	String withUnderscoreText = withUnderscore.getText();
		    	BackTrackCode backtrack = new BackTrackCode(fullWordText, withUnderscoreText, textArea);
		      	// textArea.setText(fullWordText + " " + withUnderscoreText);
		    }
		});
       frame.add(mainPanel);
       frame.setVisible(true);
    }
}