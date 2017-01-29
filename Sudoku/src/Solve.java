import java.lang.reflect.InvocationTargetException;
import java.util.Iterator;
import java.util.Random;


public class Solve {	
	private int arr[][];	
	MyList<Cell> empty_cells;
	private int toggle;
	public Solve()
	{
		arr = new int[Su.DIM][Su.DIM];
		empty_cells = new MyList<Cell>();
		toggle = 24;
		for (int i=0; i<Su.DIM; i++)
			for (int j=0; j<Su.DIM; j++)
			{				
				if (Su.txt[i][j].getText() == null
						||Su.txt[i][j].getText().trim().equals(""))
					Su.txt[i][j].setText(Integer.toString(0));
				arr[i][j] = Integer.parseInt(Su.txt[i][j].getText());
			}
		
		populate_empty_list();
	}
	
	public void repopulate()
	{
		for (int i=0; i<Su.DIM; i++)
		{
			for (int j=0; j<Su.DIM; j++)
			{
				System.out.print(arr[i][j]);
				Su.txt[i][j].setText(Integer.toString(arr[i][j]));
			}
			System.out.println("");
		}
	}
	
	public boolean isempty (int i, int j)
	{
		if (arr[i][j] == 0)
		   return true;
		return false;
	}
	
	public void populate_empty_list()
	{
	      for (int i=0; i<Su.DIM; i++)
	          for (int j=0; j<Su.DIM; j++)
	              if (isempty(i,j))
	              {	                 
	                  empty_cells.add(new Cell(i,j));
	              }
	}
	
	private boolean randomize()
	{
		Random randomGenerator = new Random();
		if (toggle != 0)
		{
			toggle = (toggle+1) % 80;
			return true;
		}
		else
		{
								
			int num1 = randomGenerator.nextInt(1);
			int num2 = randomGenerator.nextInt(2);			
			toggle = 1;
			return (num1 == num2);
		}
	}
	
	public boolean solve() throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException
	{
	    boolean changed = true;
	    //populate_empty_list();
		while (changed)
		{
	            changed = false;

	            Iterator<Cell> it = empty_cells.iterator();
	            for (; it.hasNext() && changed == false;)
	            {				
	            		Cell cell = it.next();
	                    int row = cell.row;
	                    int column = cell.column;	                 	                    

	                    for (int i = 0; i < Su.DIM; i++)
	                            if ( i != column)
	                            {
	                            		Choice c = new Choice (arr[row][i]);
	                            	 	cell.choices.remove(c);	                                                                                 
	                            }

	                    for (int i = 0; i < Su.DIM; i++)
	                            if ( i != row)
	                            {
	                            		Choice c = new Choice (arr[i][column]);
	                                    cell.choices.remove(c);	                                   

	                            }

	                    int box = cell.findBox(row, column);

	                    for (int i=0; i<Su.DIM; i++)
	                            for (int j=0; j<Su.DIM; j++)
	                            {
	                                    if ( cell.matchBox(box, i, j) && !(row == i && column == j) )
	                                    {
	                                    	Choice c = new Choice (arr[i][j]);    
	                                    	cell.choices.remove(c);	                                            
	                                    }

	                            }

	                    if (cell.choices.size() == 1)
	                    {
	                            Choice choice = cell.choices.front();
	                            arr[row][column] = choice.choice;
	                            changed = true;
	                            empty_cells.remove(cell);	                           
	                    }                               
	            }										
		}
		
		if (empty_cells.empty())
			return true;
		else 
	    {	        	         
		     return bt();
	    }

	}
	
	public boolean bt() throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException
	{
		
			while (true)
			{
					Cell cell = empty_cells.getNonVisited();
					
					// Pick the first empty cell randomly
					while (randomize() == false)
					{
						empty_cells.remove(cell);
						empty_cells.add(cell);
						cell = empty_cells.getNonVisited();
					}
			
					if (cell == null)
					{
	                    	//System.out.println("*** empty cells exhausted ****");
	                        return false;
	                }
	        
	                
					cell.visited = true;
	                empty_cells.remove(cell);
	                //System.out.println("\tFirst Cell to be selected ("+cell.row+","+cell.column+")");
	                
	                //take the non visited first choice for that cell
	                Choice option = cell.choices.getNonVisited();
	                                  
	                // Loop through all the options until it is solved or options 
	                // are exhausted
	                while (true)
	                {
	                    if (option == null)
	                    {                        
	                    		System.out.println("\tchoice exhausted for cell ("+cell.row+","+cell.column+")");	                    		
	                    		
	                    		cell.visited = false;
	                    		empty_cells.add(cell);
	                    		arr[cell.row][cell.column] = 0;
	                    		
	                    		Iterator<Choice> it = cell.choices.iterator();
	                    		
	                    		while (it.hasNext())
	                    		{
	                    			Choice c = it.next();
	                    			c.visited = false;
	                    		}
	                    		
	                            return false;
	                    }
	                    System.out.println("\tselected choice "+ option.choice +" for cell ("+cell.row+","+cell.column+")");
	                    
	                    arr[cell.row][cell.column] = option.choice;	                    
	                    option.visited = true;
	                    MyList<Cell> empty_cell_backup = new MyList<Cell> (empty_cells);
	                    int[][] arr_backup = new int[Su.DIM][Su.DIM];
	                    
	                    for (int i=0; i<Su.DIM;i++)
	                    	for (int j=0; j<Su.DIM;j++)
	                    		arr_backup[i][j] = arr[i][j];
	                    
	                   if (!solve())
	                   {
	                            empty_cells = empty_cell_backup;
	                            
	                            for (int i=0; i<Su.DIM;i++)
	    	                    	for (int j=0; j<Su.DIM;j++)
	    	                    		arr[i][j] = arr_backup[i][j];
	                            
	                            option = cell.choices.getNonVisited();
	                   }
	                   else                                     
	                            return true;                    
	                }                   
			}
	}

}
