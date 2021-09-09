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
    
    /*int cnt = 1;
    vector<vector<string>> v;
    Database db;
    string s = "SELECT children,airline,com FROM children_order1;";
    db.fetch_data((char*)s.c_str(), v);
    for (auto i = v.begin(); i != v.end(); i++) {
        string tmp = (*i)[1].substr(0, 2);
        
        
        string q = "UPDATE children_order1 SET com='" + tmp + "' WHERE children=" + (*i)[0] + ";";
        db.query((char*)q.c_str());
        std::cout << cnt++ << std::endl;
    }*/

    
    return 0;
}
