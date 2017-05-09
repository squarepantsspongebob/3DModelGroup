var groupArray = new Array()
var component = Qt.createComponent("GroupButton.qml")
function addGroup(parent){
    console.log("addGroup: "+groupArray.length)
    var component = Qt.createComponent("GroupButton.qml")
    var dynamicObject = component.createObject(parent,
                                               {"groupIndex": groupArray.length+1,
                                                   "x": groupArray.length*(50+10)})
    groupArray[groupArray.length] = dynamicObject
    console.log("addGroup2: "+groupArray.length)
}
