#include "ssuinterface.h"

SsuInterface::SsuInterface(QObject *parent) :
    QDBusAbstractInterface(
        QStringLiteral("org.nemo.ssu"),
        QStringLiteral("/org/nemo/ssu"),
        "org.nemo.ssu",
        QDBusConnection::systemBus(),
        parent)
{

}

void SsuInterface::addRepo(const QString &alias, const QString &url)
{
    callWithArgumentList(QDBus::BlockWithGui,
                         QStringLiteral("addRepo"),
                         QVariantList{alias, url});
}

void SsuInterface::modifyRepo(int action, const QString &alias)
{
    callWithArgumentList(QDBus::BlockWithGui,
                         QStringLiteral("modifyRepo"),
                         QVariantList{action, alias});
}

void SsuInterface::updateRepos()
{
    call(QDBus::BlockWithGui, QStringLiteral("updaterepos"));
}
