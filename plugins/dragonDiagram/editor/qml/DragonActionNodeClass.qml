import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 80; height: 60
	color: "transparent"
	Path { 
		fill: "#f8f8f8"
		style: "solid"
		width: 1
		sizex: parent.width
		sizey: parent.height
		color: "#000000"
		str: " M 10.75 1 C 5.36522 1 1 5.41447 1 10.86 L 1 49.14 C 1 54.5855 5.36522 59 10.75 59 L 69.25 59 C 74.6348 59 79 54.5855 79 49.14 L 79 10.86 C 79 5.41447 74.6348 1 69.25 1 L 10.75 1"
	} 
} 
