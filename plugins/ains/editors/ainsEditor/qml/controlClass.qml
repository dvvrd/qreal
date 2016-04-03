import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 80; height: 90
	color: "transparent"
	Picture { 
		x1: 1 * parent.width / 16
		y1: 1 * parent.height / 18
		x2: 15 * parent.width / 16
		y2: 17 * parent.height / 18
		source: "images/ktalkd.png"
	}
} 
