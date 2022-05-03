#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H
#include"Event.h"
#include"ServiceWindows.h"
#include<deque>
#include<algorithm>
using namespace std;

class QueueSystem
{
public:
	QueueSystem(int total_service_time, int total_customer_num, int windows_num, int max_service_time)
		:total_service_time(total_service_time), total_customer_num(total_customer_num), windows_num(windows_num), max_service_time(max_service_time)
	{}
	~QueueSystem()
	{
		delete[] windows;
	}
	void simulate()
	{
		run();
	}

	// 提供外部接口用于获取结果
	double get_avr_wait_time()
	{
		return avr_wait_time/serviced_customer_num;
	}
	int get_max_wait_num()
	{
		return max_wait_num;
	}
	int get_no_service_num()
	{
		return no_service_num;
	}
	int get_serviced_customer_num()
	{
		return serviced_customer_num;
	}
private:
	void run()
	{
		this->init();
		while (current_event->occur_time<=total_service_time && current_event->occur_time>=0)
		{
			if (current_event->event_type == -1)
				customerArrived();
			if (current_event->event_type >= 0)
				customerDeparture();
			*current_event = event_list.front();
			event_list.pop_front();
		}
		no_service_num = customer_list.size();
		this->makeEmpty();
	}
	// 初始化
	void init()
	{
		this->windows = new ServiceWindows[windows_num];
		for (int i = 0; i < total_customer_num; ++i)
		{
			Event* event = new Event(unifrand(0, total_service_time));
			event_list.push_back(*event);
		}
		event_list=Eorder(event_list);
		current_event = new Event(exprand(0, total_service_time));
		*current_event = event_list.front();
	}
	// 清空所有队列并设置所有窗口为空闲状态
	void makeEmpty()
	{
		for (int i = 0; i < windows_num; ++i)
			windows[i].setIdle();
		while (!customer_list.empty()) customer_list.pop_front();
		while (!event_list.empty()) event_list.pop_front();
	}
	// 获取空闲窗口索引
	int getIdleWindow()
	{
		for (int i = 0; i < windows_num; ++i)
		{
			if (windows[i].isIdle())
				return i;
		}
		return -1;
	}

	// 处理顾客到达事件
	void customerArrived()
	{
		// 将顾客加入顾客队列中
		Customer* customer = new Customer(exprand(1, max_service_time), current_event->occur_time);
		if (!customer) exit(-1);
		customer_list.push_back(*customer);
		Corder(customer_list);

		// 如果有空闲窗口就将顾客送到窗口
		int Idlewindow = getIdleWindow();
		if (Idlewindow >= 0)
		{
			serviced_customer_num++; // 已被服务的顾客数+1
			windows[Idlewindow].ServiceCustomer(customer_list.front());
			customer_list.pop_front();
			//event_list.pop();
			windows[Idlewindow].setBusy();

			// 将该顾客的离开事件放入事件队列中,离开时间为到达时间加服务时间
			Event* departureEvent = new Event(current_event->occur_time + customer->service_time, Idlewindow);
			event_list.push_back(*departureEvent);
			event_list=Eorder(event_list);
		}
		delete customer;
	}
	// 处理顾客离开事件
	void customerDeparture()
	{
		if (current_event->occur_time < total_service_time)
		{
			// 等待时间=离开事件的发生时间-顾客到达时间-顾客服务时间
			avr_wait_time += current_event->occur_time - windows[current_event->event_type].getCustomerArriveTime() - windows[current_event->event_type].getCustomerServiceTime();
			// 如果顾客队列中还有人,则将其放到窗口中
			if (!customer_list.empty())
			{
				serviced_customer_num++;
				Customer* customer=new Customer();
				*customer = customer_list.front();
				customer_list.pop_front();
				windows[current_event->event_type].ServiceCustomer(*customer);
				Event tmpEvent(current_event->occur_time + customer->service_time, current_event->event_type);
				event_list.push_back(tmpEvent);
				event_list=Eorder(event_list);
				delete customer;
			}
			// 如果顾客队列中没人,则将此窗口设为空闲
			else
				windows[current_event->event_type].setIdle();
		}
	}
	// 对事件队列进行排序,先发生的在前
	deque<Event> Eorder(deque<Event> q)
	{	
		for (int i = 0; i <= q.size(); i++)
		{
			for (int j = i + 1; j <= q.size() - 1; j++)
			{
				if (q[i].occur_time > q[j].occur_time)
				{
					swap(q[i], q[j]);
				}

			}
		}
		return q;
	}
	// 对顾客队列进行排序,优先级高的在前
	deque<Customer> Corder(deque<Customer> q)
	{
		for (int i = 0; i <= q.size(); i++)
		{
			for (int j = i + 1; j <= q.size() - 1; j++)
			{
				if (q[i].vip > q[j].vip)
				{
					swap(q[i], q[j]);
				}
				if (q[i].vip == q[j].vip)
				{
					if (q[i].arrive_time < q[j].arrive_time)
						swap(q[i], q[j]);
				}
			}
		}
		return q;
	}

	int windows_num;		// 窗口总数K
	int total_service_time; // 总服务时间T
	int total_customer_num; // 总顾客数C
	int max_service_time;   //最大处理时间L

	ServiceWindows* windows;
	deque<Customer> customer_list;
	deque<Event> event_list;
	Event* current_event;

	int serviced_customer_num=0;	// 已经被服务的顾客数
	double avr_wait_time;		// 平均等待时间 
	int max_wait_num = 0;		// 最大等待人数
	int no_service_num;			// 服务大厅关闭时还未被服务的人数
};
#endif // !QUEUESYSTEM_H
