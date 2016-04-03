import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 80; height: 90
	color: "transparent"
	Picture { 
		x1: 7 * parent.width / 80
		y1: 1 * parent.height / 15
		x2: 1 * parent.width / 1
		y2: 8 * parent.height / 9
		source: "images/network-wireless.png"
	}
} 
