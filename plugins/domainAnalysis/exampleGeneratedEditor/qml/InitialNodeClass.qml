import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 30; height: 30
	color: "transparent"
	Ellipse { 
		x: 15 * parent.width / 30
		y: 15 * parent.height / 30
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#000000"
		border.color: "#000000"
		border.style: "solid"
		border.width: 1
	} 
} 
