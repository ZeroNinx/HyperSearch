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
        color: "#444444"
    }//背景

    //右区
    Item
    {
        id:rightArea
        anchors.right: parent.right
        anchors.left: leftArea.right
        anchors.bottom: bottomBarArea.top
        anchors.top: titleBarArea.bottom

        //右区图片
        Image
        {
            id:bgr_rightArea
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
                width:parent.width - x - 10
                height: 55

                Rectangle
                {
                    id: border_result_item
                    y: 5
                    height: parent.height - 2*y
                    color: "#777777"
                    border.color: "#333333"
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
                            bottomBar.text = model.downloadUrl
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
            ScrollBar.vertical: ScrollBar
            {
                anchors.left: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 10
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
    }//右区

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

        //左区背景
        Rectangle
        {
            id: bgr_leftArea
            anchors.fill: parent
            width: 300
            height: 640
            color: "#555555"
            border.width: 0
        }//左区背景

        //分类列表
        ListView
        {
            id:lv_host
            anchors.rightMargin: 8
            anchors.bottomMargin: 8
            anchors.leftMargin: 12
            anchors.topMargin: 12
            anchors.top: searchArea.bottom
            anchors.bottom: updateCheckBar.top
            anchors.left: leftArea.left
            anchors.right: leftArea.right
            anchors.margins: 10

            //分类列表显示条目
            delegate: Item
            {
                width: parent.width
                height: 60

                //分类条目按钮
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

                }//分类条目按钮

            }//分类列表显示条目

            //数据条目
            model: mainWindow.hostModel

        }//分类列表

        //搜索框区域
        Rectangle
        {
            id: searchArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 60
            color: "#555555"

            //搜索图标
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

            }//搜索图标

            //搜索框
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

                //搜索框鼠标响应
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true

                    property bool isHovered: false

                    onHoveredChanged:
                    {
                        isHovered = ! isHovered
                        if(isHovered)
                        {
                            cursorShape = Qt.IBeamCursor
                        }
                        else
                        {
                            cursorShape = Qt.ArrowCursor
                        }
                    }
                }//搜索框鼠标响应

                //搜索提示文本
                Text
                {
                    id: searchHint
                    anchors.fill: parent
                    anchors.leftMargin: 15
                    anchors.rightMargin: 15
                    text: qsTr("搜索...")
                    color: "#555555"
                    font.family: "微软雅黑"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                }//搜索提示文本

                //搜索输入框
                TextInput
                {
                    id: textInput_searchBar
                    anchors.fill: parent
                    anchors.rightMargin: 15
                    anchors.leftMargin: 15
                    font.family: "微软雅黑"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter

                    property bool isFocused: false

                    onAccepted:
                    {
                        bottomBar.text = textInput_searchBar.text
                        focus = false
                    }

                    onFocusChanged:
                    {
                        isFocused = !isFocused
                        if(!isFocused && text === "")
                        {
                            searchHint.opacity = 1
                        }

                        if(isFocused)
                        {
                            searchHint.opacity = 0
                        }
                    }

                }//搜索输入框

            }//搜索框

        }//搜索框区域


        //常用状态栏
        Module.ButtonArea
        {
            id: updateCheckBar
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: stateBarArea.top
            height: 40
            color: "#626262"
            fontSize: 18

            Connections
            {
                target:mainWindow
                onUpdateUpdateCheckBarText:
                {
                    updateCheckBar.setText(newText)
                }
            }

        }//常用状态栏

        //状态栏
        Rectangle
        {
            id: stateBarArea
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 40
            color: "#777777"

            //状态栏文字
            Text
            {
                id: stateBar
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:  Text.AlignVCenter
                text: qsTr("你好！状态栏！")
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                font.family: "微软雅黑"
                font.pixelSize: 18

                //信号槽链接
                Connections
                {
                    target: mainWindow
                    onUpdateStateBarText:
                    {
                        stateBar.text = newText
                    }
                }
            }//状态栏文字

            //搜索终止按钮
            Module.ButtonArea
            {
                id:btn_terminateSearch
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 11
                anchors.top: parent.top
                anchors.topMargin: 11
                anchors.right: parent.right
                anchors.rightMargin: 10
                width: 0
                color: "#FF6666"

                onClicked:
                {
                    mainWindow.terminateSearch()
                }

                Connections
                {
                    target: mainWindow
                    onShowTerminateButton:
                    {
                        btn_terminateSearch.width = btn_terminateSearch.height
                        stateBar.anchors.right = btn_terminateSearch.left
                    }
                    onHideTerminateButton:
                    {
                        btn_terminateSearch.width = 0
                        stateBar.anchors.right = stateBarArea.right
                    }
                }

            }//搜索终止按钮

        }//状态栏

    }//左区

    //标题栏
    Item
    {
        id: titleBarArea
        width: 1280
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        //标题栏背景
        Rectangle
        {
            id: bgr_titleBarArea
            color: "#66c0ff"
            anchors.fill: parent

            //标题栏拖动区
            MouseArea
            {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton

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
            }//标题栏拖动区

            //标题文字
            Text
            {
                id: titleBar
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("HyperSearch v0.1")
                font.family: "微软雅黑"
                font.pixelSize: 20
            }//标题文字
        }//标题栏背景

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
        }//最小化按钮
    }//左区

    //底部栏
    Item
    {
        id: bottomBarArea
        y: 690
        height: 30
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        //底部栏背景
        Rectangle
        {
            id:bgr_bottomBar
            anchors.fill:parent
            color: "#66c0ff"

            //底部栏文字
            Text
            {
                id: bottomBar
                anchors.fill: parent
                text: qsTr("你好！底部栏！")
                font.family: "微软雅黑"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }//底部栏文字

            //底部栏鼠标区
            MouseArea
            {
                anchors.fill:parent
                hoverEnabled: true

                property bool isHovered: false
                property bool isHiddenMode: false
                property int clickCount: 0
                property string hiddenColor: "#ff96b6"
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0

                function enableHiddenMode()
                {
                    isHiddenMode = true
                    bottomBar.text = qsTr("隐藏模式启动!")
                    stateBar.text = qsTr("Surprise！")
                    bgr_bottomBar.color = hiddenColor
                    bgr_titleBarArea.color = hiddenColor
                    mainWindow.enableHiddenMode()
                }

                onHoveredChanged:
                {
                    isHovered = !isHovered

                    if(isHovered)
                    {
                        bgr_bottomBar.color = hiddenColor
                        cursorShape = Qt.PointingHandCursor
                    }
                    else
                    {
                        if(!isHiddenMode)
                        {
                            bgr_bottomBar.color = "#66c0ff"
                        }
                        cursorShape = Qt.ArrowCursor
                    }
                }

                Keys.onPressed:
                {
                    if(event.key === Qt.Key_Q && !isHiddenMode)
                    {
                        enableHiddenMode()
                    }
                }

                onPressed:
                {
                    focus = true
                    clickCount++

                    if(clickCount <= 2)
                    {
                        bottomBar.text = qsTr("你好！")
                    }
                    else if(clickCount <= 5)
                    {
                        bottomBar.text = qsTr("这里是超级底部栏！")
                    }
                    else if(clickCount == 10 && !isHiddenMode)
                    {
                        enableHiddenMode()
                    }

                }
            }//底部栏鼠标区

        }//底部栏背景

    }//底部栏

}//主界面


