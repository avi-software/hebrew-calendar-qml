#include <QtQml>
#include <QtQml/QQmlContext>
#include "backend.h"
#include "hebdate.h"


void BackendPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("HebrewCalendar"));

    qmlRegisterType<HDate>(uri, 1, 0, "HDate");

    qRegisterMetaType<hdate_struct>("hdate_struct");

    //qmlRegisterType<hdate_struct>(uri, 1, 0, "hdate_struct");
}

void BackendPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}

