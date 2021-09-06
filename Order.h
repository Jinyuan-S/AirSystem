#pragma once
#include "Mother_order.h"
#include "Database.h"
#include <vector>
#include "Children_order.h"

class Order
{
public:
	//�õ�һ���û������ж���,�����ҵ�ĸ�����ĸ���
	int get_all_order(string& id, vector<Mother_order>& vec);
	//�õ�һ��ĸ�������е��Ӷ����������ҵ��Ӷ����ĸ���
	int get_sub_order(Mother_order& mo, vector<Children_order>& vec);
	/*
	���Ӷ���:����һ��ĸ�������Ӷ���vector���Զ�����ĸ������������ӵ����ݿ⣬����bool
	�����ĸ������Ҫ��дTime��Contain��sub1-5֮���������Ϣ
	*********ע�⣺�������ڸ�ʽ����2021-9-03 ***********
	*/
	bool add_order(Mother_order& mo, vector<Children_order>& vec);
	/*
		��factor���Ե�ֵ��ע��factor�������ͷƥ�䣡�������򱨴�����û�м��쳣��⣡����
		table:�ĸ���mother_order��children_order
		factor:�ĸ��У����е���ȫ��Сд
		order_id:ĸ�����Ż����Ӷ�����
		value:���µ�ֵ
	*/
	//int change(int which, string& factor, string& order_id, string& value);
	
	//����mother_order��ֻ�������is_paid��is_cancel
	bool renew(Mother_order& mo);
	//����mother_order��ֻ�������seat
	bool renew(Children_order& co);


	//*********���������ȷ��������������û��д�����ŵ��ж�

private:
	Database db;
};

