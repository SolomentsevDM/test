import QtQuick
import QtQuick.Window 2.12
import TableModel 0.1
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import QtQuick.Layouts 1.3
Window {
    width: 640
    height: 480
    visible: true
    id: window
    property color color:"white"
    Popup{
        id: popup
        x: 100
        y: 100
        width: 400
        height: 200
        modal: true
        focus: true
        Text{
            id: pptxt
            text:""
            color:"blue"
            anchors.centerIn: parent
        }

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        onClosed:{
            Qt.quit()
        }
    }
    Connections{
        target:myModel
       function onGetError(err){
            pptxt.text=err
            popup.open()
        }
    }


    title: qsTr("TEST")
    TableView{
        id:tableview
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        anchors.topMargin:77
        model: myModel
        TableModelColumn {display: "id" }
        TableModelColumn {display: "name" }
        TableModelColumn { display: "username" }
        TableModelColumn { display: "email" }
        TableModelColumn { display: "street" }
        TableModelColumn { display: "suite" }
        TableModelColumn { display: "city" }
        TableModelColumn { display: "zipcode" }
        TableModelColumn { display: "lat" }
        TableModelColumn { display: "lng" }
        TableModelColumn { display: "phone" }
        TableModelColumn { display: "website" }
        TableModelColumn { display: "name" }
        TableModelColumn { display: "catchPhrase" }
        TableModelColumn { display: "bs" }
        delegate: DelegateChooser{
            id:delc
            DelegateChoice{
                id: dr
                column: 8

                delegate: Rectangle {

                    id:rectt
                    implicitWidth: 150
                    implicitHeight: 150
                    border.width: 1

                    radius: 100


                    property string text:modelData
                    Text {
                        text: parent.text
                        anchors.centerIn: parent
                    }



                    color: parseInt(text)>0?"green":"red"
                    property color colo:this.color
                }
            }
            DelegateChoice{
                column: 12
                delegate: Rectangle {
                    implicitWidth: 150
                    implicitHeight: 150
                    border.width: 1
                    radius: 100

                    color:parseInt(myModel.getdata(model.row,8))>0?"green":"red"
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                    }

                }
            }
            DelegateChoice{
                column: 1
                delegate: Rectangle {
                    implicitWidth: 150
                    implicitHeight: 150
                    border.width: 1
                    radius: 100

                    color: parseInt(myModel.getdata(model.row,8))>0?"green":"red"
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                    }


                }
            }
            DelegateChoice{
                delegate: Rectangle {
                    implicitWidth: 220
                    implicitHeight: 100
                    border.width: 1
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                    }

                }
            }
        }


    }
    HorizontalHeaderView {
        id: horizontalHeader
        syncView: tableview
        model: ["id","name","username","email","street","suite","city","zipcode","lat","lng","phone","website","name","catchPhrase","bs"]
        delegate: Rectangle {
            implicitWidth: 50
            implicitHeight: 75
            border.width: 2
            Text {
                text:modelData
                anchors.centerIn: parent
            }
        }
    }

}

