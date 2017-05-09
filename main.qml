import QtQuick 2.7
import MyConnection 1.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "Grouplogic.js" as GroupLogic
import "property.js" as PropertyM

Rectangle{
    id: rootRec
    width: 520; height:400
    property int groupNum: 0
    signal nameChange(string name)

    MyClass{
        id: myClass
        //        signal modelChange(string roleName, variant value)
    }
    RowLayout{
        ColumnLayout{
            width: 350; height: 400
            spacing: 10
            ListView{
                id: listView
                width: parent.width; height: 300
                model: groupNum==0?myModel0:(groupNum==1?myModel1:(groupNum==2?myModel2:(groupNum==3?myModel3:myModel4)))
                header: Item{
                    width: parent.width; height: 30
                    Text{x:0; text: "Name"}
                    Text{x: 100; text: "Color"}
                    Text{x: 150; text: "Visible"}
                    Text{x: 220; text: "Opacity"}
                }
                //                headerPositioning:
                delegate:Item{
                    width: 300; height: 30

                    TextInput{
                        id: nameT2
                        Component.onCompleted: text=model.name
                        readOnly: true

                        onTextChanged: {
                            listView.model.set(index, nameT2.text, model.color, model.isVisible, model.opacity)
                            nameChange(nameT2.text)
                            //                        myClass.PMNameChange2("name")
                        }
                    }
                    Rectangle{
                        id: colorRec
                        x: 100; width: 30; height: 30; color: "white"
                        Component.onCompleted: color=model.color
                        signal colorChange(string color)
                        onColorChange: {
                            listView.model.set(index, model.name, color, model.isVisible, model.opacity)
                            colorRec.color = model.color
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {listView.currentIndex=index; colorPopup.open();console.log(model)}
                        }
                    }
                    Popup{
                        id: colorPopup
                        width: 200; height: 300
                        modal: true; focus: true
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

                        contentItem: Item{
                            width: 150; height: 250
                            Grid{
                                anchors.fill: parent; columns: 4; rows: 6
                                Repeater{
                                    id: colorRepeater
                                    model: PropertyM.colorArray
                                    delegate: Rectangle{
                                        width: 40; height: 40; color: modelData
                                        MouseArea{
                                            anchors.fill: parent;
                                            onClicked:{
                                                colorRec.colorChange(modelData)
                                                colorPopup.close()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    CheckBox{
                        id: isVisibleBtn
                        x: 150
                        anchors.verticalCenter: parent.verticalCenter
                        Component.onCompleted: {
                            checked = model.isVisible
                        }
                        checkable: true
                        onClicked: {
                            listView.model.set(index, model.name, model.color, !model.isVisible, model.opacity)
                            //                    myClass.PMNameChange2("name")
                            //myClass.ModelChange("IsVisibleRole", model.isVisible)
                        }
                    }

                    Text{ x: 220
                        text: model.opacity; anchors.verticalCenter: parent.verticalCenter
                    }

                    Rectangle{
                        id: enableNT2
                        x: 250
                        color: "gray"
                        Text{text:"Edit"; anchors.centerIn: parent}
                        visible: ma.containsMouse
                        height: 30; width: 30; anchors.verticalCenter: parent.verticalCenter
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                nameT2.readOnly=!nameT2.readOnly
                            }
                        }
                    }

                    MouseArea{
                        id: ma
                        anchors.fill: parent
                        propagateComposedEvents: true
                        hoverEnabled: true
                        onPressed: {
                            mouse.accepted=false
                        }
                    }
                }
            }

            RowLayout{
                Text{text: "Now Editing Group " + groupNum}
            }

            //4 groupbutton
            Item{ width: parent.width; height: 60
                property int spacing: 30
                Rectangle{
                    id: addBtn
                    width: 50; height:50
                    x: 0
                    color: "#bdbdbd"
                    visible: true
                    Text{text: "Add"; anchors.centerIn: parent}
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            GroupLogic.addGroup(addBtn.parent)
                            addBtn.x = GroupLogic.groupArray.length*(width+10)
                            if(GroupLogic.groupArray.length==4) parent.visible=false
                        }
                    }
                }
            }


        }

        ColumnLayout{
            width: 150; height: 150
            Rectangle{
                anchors.fill: parent; color: "lightgray"
                Text{
                    text: "3D Display"; anchors.centerIn: parent
                }
            }
        }
    }
}
