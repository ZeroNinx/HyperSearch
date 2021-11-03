import QtQuick 2.7
import QtQuick.Controls 2.7

MouseArea
{
    //鼠标
    property bool enableAutoCursorShape: true
    property bool isHovered: false

    //背景
    property string color: "white"
    property string hoveredColor: color
    property int radius: 0
    property int borderWidth: 0
    property string borderColor: ""

    //图片
    property string imageSource: ""
    property int imagePadding: 0
    property int imageLeftPadding: 0
    property int imageRightPadding: 0
    property int imageTopPadding: 0
    property int imageBottomPadding: 0

    //文字
    property string text: ""
    property string fontColor: "black"
    property string fontFamily: "微软雅黑"
    property bool fontBold: false
    property int fontSize: 10
    function setText(newText)
    {
        content.text = newText
    }


    hoverEnabled: true

    onHoveredChanged:
    {
        isHovered = !isHovered
        background.color = isHovered? hoveredColor:color

        if(enableAutoCursorShape)
        {
            cursorShape = isHovered? Qt.PointingHandCursor:Qt.ArrowCursor
        }
    }


    Rectangle
    {
        id:background

        anchors.fill: parent
        radius: parent.radius
        color: parent.color
        border.width: parent.borderWidth
        border.color: parent.borderColor
    }

    Image
    {
        id: image

        source: parent.imageSource
        anchors.fill: parent
        anchors.topMargin: parent.imagePadding === 0 ? parent.imageTopPadding : parent.imagePadding
        anchors.bottomMargin: parent.imagePadding === 0 ? parent.imageBottomPadding : parent.imagePadding
        anchors.leftMargin: parent.imagePadding === 0 ? parent.imageLeftPadding : parent.imagePadding
        anchors.rightMargin: parent.imagePadding === 0 ? parent.imageRightPadding : parent.imagePadding

        fillMode: Image.PreserveAspectFit
    }

    Text
    {
        id: content

        text: parent.text
        color: parent.fontColor
        font.bold: parent.fontBold
        font.family: parent.fontFamily
        font.pixelSize: parent.fontSize

        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}

/*##^##
Designer {
    D{i:0;height:50;width:1280}
}
##^##*/
