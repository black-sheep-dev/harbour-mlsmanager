import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.DBus 2.0
import Nemo.Notifications 1.0

import "pages"

import org.nubecula.harbour.mlsmanager 1.0

ApplicationWindow
{
    property int updateNotificationId : 0

    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Component.onCompleted: MlsManager.initialize()

    DBusAdaptor {
        service: "harbour.mlsmanager.service"
        iface: "harbour.mlsmanager.service"
        path: "/harbour/mlsmanager/service"
        xml: '\
  <interface name="harbour.mlsmanager.service">
    <method name="open">
    </method>
  </interface>'

        function open() {
            updatesNotification.close()
            __silica_applicationwindow_instance.activate()
        }
    }

    Notification {
        id: updatesNotification
        category: "x-mlsmanager.updates"
        appIcon: "image://theme/icon-lock-application-update"
        previewSummary: qsTr("Updates available")
        previewBody: qsTr("Click to show updates")
        body: qsTr("Updates of MLS offline packages are available.")
        remoteActions: [ {
                name: "default",
                service: "harbour.mlsmanager.service",
                path: "/harbour/mlsmanager/service",
                iface: "harbour.mlsmanager.service",
                method: "open",
                arguments: [ ]
            } ]
    }



    Connections {
        target: MlsManager

        onOperationError: {}
        onOperationSucces: {}
        onUpdatesAvailable: {
            if (updateNotificationId > 0) {
                updatesNotification.replacesId = updateNotificationId
            }

            updatesNotification.publish()
            updateNotificationId = updatesNotification.replacesId
        }
    }
}
