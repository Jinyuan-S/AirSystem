#include <iostream>
//#include "Person.h"
#include <mysql.h>
#include <stdlib.h>
#include "Database.h"

using namespace std;




int main() {

    Database db;
    vector<vector<string>> vec;
    vector<vector<string>>::iterator i;
    char a[500] = "SELECT airline,origin,destination,company,time FROM air WHERE origin=\'BEIJING\' AND destination=\'XIAN\'; ";
    db.fetchdata(a, vec);
    for (i = vec.begin(); i != vec.end(); i++) {
        vector<string>::iterator j;
        for (auto str : *i)
        {
            cout << str << endl;
        }

    }

    return 0;
}
