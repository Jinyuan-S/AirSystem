
#pragma once
#include "Mother_order.h"
#include "Database.h"
#include <vector>
#include "Children_order.h"
#include <algorithm>


class Order
{
public:
	//拿到一个用户的所有订单,返回找到母订单的个数
	int get_all_order(string& id, vector<Mother_order>& vec);
	//拿到一个母订单所有的子订单，返回找到子订单的个数
	int get_sub_order(Mother_order& mo, vector<Children_order>& vec);
	/*
	增加订单:传入一个母订单和子订单vector，自动填满母订单，并且添加到数据库，返回bool
	传入的母订单需要填写Time、Contain和sub1-5之外的其他信息
	子订单的舱位必须是A,B,C格式，否则出错
	子订单日期必须是 9.03 的格式，否则出错

	conf_idx是冲突的vector<Children_order>下标，如果不冲突返回-1，children是冲突的已有订单对象

	返回值：
		0：成功购买
		1：当前正在飞机上
		2：不能及时从上一趟航班落地地赶到新加航班起飞地
		3：来不及从新加航班目的地赶往下一班航班出发地
	*/
	//bool add_order(Mother_order& mo, vector<Children_order>& vec);
	int add_order(Mother_order& mo, vector<Children_order>& vec, int& conf_idx, Children_order& conf);
	
	//更新mother_order：只允许更新is_paid和is_cancel
	bool renew(Mother_order& mo);
	//更新mother_order：只允许更新seat
	bool renew(Children_order& co);
	
	//根据机型查找起飞地目的地：返回vector：origin,destination,time_on,time_off,tomorrow
    void where2where(vector<string>airline, vector<vector<string>> &res);

	//查询飞行员/用户能不能到达
	//bool wuhu(string land, string off);
	/*
		用户能不能买,传入的时间格式一定是hh:mm:ss，返回冲突订单号
		0:可以买
		1：当前正在飞机上
		2：不能及时从上一趟航班将落地赶到新加航班起飞地
		3：来不及从新加航班目的地赶往下一班航班出发地
	
	*/
	int cannot(Children_order& co, string& conflit);

private:
	Database db;
	//比较函数，按照落地时间比较大小（从小到大)
	static bool cmp_timei(vector<string> f1, vector<string> f2);
	//将hh:mm:ss的形式转化成分钟
	inline int to_minute(string& time);
	//查询两个地方之间的距离（分钟）
	inline int between(string& ori, string& des);
	//通过航班号和日期在children_order中寻找订单号children
	inline string get_conflict(string& airline, string& date);
};

