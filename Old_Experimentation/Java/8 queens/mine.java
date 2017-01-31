import java.io.*;
class Eight
{
  static byte chessboard[][] = {
	                             {0,0,0,0,0,0,0,0},
	                             {0,0,0,0,0,0,0,0},
	                             {0,0,0,0,0,0,0,0},
	                             {0,0,0,0,0,0,0,0},
	                             {0,0,0,0,0,0,0,0},
								 {0,0,0,0,0,0,0,0},
								 {0,0,0,0,0,0,0,0},
	                             {0,0,0,0,0,0,0,0},
                            };
  public static int CHESS = 8;
  public static void main(String args[])
  {

    Eight singularity = new Eight();
    Stack stack = new Stack();
    Hold_Pos st_obj=null;
    boolean flag = true;
	//int o;
    int j = 0;
	//System.in(o);
    //singularity.print();
    for (int i=0;i<=CHESS;i++)
    {
		if (flag==true)
		{
          if (i==CHESS)
             break;
		  flag = false;
		  j = 0;
	    }
	    else
	    {
			 //System.out.println(i+"  "+j);
			 st_obj = stack.pop();
		     i = st_obj.row;
             j = st_obj.col + 1;
             Eight.chessboard[i][j-1] = 0;
             //System.out.println("--> Popped after "+i+"  "+j);
             if (j > CHESS-1)
                 continue;
	    }
		for (;j<CHESS;j++)
		{
			//System.out.println("processing "+i+"  "+j);
			if (singularity.isSafe(i,j))
			{
			   Eight.chessboard[i][j] = 1;
			   stack.push(i,j);
			   flag = true;
			   break;
		    }
	    }

	}
	//System.out.println("Omer Asif");
	singularity.print();

  }

  private void print()
  {
	 for (int i=0;i<CHESS;i++)
     {
		for (int j=0;j<CHESS;j++)
		{
			System.out.print(Eight.chessboard[i][j]);
	    }
	    System.out.println();
	 }
  }


  private boolean isSafe(int row,int col)
  {

    for (int i=0;i<row;i++)
		if (Eight.chessboard[i][col] == 1)
		   return false;

	for (int i=0;i<col;i++)
	    if (Eight.chessboard[row][i] == 1)
		   return false;

	for (int i=row,j=col;i>=0&&j>=0;i--,j--)
		if (Eight.chessboard[i][j] == 1)
		   return false;

    for (int i=row,j=col;i>=0&&j<CHESS;i--,j++)
		if (Eight.chessboard[i][j] == 1)
		   return false;

	/*for (int i=row,j=col;i<CHESS&&j>=0;i++,j--)
			if (Eight.chessboard[i][j] == 1)
		   return false;*/

    /*for (int i=row,j=col;i<CHESS&&j<CHESS;i++,j++)
		if (Eight.chessboard[i][j] == 1)
		   return false;*/

    return true;
 }

}


class Stack
{
    public int top;
	public Hold_Pos st_obj[] = new Hold_Pos[10];
	public Stack()
	{
		top=-1;
		for (int i=0;i<10;i++)
          st_obj[i] = new Hold_Pos();
	}

    public void push(int i,int j)
    {
		top++;
		st_obj[top].row = i;
		st_obj[top].col = j;
		//System.out.println("--> pushed "+i+"and "+j);
		//System.out.println("--> top is "+top);
    }

    public Hold_Pos pop()
    {
		if (top >= 0 )
		{
		  top--;
		  return st_obj[top+1];
	    }
	    else
	    {
			System.out.println("Fatal error!");
			return null;
	    }
    }
}

class Hold_Pos
{
		int row;
		int col;

  public Hold_Pos ()
  {}
};





