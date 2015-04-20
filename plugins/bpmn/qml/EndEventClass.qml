import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 100; height: 100
	color: "transparent"
    Rectangle {
        anchors.fill: parent
        x: 15 * parent.width / 100
        y: 15 * parent.height / 50
        width: 7 * parent.width / 10
        height: 2 * parent.height / 5
        border.color: "#000000"
        border.width: 2
    }

	Ellipse { 
		x: 5 * parent.width / 10
		y: 5 * parent.height / 10
		width: 47 * parent.width / 50
		height: 47 * parent.height / 50
		color: "#ffffff"
		border.color: "#000000"
		border.style: "solid"
		border.width: 10
	} 
	Line { 
		x1: 3 * parent.width / 20
		y1: 3 * parent.height / 10
		x2: 1 * parent.width / 2
		y2: 1 * parent.height / 2
		visible: models.getProperties(ids, "Type")== "Message"
		color: "#ffffff"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 1 * parent.height / 2
		x2: 17 * parent.width / 20
		y2: 3 * parent.height / 10
		visible: models.getProperties(ids, "Type")== "Message"
		color: "#ffffff"
		style: "solid"
		width: 2
	} 
	Ellipse { 
		visible: models.getProperties(ids, "Type")== "Terminate"
		x: 50 * parent.width / 100
		y: 50 * parent.height / 100
		width: 7 * parent.width / 10
		height: 7 * parent.height / 10
		color: "#000000"
		border.color: "#000000"
		border.style: "solid"
		border.width: 1
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
	Line { 
		x1: 1 * parent.width / 4
		y1: 1 * parent.height / 4
		x2: 3 * parent.width / 4
		y2: 3 * parent.height / 4
		visible: models.getProperties(ids, "Type")== "Cancel"
		color: "#000000"
		style: "solid"
		width: 10
	} 
	Line { 
		x1: 3 * parent.width / 4
		y1: 1 * parent.height / 4
		x2: 1 * parent.width / 4
		y2: 3 * parent.height / 4
		visible: models.getProperties(ids, "Type")== "Cancel"
		color: "#000000"
		style: "solid"
		width: 10
	} 
} 
