import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 48; height: 48
	color: "transparent"
	Picture { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 47 * parent.width / 48
		y2: 47 * parent.height / 48
		source: "images/table.png"
	}
} 
