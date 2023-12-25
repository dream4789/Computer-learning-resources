import java.awt.*;
import java.awt.event.ActionEvent;

import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.IOException;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JEditorPane;
import javax.swing.JTextPane;
import javax.swing.UIManager;
import javax.swing.text.*;
import javax.swing.event.*;
import javax.swing.plaf.*;

/*
 * @author Timothy Prinzing
 * @version 1.94 11/17/05
 * @see javax.swing.text.StyledEditorKit
 */
public class MyJTextJPane extends JTextPane {

	public StringBuffer sbText = new StringBuffer();

	/**
	 * Creates a new <code>JTextPane</code>. A new instance of
	 * <code>StyledEditorKit</code> is created and set, and the document model
	 * set to <code>null</code>.
	 */
	public MyJTextJPane() {
		super();
	}

	/**
	 * Creates a new <code>JTextPane</code>, with a specified document model. A
	 * new instance of <code>javax.swing.text.StyledEditorKit</code> is created
	 * and set.
	 * 
	 * @param doc
	 *            the document model
	 */
	public MyJTextJPane(StyledDocument doc) {
		super(doc);
	}

	public void insertIcon(ImageIcon g,String icon) {
		MutableAttributeSet inputAttributes = getInputAttributes();
		inputAttributes.removeAttributes(inputAttributes);
		StyleConstants.setIcon(inputAttributes, g);
		replaceSelection(icon, false);
		inputAttributes.removeAttributes(inputAttributes);
	}

	private void replaceSelection(String content, boolean checkEditable) {
		if (checkEditable && !isEditable()) {
			UIManager.getLookAndFeel().provideErrorFeedback(this);
			return;
		}
		Document doc = getStyledDocument();
		if (doc != null) {
			try {
				Caret caret = getCaret();
				int p0 = Math.min(caret.getDot(), caret.getMark());
				int p1 = Math.max(caret.getDot(), caret.getMark());
				AttributeSet attr = getInputAttributes().copyAttributes();
				if (doc instanceof AbstractDocument) {
					((AbstractDocument) doc)
							.replace(p0, p1 - p0, content, attr);
				} else {
					if (p0 != p1) {
						doc.remove(p0, p1 - p0);
					}
					if (content != null && content.length() > 0) {
						doc.insertString(p0, content, attr);
					}
				}
			} catch (BadLocationException e) {
				UIManager.getLookAndFeel().provideErrorFeedback(this);
			}
		}
	}

	/**
	 * Adds a new style into the logical style hierarchy. Style attributes
	 * resolve from bottom up so an attribute specified in a child will override
	 * an attribute specified in the parent.
	 * 
	 * @param nm
	 *            the name of the style (must be unique within the collection of
	 *            named styles). The name may be <code>null</code> if the style
	 *            is unnamed, but the caller is responsible for managing the
	 *            reference returned as an unnamed style can't be fetched by
	 *            name. An unnamed style may be useful for things like character
	 *            attribute overrides such as found in a style run.
	 * @param parent
	 *            the parent style. This may be <code>null</code> if unspecified
	 *            attributes need not be resolved in some other style.
	 * @return the new <code>Style</code>
	 */
	public Style addStyle(String nm, Style parent) {
		StyledDocument doc = getStyledDocument();
		return doc.addStyle(nm, parent);
	}

	/**
	 * Removes a named non-<code>null</code> style previously added to the
	 * document.
	 * 
	 * @param nm
	 *            the name of the style to remove
	 */
	public void removeStyle(String nm) {
		StyledDocument doc = getStyledDocument();
		doc.removeStyle(nm);
	}

	/**
	 * Fetches a named non-<code>null</code> style previously added.
	 * 
	 * @param nm
	 *            the name of the style
	 * @return the <code>Style</code>
	 */
	public Style getStyle(String nm) {
		StyledDocument doc = getStyledDocument();
		return doc.getStyle(nm);
	}

	/**
	 * Sets the logical style to use for the paragraph at the current caret
	 * position. If attributes aren't explicitly set for character and paragraph
	 * attributes they will resolve through the logical style assigned to the
	 * paragraph, which in term may resolve through some hierarchy completely
	 * independent of the element hierarchy in the document.
	 * <p>
	 * This method is thread safe, although most Swing methods are not. Please
	 * see <A HREF=
	 * "http://java.sun.com/docs/books/tutorial/uiswing/misc/threads.html">How
	 * to Use Threads</A> for more information.
	 * 
	 * @param s
	 *            the logical style to assign to the paragraph, or
	 *            <code>null</code> for no style
	 */
	public void setLogicalStyle(Style s) {
		StyledDocument doc = getStyledDocument();
		doc.setLogicalStyle(getCaretPosition(), s);
	}

}
