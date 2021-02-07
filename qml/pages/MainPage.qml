import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.mlsmanager 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: MlsManager.packagesModel().loading
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Refresh")
                onClicked: MlsManager.refreshRepo()
            }
            MenuItem {
                visible: MlsManager.packagesModel().updatesAvailable
                text: qsTr("Update all packages")
                onClicked: remorsePopup.execute(qsTr("Updating all packages"), function() {MlsManager.updatePackages()} )
            }
            MenuItem {
                text: listView.showSearch ? qsTr("Hide search") : qsTr("Search")
                onClicked: {
                    listView.showSearch = !listView.showSearch

                    if (!listView.showSearch) {
                        searchField.focus = false
                        searchField.text = ""
                    }
                }
            }
            /*
            MenuItem {
                text: "Test"
                onClicked: MlsManager.testSlot()
            }*/
        }

        RemorsePopup { id: remorsePopup }

        Connections {
            target: MlsManager.packagesModel()
            onLoadingChanged: if (!loading) packagesSortFilterModel.sortModel()
        }

        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Offline Packages")
            }

            SearchField {
                id: searchField
                width: parent.width
                height: listView.showSearch ? implicitHeight : 0
                opacity: listView.showSearch ? 1 : 0
                onTextChanged: packagesSortFilterModel.setFilterFixedString(text)


                EnterKey.onClicked: searchField.focus = false

                Connections {
                    target: listView
                    onShowSearchChanged: {
                        searchField.forceActiveFocus()
                    }
                }

                Behavior on height {
                    NumberAnimation { duration: 300 }
                }
                Behavior on opacity {
                    NumberAnimation { duration: 300 }
                }
            }
        }

        SilicaListView {
            property bool showSearch: false

            id: listView

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom

            clip: true

            model: PackagesSortFilterModel {
                id: packagesSortFilterModel
                sourceModel: MlsManager.packagesModel()
            }

            delegate: ListItem {
                id: delegate

                contentHeight: contentRow.height

                menu: ContextMenu {
                    MenuItem {
                        visible: !model.installed
                        text: qsTr("Install")

                        onClicked: remorse.execute(delegate, qsTr("Installing offline package"), function() { MlsManager.installPackage(model.code) })
                    }
                    MenuItem {
                        visible: model.installed
                        text: qsTr("Remove")

                        onClicked: remorse.execute(delegate, qsTr("Removing offline package"), function() { MlsManager.removePackage(model.code) })
                    }

                    MenuItem {
                        visible: model.updateAvailable
                        text: qsTr("Update")

                        onClicked: remorse.execute(delegate, qsTr("Updating offline package"), function() { MlsManager.updatePackage(model.code) })
                    }
                }

                RemorseItem { id: remorse }

                Row {
                    id: contentRow

                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    spacing: Theme.paddingMedium

                    Image {
                        id: flagIcon
                        height: Theme.itemSizeMedium
                        width: 100
                        anchors.verticalCenter: parent.verticalCenter

                        fillMode: Image.PreserveAspectFit
                        smooth: true

                        source: "/usr/share/" + Qt.application.name + "/flags/" + model.code + ".png"
                    }

                    Label {
                        width: parent.width - flagIcon.width - selectedIcon.width - 2*parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        text: model.name
                    }

                    Image {
                        id: selectedIcon
                        anchors.verticalCenter: parent.verticalCenter
                        visible: model.installed

                        source: (model.updateAvailable ? "image://theme/icon-m-capslock?" : "image://theme/icon-m-acknowledge?")
                    }
                }
            }

            ViewPlaceholder {
                enabled: listView.count == 0
                text: qsTr("No offline packages available")
                hintText: qsTr("Check your internet connection")
            }

            VerticalScrollDecorator {}
        }
    }
}
