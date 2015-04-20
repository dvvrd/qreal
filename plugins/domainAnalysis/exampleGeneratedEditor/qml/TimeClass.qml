import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 133; height: 64
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 1 * parent.width / 133
		y: 0 * parent.height / 1
		width: 128 * parent.width / 133
		height: 31 * parent.height / 32
		border.color: "#ffffff"
		border.width: 0
	} 
} 
