#include <iostream>
#include "Person.h"
#include <mysql.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Database.h"
#include "Admin.h"
#include "Buyer.h"
#include "Person.h"
#include "Inquiry.h"
#include "Order.h"


#include <algorithm>
using std::vector;


int main() {

    /*Database db;
    vector<vector<string>> vec;
    vector<vector<string>>::iterator i;
    char a[100] = "select airline from air where company=\"Air China\";";
    db.fetchdata(a, vec);
    for (i = vec.begin(); i != vec.end(); i++) {
        vector<string>::iterator j;
        for (auto str : *i)
        {
            cout << str << endl;
        }
    }*/

    Mother_order mo;
    mo.Who = "fuck";
    mo.Is_cancel = "0";
    mo.Is_paid = "0";
    mo.Money = "100";
    mo.Contain = "1";
    mo.Sub1 = "10086";

    Database db;

    //INSERT INTO mother_order(mother,who,time,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES();
    string head = "INSERT INTO mother_order(who,is_cancel,is_paid,money,contain,sub1,sub2,sub3,sub4,sub5) VALUES('";
    string tail = "');";
    string sql = head + mo.Who + "','" + mo.Is_cancel + "','" + mo.Is_paid + "','" + mo.Money + "','"
        + mo.Contain + "','" + mo.Sub1 + "','" + mo.Sub2 + "','" + mo.Sub3 + "','" + mo.Sub4 + "','" + mo.Sub5 + tail;
    
    std::cout << sql << std::endl;
    //db.query((char*)sql.c_str());
    


    //string date = "01:55:00";
    ////8 2021-08-20
    //string d1 = date.substr(8, 2);
    //string m = date.substr(5, 2);
    //string y = date.substr(0, 4);

    //int a = std::stoi(d1);
    ////std::cout << a << std::endl;
    //string d = "";
    //if (d1 > "01") {
    //    a--;
    //    d = std::to_string(a);
    //    if (d.length() < 2)
    //        d = "0" + d;
    //}
    //else {
    //    d = "31";
    //    int b = std::stoi(m);
    //    b--;
    //    m = std::to_string(b);
    //    if (m.length() < 2)
    //        m = "0" + m;
    //}
    //string out = y + "-" + m + "-" + d;
    //std::cout << out << std::endl;
    
    return 0;
}
