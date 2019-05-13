#include <iostream>

using namespace std;

void CommitOrAbort(bool commit)
{
	if (commit)
		cout << "Committed" << endl;
	else
		cout << "Aborted" << endl;
}


struct AutoCommit
{
	int& sRetVal;
	
	AutoCommit(int& returnValue): sRetVal(returnValue) {}

	~AutoCommit() { CommitOrAbort(sRetVal == 0);}
};


int main()
{
	int sRetVal = 1001;
	AutoCommit autoCommit(sRetVal);
	//sRetVal = 0;
	return 0;
}