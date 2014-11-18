import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 155; height: 75
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 2 * parent.width / 155
		y: 0 * parent.height / 1
		width: 30 * parent.width / 31
		height: 73 * parent.height / 75
		border.color: "#ffffff"
		border.width: 0
	} 
} 
