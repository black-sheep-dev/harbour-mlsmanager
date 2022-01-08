import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All


    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("About")
            }

            Image {
                id: logo
                source: "/usr/share/icons/hicolor/512x512/apps/harbour-mlsmanager.png"
                smooth: true
                height: parent.width / 2
                width: parent.width / 2
                sourceSize.height: 512
                sourceSize.width:  512
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 0.7
            }

            Label {
                x : Theme.horizontalPageMargin
                width: parent.width - 2*x

                font.pixelSize: Theme.fontSizeExtraLarge
                color: Theme.secondaryHighlightColor

                text: qsTr("MLS Manager")
            }

            Label {
                x : Theme.horizontalPageMargin
                width: parent.width - 2*x

                text: Qt.application.version
            }

            Item {
                height: Theme.paddingMedium
                width: 1
            }

            Label {
                x : Theme.horizontalPageMargin
                width: parent.width - 2 * x

                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall

                text: qsTr("Manager for Mozilla Location Service offline packages for Sailfish OS.")
            }

            SectionHeader{
                text: qsTr("Translations")
            }

            Label {
                x : Theme.horizontalPageMargin
                width: parent.width - 2*x
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall

                text: qsTr("Your language is not available? You are welcome to support this project by translating it on my self hosted Weblate server.")
            }

            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    x : Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing:Theme.paddingMedium

                    Image {
                        width: parent.height
                        height: width
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:///icons/weblate"
                    }

                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall

                        text: "https://weblate.nubecula.org/engage/harbour-mlsmanager"
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor

                    }
                }
                onClicked: Qt.openUrlExternally("https://weblate.nubecula.org/engage/harbour-mlsmanager")
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: sourceSize.height * width / sourceSize.width
                smooth: true
                fillMode: Image.PreserveAspectFit
                source: "http://weblate.nubecula.org/widgets/harbour-mlsmanager/-/harbour-mlsmanager/multi-auto.svg"
            }

            SectionHeader{
                text: qsTr("Sources")
            }

            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    x : Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing:Theme.paddingMedium

                    Image {
                        width: parent.height
                        height: width
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:///icons/git"
                    }

                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall

                        text: "https://github.com/black-sheep-dev/harbour-mlsmanager"
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor

                    }
                }
                onClicked: Qt.openUrlExternally("https://github.com/black-sheep-dev/harbour-mlsmanager")
            }

            SectionHeader{
                text: qsTr("Donations")
            }

            Label {
                x : Theme.horizontalPageMargin
                width: parent.width - 2*x

                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("If you like my work why not buy me a beer?")
            }

            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium

                Row{
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing:Theme.paddingMedium

                    Image {
                        width: parent.height
                        height: width
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:///icons/paypal"
                    }
                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        text: qsTr("Donate with PayPal")
                    }
                }
                onClicked: Qt.openUrlExternally("https://www.paypal.com/paypalme/nubecula/1")
            }

            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium

                Row{
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height

                    spacing:Theme.paddingMedium

                    Image {
                        width: parent.height
                        height: width
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:///icons/liberpay"
                    }
                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        text: qsTr("Donate with Liberpay")
                    }
                }
                onClicked: Qt.openUrlExternally("https://liberapay.com/black-sheep-dev/donate")
            }

            Item {
                width: 1
                height: Theme.paddingSmall
            }
        }
    }
}
