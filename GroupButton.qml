import QtQuick 2.0
Rectangle {
    width: 50; height:50
    color: groupNum==groupIndex?"#fdd835":"#bdbdbd"
    property int groupIndex: 0
    Text{
        text: groupIndex
        anchors.centerIn: parent
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            console.log(groupIndex)
            groupNum=groupNum == groupIndex?0:groupIndex
        }
    }
}
