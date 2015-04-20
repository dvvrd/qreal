import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 149; height: 95
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 2 * parent.width / 149
		y: 2 * parent.height / 95
		width: 142 * parent.width / 149
		height: 89 * parent.height / 95
		border.color: "#ffffff"
		border.width: 0
	} 
} 
