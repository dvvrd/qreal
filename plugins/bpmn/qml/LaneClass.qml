import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 450; height: 150
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 0 * parent.width / 1
		y: 0 * parent.height / 1
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		border.color: "#ffffff"
		border.width: 0
	} 
} 
