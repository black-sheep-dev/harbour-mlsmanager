import QtQuick 2.0
import Sailfish.Silica 1.0

import org.nubecula.harbour.mlsmanager 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        PullDownMenu {
            busy: MlsManager.packagesModel().busy
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
                onClicked: Remorse.popupAction(page, qsTr("Updating all packages"), function() {MlsManager.updatePackages()} )
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
//            MenuItem {
//                text: "Test"
//                onClicked: MlsManager.testSlot()
//            }
        }

        PageBusyIndicator {
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: MlsManager.packagesModel().loading
        }

        Connections {
            target: MlsManager.packagesModel()
            onLoadingChanged: if (!loading) packagesSortFilterModel.sortModel()
        }

        anchors.fill: parent

        Column {
            id: header
            width: parent.width

            PageHeader {
                title: qsTr("Countries")
                titleColor: Theme.highlightColor
            }

            SearchField {
                id: searchField
                width: parent.width
                height: listView.showSearch ? implicitHeight : 0
                opacity: listView.showSearch ? 1 : 0
                onTextChanged: packagesSortFilterModel.setNameFilter(text)


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

            opacity: MlsManager.packagesModel().loading ? 0.0 : 1.0

            Behavior on opacity {
                FadeAnimation {}
            }

            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom

            clip: true

            model: PackagesSortFilterModel {
                id: packagesSortFilterModel
                sourceModel: MlsManager.packagesModel()
                typeFilter: PackageType.Country
            }

            delegate: ListItem {
                id: delegate

                contentHeight: contentRow.height

                menu: ContextMenu {
                    MenuItem {
                        visible: !model.installed
                        text: qsTr("Install")

                        onClicked: delegate.remorseAction(qsTr("Installing offline package"), function() { MlsManager.installPackage(model.code) })
                    }
                    MenuItem {
                        visible: model.installed
                        text: qsTr("Remove")

                        onClicked: delegate.remorseAction(qsTr("Removing offline package"), function() { MlsManager.removePackage(model.code) })
                    }

                    MenuItem {
                        visible: model.updateAvailable
                        text: qsTr("Update")

                        onClicked: delegate.remorseAction(qsTr("Updating offline package"), function() { MlsManager.updatePackage(model.code) })
                    }
                }

                Rectangle {
                    id: progressBar
                    anchors.left: parent.left
                    anchors.top:    parent.top
                    anchors.bottom: parent.bottom
                    width: parent.width * model.progress / 100

                    color: Theme.highlightBackgroundColor
                    opacity: 0.2

//                    Behavior on width {
//                        NumberAnimation { duration: 300 }
//                    }
                }

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

                        source: "/usr/share/harbour-mlsmanager/flags/" + model.code + ".png"
                    }

                    Column {
                        width: parent.width - flagIcon.width - selectedIcon.width - 2*parent.spacing
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            width: parent.width
                            font.bold: true

                            text: model.name
                        }

                        Label {
                            width: parent.width
                            font.italic: true
                            font.pixelSize: Theme.fontSizeTiny

                            text: {
                                var out = model.latestVersion

                                if (model.installed && model.installedVersion !== model.latestVersion) {
                                    out += " (" + model.installedVersion + " " + qsTr("installed") + ")"
                                }

                                return out
                            }
                        }

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

    onStatusChanged: if (status === PageStatus.Active) pageStack.pushAttached(Qt.resolvedUrl("RegionsPage.qml"))
}
