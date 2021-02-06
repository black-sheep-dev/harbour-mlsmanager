#ifndef SSUINTERFACE_H
#define SSUINTERFACE_H

#include <QDBusAbstractInterface>

class SsuInterface : public QDBusAbstractInterface
{
public:
    explicit SsuInterface(QObject *parent = nullptr);

    void addRepo(const QString &alias, const QString &url);
    void modifyRepo(int action, const QString &alias);
    void updateRepos();
};

#endif // SSUINTERFACE_H
