import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 80; height: 80
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 0 * parent.width / 1
		y: 0 * parent.height / 1
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		border.color: "#f0ffff"
		border.width: 0
	} 
} 
