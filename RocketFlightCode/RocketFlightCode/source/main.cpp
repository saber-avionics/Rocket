// main.cpp

#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;

extern float initialAltitude;
extern flightState myFS;

float airTemp;
uint32_t pressure;
uint32_t initialPressure;

void executeCommands();

int main(void) {
	cout << "Rocketry Begins" << endl;

	//--Initialize Variables

	airTemp = getTemperature();
}