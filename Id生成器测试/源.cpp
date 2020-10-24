#include<iostream>
#include"IdCreater.h"
#include<conio.h>
using namespace std;
int main()
{
	IdCreater test(1000);
	for (int i = 1; i < 10; i++)
	{
		cout<< test.out()<<endl;
	}
	_getch();
}