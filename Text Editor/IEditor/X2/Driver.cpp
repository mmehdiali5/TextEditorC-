#include<iostream>
#include<fstream>
using namespace std;
#include"IEditor.h"

int main(int argc,const char*argv[])
{
	if (*(argv[1]) == 'C')
	{
		IEditor ie;
		ie.setFileName(CString(argv[2]));
		ie.create();
		ie.start();
	}
	else if (*(argv[1]) == 'O')
	{
		IEditor ie;
		ie.setFileName(CString(argv[2]));
		ie.open();
		ie.start();
	}
	
	return 0;
}