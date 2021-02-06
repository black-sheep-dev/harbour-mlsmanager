#include "package.h"

#include "constants.h"

#include <QVersionNumber>

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
            && installed == other.installed;
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
