import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import QtQuick 2.0

import ChartView 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scene Graph chart")



        ChartView {
            id: graph

            gridSize: 50
            anchors.fill: parent
//            anchors.margins: 100


            function newSample(i) {
                return (Math.sin(i / 100.0 * Math.PI * 2) + 1) * 0.4 + Math.random() * 0.05;
            }

            Component.onCompleted: {
                for (var i=0; i<100; ++i)
                    appendSample(newSample(i));
            }

            property int offset: 100;
        }

        Timer {
            id: timer
            interval: 50
            repeat: true
            running: true
            onTriggered: {
                graph.removeFirstSample();
                graph.appendSample(graph.newSample(++graph.offset));
            }

        }

        Rectangle {
            anchors.fill: graph
            color: "transparent"
            border.color: "black"
            border.width: 2
        }




}
