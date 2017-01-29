#include <list>
#include <iostream>
using namespace std;

int arr [9][9] = {{0,1,4,5,2,0,0,0,9},
                  {3,0,0,0,9,0,4,5,1},
                  {5,0,8,0,0,0,0,6,7},
                  {0,0,0,0,0,3,7,0,0},
                  {0,0,6,2,0,5,1,0,0},
                  {0,0,3,4,0,0,0,0,0}, 
                  {4,3,0,0,0,0,6,0,2},
                  {8,2,7,0,4,0,0,0,5},
                  {1,0,0,0,5,2,8,4,0}
                };

template <typename T>
class MyList:public list<T>
{    
    static T nullv;
    public:       
        T& getNonVisited()
	{                
            typename list<T>::iterator it = this->begin();  
            
            for (;it != this->end(); it++)
                if (it->isNotVisited())
				{
                                        return *it;
				}
            
            return nullv;
	}
        
};

template <typename T>
T MyList<T>::nullv = T();

class Cell
{    
public:
	int row;
	int column;
	int box;        
	struct Choice
	{
		int choice;
		bool visited;
		Choice() : choice(-1) {}
		Choice(int i) : choice(i), visited(false) {}
		bool isNotVisited() { return (visited==false); }
                bool operator== (Choice other) { return (other.choice == choice);}
	};
	MyList<Choice> choices;
    bool visited;
	
    bool isNotVisited() { return (visited==false); }
	
	Cell()
	{
		row = column = -1;
	}
	
	Cell(int i, int j)
	{
		row = i;
		column = j;
		visited = false;
		box = findBox (i,j);
		for (int x = 1; x <= 9; x++)
		{
			choices.push_front( Choice(x) );
		}
	}

	bool operator == (Cell other)
	{
		if (row == other.row && column == other.column)
			return true;
		return false;
	}
	
	int getNonVisitedChoice()
	{		
		Choice temp = choices.getNonVisited();		
                return temp.choice;		
	}
	
	int findBox(int row, int col)
	{
		int row_box = row / 3;
		int column_box = col/3;
                row_box = row_box * 3;                                		
		return (row_box+column_box);
	}

	bool matchBox(int box, int row, int column)
	{
            int box2 = findBox (row, column);
		if ( box2 == box)
			return true;
		return false;
	}	    
};

MyList<Cell> empty_cells;

bool isempty (int i, int j)
{
	if (arr[i][j] == 0)
	   return true;
	return false;
}

void populate_empty_list()
{
      for (int i=0; i<9; i++)
          for (int j=0; j<9; j++)
              if (isempty(i,j))
              {
                  //cout << "populate_empty_list row " << i << " column " << j << " value " << arr[i][j] << endl;
                  empty_cells.push_front(Cell(i,j));
              }
}
bool solve ();
bool bt()
{
   while (1)
   {
       //take the non visited first element in the list	
	   
        Cell& cell = empty_cells.getNonVisited();
		
		if (cell.row == -1)
                {
                    cout << "*** TIME TO BACKTRACK ****" << endl;
                        return false;
                }
        
        //take the non visited first choice for that cell
		Cell::Choice& option = cell.choices.getNonVisited();
		cell.visited = true;
								
                if (option.choice == -1)
		{                        
			continue;
		}
		arr[cell.row][cell.column] = option.choice;	
                empty_cells.remove(cell);
                //cout << "\t***backtrace***\n";
               // cout << "\tstore " << cell.row << "," << cell.column << " :" 
                       // << option.choice << endl;
		
         // solve the rest         
         if (!solve())
         {
		option.visited = true;                
                arr[cell.row][cell.column] = 0;                
         }
         else
         {                 
             return true;
         }
    }
}

bool solve()
{
    bool changed = true;
     populate_empty_list();
	while (changed)
	{
            changed = false;

            MyList<Cell>::iterator it = empty_cells.begin();
            for (; it != empty_cells.end() && changed == false; it++)
            {				
                    int row = it->row;
                    int column = it->column;
                   // cout << endl;
                   // cout << endl;
                   // cout << "solve: taking empty cell row " << row << "  column " << column <<endl;
                    Cell& cell = *it;

                    for (int i = 0; i < 9; i++)
                            if ( i != it->column)
                            {
                                    cell.choices.remove(Cell::Choice(arr[row][i]));
                                   // cout << "solve: row: " << row << "  removed choice " << arr[row][i] << endl;                                                
                            }

                    for (int i = 0; i < 9; i++)
                            if ( i != it->row)
                            {
                                    cell.choices.remove(Cell::Choice(arr[i][column]));
                                    // cout << "solve: column" << column << "  removed choice " << arr[i][column] << endl;

                            }

                    int box = cell.findBox(row, column);

                    for (int i=0; i<9; i++)
                            for (int j=0; j<9; j++)
                            {
                                    if ( cell.matchBox(box, i, j) && !(row == i && column == j) )
                                    {
                                            cell.choices.remove(Cell::Choice(arr[i][j]));	                                                        
                                            // cout << "solve: box:" << box <<  " row: " << i << " column: " 
                                                //   << j << "  removed choice " << arr[i][j] << endl;
                                    }

                            }

                    if (cell.choices.size() == 1)
                    {
                            Cell::Choice choice = cell.choices.front();
                            arr[row][column] = choice.choice;
                            changed = true;
                            empty_cells.remove(cell);
                            //cout << "***SOLVED***: arr["<<row<<"][" << column << "] " <<choice.choice << endl;
                    }                               
            }										
	}
	
	if (empty_cells.empty())
		return true;
	else 
        {
           // cout << endl;
           // cout << "*****Couldn't solve deterministically start BACKTRACE******* " << endl;
	    return bt();
        }

}

int main()
{          	
    if (solve())
        cout << "Oh Boy SOLVED !!!!!!" << endl;
    else
        cout << "Soryy couldn't solve it" << endl;
    
    for (int i =0; i<9; i++)
    {
        for (int j=0; j<9; j++)
            cout << arr[i][j];
        cout << endl;
    }
    
}
