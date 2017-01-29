#include <iostream>
using namespace std;

struct Matrix
{

private:
	int row;
	int col;
	int** ptr;

public:
	
	Matrix() : row(0), col(0), ptr(0) {	}

	Matrix(int row, int col, int num=0) : row(row), col(col), ptr( new int*[row])
	{				
		for (int i=0; i< row; i++)
		{
			ptr[i] = new int[col];
			for (int j=0; j<col; j++)
				ptr[i][j] = num++;
		}					
	}

	Matrix(Matrix& m)
	{
		row = m.row, col= m.col;
		ptr =  new int*[row];
		for (int i=0; i< row; i++)
                {
                        ptr[i] = new int[col];
                        for (int j=0; j<col; j++)
                                ptr[i][j] = m.ptr[i][j];
                }
	}

	Matrix& operator= (const Matrix& rhs)
	{
		if (this != &rhs)
		{
			int** new_ptr = new int*[rhs.row];
			for (int i=0; i< rhs.row; i++)
                	{
                        	new_ptr[i] = new int[rhs.col];
                        	for (int j=0; j<rhs.col; j++)
                                	new_ptr[i][j] = rhs.ptr[i][j];
			}

			for (int i=0; i<row; i++)
                        	delete[] ptr[i];
                	delete[] ptr;
			ptr = new_ptr;
			row = rhs.row;
			col = rhs.col;
		}
		return *this;
	}

	~Matrix()
	{
		//cout << "Destructor called for " << ptr << endl;
		for (int i=0; i<row; i++)
			delete[] ptr[i];
		delete[] ptr;
		row = 0;
		col = 0;
		ptr = 0;
	}

	void print()
	{
		for (int i=0; i<row; i++)
		{
			for (int j=0; j<col; j++)
				cout << ptr[i][j] << " ";
			cout << endl;
		}
	}
};
	
	
