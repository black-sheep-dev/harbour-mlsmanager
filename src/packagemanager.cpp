#include "packagemanager.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QMutex>
#include <QProcess>
#include <QSettings>
#include <QVersionNumber>

#include "constants.h"
#include "ssuinterface.h"

PackageManager::PackageManager(QObject *parent) :
    QObject(parent)
{    
    initialize();
}

void PackageManager::getPackageDetails(const QStringList &ids)
{
    QueuedJob job;
    job.operation = PackageGetDetails;
    job.payload = ids;

    enqueueJob(job);
}

void PackageManager::installPackages(const QStringList &ids)
{
    QueuedJob job;
    job.operation = PackageInstall;
    job.payload = ids;

    enqueueJob(job);
}

void PackageManager::removePackages(const QStringList &ids)
{
    QueuedJob job;
    job.operation = PackageRemove;
    job.payload = ids;

    enqueueJob(job);
}

void PackageManager::searchPackages()
{
    QueuedJob job;
    job.operation = PackageSearch;
    job.payload = QStringList{"harbour-mls-offline"};

    enqueueJob(job);
}

void PackageManager::updatePackages(const QStringList &ids)
{
    QueuedJob job;
    job.operation = PackageUpdate;
    job.payload = ids;

    enqueueJob(job);
}

void PackageManager::refreshRepo()
{
    QueuedJob job;
    job.operation = RefreshRepo;

    enqueueJob(job);
}

void PackageManager::refreshCache(bool force)
{
    QueuedJob job;
    job.operation = RefreshCache;
    job.payload = force;

    enqueueJob(job);
}

void PackageManager::refreshPackages()
{
    searchPackages();
}

void PackageManager::onDetails(const QVariantMap &details)
{
#ifdef QT_DEBUG
    qDebug() << "DETAILS";
    qDebug() << details;
#endif
}

void PackageManager::onErrorCode(quint32 code, const QString &details)
{
#ifdef QT_DEBUG
    qDebug() << "ERROR CODE";
    qDebug() << code;
    qDebug() << details;
#endif
}

void PackageManager::onFinished(quint32 exit, quint32 runtime)
{
#ifdef QT_DEBUG
    qDebug() << "FINISHED";
    qDebug() << exit;
    qDebug() << runtime;
#endif

    if (exit != 1) {
        startJob();
        return;
    }

    auto t = qobject_cast<PackageTransaction *>(sender());

    if (t == nullptr)
        return;

    switch (t->operation()) {
    case RefreshRepo:
    case RefreshCache:
        refreshPackages();
        break;

    case PackageInstall:
    case PackageRemove:
    case PackageUpdate:
        refreshRepo();
        break;

    case PackageSearch:
        parsePackages();
        break;

    default:
        break;
    }

    // start next job
    startJob();
}

void PackageManager::onPackage(quint32 info, const QString &packageId, const QString &summary)
{
#ifdef QT_DEBUG
    qDebug() << "PACKAGE";
    qDebug() << info;
    qDebug() << packageId;
    qDebug() << summary;
#endif

    auto t = qobject_cast<PackageTransaction *>(sender());

    if (t == nullptr)
        return;

    switch (t->operation()) {
    case PackageSearch:
        m_packageIds.append(packageId);
        break;

    default:
        break;
    }

    // start next job
    startJob();
}

void PackageManager::onItemProgress(const QString &id, uint status, uint percentage)
{
#ifdef QT_DEBUG
    qDebug() << "ITEM PROGRESS";
    qDebug() << id;
    qDebug() << status;
    qDebug() << percentage;
#endif
}

void PackageManager::startJob()
{
    if (m_jobQueue.isEmpty()) {
        m_jobIsRunning = false;
        return;
    }

    m_mutex.lock();
    m_jobIsRunning = true;
    const auto job = m_jobQueue.dequeue();
    m_mutex.unlock();

    auto t = m_packageDaemon->transaction();
    t->setOperation(job.operation);
    connect(t, &PackageTransaction::Details, this, &PackageManager::onDetails, Qt::QueuedConnection);
    connect(t, &PackageTransaction::Finished, this, &PackageManager::onFinished, Qt::QueuedConnection);
    connect(t, &PackageTransaction::ErrorCode, this, &PackageManager::onErrorCode, Qt::QueuedConnection);
    connect(t, &PackageTransaction::Package, this, &PackageManager::onPackage, Qt::QueuedConnection);
    connect(t, &PackageTransaction::ItemProgress, this, &PackageManager::onItemProgress, Qt::QueuedConnection);

    switch (job.operation) {
    case PackageInstall:
        t->installPackages(job.payload.toStringList());
        break;

    case PackageRemove:
        t->removePackages(job.payload.toStringList());
        break;

    case PackageSearch:
        m_packageIds.clear();
        t->searchPackages(job.payload.toStringList());
        break;

    case PackageUpdate:
        t->updatePackages(job.payload.toStringList());
        break;

    case RefreshCache:
        t->refreshCache(job.payload.toBool());
        break;

    case RefreshRepo:
        t->refreshRepo();
        break;

    case PackageGetDetails:
        t->getPackageDetails(job.payload.toStringList());
        break;

    default:
        t->deleteLater();
        break;
    } 
}

bool PackageManager::enqueueJob(const QueuedJob &job)
{
    m_mutex.lock();
    if (m_jobQueue.contains(job)) {
        return false;
    }

    m_jobQueue.enqueue(job);
    m_mutex.unlock();

    if (!m_jobIsRunning) {
        startJob();
    }

    return true;
}

void PackageManager::initialize()
{
    // check if repo is in ssu config file otherwise add it
    QSettings settings(QStringLiteral("/etc/ssu/ssu.ini"), QSettings::IniFormat);

    settings.beginGroup(QStringLiteral("repository-urls"));

    bool available{false};

    const auto repos = settings.childKeys();
    for (const auto &repo : repos) {
        if (repo.startsWith(MLS_MANAGER_REPO_ALIAS)) {
            available = true;
            break;
        }
    }

    if (!available) {
        SsuInterface ssu;
        ssu.addRepo(MLS_MANAGER_REPO_ALIAS,
                    MLS_MANAGER_REPO_URL);
    }

    settings.endGroup();
}

void PackageManager::parsePackages()
{
    m_mutex.lock();
    const auto ids = m_packageIds;
    m_mutex.unlock();

    QHash<QString, Package> packages;

    for (const auto &id: ids) {
        if (id.isEmpty())
            continue;

        const auto parts = id.split(";");

        if (parts.count() != 4)
            continue;

        const QString name = parts.at(0);
        const QString code = name.section("-", 3, 3);
        const QString version = parts.at(1);

        if (code.isEmpty() && code == QLatin1String("eu"))
            continue;

        Package pkg = packages.value(code, Package());
        pkg.code = code;

        if (parts.last() == QLatin1String("installed")) {
                pkg.installed = true;
                pkg.installedVersion = version;
        }

        if (QVersionNumber::fromString(version) > QVersionNumber::fromString(pkg.latestVersion)) {
            pkg.latestVersion = version;
            pkg.updateAvailable = !pkg.installedVersion.isNull() && pkg.installedVersion < version;
        }

        packages.insert(code, pkg);
    }

    emit packagesAvailable(packages.values());
}
