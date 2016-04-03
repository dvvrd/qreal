import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 450; height: 150
	color: "transparent"
	Rectangle { 
		anchors.fill: parent
		x: 0 * parent.width / 1
		y: 0 * parent.height / 1
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		border.color: "#ffffff"
		border.width: 0
	} 
	Line { 
		x1: 30 
		y1: 0 * parent.height / 1
		x2: 30 
		y2: 1 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 43 * parent.width / 90
		y1: 5 * parent.height / 6
		x2: 43 * parent.width / 90
		y2: 29 * parent.height / 30
		visible: models.getProperties(ids, "multiple")== "true"
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 5 * parent.height / 6
		x2: 1 * parent.width / 2
		y2: 29 * parent.height / 30
		visible: models.getProperties(ids, "multiple")== "true"
		color: "#000000"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 47 * parent.width / 90
		y1: 5 * parent.height / 6
		x2: 47 * parent.width / 90
		y2: 29 * parent.height / 30
		visible: models.getProperties(ids, "multiple")== "true"
		color: "#000000"
		style: "solid"
		width: 2
	} 
} 
