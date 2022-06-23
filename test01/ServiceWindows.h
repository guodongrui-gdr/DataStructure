#ifndef SERVICEWINDOWS_H
#define SERVICEWINDOWS_H

#include"Customer.h"
enum WindowsStatus
{
	SERVICE,
	IDLE,
};

class ServiceWindows
{
public:
	inline ServiceWindows() { windows_status = IDLE; }
	inline bool isIdle()
	{
		if (windows_status == IDLE)
			return true;
		else
		{
			return false;
		}
	}
	inline void ServiceCustomer(Customer& customer)
	{
		this->customer = customer;
	}
	inline void setBusy()
	{
		windows_status = SERVICE;
	}
	inline void setIdle()
	{
		windows_status = IDLE;
	}
	inline int getCustomerArriveTime()const
	{
		return customer.arrive_time;
	}
	inline int getCustomerServiceTime()const
	{
		return customer.service_time;
	}

private:
	Customer customer;
	WindowsStatus windows_status;
};
#endif // !SERVICEWINDOWS_H

