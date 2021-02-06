#include "packagetransaction.h"

#include <QDBusPendingCall>

#include <QDebug>

#include "constants.h"
#include "packagemanager.h"

#include <Transaction>

constexpr quint64 FlagNone{PackageKit::Transaction::TransactionFlagNone};

PackageTransaction::PackageTransaction(const QString &path, QObject *parent) :
    QDBusAbstractInterface(
        QStringLiteral("org.freedesktop.PackageKit"),
        path,
        "org.freedesktop.PackageKit.Transaction",
        QDBusConnection::systemBus(),
        parent)
{

}

quint8 PackageTransaction::operation() const
{
    return m_operation;
}

void PackageTransaction::setOperation(quint8 operation)
{
    m_operation = operation;
}

void PackageTransaction::getPackageDetails(const QStringList &ids)
{
    asyncCall(QStringLiteral("GetDetails"), ids);
}

void PackageTransaction::installPackages(const QStringList &ids)
{
    asyncCall(QStringLiteral("InstallPackages"), FlagNone, ids);
}

void PackageTransaction::removePackages(const QStringList &ids)
{
    asyncCall(QStringLiteral("RemovePackages"), FlagNone, ids, true, true);
}

void PackageTransaction::searchPackages(const QStringList &values)
{
    asyncCall(QStringLiteral("SearchNames"), FlagNone, values);
}

void PackageTransaction::updatePackages(const QStringList &ids)
{
    asyncCall(QStringLiteral("UpdatePackages"), FlagNone, ids);
}

void PackageTransaction::getUpdates()
{
    asyncCall(QStringLiteral("GetUpdates"), quint64(1));
}

void PackageTransaction::refreshCache(bool force)
{
    asyncCall(QStringLiteral("RefreshCache"), force);
}

void PackageTransaction::refreshRepo()
{
    asyncCall(QStringLiteral("RepoSetData"),
              MLS_MANAGER_REPO_ALIAS,
              "refresh-now",
              "true");
}



