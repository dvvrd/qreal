import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 100; height: 100
	color: "transparent"
	Picture { 
		x1: 1 * parent.width / 100
		y1: 3 * parent.height / 50
		x2: 9 * parent.width / 10
		y2: 9 * parent.height / 10
		source: "images/database.png"
	}
} 
