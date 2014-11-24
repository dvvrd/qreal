import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 80; height: 90
	color: "transparent"
	Picture { 
		x1: 7 * parent.width / 80
		y1: 4 * parent.height / 45
		x2: 1 * parent.width / 1
		y2: 8 * parent.height / 9
		source: "images/satellite.png"
	}
} 
