#ifndef DBUSUTILS_H
#define DBUSUTILS_H
#include <QVariant>


class DBusUtils
{
public:
    DBusUtils();
    static QVariant readDBusProperty(const QString &service, const QString &path, const QString &interface = QString(), const char *propert = "");
//    static QVariant readDBusMethod(const QString &service, const QString &path, const QString &interface, const char *method);
};

#endif // DBUSUTILS_H
