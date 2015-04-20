import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 50; height: 50
	color: "transparent"
	Picture { 
		x1: 3 * parent.width / 50
		y1: 3 * parent.height / 50
		x2: 4 * parent.width / 5
		y2: 4 * parent.height / 5
		source: "images/controlpanel.png"
	}
} 
