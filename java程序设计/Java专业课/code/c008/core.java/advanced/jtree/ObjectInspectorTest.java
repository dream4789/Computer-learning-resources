package C011_SwingGui.advanced.jtree;

import java.awt.BorderLayout;
import java.lang.reflect.AccessibleObject;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.EventListener;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.EventListenerList;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui.advanced.jtree 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-4-17 ����9:29:38 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ObjectInspectorTest.java  
 *
 * Description:  
 *
 */
public class ObjectInspectorTest {
	public static void main(String[] args)
	   {  
	      JFrame frame = new ObjectInspectorFrame();
	      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	      frame.setVisible(true);
	   }
	}

	/**
	   This frame holds the object tree. 
	*/
	class ObjectInspectorFrame extends JFrame
	{  
	   /**
		 * 
		 */
		private static final long serialVersionUID = 1L;
	public ObjectInspectorFrame()
	   {  
	      setTitle("ObjectInspectorTest");
	      setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

	      // we inspect this frame object

	      Variable v = new Variable(getClass(), "this", this);
	      ObjectTreeModel model = new ObjectTreeModel();
	      model.setRoot(v);

	      // construct and show tree

	      tree = new JTree(model);
	      add(new JScrollPane(tree), BorderLayout.CENTER);
	   }

	   private JTree tree;
	   private static final int DEFAULT_WIDTH = 400;
	   private static final int DEFAULT_HEIGHT = 300;
	}

	/**
	   This tree model describes the tree structure of a Java
	   object. Children are the objects that are stored in instance
	   variables.
	*/
	class ObjectTreeModel implements TreeModel
	{ 
	   /**
	      Constructs an empty tree.
	   */
	   public ObjectTreeModel()
	   {  
	      root = null;
	   }

	   /**
	      Sets the root to a given variable.
	      @param v the variable that is being described by this tree
	   */
	   public void setRoot(Variable v)
	   {  
	      Variable oldRoot = v;
	      root = v;
	      fireTreeStructureChanged(oldRoot);
	   }

	   public Object getRoot()
	   {  
	      return root;
	   }

	   public int getChildCount(Object parent)
	   {  
	      return ((Variable) parent).getFields().size();
	   }

	   public Object getChild(Object parent, int index)
	   {  
	      ArrayList<Field> fields = ((Variable) parent).getFields();
	      Field f = (Field) fields.get(index);
	      Object parentValue = ((Variable) parent).getValue();
	      try
	      {  
	         return new Variable(f.getType(), f.getName(), f.get(parentValue));
	      }
	      catch (IllegalAccessException e)
	      {  
	         return null;
	      }
	   }

	   public int getIndexOfChild(Object parent, Object child)
	   {  
	      int n = getChildCount(parent);
	      for (int i = 0; i < n; i++)
	         if (getChild(parent, i).equals(child))
	            return i;
	      return -1;
	   }

	   public boolean isLeaf(Object node)
	   {  
	      return getChildCount(node) == 0;
	   }

	   public void valueForPathChanged(TreePath path, 
	      Object newValue)
	   {}

	   public void addTreeModelListener(TreeModelListener l)
	   {  
	      listenerList.add(TreeModelListener.class, l);
	   }

	   public void removeTreeModelListener(TreeModelListener l)
	   {  
	      listenerList.remove(TreeModelListener.class, l);
	   }

	   protected void fireTreeStructureChanged(Object oldRoot)
	   {  
	      TreeModelEvent event = new TreeModelEvent(this, new Object[] {oldRoot});
	      EventListener[] listeners = listenerList.getListeners(TreeModelListener.class);
	      for (int i = 0; i < listeners.length; i++)
	         ((TreeModelListener) listeners[i]).treeStructureChanged(event);
	   }

	   private Variable root;
	   private EventListenerList listenerList = new EventListenerList();
	}

	/**
	   A variable with a type, name, and value.
	*/
	class Variable
	{ 
	   /**
	      Construct a variable
	      @param aType the type
	      @param aName the name
	      @param aValue the value
	   */
	   @SuppressWarnings("rawtypes")
	public Variable(Class aType, String aName, Object aValue)
	   {  
	      type = aType;
	      name = aName;
	      value = aValue;
	      fields = new ArrayList<Field>();

	      // find all fields if we have a class type except we don't expand strings and null values

	      if (!type.isPrimitive() && !type.isArray() && !type.equals(String.class) && value != null)
	      {  
	         // get fields from the class and all superclasses
	         for (Class c = value.getClass(); c != null; c = c.getSuperclass())
	         {  
	            Field[] fs = c.getDeclaredFields();
	            AccessibleObject.setAccessible(fs, true);

	            // get all nonstatic fields
	            for (Field f : fs)
	               if ((f.getModifiers() & Modifier.STATIC) == 0)
	                  fields.add(f);
	         }
	      }
	   }

	   /**
	      Gets the value of this variable.
	      @return the value
	   */
	   public Object getValue() { return value; }

	   /**
	      Gets all nonstatic fields of this variable.
	      @return an array list of variables describing the fields
	   */
	   public ArrayList<Field> getFields() { return fields; }

	   public String toString()
	   {  
	      String r = type + " " + name;
	      if (type.isPrimitive()) r += "=" + value;
	      else if (type.equals(String.class)) r += "=" + value;
	      else if (value == null) r += "=null";
	      return r;
	   }

	   @SuppressWarnings("rawtypes")
	private Class type;
	   private String name;
	   private Object value;
	   private ArrayList<Field> fields;
	}
