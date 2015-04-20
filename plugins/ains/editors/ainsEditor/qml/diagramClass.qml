import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 32; height: 32
	color: "transparent"
	Picture { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 31 * parent.width / 32
		y2: 31 * parent.height / 32
		source: "images/circle_blue.png"
	}
} 
