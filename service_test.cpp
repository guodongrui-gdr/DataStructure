#include <iostream>
#include<algorithm>
#include"random.h"
#include"QueueSystem.h"
using namespace std;

int main()
{   
    QueueSystem q(480,1000,5,10);
    q.simulate();
    cout << "平均等待时间为" << q.get_avr_wait_time() << endl;
    cout << "服务顾客数为" << q.get_serviced_customer_num() << endl;
    cout << q.get_no_service_num();
}
