
#pragma once
#include "Mother_order.h"
#include "Database.h"
#include <vector>
#include "Children_order.h"

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
	*/
	bool add_order(Mother_order& mo, vector<Children_order>& vec);
	
	//更新mother_order：只允许更新is_paid和is_cancel
	bool renew(Mother_order& mo);
	//更新mother_order：只允许更新seat
	bool renew(Children_order& co);
	
	//根据机型查找起飞地目的地：返回vector：origin,destination,time_on,time_off,tomorrow
	void where2where(vector<string>airline, vector<vector<string>> res);


private:
	Database db;
};

