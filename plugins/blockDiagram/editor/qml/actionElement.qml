<picture sizex="80" sizey="60">
import QtQuick 2.5

Rectangle {
	property string ids
	width: 80
	height: 60
	border.width: 1
	radius: 12
	color: models.property(ids, "process") == "123" ? "blue" : "#f8f8f8"

	MouseArea {
		anchors.fill: parent
		onClicked: {
			parent.color = "red";
		}
	}
}
</picture>
