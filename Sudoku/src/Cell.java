import java.lang.reflect.InvocationTargetException;



public class Cell {
	public int row;
	public int column;
	public int box;        	
	
	public MyList<Choice> choices = new MyList<Choice>();
	public boolean visited;
	
    public boolean isNotVisited() { return (visited==false); }
	
	public Cell()
	{
		row = column = -1;
	}
	
	public Cell(int i, int j)
	{
		row = i;
		column = j;
		visited = false;
		box = findBox (i,j);
		for (int x = 1; x <= Su.DIM; x++)
		{
			choices.add( new Choice(x) );
		}
	}
	
	public Cell (Cell other)
	{
		row = other.row;
		column = other.column;
		box = other.box;
		choices = new MyList<Choice> (other.choices);
		visited = other.visited;
	}

	public boolean equals (Object other)
	{
		//System.out.println("choice equals called");
		if (row == ((Cell)other).row && column == ((Cell)other).column)
			return true;
		return false;
	}
	
	public int getNonVisitedChoice()
	{		
		Choice temp = null;
		try {
			temp = choices.getNonVisited();
		} catch (NoSuchMethodException | SecurityException
				| IllegalAccessException | IllegalArgumentException
				| InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
        return temp.choice;		
	}
	
	public int findBox(int row, int col)
	{
		int sqr = (int)Math.sqrt((double)Su.DIM);
		int row_box = row / sqr;
		int column_box = col/sqr;
                row_box = row_box * sqr;                                		
		return (row_box+column_box);
	}

	public boolean matchBox(int box, int row, int column)
	{
        int box2 = findBox (row, column);
        
		if ( box2 == box)
			return true;
		
		return false;
	}	    
}

class Choice
{
	public int choice;
	public boolean visited;
	public Choice() 
	{
		choice = -1;
	}
	public Choice(int i)  
	{
		choice = i;
		visited = false;
	}
	
	public Choice(Choice other)
	{
		choice = other.choice;
		visited = other.visited;		
	}
	
	public boolean isNotVisited() 
	{ 
		return (visited==false); 
	}
    public boolean equals (Object other) 
    {     	
    	return (((Choice)other).choice == choice);
    }
}
