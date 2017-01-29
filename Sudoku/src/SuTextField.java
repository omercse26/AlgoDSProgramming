import javax.swing.*;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import javax.swing.text.PlainDocument;

public class SuTextField extends JTextField {
	 
    public SuTextField(int cols) {
        super(cols);
    }

    protected Document createDefaultModel() {
        return new FixedLengthPlainDocument(2);
    }

    static class FixedLengthPlainDocument  extends PlainDocument {

    	private int maxlength;

        // This creates a Plain Document with a maximum length
        // called maxlength.
        FixedLengthPlainDocument(int maxlength) {
            this.maxlength = maxlength;
        }
        
        public void insertString(int offs, String str, AttributeSet a)
            throws BadLocationException {

        	 if (str.matches("^.*[^a-zA-Z].*$") && !((getLength() + str.length()) > maxlength)) {
                 super.insertString(offs, str, a);
             }
        }
    }
}

