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

    // process feedback
    void operationError(const QString &msg);
    void operationSuccess(const QString &msg);
    void updatesAvailable();

public slots:
    void installPackage(const QString &code);
    void removePackage(const QString &code);
    void updatePackage(const QString &code);
    void updatePackages();

    void getUpdates();
    void refreshCache();
    void refreshRepo();

    Q_INVOKABLE void testSlot();

private slots:
    void onErrorAvailable(const QString &msg);
    void onUpdatesAvailable(bool available);

private:
    QThread *m_backgroundThread{new QThread};
    PackageManager *m_manager{new PackageManager};
    PackagesModel *m_packagesModel{new PackagesModel(this)};
};

#endif // MLSMANAGER_H
