#include <iostream>
#include<algorithm>
#include"random.h"
#include"QueueSystem.h"
using namespace std;
#define windows_num 5		   // 窗口总数K
#define total_service_time 480 // 总服务时间T
#define total_customer_num 500 // 总顾客数C
#define max_service_time 10    //最大处理时间L
int main()
{   
    srand(time(NULL));
        QueueSystem q(total_service_time, total_customer_num, windows_num, max_service_time);
        double avr_wait_time = 0.0, avr_no_serviced_customer_num = 0.0, avr_max_wait_num = 0.0;
        int num = 1; // 模拟次数
        for (int i = 0; i < num; ++i)
        {
            q.simulate();
            avr_wait_time += q.get_avr_wait_time();
            avr_no_serviced_customer_num += q.get_no_service_num();
            avr_max_wait_num += q.get_max_wait_num();
        }
        cout << "===================================" << endl;
        cout << "K=" << windows_num << " T=" << total_service_time << " C=" << total_customer_num << " L=" << max_service_time << endl;
        cout << "平均每名顾客等待时间:" << avr_wait_time / (double)num << endl;
        cout << "平均每次模拟未被服务人数:" << avr_no_serviced_customer_num / (double)num << endl;
        cout << "平均每次模拟队列内最大等待人数:" << avr_max_wait_num / (double)num << endl;
}
