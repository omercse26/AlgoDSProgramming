import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.LinkedList;
import java.util.List;
import java.util.Iterator;


public class MyList<T>{
	
	private LinkedList<T> my;	
	public MyList()
	{
		my = new LinkedList<T>();		
	}
	
	public MyList(MyList<T> other)
	{
		Iterator<T> it = other.iterator();
		my = new LinkedList<T> ();
		while (it.hasNext())
		{
			Object obj = (Object)it.next();
			
			if (obj instanceof Cell)
			{
				Cell c = new Cell((Cell)obj);
				my.add((T)c);
			}
			else if (obj instanceof Choice)
			{
				Choice c = new Choice((Choice)obj);
				my.add((T)c);
			}
			
		}
	}
	
	public void add(T obj)
	{
		my.add(obj);
	}
	
	public T getNonVisited() throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException
	{
		for (T obj: my)
		{
			Method method = obj.getClass().getMethod("isNotVisited", null);
			boolean ret = (boolean)method.invoke(obj, null);
			if (ret)
				return obj;
		}
		
		return null;
	}
	
	public Iterator<T> iterator()
	{
		return my.iterator();
	}
	
	public void remove(T obj)
	{
		my.remove(obj);
	}
	
	public int size()
	{
		return my.size();
	}
	
	public T front()
	{
		return my.getFirst();
	}
	
	public boolean empty()
	{
		return (my.size()==0);
	}

}
