import QtQuick 1.0 
import CustomComponents 1.0

Rectangle { 
	width: 200; height: 200
	color: "transparent"
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 2
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "dash"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 1 * parent.height / 2
		x2: 5 * parent.width / 6
		y2: 1 * parent.height / 4
		color: "#2f4f4f"
		style: "dash"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 1 * parent.height / 2
		x2: 5 * parent.width / 6
		y2: 3 * parent.height / 4
		color: "#2f4f4f"
		style: "dash"
		width: 2
	} 
} 
