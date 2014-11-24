import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 160; height: 160
	color: "transparent"
	Picture { 
		x1: 21 * parent.width / 160
		y1: 17 * parent.height / 160
		x2: 37 * parent.width / 40
		y2: 9 * parent.height / 10
		source: "images/server.png"
	}
} 
