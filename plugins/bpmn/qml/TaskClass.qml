import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 210; height: 160
	color: "transparent"
	Line { 
		x1: 3 * parent.width / 35
		y1: 9 * parent.height / 32
		x2: 3 * parent.width / 35
		y2: 23 * parent.height / 32
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 3 * parent.width / 14
		y1: 9 * parent.height / 80
		x2: 11 * parent.width / 14
		y2: 9 * parent.height / 80
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 32 * parent.width / 35
		y1: 9 * parent.height / 32
		x2: 32 * parent.width / 35
		y2: 23 * parent.height / 32
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 3 * parent.width / 14
		y1: 71 * parent.height / 80
		x2: 11 * parent.width / 14
		y2: 71 * parent.height / 80
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Curve { 
		fill: "#ffffff"
		style: "solid"
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		width: 0
		startx: 18
		starty: 45
		endx: 45
		endy: 18
		x: 15
		y: 15
	}
	Curve { 
		fill: "#ffffff"
		style: "solid"
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		width: 0
		startx: 192
		starty: 45
		endx: 165
		endy: 18
		x: 195
		y: 15
	}
	Curve { 
		fill: "#ffffff"
		style: "solid"
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		width: 0
		startx: 165
		starty: 142
		endx: 192
		endy: 115
		x: 195
		y: 145
	}
	Curve { 
		fill: "#ffffff"
		style: "solid"
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		width: 0
		startx: 18
		starty: 115
		endx: 45
		endy: 142
		x: 15
		y: 145
	}
	Line { 
		x1: 8 * parent.width / 21
		y1: 117 * parent.height / 160
		x2: 8 * parent.width / 21
		y2: 133 * parent.height / 160
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Parallel)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 3 * parent.width / 7
		y1: 117 * parent.height / 160
		x2: 3 * parent.width / 7
		y2: 133 * parent.height / 160
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Parallel)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 10 * parent.width / 21
		y1: 117 * parent.height / 160
		x2: 10 * parent.width / 21
		y2: 133 * parent.height / 160
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Parallel)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 41 * parent.width / 105
		y1: 23 * parent.height / 32
		x2: 7 * parent.width / 15
		y2: 23 * parent.height / 32
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Sequential)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 41 * parent.width / 105
		y1: 25 * parent.height / 32
		x2: 7 * parent.width / 15
		y2: 25 * parent.height / 32
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Sequential)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Line { 
		x1: 41 * parent.width / 105
		y1: 27 * parent.height / 32
		x2: 7 * parent.width / 15
		y2: 27 * parent.height / 32
		visible: models.getProperties(ids, "loopType")== "Multiple Instances (Sequential)"
		color: "#000000"
		style: "solid"
		width: 3
	} 
	Ellipse { 
		visible: models.getProperties(ids, "loopType")== "Standard Loop"
		x: 3 * parent.width / 7
		y: 25 * parent.height / 32
		width: 2 * parent.width / 21
		height: 1 * parent.height / 8
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 0
	} 
	Line { 
		x1: 3 * parent.width / 7
		y1: 27 * parent.height / 32
		x2: 43 * parent.width / 105
		y2: 17 * parent.height / 20
		visible: models.getProperties(ids, "loopType")== "Standard Loop"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 3 * parent.width / 7
		y1: 27 * parent.height / 32
		x2: 29 * parent.width / 70
		y2: 33 * parent.height / 40
		visible: models.getProperties(ids, "loopType")== "Standard Loop"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "isForCompensation")== "true"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "110,125,125"
		y: "125,115,135"
		n: 3
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "isForCompensation")== "true"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "125,140,140"
		y: "125,115,135"
		n: 3
	} 
} 
