#ifndef EVENT_H
#define EVENT_H

#include"random.h"
#define lamda 0.1
struct Event
{
	int occur_time;// 事件发生时间
	int event_type;// 事件类型,-1表示到达事件,>=0表示离开事件
	Event* next;
	Event(int occ ,int event_Type=-1):occur_time(occ),event_type(event_Type),next(nullptr){}
};
#endif // !EVENT_H