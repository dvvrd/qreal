import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 25; height: 25
	color: "transparent"
	Ellipse { 
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#ffffff"
		border.color: "#2f4f4f"
		border.style: "solid"
		border.width: 1
	} 
	Ellipse { 
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 3 * parent.width / 5
		height: 3 * parent.height / 5
		color: "#2f4f4f"
		border.color: "#2f4f4f"
		border.style: "solid"
		border.width: 1
	} 
} 
