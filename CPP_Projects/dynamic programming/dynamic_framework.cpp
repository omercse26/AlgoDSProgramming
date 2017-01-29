#include <iostream>.
#include <vector>
#include <limits>
#define NUM1 38
#define NUM2 5

using namespace std;
 
int global_range[] = {1,5,10,25};
int table[NUM1][NUM2];

int test_scenario(int i, int k, vector<int> range, int vs)
{
	cout << "Total of : " << i << " with the ranges [";
	
	for (int j=0; j<range.size(); j++)
        {
            if (j != range.size()-1)		
                cout << range[j] << "," ;
        }
               
       if (range.size()-1 <= range.size())
        {                   
                cout << range[range.size()-1] ;
        }
        cout << "] ";
        
        cout << "= " << table[i][k];
        cout << "   (vs)   " ;//<<endl;

	int row;
	int column;
	int range_size;
		
	switch (vs)
	{
		case 1:  // Diagonally one above
			row = i-1;
			column = k-1;
			range_size = range.size()-1;
			break;
		case 2: // one up
			row = i-1;
			column = k;
			range_size = range.size();
			break;
			
		case 3: // one to the left- more complex since we will be having new denominations.
			row = i;
			column = k-1;
			range_size = range.size()-1;
			break;		
	}
	cout << "Total of : " << row << " with the ranges [";		
	for (int j=0; j<range_size-1; j++)
        {            
                cout << range[j] << "," ;
        }
        
        if (range_size>0)
        {                   
                cout << range[range_size-1] ;
        }
        cout << "] ";
        
        cout << "= " << table[row][column];
        cout << endl;
        
        if (table[row][column] == -1)
        {
            cout << " comparison invalidated" << endl;
            return -1;
        }
        
        cout << "   The diff in total is " << i-row << endl;
        
        if (i-row == 1)
            return table[row][column]+1;
        
        int min = 0;
        int size = k-1;
        
        // find the no. of coins with the new denomination + optimal solution 
        // for the remaining change in the table
        while (i >= range[range_size])
        {
            i -= range[range_size];
            min++;
        }
        
        min = min+table[i][size];
        return min;

}

int main()
{
    for (int i=0; i<NUM1; i++)    
        table[i][0] = -1;   
    
    for (int j=0; j<NUM2; j++)    
        table[0][j] = 0;    
            
    int min1, min2, min3;
    int min;
    //char dummy[10];
    for (int i=1; i < NUM1; i++)
        for (int j=1; j < NUM2;j++)
        {
            min1 = test_scenario(i, j, vector<int>(global_range, global_range + size_t(j)),1);
            min2 = test_scenario(i, j, vector<int>(global_range, global_range + size_t(j)),2);
            min3 = test_scenario(i, j, vector<int>(global_range, global_range + size_t(j)),3);
            cout << "  The results are min1: " << min1 << " min2: " << min2 
                    << " min3 " << min3 << endl;
            if (min1 != -1)
                min = min1;
            
            if (min2 != -1 && (min > min2 || min1 == -1))
                min = min2;
            
            if (min3 != -1 && (min > min3 || min1==-1 || min2==-1))
                min = min3;
            cout << "  Selected for i: "<<i << " j: " << j << " min " <<  min << endl;
            table[i][j] = min;
            //cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            //fflush(stdin);
            
        }
    
    
     cout << "SO THE MINIMUM NUMBER OF COINS : " << table[NUM1-1][NUM2-1];
     return 0;
    
}