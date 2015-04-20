import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 70; height: 80
	color: "transparent"
	Picture { 
		x1: 1 * parent.width / 14
		y1: 1 * parent.height / 10
		x2: 1 * parent.width / 1
		y2: 7 * parent.height / 8
		source: "images/transport.png"
	}
} 
