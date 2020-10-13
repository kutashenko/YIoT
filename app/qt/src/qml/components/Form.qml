import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    anchors.fill: parent

    default property alias children: formContainer.children
    property alias formSpacing: formContainer.spacing

    ColumnLayout {
        id: formContainer

        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            right: parent.right
        }

        spacing: 15
    }
}
