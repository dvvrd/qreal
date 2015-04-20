import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 144; height: 88
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 1 * parent.width / 72
		y: 1 * parent.height / 44
		width: 17 * parent.width / 18
		height: 10 * parent.height / 11
		border.color: "#ffffff"
		border.width: 0
	} 
} 
