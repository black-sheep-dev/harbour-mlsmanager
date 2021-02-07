#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QObject>

#include <QMetaType>
#include <QMutexLocker>
#include <QQueue>
#include <QVariant>

#include "package.h"
#include "packagedaemon.h"

struct QueuedJob {
    quint8 operation{0};
    QVariant payload;

    QueuedJob() = default;

    bool operator==(const QueuedJob &other) const {
        return operation == other.operation
                && payload == other.payload;
    }
    bool operator!=(const QueuedJob &other) const {
        return !(*this == other);
    }
};
Q_DECLARE_METATYPE(QueuedJob)

class PackageManager : public QObject
{
    Q_OBJECT

public:
    enum Operation {
        UnknownOP,
        PackageGetDetails,
        PackageInstall,
        PackageRemove,
        PackageSearch,
        PackageUpdate,
        RefreshCache,
        RefreshRepo
    };
    Q_ENUM(Operation)

    explicit PackageManager(QObject *parent = nullptr);

signals:
    void operationError(const QString &msg);
    void operationSuccess(const QString &msg);
    void packagesAvailable(const QList<Package> &packages);

public slots:
    void getPackageDetails(const QStringList &ids);
    void installPackages(const QStringList &ids);
    void removePackages(const QStringList &ids);
    void searchPackages();
    void updatePackages(const QStringList &ids);

    void refreshRepo();
    void refreshCache(bool force = true);
    void refreshPackages();

private slots:
    void onDetails(const QVariantMap &details);
    void onErrorCode(quint32 code, const QString &details);
    void onFinished(quint32 exit, quint32 runtime);
    void onPackage(quint32 info, const QString &packageId, const QString &summary);
    void onItemProgress(const QString &id, uint status, uint percentage);

    void startJob();

private:
    bool enqueueJob(const QueuedJob &job);
    void initialize();
    void parsePackages();

    QMutex m_mutex;

    QQueue<QueuedJob> m_jobQueue;
    bool m_jobIsRunning{false};
    QList<PackageDTO> m_packageBuffer;
    PackageDaemon *m_packageDaemon{new PackageDaemon(this)};
};

#endif // PACKAGEMANAGER_H
