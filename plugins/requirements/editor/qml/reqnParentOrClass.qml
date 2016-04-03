import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 30; height: 30
	color: "transparent"
	Path { 
		fill: "#ffffff"
		style: "solid"
		width: 2
		sizex: parent.width
		sizey: parent.height
		color: "#000000"
		str: " M 15 15 L 5 15 C 5 20.5228 9.47715 25 15 25 C 20.5228 25 25 20.5228 25 15 C 25 9.47715 20.5228 5 15 5 L 15 15"
	} 
	Path { 
		fill: "#000000"
		style: "solid"
		width: 2
		sizex: parent.width
		sizey: parent.height
		color: "#000000"
		str: " M 15 15 L 15 5 C 9.47715 5 5 9.47715 5 15 L 15 15"
	} 
} 
