<<<<<<< Updated upstream
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
=======
#include "loginwidget.h"
#include "welcomewidget.h"

#include <QApplication>
#include <QLocale>
#include <QIcon>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AirTicketingSystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
>>>>>>> Stashed changes
        }
    }

    //设置左上角logo
    app.setWindowIcon(QIcon(":/general/images/logo.jfif"));

//    WelcomeWidget widget;
    LoginWidget widget;
    widget.show();
    return app.exec();
}
