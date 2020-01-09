#ifndef _FLIGHTSTATES_H
#define _FLIGHTSTATES_H

#include <stdint.h>
#include <iostream>
#include <math.h>

enum flightState { UNARMED, ALP, STANDBY, ASCENT, DESCENT, LANDING };


class States {
public:
	//void whichState(flightState newState);
	void unarmed();
	void alp(float velocity, float smoothAltitude, float initialAltitude);
	void standby(float smoothAltitude, float initialAltitude);
	void ascent(float velocity, float smoothAltitude, float initialAltitude);
	bool descent(float velocity, float gForce, bool parachuteDeployed, float altitude);
	void landing();
private:
	bool checkIMUStability();
	bool checkPropTemp();
};


#endif // !_FLIGHTSTATES_H