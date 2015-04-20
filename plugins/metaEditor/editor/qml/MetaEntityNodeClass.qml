import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 150; height: 100
	color: "transparent"
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 0 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 0 
		y1: 25 
		x2: 1 * parent.width / 1
		y2: 25 
		color: "#000000"
		style: "solid"
		width: 2
	} 
} 
