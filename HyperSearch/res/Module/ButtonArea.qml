import QtQuick 2.7
import QtQuick.Controls 2.7

MouseArea
{
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
    property int fontSize: 10

    hoverEnabled: true

    onHoveredChanged:
    {
        isHovered = !isHovered
        background.color = isHovered? hoveredColor:color
        cursorShape = isHovered? Qt.PointingHandCursor:Qt.ArrowCursor
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
        font.family: parent.fontFamily
        font.pixelSize: parent.fontSize

        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
