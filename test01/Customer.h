#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<cstdlib>
#include<ctime>

struct Customer
{
	int arrive_time;// 顾客到达时间
	int service_time;
	int vip;

	Customer(int ser=1,int arr=0):arrive_time(arr), service_time(ser)
	{	
		vip = 0;
		int i;
		i = rand() % 10;
		if (i == 1) vip = 1;
	}
};
typedef struct Customer Customer;
typedef struct Customer Node;
#endif // !CUSTOMER_H