import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 132; height: 132
	color: "transparent"
	Picture { 
		x1: 1 * parent.width / 66
		y1: 1 * parent.height / 66
		x2: 65 * parent.width / 66
		y2: 65 * parent.height / 66
		source: "images/user.png"
	}
} 
