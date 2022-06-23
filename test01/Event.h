#ifndef EVENT_H
#define EVENT_H

#include"random.h"

struct Event
{
	int occur_time;// 事件发生时间
	int event_type;// 事件类型,-1表示到达事件,>=0表示离开事件
	Event(int occ=0 ,int event_Type=-1):occur_time(occ),event_type(event_Type){}
};
#endif // !EVENT_H