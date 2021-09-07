#pragma once
#include "Buyer.h"
#include "Database.h"
#include "Flight.h"

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
    int add(Flight& f);

private:
    Database db;
    inline void atd_sql(string& begin, string& end, string& sql);//attendance
    inline void ttf_sql(string& begin, string& end, string& sql);//total_fare
    inline void ttb_sql(string& begin, string& end, string& sql);//total_buyer

    inline void tail(string& sql, vector<Flight> res); //请求sql语句，取得vector<Flight>
};

