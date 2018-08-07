import QtQuick 2.9

Rectangle {
    id:page
    color:"lightgray"
    width: 640
    height: 480
    Text{
        id: helloText
        x:66
        y:93
        color: "blue"
        anchors.horizontalCenter:page.horizontalCenter
        font.pointSize: 24
        font.bold: true
        text:"Hello World"

    }

}


