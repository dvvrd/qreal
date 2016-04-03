import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 50; height: 80
	color: "transparent"
	Polygon { 
		fill: "#000000"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "0,40,50,50,0"
		y: "0,0,10,80,80"
		n: 5
	} 
	Line { 
		x1: 4 * parent.width / 5
		y1: 0 * parent.height / 1
		x2: 4 * parent.width / 5
		y2: 1 * parent.height / 8
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 4 * parent.width / 5
		y1: 1 * parent.height / 8
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 8
		color: "#000000"
		style: "solid"
		width: 1
	} 
} 
