//
// Battlezone
// A multiplayer remake of Atari's 1980 game: Battlezone
// Authors: Charles Burns
//          Trey Russell
//
// License: GPL3
// http://www.gnu.org/copyleft/gpl.html
//
// Requires QT 4.3 by Nokia's Trolltech software

#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork/QUdpSocket>

// http://lists.trolltech.com/qt-interest/2004-11/thread00856-0.html<<<<<
// Packet size: foo + 8 byte IPV4 UDP header
struct bzpacket {
	quint8 packetVersion;	// Version 1

	// 0: reserved, 1: Enter<id>, 2: leave<id>, 3: add<model num><sound num>,
	// 4: remove<id>, 5: update<x><y>, 6: kill<id>
	quint8 packetType;
	quint8 myPlayerID;   // The sending player's object ID

	quint8 gameObjectId; // Which ID is this packet going to affect?

	quint32 packetNumber; // Incremented each packet sent to gameObjectID

	// Multi-purpose data ints. For packetType(p) does <x><y><z>:
	// Unused for packetType 1, 2, 4, and 6. For other packetType:
	// packetType == 3:
	//   data1:<3D model ID> data2:<Sound file to play ID> data3:<unused>
	// packetType == 5:
	//   <New X coordinate><New Y coordinate><New azimuth>
	quint32 data1;
	quint32 data2;
	quint32 data3;
};

bzpacket bp;

//QByteArray qba = (char *)bp;


#endif
