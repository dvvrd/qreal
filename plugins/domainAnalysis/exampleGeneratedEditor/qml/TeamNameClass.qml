import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 124; height: 97
	color: "transparent"
	Ellipse { 
		x: 15 * parent.width / 31
		y: 47 * parent.height / 97
		width: 29 * parent.width / 31
		height: 95 * parent.height / 97
		color: "#ffffff"
		border.color: "#000000"
		border.style: "none"
		border.width: 0
	} 
} 
