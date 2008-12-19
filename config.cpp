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

#include "config.h"

//#define __DEBUG

config::config()
{
	parseConfigFile("battlezone.cfg");
}

config::config(QString configFile)
{
	parseConfigFile(configFile);
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
		qDebug() << "Could not open file: '" << configFile << "' on line " << __LINE__ << " in " << __FILE__;
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

		line = file.readLine();
		soundMove = this->strip(line);

		line = file.readLine();
		soundFire = this->strip(line);

		line = file.readLine();
		soundKill = this->strip(line);


		while (!file.atEnd()) {
			line = file.readLine();
			this->strip(line);
			playerIpList.append(line);
		}
#ifdef __DEBUG
		printPublicVars();
#endif
	}
	return 0;
}

#ifdef __DEBUG
void config::printPublicVars()
{
	qDebug() << "playerStartingLives:" << playerStartingLives;
	qDebug() << "playerTankSpeed:" << playerTankSpeed;
	qDebug() << "playerTankTurnRate: " << playerTankTurnRate;
	qDebug() << "projectileSpeed: " << projectileSpeed;
	qDebug() << "playerMaxInFlightProjectiles: " << playerMaxInFlightProjectiles;
	qDebug() << "playerTankMaxRof: " << playerTankMaxRof;
	qDebug() << "playerStartingAmmo: " << playerStartingAmmo;
	qDebug() << "playerTankMaxDetectibilityRange: " << playerTankMaxDetectibilityRange;
	qDebug() << "playerTankMaxEngageabilityRange: " << playerTankMaxEngageabilityRange;
	qDebug() << "soundMove: " << soundMove.toLocal8Bit().constData();
	qDebug() << "soundFire: " << soundFire.toLocal8Bit().constData();
	qDebug() << "soundKill: " << soundKill.toLocal8Bit().constData();
	for(int i = 0; i < playerIpList.size(); ++i) {
		qDebug() << "IP address number " << i << ": " << playerIpList.at(i).toLocal8Bit().constData();
	}
}
#endif

