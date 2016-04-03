import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 30; height: 30
	color: "transparent"
	Ellipse { 
		x: 15 * parent.width / 30
		y: 15 * parent.height / 30
		width: 2 * parent.width / 3
		height: 2 * parent.height / 3
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 2
	} 
} 
