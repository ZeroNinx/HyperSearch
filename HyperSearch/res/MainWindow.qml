import QtQuick 2.7
import QtQuick.Window 2.7
import QtQuick.Controls 2.7
import QtQuick.Controls.Material 2.7
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

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    //背景
    Rectangle
    {
        id: bgr_window
        anchors.fill: parent
        color: "#555555"
    }

    //右区
    Item
    {
        id:rightArea
        anchors.right: parent.right
        anchors.left: leftArea.right
        anchors.bottom: bottomBarArea.top
        anchors.top: titleBarArea.bottom

        Image
        {
            anchors.fill: parent
            anchors.margins: 100
            source: "../Image/cirno.png"
            fillMode: Image.PreserveAspectFit
            opacity: 0.2
        }

        //结果列表
        ListView
        {
            id: lv_result
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.bottomMargin: 15
            anchors.topMargin: 15

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
                    color: "#6F6F6F"
                    border.color: "#444444"
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
                            bottomBar.text = model.url
                        }
                    }

                    //网站图标
                    Image
                    {
                        id:siteIcon
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 12
                        anchors.top: parent.top
                        anchors.topMargin: 12
                        width: height
                        source: model.siteIcon
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
                        anchors.left: siteIcon.right
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
        anchors.bottom: bottomBarArea.top
        anchors.top: titleBarArea.bottom

        layer.enabled: true
        layer.effect: DropShadow
        {
            id: shadow_leftArea
            color: "#000000"
            radius: 10
            samples: 20
            spread: 0
            horizontalOffset: 0
        }

        //背景
        Rectangle
        {
            id: bgr_leftArea
            anchors.fill: parent
            width: 300
            height: 640
            color: "#555555"
            border.width: 0
        }

        //分类列表
        ListView
        {
            id:lv_host
            anchors.rightMargin: 8
            anchors.bottomMargin: 8
            anchors.leftMargin: 12
            anchors.topMargin: 12
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
                    id: buttonArea
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    anchors.topMargin: 8
                    anchors.bottomMargin: 8

                    color: "#777777"
                    hoveredColor: "#666666"

                    text: model.name
                    fontSize: 22
                    radius: 20

                    layer.enabled: true
                    layer.effect: DropShadow
                    {
                        color: "#444444"
                        radius: 7
                        samples: 10
                        spread: 0
                    }

                    onClicked:
                    {
                        mainWindow.search(textInput_searchBar.text, model.siteType)
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
            anchors.top: titleBarArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 60
            color: "#555555"

            Image
            {
                id:search_img
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 13
                anchors.top: parent.top
                anchors.topMargin: 22
                width:height
                source: "../Image/search.png"
                opacity: 0.7

            }

            Rectangle
            {
                id: searchBar
                color: "#777777"
                radius: 25

                border.color: "#333333"
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: search_img.right
                anchors.leftMargin: 10
                border.width: 2

                //文本框
                TextInput
                {
                    id: textInput_searchBar
                    font.family: "微软雅黑"
                    text: qsTr("搜索...")
                    color: "#444444"
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16

                    property bool isFocused: false
                    property string search_text: qsTr("搜索...")

                    onAccepted:
                    {
                        bottomBar.text = "OK"
                        mainWindow.search(text,257)
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
        id: titleBarArea
        width: 1280
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Module.ButtonArea
        {
            id: titleBar
            color: "#66c0ff"
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            enableAutoCursorShape: false

            text: qsTr("HyperSearch v0.1")
            fontSize: 20

            property point clickPos: "0,0"
            property bool isPressed: false
            onPressed:
            {
                clickPos = Qt.point(mouseX,mouseY)
                isPressed = true
            }
            onReleased:
            {
                isPressed = false
            }

            onPositionChanged:
            {
                if(isPressed)
                {
                    var delta = Qt.point(mouseX-clickPos.x , mouseY-clickPos.y)
                    window.setX(window.x+delta.x)
                    window.setY(window.y+delta.y)
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
            hoveredColor: "#ffa000"
            radius: 8

            text: qsTr("×")
            fontSize: 20

            onClicked: Qt.quit()
        }

        //最小化按钮
        Module.ButtonArea
        {
            id: btn_minilize

            property bool isHovered: false
            width: height
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 7
            anchors.top: parent.top
            anchors.topMargin: 7
            anchors.right: btn_close.left
            anchors.rightMargin: 15

            color: "#55ee88"
            hoveredColor: "#eeeeee"
            radius: 8

            text: qsTr("_")
            fontSize: 16
            fontBold: true

            onClicked:
            {
                window.visibility = Window.Minimized
            }
        }
    }

    //底部栏
    Item
    {
        id: bottomBarArea
        y: 690
        height: 30
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Module.ButtonArea
        {
            id: bottomBar
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
                titleBar.color =  "#ff96b6"
                titleBar.hoveredColor = "#ff96b6"
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


