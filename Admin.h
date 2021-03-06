5333.









































#pragma once
#include "Buyer.h"
#include "Database.h"
#include "Flight.h"
//#include "Order.h"
#include <algorithm>

class Admin:public Buyer
{
public:
    string Company;

public:
    Admin();
    //按上座率排序,返回begin到end时间段内的flight数据
    void order_by_attendance(string& begin, string& end, vector<Flight>& res);
    //按总钱数排序,返回begin到end时间段内的flight数据
    void order_by_total_fare(string& begin, string& end, vector<Flight>& res);
    //按已购买人数排序,返回begin到end时间段内的flight数据（老师要求排序未起飞的航班，后端不做判定）
    void order_by_total_buyer(string& begin, string& end, vector<Flight>& res);

    //添加航班：成功返回0，找不到飞行员返回1，时间冲突返回2，航班号重复返回3
    //前端需要提供：airline,origin,destination,company,time_on,time_off,tomorrow,model,A_remain,B_remain,C_remain,date,price,pilot
    
    //判断飞行员
    int fly(Flight flt, int& which);
    int fly(Flight& flt);
    //添加航班0：正常，1：航班已存在，2：飞行员冲突
    int add_flight(Flight f);
    

private:
    Database db;

    inline void atd_sql(string& begin, string& end, string& sql);//attendance
    inline void ttf_sql(string& begin, string& end, string& sql);//total_fare
    inline void ttb_sql(string& begin, string& end, string& sql);//total_buyer

    inline void tail(string& sql, vector<Flight> res); //请求sql语句，取得vector<Flight>

    static bool cmp_time_i(vector<string> f1, vector<string> f2);
    inline int between(string& ori, string& des);
    inline int to_minute(string& time);
    
    //判断第二个飞行员，如果可以返回0
    int fly2(Flight flt);
    bool isChanged = 0;
    string ttt = "0";
};
