#ifndef PACKAGESMODEL_H
#define PACKAGESMODEL_H

#include <QAbstractListModel>

#include "package.h"

class PackagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool updatesAvailable READ updatesAvailable WRITE setUpdatesAvailable NOTIFY updatesAvailableChanged)

public:
    enum PackageRoles {
        CodeRole            = Qt::UserRole + 1,
        DownloadSizeRole,
        NameRole,
        InstalledRole,
        InstalledVersionRole,
        LatestVersionRole,
        ProgressRole,
        TypeRole,
        UpdateAvailableRole
    };
    Q_ENUM(PackageRoles)

    explicit PackagesModel(QObject *parent = nullptr);

    Package packageByCode(const QString &code) const;
    QList<Package> packages() const;

    // properties
    bool busy() const;
    bool loading() const;
    bool updatesAvailable() const;

signals:
    // properties
    void busyChanged(bool busy);
    void loadingChanged(bool loading);
    void updatesAvailableChanged(bool updatesAvailable);

public slots:
    void setPackagesStatus(const QStringList &packageIds, quint8 status);
    void setPackageProgress(const QString &packageId, quint8 percentage);
    void setPackages(const QList<Package> &packages);

    // properties
    void setBusy(bool busy);
    void setLoading(bool loading);   
    void setUpdatesAvailable(bool updatesAvailable);

private:
    QList<Package> m_packages;

    // properties
    bool m_busy{false};
    bool m_loading{true};
    bool m_updatesAvailable{false};

    // QAbstractItemModel interface


public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // PACKAGESMODEL_H
