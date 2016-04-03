import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 137; height: 75
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 3 * parent.width / 137
		y: 0 * parent.height / 1
		width: 129 * parent.width / 137
		height: 73 * parent.height / 75
		border.color: "#ffffff"
		border.width: 0
	} 
} 
