import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 181; height: 93
	color: "transparent"
	Ellipse { 
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 176 * parent.width / 181
		height: 88 * parent.height / 93
		color: "#bfefff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 1
	} 
} 
