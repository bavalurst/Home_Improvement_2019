#include "Deur.h"

Deur::Deur(char* ip) : Device(ip) {

	a0 = new Actuator("17", "0"); //Actuator voor lichtintensiteit
	addActuator("17", a0);
	a1 = new Actuator("22", "0"); //Actuator voor DeurLed binnen
	addActuator("22", a1);
	a2 = new Actuator("23", "0"); //Actuator voor DeurLed buiten
	addActuator("23", a2);
	a3 = new Actuator("24", "0"); //Actuator voor Servo
	addActuator("24", a3);
	a4 = new Actuator("27", "0"); //Actuator voor de PIN Code
	addActuator("24", a4);
	a5 = new Actuator("28", "0"); //Actuator voor Enter Knop
	addActuator("24", a5);
	a6 = new Actuator("29", "0"); //Actuator voor Terugkopeling Pin validatie
	addActuator("24", a6);
	a7 = new Actuator("32", "0"); //Brandalarm Alert
	addActuator("32", a7);
	a8 = new Actuator("38", "0"); //Incorrect PIN Alert
	addActuator("32", a8);
	s1 = new Sensor("25", "0"); //sensor voor Deurknop binnen
	addSensor(s1);
	s2 = new Sensor("26", "0"); //sensor voor Deurknop buiten
	addSensor(s2);

}

Deur::~Deur() {

	delete a1;
	delete a2;
	delete a3;
	delete a4;
	delete s1;
	delete s2;

}

string Deur::logic(map<string, Device*> dev)
{

PIN = 1234;


if(a5->getValue() == "1" && a7->getValue() == PIN) {
	s = s + "24;1;27;0;28;0";
	incorrectPinCount = 0;
}
else{
	incorrectPinCount = a8->getValue();
	incorrectPinCount++;
	s = s + "29;1;38;incorrectPinCount;";
}

if(a2->getValue() == "1" && a3->getValue() != "1") { //Wanneer op de Deurknop buiten wordt gedrukt, gaat de deur open.
	s = s + "24;1;";

	cout << "Deur gaat open. \n";
}

if(a2->getValue() == "0" && a3->getValue() != "0" /*&& a4->getValue() != "1"*/ ) {
	s = s + "24;0;";

	cout << "Deur gaat dicht. \n";
}
if((a1->getValue() == "1" || a2->getValue() == "1")&& a7->getValue() == "1" ) { //Wanneer Brandalarm afgaat openen beide deurknoppen de deur
	s = s + "24;0;";

	cout << "Brandalarm is afgegaan, deur gaat open.\n";
}

if(a0->getValue() < 400 && (a2->getValue() == "1" && a2->getValue() != "1")){
	s = s + "39;1;23;1";
	timeStart = time(nullptr);

}
if( timeStart != NULL) {
	if (time(nullptr) >= timeStart + 6){
			s = s + "39;1;23;0";
			timeStart = NULL;
	}

}

	return s;
}

