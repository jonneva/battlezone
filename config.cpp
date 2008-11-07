//
// C++ Implementation: config
//
// Description: 
//
//
// Author: Charles Burns, Trey Russel, Zak Kohler <charles@sheridan>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "config.h"

config::config()
{
}

config::config(QString configFile)
{
	QFile fin(configFile);
	if( !fin.open(QIODevice::ReadOnly | QIODevice::Text) ) {
		cerr << "Could not open file: '" << configFile.toStdString() << "' on line " << __LINE__ << " in " << __FILE__ << endl;
	}
	else {
		parseConfigFile(configFile);
	}
	return;	
}

qint32 config::parseConfigFile(QString configFile)
{
	return 0;
}

// 	qint32 playerStartingLives;
// 	qint32 playerTankSpeedMove;
// 	qint32 playerTankTurnRate;
// 	qint32 playerMaxInFlightProjectiles;
// 	qint32 playerTankMaxRof;
// 	qint32 playerStartingAmmo;
// 	qint32 playerTankMaxDetectibilityRange;
// 	qint32 playerTankMaxEngageabilityRange;
// 	
// 	QString soundMove;
// 	QString soundFire;
// 	QString soundKill;
// 	QList<QString> playerIpList;