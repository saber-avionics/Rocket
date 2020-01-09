#include <stdint.h>

#include "drivers/FlightStates.h"
#include "drivers/Mechanical.h"

using namespace std;

Mechanical mech;

flightState myFS = UNARMED;

void States::unarmed() {
	myFS = UNARMED;
	//Hard lock on doing nothing - transmits sensor stuff and that's it
}

void States::alp(float velocity, float smoothAltitude, float initialAltitude) {
	myFS = ALP;
	//Monitor progress of Launch Platform as it ascends
	if ((smoothAltitude - initialAltitude) >= 15000 && abs((int16_t)velocity) <= 5) {
		cout << "Entering Standby" << endl;
		myFS = STANDBY;
	}
}

void States::standby(float smoothAltitude, float initialAltitude) {
	myFS = STANDBY;
	//Wait for Launch command and monitor float conditions
	cout << "Stability: " << checkIMUStability << " Propellant Temperature: " << checkPropTemp << endl;
	if (checkIMUStability && checkPropTemp) {
		cout << "Ready for Launch" << endl;
	}
}

void States::ascent(float velocity, float smoothAltitude, float initialAltitude) {
	myFS = ASCENT;
	//Perform Ascent Operations
	if (velocity <= -5) {
		cout << "Entering Descent" << endl;
		myFS = DESCENT;
	}
}

bool States::descent(float velocity, float gForce, bool parachuteDeployed, float altitude) {
	myFS = DESCENT;
	//Perform Descent Operations
	mech.OpenTrapDoor();
	mech.OpenVent();
	mech.ExplosiveSeparation();
	mech.HotwireSeparation();
	if (parachuteDeployed == false && altitude <= 5000) {
		//Deploy Parachute
		parachuteDeployed = mech.DeployParachute();
		return parachuteDeployed;
	}

	if (abs((int16_t)velocity) <= 5 && gForce < .05) {
		cout << "Entering LANDING" << endl;
		myFS = LANDING;
	}
}

void States::landing() {
	myFS = LANDING;
	//Perform Ground Operations
	mech.BuzzerOn();
	//Decrease transmission rate
	//Run until powered off
}

bool States::checkIMUStability() {
	bool stabilityCheck = true;
	return stabilityCheck;
}

bool States::checkPropTemp() {
	bool tempCheck = true;
	return tempCheck;
}

/*void States::whichState(flightState newState) {
	switch (newState) {
	case UNARMED:
		//Just chillin'.
		cout << "UNARMED" << endl;
		unarmed();
		break;
	case STANDBY:
		//I'M READY!!!
		cout << "STANDBY" << endl;
		standby(smoothAltitude, initialAltitude);
		break;
	case ASCENT:
		//Here we go!
		cout << "ASCENT" << endl;
		ascent(velocity);
		break;
	case DESCENT:
		//Down, down, down...
		cout << "DESCENT" << endl;
		descent(velocity, gForce);
		break;
	case LANDING:
		//Getting kinda lonely, someone come find me.
		cout << "LANDING" << endl;
		landing();
		break;
	}
}*/