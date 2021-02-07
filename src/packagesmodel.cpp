#include "packagesmodel.h"

PackagesModel::PackagesModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

Package PackagesModel::packageByCode(const QString &code) const
{
    for (const auto &pkg : m_packages) {
        if (pkg.code == code)
            return pkg;
    }

    return Package();
}

QList<Package> PackagesModel::packages() const
{
    return m_packages;
}

bool PackagesModel::loading() const
{
    return m_loading;
}

bool PackagesModel::updatesAvailable() const
{
    return m_updatesAvailable;
}

void PackagesModel::setPackages(const QList<Package> &packages)
{
    beginResetModel();
    m_packages.clear();

    for (const auto &pkg : packages) {
        if (!pkg.updateAvailable)
            continue;

        setUpdatesAvailable(true);
        break;
    }

    m_packages = packages;
    endResetModel();

    setLoading(false);
}

void PackagesModel::setLoading(bool loading)
{
    if (m_loading == loading)
        return;

    m_loading = loading;
    emit loadingChanged(m_loading);
}

void PackagesModel::setUpdatesAvailable(bool updatesAvailable)
{
    if (m_updatesAvailable == updatesAvailable)
        return;

    m_updatesAvailable = updatesAvailable;
    emit updatesAvailableChanged(m_updatesAvailable);
}

int PackagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_packages.size();
}

QVariant PackagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto package = m_packages.at(index.row());

    switch (role) {
    case CodeRole:
        return package.code;

    case DownloadSizeRole:
        return package.downloadSize;

    case NameRole:
        return package.name;

    case InstalledRole:
        return package.installed;

    case LatestVersionRole:
        return package.latestVersion;

    case InstalledVersionRole:
        return package.installedVersion;

    case UpdateAvailableRole:
        return package.updateAvailable;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PackagesModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CodeRole]                 = "code";
    roles[DownloadSizeRole]         = "downloadSize";
    roles[NameRole]                 = "name";
    roles[InstalledRole]            = "installed";
    roles[InstalledVersionRole]     = "installedVersion";
    roles[LatestVersionRole]        = "latestVersion";
    roles[UpdateAvailableRole]      = "updateAvailable";

    return roles;
}
