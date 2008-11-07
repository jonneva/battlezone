//
// C++ Implementation: config
//
// Description: 
//
//
// Author: Charles Burns
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
	parseConfigFile(configFile);
	return;	
}

QByteArray& config::strip(QByteArray &ba, char commentChar)
{
	int commentLocation = ba.indexOf(commentChar);
	if(-1 == commentLocation) // If comment not found
		ba = ba.trimmed();
	else // Comment was found. Truncate before trimming.
		ba = ba.left(commentLocation).trimmed();
	return ba;
}

qint32 config::parseConfigFile(QString configFile)
{
	QFile file(configFile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		cerr << "Could not open file: '" << configFile.toStdString() << "' on line " << __LINE__ << " in " << __FILE__ << endl;
	}
	else {
		QByteArray line = file.readLine();
		playerStartingLives = this->strip(line).toInt();
		
		line = file.readLine();
		playerTankSpeed = this->strip(line).toInt();
		
		line = file.readLine();
		playerTankTurnRate = this->strip(line).toInt();
		
		line = file.readLine();
		projectileSpeed = this->strip(line).toInt();
		
		line = file.readLine();
		playerMaxInFlightProjectiles = this->strip(line).toInt();
		
		line = file.readLine();
		playerTankMaxRof = this->strip(line).toInt();
		
		line = file.readLine();
		playerStartingAmmo = this->strip(line).toInt();
		
		line = file.readLine();
		playerTankMaxDetectibilityRange = this->strip(line).toInt();
		
		line = file.readLine();
		playerTankMaxEngageabilityRange = this->strip(line).toInt();
		
		while (!file.atEnd()) {
			line = file.readLine();
			this->strip(line);
			playerIpList.append(line);
		}
		for(int i = 0; i < playerIpList.size(); ++i) {
			cerr << playerIpList.at(i).toLocal8Bit().constData() << endl;
		}
	}
	return 0;
}

// 3                    # Initial tanks per player (first line)
// 15                   # tank speed in meters/second
// 90                   # Tank turn rate in degrees/second
// 60                   # Projectile velocity in meters/second
// 3                    # Maximum simultaneous per-tank projectile count
// 120                  # Rate of fire in rounds/minute
// 12                   # Initial ammo count
// 200                  # Detectibility range in meters
// 150                  # Engageability range in meters
// sound/movesound.ogg  # Sound filename for move
// sound/firesound.ogg  # Sound filename for fire
// sound/killsound.ogg  # Sound filename for kill
// 10.0.0.100           # IP addresses of participating computers, one per line
// 10.0.0.101
// 10.0.0.102

// 	qint32 ;
// 	qint32 ;
// 	qint32 ;
// 	qint32 ;
// 	qint32 ;
// 	qint32 ;
// 	qint32 ;
// 	qint32 playerTankMaxEngageabilityRange;
// 	
// 	QString soundMove;
// 	QString soundFire;
// 	QString soundKill;
// 	QList<QString> playerIpList;
