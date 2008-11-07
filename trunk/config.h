//
// C++ Interface: config
//
// Description: Include for config.cpp
// Class for reading and dispending configuration information
//
// Author: Charles Burns
//
// Copyright: See COPYING file that comes with this distribution
//
//


/// 3 # Initial tanks per player (first line)
/// 15 # tank speed in meters/second
/// 90 # Tank turn rate in degrees/second
/// 60 # Projectile velocity in meters/second
/// 3 # Maximum simultaneous per-tank projectile count
/// 120 # Rate of fire in rounds/minute
/// 12 # Initial ammo count
/// 200 # Detectibility range in meters
/// 150 # Engageability range in meters
/// sound/movesound.ogg # Sound filename for move
/// sound/firesound.ogg # Sound filename for fire
/// sound/killsound.ogg # Sound filename for kill
// 10.0.0.100 # IP addresses of participating computers, one per line
// 10.0.0.101
// 10.0.0.102

#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QStringList>
//#include <QProcess>
#include <iostream>
using namespace std;

// config class. Gets settings from config file and exposes them.
// Exposure is public (not get/set) for simplicity.
class config {
	public:
	// Should use an IDE with auto-fill-in for these long variable names
	qint32 playerStartingLives;
	qint32 playerTankSpeed;
	qint32 playerTankTurnRate;
	qint32 projectileSpeed;
	qint32 playerMaxInFlightProjectiles;
	qint32 playerTankMaxRof;
	qint32 playerStartingAmmo;
	qint32 playerTankMaxDetectibilityRange;
	qint32 playerTankMaxEngageabilityRange;
	
	QString soundMove;
	QString soundFire;
	QString soundKill;
	QStringList playerIpList;

	config();
	config(QString configFile);
	qint32 parseConfigFile(QString configFile);
	QByteArray& strip(QByteArray &ba, char commentChar = '#');
};

#endif
