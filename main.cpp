#include <iostream>
#include "Person.h"
#include <mysql.h>
#include <stdlib.h>
#include "Database.h"

using namespace std;




int main() {

    Database db;
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

    }

    return 0;
}
