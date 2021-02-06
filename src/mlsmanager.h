#ifndef MLSMANAGER_H
#define MLSMANAGER_H

#include <QObject>
#include <QThread>

#include "packagemanager.h"
#include "packagesmodel.h"
#include "packagessortfiltermodel.h"

class MlsManager : public QObject
{
    Q_OBJECT
public:
    explicit MlsManager(QObject *parent = nullptr);
    ~MlsManager() override;

    Q_INVOKABLE void initialize();
    Q_INVOKABLE PackagesModel *packagesModel();

signals:
    void requestInstallPackage(const QStringList &packageIds);
    void requestRemovePackage(const QStringList &packageIds);
    void requestUpdatePackage(const QStringList &packageIds);

    void requestRefreshCache(bool force);
    void requestRefreshPackages();
    void requestRefreshRepo();

public slots:
    Q_INVOKABLE void installPackage(const QString &code);
    Q_INVOKABLE void removePackage(const QString &code);
    Q_INVOKABLE void updatePackage(const QString &code);

    Q_INVOKABLE void getUpdates();
    Q_INVOKABLE void refreshCache();
    Q_INVOKABLE void refreshRepo();

private:
    QThread *m_backgroundThread{new QThread};
    PackageManager *m_manager{new PackageManager};
    PackagesModel *m_packagesModel{new PackagesModel(this)};
};

#endif // MLSMANAGER_H
