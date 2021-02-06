#ifndef PACKAGETRANSACTION_H
#define PACKAGETRANSACTION_H

#include <QDBusAbstractInterface>

class PackageTransaction : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit PackageTransaction(const QString &path, QObject *parent = nullptr);

    quint8 operation() const;
    void setOperation(quint8 operation);

    // package functions
    void getPackageDetails(const QStringList &ids);
    void installPackages(const QStringList &ids);
    void removePackages(const QStringList &ids);
    void searchPackages(const QStringList &values);
    void updatePackages(const QStringList &ids);

    // repository functions
    void getUpdates();
    void refreshCache(bool force);
    void refreshRepo();

private:
    quint8 m_operation{0};

signals:
    void Details(const QVariantMap &details);
    void ErrorCode(quint32 code, const QString &details);
    void Finished(quint32 exit, quint32 runtime);
    void Package(quint32 info, const QString &packageId, const QString &summary);
    void ItemProgress(const QString &id, uint status, uint percentage);
};

#endif // PACKAGETRANSACTION_H
