import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 110; height: 110
	color: "transparent"
	Line { 
		x1: 1 * parent.width / 2
		y1: 0 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 2
		x2: 1 * parent.width / 2
		y2: 1 * parent.height / 1
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Ellipse { 
		visible: models.getProperties(ids, "Type")== "Inclusive"
		x: 11 * parent.width / 22
		y: 11 * parent.height / 22
		width: 3 * parent.width / 5
		height: 3 * parent.height / 5
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 5
	} 
	Ellipse { 
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 6 * parent.width / 11
		height: 6 * parent.height / 11
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 0
	} 
	Ellipse { 
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 7 * parent.width / 11
		height: 7 * parent.height / 11
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 3 * parent.height / 10
		x2: 7 * parent.width / 22
		y2: 26 * parent.height / 55
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 21 * parent.width / 55
		y1: 15 * parent.height / 22
		x2: 7 * parent.width / 22
		y2: 26 * parent.height / 55
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 21 * parent.width / 55
		y1: 15 * parent.height / 22
		x2: 34 * parent.width / 55
		y2: 15 * parent.height / 22
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 34 * parent.width / 55
		y1: 15 * parent.height / 22
		x2: 15 * parent.width / 22
		y2: 26 * parent.height / 55
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 3 * parent.height / 10
		x2: 15 * parent.width / 22
		y2: 26 * parent.height / 55
		visible: models.getProperties(ids, "Type")== "Exclusive (Event Based)"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 3 * parent.height / 11
		x2: 1 * parent.width / 2
		y2: 8 * parent.height / 11
		visible: models.getProperties(ids, "Type")== "Parallel"
		color: "#000000"
		style: "solid"
		width: 6
	} 
	Line { 
		x1: 3 * parent.width / 11
		y1: 1 * parent.height / 2
		x2: 8 * parent.width / 11
		y2: 1 * parent.height / 2
		visible: models.getProperties(ids, "Type")== "Parallel"
		color: "#000000"
		style: "solid"
		width: 6
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 3 * parent.height / 11
		x2: 1 * parent.width / 2
		y2: 8 * parent.height / 11
		visible: models.getProperties(ids, "Type")== "Complex"
		color: "#000000"
		style: "solid"
		width: 6
	} 
	Line { 
		x1: 3 * parent.width / 11
		y1: 1 * parent.height / 2
		x2: 8 * parent.width / 11
		y2: 1 * parent.height / 2
		visible: models.getProperties(ids, "Type")== "Complex"
		color: "#000000"
		style: "solid"
		width: 6
	} 
	Line { 
		x1: 7 * parent.width / 22
		y1: 7 * parent.height / 22
		x2: 15 * parent.width / 22
		y2: 15 * parent.height / 22
		visible: models.getProperties(ids, "Type")== "Complex"
		color: "#000000"
		style: "solid"
		width: 6
	} 
	Line { 
		x1: 15 * parent.width / 22
		y1: 7 * parent.height / 22
		x2: 7 * parent.width / 22
		y2: 15 * parent.height / 22
		visible: models.getProperties(ids, "Type")== "Complex"
		color: "#000000"
		style: "solid"
		width: 6
	} 
} 
