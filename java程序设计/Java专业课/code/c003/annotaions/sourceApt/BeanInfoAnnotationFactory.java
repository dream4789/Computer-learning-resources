package C012_Annotations.sourceApt;

import java.beans.Introspector;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

import com.sun.mirror.apt.AnnotationProcessor;
import com.sun.mirror.apt.AnnotationProcessorEnvironment;
import com.sun.mirror.apt.AnnotationProcessorFactory;
import com.sun.mirror.declaration.AnnotationTypeDeclaration;
import com.sun.mirror.declaration.MethodDeclaration;
import com.sun.mirror.declaration.Modifier;
import com.sun.mirror.declaration.TypeDeclaration;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations.sourceApt 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ÉÏÎç9:15:34 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: BeanInfoAnnotationFactory.java  
 *
 * Description:  
 *
 */
public class BeanInfoAnnotationFactory implements AnnotationProcessorFactory 
{
	   public Collection<String> supportedAnnotationTypes() 
	   {
	      return Arrays.asList("Property");
	   }

	   public Collection<String> supportedOptions() 
	   {
	      return Arrays.asList(new String[0]);
	   }

	   public AnnotationProcessor getProcessorFor(Set<AnnotationTypeDeclaration> atds,
	      AnnotationProcessorEnvironment env) 
	   {
	      return new BeanInfoAnnotationProcessor(env);
	   }
	   
	   /**
	      This class is the processor that analyzes @Property annotations.
	   */
	   private static class BeanInfoAnnotationProcessor implements AnnotationProcessor 
	   {
	      BeanInfoAnnotationProcessor(AnnotationProcessorEnvironment env) 
	      {
	         this.env = env;
	      }

	      public void process()
	      {
	         for (TypeDeclaration t : env.getSpecifiedTypeDeclarations())
	         {
	            if (t.getModifiers().contains(Modifier.PUBLIC))
	            {
	               System.out.println(t);
	               Map<String, Property> props = new TreeMap<String, Property>();
	               for (MethodDeclaration m : t.getMethods())
	               {
	                  Property p = m.getAnnotation(Property.class);
	                  if (p != null)
	                  {
	                     String mname = m.getSimpleName();
	                     String[] prefixes = { "get", "set", "is" };
	                     boolean found = false;
	                     for (int i = 0; !found && i < prefixes.length; i++)
	                        if (mname.startsWith(prefixes[i]))
	                        {
	                           found = true;
	                           int start = prefixes[i].length();
	                           String name = Introspector.decapitalize(mname.substring(start));
	                           props.put(name, p);
	                        }

	                     if (!found)
	                        env.getMessager().printError(m.getPosition(), 
	                           "@Property must be applied to getXxx, setXxx, or isXxx method");
	                  }
	               }

	               try
	               {
	                  if (props.size() > 0)
	                     writeBeanInfoFile(t.getQualifiedName(), props);
	               }
	               catch (IOException e)
	               {
	                  e.printStackTrace();
	               }
	            }
	         }
	      }

	      /**
	         Writes the source file for the BeanInfo class.
	         @param beanClassName the name of the bean class
	         @param props a map of property names and their annotations
	      */
	      private void writeBeanInfoFile(String beanClassName, Map<String, Property> props) 
	         throws IOException
	      {
	         PrintWriter out = env.getFiler().createSourceFile(beanClassName + "BeanInfo");
	         int i = beanClassName.lastIndexOf(".");
	         if (i > 0)
	         {
	            out.print("package ");
	            out.println(beanClassName.substring(0, i)); 
	         }
	         out.print("public class ");
	         out.print(beanClassName.substring(i + 1));
	         out.println("BeanInfo extends java.beans.SimpleBeanInfo");
	         out.println("{");
	         out.println("   public java.beans.PropertyDescriptor[] getPropertyDescriptors()");
	         out.println("   {");
	         out.println("      try");
	         out.println("      {");
	         for (Map.Entry<String, Property> e : props.entrySet())
	         {
	            out.print("         java.beans.PropertyDescriptor ");
	            out.print(e.getKey());
	            out.println("Descriptor");
	            out.print("            = new java.beans.PropertyDescriptor(\"");
	            out.print(e.getKey());
	            out.print("\", ");
	            out.print(beanClassName);
	            out.println(".class);");            
	            String ed = e.getValue().editor().toString();
	            if (!ed.equals(""))
	            {
	               out.print("         ");
	               out.print(e.getKey());
	               out.print("Descriptor.setPropertyEditorClass(");
	               out.print(ed);
	               out.println(".class);");
	            }
	         }
	         out.println("         return new java.beans.PropertyDescriptor[]");
	         out.print("         {");
	         boolean first = true;
	         for (String p : props.keySet())
	         {
	            if (first) first = false; else out.print(",");
	            out.println();
	            out.print("            ");
	            out.print(p);
	            out.print("Descriptor");
	         }
	         out.println();
	         out.println("         };");
	         out.println("      }");
	         out.println("      catch (java.beans.IntrospectionException e)");
	         out.println("      {");
	         out.println("         e.printStackTrace();");
	         out.println("         return null;");
	         out.println("      }");
	         out.println("   }");
	         out.println("}");
	         out.close();
	      }


	      private AnnotationProcessorEnvironment env;
	    }
	}


 