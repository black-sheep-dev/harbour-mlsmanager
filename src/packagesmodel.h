#ifndef PACKAGESMODEL_H
#define PACKAGESMODEL_H

#include <QAbstractListModel>

#include "package.h"

class PackagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)

public:
    enum PackageRoles {
        CodeRole            = Qt::UserRole + 1,
        DownloadSizeRole,
        NameRole,
        InstalledRole,
        InstalledVersionRole,
        LatestVersionRole,
        UpdateAvailableRole
    };
    Q_ENUM(PackageRoles)

    explicit PackagesModel(QObject *parent = nullptr);

    Package packageByCode(const QString &code) const;

    // properties
    bool loading() const;

signals:
    // properties
    void loadingChanged(bool loading);

public slots:
    void setPackages(const QList<Package> &packages);

    // properties
    void setLoading(bool loading);

private:
    QList<Package> m_packages;

    // properties
    bool m_loading{true};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;


};

#endif // PACKAGESMODEL_H
