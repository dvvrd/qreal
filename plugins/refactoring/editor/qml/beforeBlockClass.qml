import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 200; height: 200
	color: "transparent"
	Line { 
		x1: 1 * parent.width / 10
		y1: 0 * parent.height / 1
		x2: 9 * parent.width / 10
		y2: 0 * parent.height / 1
		color: "black"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 1 * parent.width / 10
		y1: 1 * parent.height / 1
		x2: 9 * parent.width / 10
		y2: 1 * parent.height / 1
		color: "black"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 10
		x2: 0 * parent.width / 1
		y2: 9 * parent.height / 10
		color: "black"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 1 * parent.height / 10
		x2: 1 * parent.width / 1
		y2: 9 * parent.height / 10
		color: "black"
		style: "solid"
		width: 3
	} 
	Arc { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 5
		y2: 1 * parent.height / 5
		startAngle: 1440; spanAngle: 1440
		color: "black"
		style: "solid"
		width: 3
	} 
	Arc { 
		x1: 4 * parent.width / 5
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 5
		startAngle: 0; spanAngle: 1440
		color: "black"
		style: "solid"
		width: 3
	} 
	Arc { 
		x1: 0 * parent.width / 1
		y1: 4 * parent.height / 5
		x2: 1 * parent.width / 5
		y2: 1 * parent.height / 1
		startAngle: 2880; spanAngle: 1440
		color: "black"
		style: "solid"
		width: 3
	} 
	Arc { 
		x1: 4 * parent.width / 5
		y1: 4 * parent.height / 5
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		startAngle: 0; spanAngle: -1440
		color: "black"
		style: "solid"
		width: 3
	} 
} 
