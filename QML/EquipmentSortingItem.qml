import QtQuick 2.0
import ItemSort 1.0

RectangleBorders {
    height: 60
    width: parent.width

    property int sortBoxHeight: 35
    property int sortBoxWidth: 100

    Row {
        height: parent.height
        width: parent.width - 3
        anchors {
            right: parent.right
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 45

            onRectangleClicked: itemModel.selectSort(ItemSort.ByIlvl)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByIlvl)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByIlvl ? root.darkGray :
                                                                            root.darkDarkGray

            Text {
                text: "ILVL"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 300

            onRectangleClicked: itemModel.selectSort(ItemSort.ByName)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByName)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByName ? root.darkGray :
                                                                            root.darkDarkGray

            Text {
                text: "Name"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 50

            onRectangleClicked: itemModel.selectSort(ItemSort.ByPatch)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByPatch)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByPatch ? root.darkGray :
                                                                             root.darkDarkGray

            Text {
                text: "Patch"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        RectangleBorders {
            anchors.bottom: parent.bottom
            height: sortBoxHeight
            width: 60

            onRectangleClicked: itemModel.selectSort(ItemSort.ByItemType)
            onRectangleRightClicked: itemModel.selectSort(ItemSort.ByItemType)

            rectColor: itemModel.currentSortingMethod === ItemSort.ByItemType ? root.darkGray :
                                                                                root.darkDarkGray

            Text {
                text: "Type"

                font {
                    family: "Arial"
                    pointSize: 9
                }

                anchors.fill: parent

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}