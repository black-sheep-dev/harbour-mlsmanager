# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# VERSION
VERSION = 0.1.13
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# The name of your application
TARGET = harbour-mlsmanager
DEFINES += APP_TARGET=\\\"$$TARGET\\\"

QT += dbus

CONFIG += sailfishapp

PKGCONFIG += \
    nemonotifications-qt5

INCLUDEPATH += \
    /usr/include/packagekitqt5/PackageKit \
    /usr/include/PackageKit/packagekit-qt5

SOURCES += src/harbour-mlsmanager.cpp \
    src/mlsmanager.cpp \
    src/package.cpp \
    src/packagedaemon.cpp \
    src/packagemanager.cpp \
    src/packagesmodel.cpp \
    src/packagessortfiltermodel.cpp \
    src/packagetransaction.cpp \
    src/ssuinterface.cpp

DISTFILES += qml/harbour-mlsmanager.qml \
    data/harbour-mlsmanager.privileges \
    data/harbour.mlsmanager.service \
    qml/cover/CoverPage.qml \
    rpm/harbour-mlsmanager.changes \
    rpm/harbour-mlsmanager.changes.run.in \
    rpm/harbour-mlsmanager.spec \
    rpm/harbour-mlsmanager.yaml \
    translations/*.ts \
    harbour-mlsmanager.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 512x512

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-mlsmanager-de.ts \
    translations/harbour-mlsmanager-nb_NO.ts \
    translations/harbour-mlsmanager-pl.ts \
    translations/harbour-mlsmanager-sk.ts \



HEADERS += \
    src/constants.h \
    src/mlsmanager.h \
    src/package.h \
    src/packagedaemon.h \
    src/packagemanager.h \
    src/packagesmodel.h \
    src/packagessortfiltermodel.h \
    src/packagetransaction.h \
    src/ssuinterface.h

flags.files = icons/flags/*
flags.path = $$INSTALL_ROOT/usr/share/harbour-mlsmanager/flags/

privileges.files = data/harbour-mlsmanager.privileges
privileges.path = $$INSTALL_ROOT/usr/share/mapplauncherd/privileges.d/

dbus.files = data/harbour.mlsmanager.service
dbus.path = $$INSTALL_ROOT/usr/share/dbus-1/services

INSTALLS += flags privileges dbus

RESOURCES += \
    ressources.qrc
