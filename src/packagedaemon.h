#ifndef PACKAGEDAEMON_H
#define PACKAGEDAEMON_H

#include <QDBusAbstractInterface>

#include "packagetransaction.h"

class PackageDaemon : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit PackageDaemon(QObject *parent = nullptr);

    bool canAuthorize();
    PackageTransaction *transaction();
};

#endif // PACKAGEDAEMON_H
