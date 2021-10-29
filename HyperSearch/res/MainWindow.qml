import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import "Module"
import "./Module" as Module

//主界面

Window
{
    id: window
    visible: true
    width: 1280
    height: 720
    color: "#00000000"
    title: "HyperSearch v0.1"
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
        id:rightArea
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
            id: bgr_rightArea
            anchors.fill: parent
            color: "#ffffff"
        }

        //结果列表
        ListView
        {
            id: lv_result
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.bottomMargin: 15
            anchors.topMargin: 15
            anchors.fill: parent

            //项目显示条目
            delegate: Item
            {
                x: 0
                width:parent.width - x - 10
                height: 55

                Rectangle
                {
                    id: border_result_item
                    y: 5
                    height: parent.height - 2*y
                    border.color: "#777777"
                    border.width: 2
                    radius: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5

                    MouseArea
                    {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onClicked:
                        {
                            txt_bottomBar.text = model.url
                        }
                    }

                    //按钮右
                    Module.ButtonArea
                    {
                        id:btn_right
                        anchors.right: parent.right;
                        anchors.rightMargin: 20;
                        anchors.bottom: parent.bottom;
                        anchors.bottomMargin: 8;
                        anchors.top: parent.top;
                        anchors.topMargin: 8;

                        height: parent.height - 2*5
                        width: height

                        color: "#55AAFF"
                        radius: 4

                        imageSource: "../Image/direct-download.png"
                        imagePadding: 5

                        onClicked:
                        {
                            mainWindow.openUrl(model.downloadUrl)
                        }

                        Component.onCompleted:
                        {
                            if(model.downloadUrl === "")
                            {
                                width = 0
                            }
                        }
                    }

                    //按钮中
                    Module.ButtonArea
                    {
                        id:btn_mid
                        anchors.right: btn_right.left;
                        anchors.rightMargin: 10;
                        anchors.bottom: parent.bottom;
                        anchors.bottomMargin: 8;
                        anchors.top: parent.top;
                        anchors.topMargin: 8;

                        height: parent.height - 2*5
                        width: height

                        color: "#44DC44"
                        radius: 4

                        imageSource: "../Image/cloud-download.png"
                        imagePadding: 5

                        onClicked:
                        {
                            mainWindow.openUrl(model.diskUrl)
                        }

                        Component.onCompleted:
                        {
                            if(model.diskUrl === "")
                            {
                                width = 0
                            }
                        }
                    }

                    //按钮左
                    Module.ButtonArea
                    {
                        id:btn_left
                        anchors.right: btn_mid.left;
                        anchors.rightMargin: 10;
                        anchors.bottom: parent.bottom;
                        anchors.bottomMargin: 8;
                        anchors.top: parent.top;
                        anchors.topMargin: 8;

                        height: parent.height - 2*5
                        width: height

                        color: "#FF8800"
                        radius: 4

                        imageSource: "../Image/open-browser.png"
                        imagePadding: 5

                        onClicked:
                        {
                            mainWindow.openUrl(model.pageUrl)
                        }

                        Component.onCompleted:
                        {
                            if(model.pageUrl === "")
                            {
                                width = 0
                            }
                        }
                    }

                    //显示文本
                    Text
                    {
                        text:model.text
                        color: "black"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.right: btn_left.left
                        anchors.rightMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 8
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 8
                        anchors.top: parent.top
                        anchors.topMargin: 8
                        font.family: "微软雅黑"
                        font.pixelSize: 16
                    }
                    
                }
                
            }

            //滚动条
            ScrollBar.vertical:
            ScrollBar
            {
                anchors.left: parent.right
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
                        color: '#DDDDDD'
                        radius: width/2
                    }
                }

                //bar的圆角
                contentItem: Rectangle
                {
                    width: parent.width
                    radius: width/2
                    color: '#999999'
                }
            }

            //项目数据列表
            model: mainWindow.resultModel

        }
    }

    //左区
    Item
    {
        id: leftArea
        width: 300
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: 0
        anchors.top: titleBar.bottom
        anchors.topMargin: 0

        layer.enabled: true
        layer.effect: DropShadow
        {
            id: shadow_leftArea
            color: "#000000"
            radius: 15
            samples: 20
            spread: 0
            horizontalOffset: 0
        }

        //背景
        Rectangle
        {
            id: bgr_leftArea
            anchors.fill: parent
            x: 0
            y: 0
            width: 300
            height: 640
            color: "#ffffff"
            border.width: 0
        }

        //分类列表
        ListView
        {
            id:lv_host
            anchors.top: searchArea.bottom
            anchors.bottom: leftArea.bottom
            anchors.left: leftArea.left
            anchors.right: leftArea.right
            anchors.margins: 10

            //显示条目
            delegate: Item
            {
                width: parent.width
                height: 60

                Module.ButtonArea
                {
                    anchors.fill: parent
                    anchors.leftMargin: 7
                    anchors.rightMargin: 7
                    anchors.topMargin: 7
                    anchors.bottomMargin: 7

                    text: model.name
                    fontSize: 22
                    radius: 17

                    layer.enabled: true
                    layer.effect: DropShadow
                    {
                        color: "#000000"
                        radius: 7
                        samples: 10
                        spread: 0
                    }

                    onClicked:
                    {
                        mainWindow.search(textInput_searchBar.text, model.site)
                    }
                }

            }

            //数据条目
            model: mainWindow.hostModel

        }

        //搜索框
        Rectangle
        {
            id: searchArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 60
            color: "#ffffff"

            Rectangle
            {
                id: searchBar
                x: 20
                y: 10
                height: parent.height - 2*y
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
                TextInput
                {
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

            MouseArea
            {
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
        Module.ButtonArea
        {
            id: btn_close
            width: height
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 7
            anchors.top: parent.top
            anchors.topMargin: 7
            acceptedButtons: Qt.LeftButton

            color: "#ff5959"
            hoveredColor: "white"
            radius: 10

            imageSource: "../Image/close.png"
            imagePadding:10

            onClicked: Qt.quit()
        }

        //最小化按钮
        MouseArea
        {
            id: btn_minilize
            acceptedButtons: Qt.LeftButton
            onClicked: window.visibility = Window.Minimized
            hoverEnabled: true

            property bool isHovered: false
            width: height
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 7
            anchors.top: parent.top
            anchors.topMargin: 7
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
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Module.ButtonArea
        {
            property bool isSecretMode: false
            property int clickCount: 0
            property string secretColor: "#ff96b6"

            anchors.fill: parent
            color: isSecretMode? secretColor : "#66c0ff"
            hoveredColor: secretColor

            text: qsTr("你好！底部栏！")
            fontSize: 16

            function enableSecretMode()
            {
                isSecretMode = true
                text = qsTr("特殊模式启动!")
                bgr_titleBar.color =  "#ff96b6"
            }

            Keys.onPressed:
            {
                if(event.key === Qt.Key_Q )
                {
                    enableSecretMode()
                }
            }

            onPressed:
            {
                focus = true

                if(clickCount < 10)
                {
                    clickCount++
                    text = qsTr("你好！")
                }
                else if(clickCount == 10)
                {
                    enableSecretMode()
                }
            }
        }
    }

}


