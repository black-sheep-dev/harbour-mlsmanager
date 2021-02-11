#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

static const QString MLS_MANAGER_PACKAGE_DAEMON_SERVICE_NAME    = QStringLiteral("org.freedesktop.PackageKit");

#ifdef QT_DEBUG
static const QString MLS_MANAGER_REPO_URL                       = QStringLiteral("https://mls-test-repo.nubecula.org/");
static const QString MLS_MANAGER_REPO_ALIAS                     = QStringLiteral("nubecula-mls-test-repo");
#else
static const QString MLS_MANAGER_REPO_URL                       = QStringLiteral("https://mls-offline-repo.nubecula.org/");
static const QString MLS_MANAGER_REPO_ALIAS                     = QStringLiteral("nubecula-mls-offline-repo");
#endif

#endif // CONSTANTS_H
