import QtQuick 2.0

Item {
    id:container
    property alias cellColor:rectangle.color
    signal clicked(color cellColor)

    width: 40
    height:25

    Rectangle{
        id:rectangle
        border.color: "white"
        anchors.fill:patent
    }

    MouseArea{
        anchors.fill:parent
        onClicked:container.clicked(container.cellColor)
    }
}
