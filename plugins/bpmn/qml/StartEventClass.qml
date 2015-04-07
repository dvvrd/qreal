import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 100; height: 100
	color: "transparent"
    Rectangle {
        anchors.fill: parent
        x: 3 * parent.width / 20
        y: 3 * parent.height / 10
        width: 7 * parent.width / 10
        height: 2 * parent.height / 5
        border.color: "#ffffff"
        border.width: 0
    }

    Rectangle {
        anchors.fill: parent
        x: 1 * parent.width / 4
        y: 1 * parent.height / 5
        width: 1 * parent.width / 2
        height: 3 * parent.height / 5
        border.color: "#ffffff"
        border.width: 0
    }

    Ellipse {
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 0
	} 

	Line { 
		x1: 3 * parent.width / 20
		y1: 3 * parent.height / 10
		x2: 1 * parent.width / 2
		y2: 1 * parent.height / 2
		visible: models.getProperties(ids, "Type")== "Message"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 1 * parent.height / 2
		x2: 17 * parent.width / 20
		y2: 3 * parent.height / 10
		visible: models.getProperties(ids, "Type")== "Message"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Polygon { 
		fill: "#ffffff"
		visible: models.getProperties(ids, "Type")== "Multiple"
		style: "solid"
		width: 0
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "50,20,35,65,80"
		y: "25,45,75,75,45"
		n: 5
	} 
	Ellipse { 
		visible: models.getProperties(ids, "Type")== "Timer"
		x: 1 * parent.width / 2
		y: 1 * parent.height / 2
		width: 7 * parent.width / 10
		height: 7 * parent.height / 10
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 1 * parent.height / 2
		x2: 11 * parent.width / 20
		y2: 1 * parent.height / 5
		visible: models.getProperties(ids, "Type")== "Timer"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 1 * parent.height / 2
		x2: 3 * parent.width / 4
		y2: 12 * parent.height / 25
		visible: models.getProperties(ids, "Type")== "Timer"
		color: "#000000"
		style: "solid"
		width: 0
	} 

	Line { 
		x1: 1 * parent.width / 4
		y1: 7 * parent.height / 20
		x2: 3 * parent.width / 4
		y2: 7 * parent.height / 20
		visible: models.getProperties(ids, "Type")== "Conditional"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 4
		y1: 1 * parent.height / 2
		x2: 3 * parent.width / 4
		y2: 1 * parent.height / 2
		visible: models.getProperties(ids, "Type")== "Conditional"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Line { 
		x1: 1 * parent.width / 4
		y1: 13 * parent.height / 20
		x2: 3 * parent.width / 4
		y2: 13 * parent.height / 20
		visible: models.getProperties(ids, "Type")== "Conditional"
		color: "#000000"
		style: "solid"
		width: 0
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Error"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "40,20,35,60,80,65"
		y: "50,75,20,50,25,80"
		n: 6
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Escalation"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "50,30,50,70"
		y: "50,70,20,70"
		n: 4
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Compensation"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "20,45,45"
		y: "50,30,70"
		n: 3
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Compensation"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "45,70,70"
		y: "50,30,70"
		n: 3
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Signal"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "50,25,75"
		y: "25,70,70"
		n: 3
	} 
	Polygon { 
		fill: "#000000"
		visible: models.getProperties(ids, "Type")== "Parallel Multiple"
		style: "solid"
		width: 1
		color: "#000000"
		sizex: parent.width
		sizey: parent.height
		x: "15,40,40,60,60,85,85,60,60,40,40,15"
		y: "40,40,15,15,40,40,60,60,85,85,60,60"
		n: 12
	} 
} 
