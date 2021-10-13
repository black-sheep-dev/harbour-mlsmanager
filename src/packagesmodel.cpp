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

bool PackagesModel::busy() const
{
    return m_busy;
}

bool PackagesModel::loading() const
{
    return m_loading;
}

bool PackagesModel::updatesAvailable() const
{
    return m_updatesAvailable;
}

void PackagesModel::setPackagesStatus(const QStringList &packageIds, quint8 status)
{
    setBusy(false);

    for (const auto &packageId : packageIds) {
        for (int i = 0; i < m_packages.count(); ++i) {
            if (m_packages.at(i).packageId().section(';', 0, 0) != packageId.section(';', 0, 0))
                continue;

            const QString version = packageId.section(";", 1, 1);

            switch (status) {
            case Package::Install:
                m_packages[i].installed = true;
                m_packages[i].installedVersion = version;
                m_packages[i].latestVersion = version;
                break;

            case Package::Remove:
                m_packages[i].installed = false;
                m_packages[i].latestVersion = version;
                break;

            case Package::Update:
                m_packages[i].updateAvailable = false;
                m_packages[i].installedVersion = version;
                m_packages[i].latestVersion = version;
                break;

            default:
                continue;
            }

            m_packages[i].progress = 0;

            const QModelIndex idx = index(i, 0, QModelIndex());
            emit dataChanged(idx, idx,
                             QVector<int>()
                             << ProgressRole
                             << InstalledRole
                             << UpdateAvailableRole
                             << InstalledVersionRole
                             << LatestVersionRole);


            break;
        }
    }
}

void PackagesModel::setPackageProgress(const QString &packageId, quint8 percentage)
{
    for (int i = 0; i < m_packages.count(); ++i) {
        if (m_packages.at(i).packageId().section(';', 0, 0) != packageId.section(';', 0, 0))
            continue;

        if (percentage != 100)
            m_packages[i].progress = percentage;

        const QModelIndex idx = index(i, 0, QModelIndex());
        emit dataChanged(idx, idx, QVector<int>() << ProgressRole);

        break;
    }
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

void PackagesModel::setBusy(bool busy)
{
    if (m_busy == busy)
        return;

    m_busy = busy;
    emit busyChanged(m_busy);
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

    case ProgressRole:
        return package.progress;

    case TypeRole:
        return package.type;

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
    roles[ProgressRole]             = "progress";
    roles[TypeRole]                 = "type";
    roles[UpdateAvailableRole]      = "updateAvailable";

    return roles;
}
