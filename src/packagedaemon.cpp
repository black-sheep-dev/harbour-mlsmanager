#include "packagedaemon.h"

#include <QDebug>

#include "constants.h"

PackageDaemon::PackageDaemon(QObject *parent) :
    QDBusAbstractInterface(
        QStringLiteral("org.freedesktop.PackageKit"),
        QStringLiteral("/org/freedesktop/PackageKit"),
        "org.freedesktop.PackageKit",
        QDBusConnection::systemBus(),
        parent)
{

}

PackageTransaction *PackageDaemon::transaction()
{
    auto reply = call(QStringLiteral("CreateTransaction"));

    const QString path = qvariant_cast<QDBusObjectPath>(reply.arguments().first()).path();

    auto t = new PackageTransaction(
        path,
        parent()
    );
    Q_ASSERT(t->isValid());

    return t;
}
