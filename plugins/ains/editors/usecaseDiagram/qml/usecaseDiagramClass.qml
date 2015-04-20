import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 36; height: 36
	color: "transparent"
	Picture { 
		x1: 1 * parent.width / 18
		y1: 1 * parent.height / 18
		x2: 17 * parent.width / 18
		y2: 17 * parent.height / 18
		source: "images/puzzle.png"
	}
} 
