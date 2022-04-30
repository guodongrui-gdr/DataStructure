#ifndef CUSTOMER_H
#define CUSTOMER_H

#include"random.h"
#define lamda 0.1
struct Customer
{
	int arrive_time;// 顾客到达时间
	int service_time;

	Customer(int ser=1,int arr=0):arrive_time(arr), service_time(ser){}
};
typedef struct Customer Customer;
typedef struct Customer Node;
#endif // !CUSTOMER_H