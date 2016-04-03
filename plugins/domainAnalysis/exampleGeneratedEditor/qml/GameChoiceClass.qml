import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 148; height: 80
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 1 * parent.width / 148
		y: 0 * parent.height / 1
		width: 71 * parent.width / 74
		height: 39 * parent.height / 40
		border.color: "#ffffff"
		border.width: 0
	} 
} 
