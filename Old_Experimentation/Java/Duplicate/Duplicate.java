import javax.swing.*;
import java.nio.*;
import java.awt.event.*;
import java.io.*;
import java.awt.*;              //for layout managers and more


public class Duplicate extends JPanel implements ActionListener{

   // Frame and TextPane
   JFrame myFrame = null;
   JTextPane myPane = null;

   // Textfield

   private String newline = "\n";
   protected static final String textFieldString = "JTextField";
  /* protected static final String passwordFieldString = "JPasswordField";
     protected static final String ftfString = "JFormattedTextField";
     protected static final String buttonString = "JButton";   */

   private Duplicate()
   {

       // Layout

	   setLayout(new BorderLayout());


       // Text fields
	   JTextField textField = new JTextField(10);
       textField.setActionCommand(textFieldString);
       textField.addActionListener(this);

	   // Password field

	   /*JPasswordField passwordField = new JPasswordField(10);
       passwordField.setActionCommand(passwordFieldString);
       passwordField.addActionListener(this);*/

	   // Time field

	   //Create a formatted text field.
       /* JFormattedTextField ftf = new JFormattedTextField(
                                         java.util.Calendar.getInstance().getTime());
        ftf.setActionCommand(textFieldString);
        ftf.addActionListener(this);*/


      //Create some labels for the fields.
        JLabel textFieldLabel = new JLabel(textFieldString + ": ");
        textFieldLabel.setLabelFor(textField);
        /*JLabel passwordFieldLabel = new JLabel(passwordFieldString + ": ");
        passwordFieldLabel.setLabelFor(passwordField);
        JLabel ftfLabel = new JLabel(ftfString + ": ");
        ftfLabel.setLabelFor(ftf);		*/


		 //Lay out the text controls and the labels.
        JPanel textControlsPane = new JPanel();
        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();

        textControlsPane.setLayout(gridbag);

        JLabel[] labels = {textFieldLabel } ; //, passwordFieldLabel, ftfLabel};
        JTextField[] textFields = {textField } ;  //, passwordField, ftf};
        addLabelTextRows(labels, textFields ,gridbag, textControlsPane);

		
		c.gridwidth = GridBagConstraints.REMAINDER; //last
        c.anchor = GridBagConstraints.WEST;
        c.weightx = 1.0;

		textControlsPane.setBorder(
                BorderFactory.createCompoundBorder(
                                BorderFactory.createTitledBorder("Text Fields"),
                                BorderFactory.createEmptyBorder(5,5,5,5)));

	   // Frame
       /*myFrame = new JFrame("Duplicate");
       myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       myFrame.setSize(300,200);*/

       // Pane
       JTextPane myPane = new JTextPane();
       myPane.setContentType("text/plain");
       myPane.setText(
          "JEditorPane is a text component to edit various kinds of"
          +" content.\n\nThis component uses implementations of the"
          +" EditorKit to accomplish its behavior.");

       //myFrame.setContentPane(myPane);


       // Menu

       /*JMenuBar myBar = new JMenuBar();
	     JMenu myMenu = getFileMenu();
	     myBar.add(myMenu);
	     myFrame.setJMenuBar(myBar);

         myFrame.setVisible(true);
		 */



		 // Put everything together
		  JPanel leftPane = new JPanel(new BorderLayout());
		  JPanel rightPane = new JPanel(new BorderLayout());

		  myPane.setPreferredSize(new Dimension(250, 155));
          myPane.setMinimumSize(new Dimension(10, 10));

          rightPane.add(myPane);

		  leftPane.add(textControlsPane,
                         BorderLayout.PAGE_START);


          leftPane.setBorder(BorderFactory.createCompoundBorder(
                              BorderFactory.createTitledBorder("Styled Text"),
                              BorderFactory.createEmptyBorder(5,5,5,5)));

		  rightPane.setBorder(BorderFactory.createCompoundBorder(
                              BorderFactory.createTitledBorder("Styled Text"),
                              BorderFactory.createEmptyBorder(10,10,10,10)));

          add(leftPane,BorderLayout.LINE_START);
		  add(rightPane,BorderLayout.LINE_END);
   }

   private void addLabelTextRows(JLabel[] labels,
                                 JTextField[] textFields,
                                 GridBagLayout gridbag,
                                 Container container)
  {
        GridBagConstraints c = new GridBagConstraints();
        c.anchor = GridBagConstraints.EAST;
        int numLabels = labels.length;

        for (int i = 0; i < numLabels; i++)
		{
            c.gridwidth = GridBagConstraints.RELATIVE; //next-to-last
            c.fill = GridBagConstraints.NONE;      //reset to default
            c.weightx = 0.0;                       //reset to default
            container.add(labels[i], c);

            c.gridwidth = GridBagConstraints.REMAINDER;     //end row
            c.fill = GridBagConstraints.HORIZONTAL;
            c.weightx = 1.0;
            container.add(textFields[i], c);
        }
    }


   // getFileMenu

   private JMenu getFileMenu()
   {
         JMenu myMenu = new JMenu("File");
         JMenuItem myItem = new JMenuItem("Open");
         myItem.addActionListener(this);
         myMenu.add(myItem);

         myItem = new JMenuItem("Save");
         myItem.addActionListener(this);
         myMenu.add(myItem);
         return myMenu;
   }


   // Action Listener

    public void actionPerformed(ActionEvent e)
    {
         String cmd = ((AbstractButton) e.getSource()).getText();
         try {
            if (cmd.equals("Open")) {
               FileReader in = new FileReader("Duplicate.txt");
               char[] buffer = new char[1024];
               int n = in.read(buffer);
               String text = new String(buffer, 0, n);
               myPane.setText(text);
               in.close();
            } else if (cmd.equals("Save")) {
			   System.out.println("Save");
               FileWriter out = new FileWriter("Duplicate.txt");
			     System.out.println("Save1");
				 String text = myPane.getText();
				 System.out.println(text);
               out.write(myPane.getText());
			     System.out.println("Save2");
               out.close();
			     System.out.println("Save3");
            }
         } catch (Exception f) {
         	 //f.printStackTrace();
         }
      }


	   private static void createAndShowGUI()
	 {
        //Create and set up the window.
        JFrame frame = new JFrame("TextSamplerDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add content to the window.
        frame.add(new Duplicate());

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }



      public static void main(String[] a) {
        // (new Duplicate()).test();
         createAndShowGUI();
   }
}
