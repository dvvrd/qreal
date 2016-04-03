import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 200; height: 100
	color: "transparent"
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 9 * parent.width / 10
		y2: 0 * parent.height / 1
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 5
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 9 * parent.width / 10
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 5
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 9 * parent.width / 10
		y1: 0 * parent.height / 1
		x2: 9 * parent.width / 10
		y2: 1 * parent.height / 5
		color: "black"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 1 * parent.height / 5
		x2: 9 * parent.width / 10
		y2: 1 * parent.height / 5
		color: "black"
		style: "solid"
		width: 1
	} 
} 
