#include "package.h"

#include "constants.h"

#include <QVersionNumber>

PackageDTO::PackageDTO(const QString &packageId, const QString &summary) :
    id(packageId),
    summary(summary)
{

}

bool PackageDTO::operator==(const PackageDTO &other) const
{
    return id == other.id
            && summary == other.summary;
}

bool PackageDTO::operator!=(const PackageDTO &other) const
{
    return !(*this == other);
}

bool Package::isValid() const
{
    return !code.isEmpty();
}

QString Package::packageId(quint8 action) const
{

    return QStringLiteral("harbour-mls-offline-%1;%2;noarch;%3")
            .arg(code,
                 action == Remove ? installedVersion : latestVersion,
                 (installed && action != Update) ? QStringLiteral("installed") : MLS_MANAGER_REPO_ALIAS);
}

bool Package::operator==(const Package &other) const
{
    return code == other.code
            && downloadSize == other.downloadSize
            && latestVersion == other.latestVersion
            && installedVersion == other.installedVersion
            && installed == other.installed
            && name == other.name
            && updateAvailable == other.updateAvailable;
}

bool Package::operator!=(const Package &other) const
{
    return !(*this == other);
}

QDebug operator<<(QDebug d, const Package &package)
{
    d.nospace() << "Package("
                << package.code
                << ", "
                << package.name
                << ", "
                << package.installedVersion
                << ", "
                << package.installed
                << ", "
                << package.latestVersion
                << ", "
                << package.downloadSize
                << ")";
    return d;
}
