import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

//主界面
Window
{
    id: window
    visible: true
    width: 1280
    height: 720
    color: "#00000000"
    title: "HyperSearch v0.1"
    opacity: 1
    flags:  Qt.Window | Qt.FramelessWindowHint

    //背景
    Rectangle
    {
        id: backgrund
        width: 1280
        height: 720
        color: "#ffffff"
        radius: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        border.width: 0
    }

    //右区
    Item
    {
        id: rightArea
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: leftArea.right
        anchors.leftMargin: 0
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: 0
        anchors.top: titleBar.bottom
        anchors.topMargin: 0
        Rectangle
        {
            anchors.fill: parent
            color: "#ffffff"
        }

        //结果列表
        ListView {
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.bottomMargin: 15
            anchors.topMargin: 15
            anchors.fill: parent

            //项目显示条目
            delegate: Item
            {
                x: 5
                width:parent.width - x - 10
                height: 55

                Rectangle
                {
                    y: 5
                    width: parent.width
                    height: parent.height - 2*y
                    border.color: "#777777"
                    border.width: 2
                    radius: 20

                    MouseArea
                    {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onClicked:
                        {
                            txt_bottomBar.text = colorCode
                        }
                    }

                    Row 
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        Text
                        {
                            text: "["+name+"]"+colorCode
                            color: colorCode
                            font.family: "微软雅黑"
                            font.pixelSize: 22
                            font.bold: true
                        }
                        spacing: 10
                    }


                    
                }
                
            }

            //项目数据列表
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }

            //滚动条
            ScrollBar.vertical:
            ScrollBar
            {
                anchors.left: listView_rightArea.right
                width: 10
                height: parent.height
                active: true

                //滚动条的背景样式
                background: Item
                {
                    Rectangle
                    {
                        height: parent.height
                        width: parent.width
                        anchors.left: parent.left
                        color: '#DDDDDD'
                        radius: width/2
                    }
                }

                //bar的圆角
                contentItem: Rectangle
                {
                    x:0
                    y:0
                    width: 10
                    radius: width/2
                    color: '#999999'
                }
             }
        }
    }

    //左区
    Item {
        //左区
        id: leftArea
        width: 300
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: 0
        anchors.top: titleBar.bottom
        anchors.topMargin: 0
        layer.enabled: true
        layer.effect: DropShadow {
            id: shadow_leftArea
            color: "#000000"
            radius: 15
            samples: 20
            spread: 0
            horizontalOffset: 0

        }

        //背景
        Rectangle {
            id: bgr_leftArea
            anchors.fill: parent
            x: 0
            y: 0
            width: 300
            height: 640
            color: "#ffffff"
            border.width: 0
        }


        //搜索框
        Rectangle {
            id: searchBar
            height: 40
            color: "#ffffff"
            radius: 25
            border.color: "#777777"
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            border.width: 2

            //文本框
            TextInput {
                id: textInput_searchBar
                font.family: "微软雅黑"
                text: qsTr("搜索...")
                color: "#777777"
                anchors.right: parent.right
                anchors.rightMargin: 15
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 15
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16

                property bool isFocused: false
                property string search_text: qsTr("搜索...")

                onAccepted:
                {
                    txt_bottomBar.text = "OK"
                    focus = false
                }

                onFocusChanged:
                {
                    isFocused = !isFocused
                    if(!isFocused && text == "")
                    {
                        color = "#777777"
                        text = search_text
                    }

                    if(isFocused && text == search_text)
                    {
                        color = "#000000"
                        text = ""
                    }

                }
            }
        }


        ListView
        {
            anchors.top: searchBar.bottom
            anchors.bottom: leftArea.bottom
            anchors.left: leftArea.left
            anchors.right: leftArea.right
            anchors.margins: 10

            //显示条目
            delegate: Item
            {
                width: parent.width
                height: 50

                Rectangle
                {
                    id: rectangle
                    width: parent.width
                    height: parent.height
                    border.width: 2

                    border.color: "red"

                    LinearGradient
                    {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left

                        width: parent.width/7
                        gradient: Gradient
                        {
                            GradientStop
                            {
                                position: 0
                                color: "#999999"
                            }

                            GradientStop
                            {
                                position: 1
                                color: "#FFFFFF"
                            }
                        }
                        start: Qt.point(0,0)
                        end:Qt.point(width,0)

                    }

                    TextArea
                    {
                        color: "red"
                        anchors.centerIn: parent
                        text: name
                        font.pixelSize: 22

                        font.family: "微软雅黑"

                    }
                }
            }

            //数据条目
            model: ListModel
            {
                ListElement
                {
                    name: "123"
                }

                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
                ListElement
                {
                    name: "123"
                }
            }

        }
    }

    //标题栏
    Item
    {
        id: titleBar
        width: 1280
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 0

        //顶部栏背景
        Rectangle
        {
            id: bgr_titleBar
            color: "#66c0ff"
            radius: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            border.width: 0

            MouseArea {
                id: msa_titleBar
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                acceptedButtons: Qt.LeftButton

                property point clickPos: "0,0"
                property bool allowMove: false
                onPressed: clickPos = Qt.point(mouseX,mouseY)
                onPositionChanged:
                {
                    var delta = Qt.point(mouseX-clickPos.x , mouseY-clickPos.y)
                    window.setX(window.x+delta.x)
                    window.setY(window.y+delta.y)
                }

                Text {
                    id: element
                    text: qsTr("HyperSearch v0.1")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    font.family: "微软雅黑"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 24
                }


            }
        }




        //关闭按钮
        MouseArea
        {
            id: btn_close
            x: 1232
            width: 34
            anchors.right: parent.right
            anchors.rightMargin: 14
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true

            property bool isHovered: false

            onHoveredChanged:
            {
                isHovered = !isHovered
                if(isHovered)
                {
                    txt_btn_close.color = "black"
                }
                else
                {
                    txt_btn_close.color = "white"
                }
            }

            onClicked:
            {
                Qt.quit()
            }

            Rectangle
            {
                id: bgr_btn_close
                x: 0
                y: 0
                anchors.fill: parent
                width: 34
                height: 34
                color: "#ff5959"
                radius: 10
                border.width: 0
            }

            Text
            {
                id: txt_btn_close
                x: 0
                width: 34
                height: 34
                color: "#ffffff"
                text: qsTr("×")
                anchors.top: parent.top
                anchors.topMargin: 1
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
            }
        }

        //最小化按钮
        MouseArea
        {
            id: btn_minilize
            acceptedButtons: Qt.LeftButton
            onClicked: window.visibility = Window.Minimized
            hoverEnabled: true

            property bool isHovered: false
            x: 1182
            width: 34
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.right: btn_close.left
            anchors.rightMargin: 15

            onHoveredChanged:
            {
                isHovered = !isHovered
                if(isHovered)
                    bgr_btn_minilize.color = "#66ff77"
                else
                    bgr_btn_minilize.color = "#ffffff"
            }


            Rectangle
            {
                id: bgr_btn_minilize
                color: "#ffffff"
                radius: 10
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                border.width: 0
            }

            Text {
                id: txt_btn_minilize
                text: qsTr("_")
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
            }
        }




    }

    //底部栏
    Item
    {
        id: bottomBar
        y: 690
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0




        //底部栏背景
        Rectangle
        {
            id: bgr_bottomBar
            color: "#66c0ff"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            border.width: 0
        }




        //底部栏文本
        Text {
            id: txt_bottomBar
            text: qsTr("你好！底部栏！")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.family: "微软雅黑"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
        }


        MouseArea
        {
            id: msa_bottomBar
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            hoverEnabled: true

            property bool isHovered: false
            property bool isSecretMode: false
            property int clickCount: 0

            function enableSecretMode()
            {
                isSecretMode = true
                txt_bottomBar.text = qsTr("特殊模式启动!")
                bgr_titleBar.color =  "#ff96b6"
                bgr_bottomBar.color =  "#ff96b6"
            }

            onHoveredChanged:
            {
                isHovered = !isHovered
                if(isHovered || isSecretMode)
                {
                    bgr_bottomBar.color =  "#ff96b6"
                }
                else
                {
                    bgr_bottomBar.color =  "#66c0ff"
                }
            }

            Keys.onPressed:
            {
                if(event.key ===Qt.Key_Q )
                {
                    enableSecretMode()
                }
            }

            onPressed:
            {
                focus = true
                clickCount++
                if(clickCount == 1)
                {
                    txt_bottomBar.text = qsTr("你好！")
                }
                else if(clickCount >= 10)
                {
                    enableSecretMode()
                }
            }

        }



    }


}

/*##^##
Designer {
    D{i:4;anchors_height:632;anchors_width:972;anchors_x:0;anchors_y:0}D{i:33;anchors_height:640;anchors_width:980;anchors_x:300;anchors_y:50}
D{i:50;anchors_height:640;anchors_width:300;anchors_y:50}D{i:61;anchors_height:30;anchors_width:1280;anchors_x:0;anchors_y:0}
D{i:62;anchors_height:30;anchors_width:1280}D{i:63;anchors_height:30;anchors_width:1280;anchors_x:0;anchors_y:0}
D{i:60;anchors_height:30;anchors_width:1280;anchors_x:0;anchors_y:690}
}
##^##*/
