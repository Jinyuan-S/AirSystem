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
        }
    }

    //设置左上角logo
    app.setWindowIcon(QIcon(":/general/images/logo.jfif"));

//    WelcomeWidget widget;
    LoginWidget widget;
    widget.show();
    return app.exec();
}
