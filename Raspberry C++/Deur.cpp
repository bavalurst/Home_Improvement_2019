#include "Deur.h"

Deur::Deur(char* ip) : Device(ip) {

	a1 = new Actuator("22", "0"); //Actuator voor DeurLed binnen
	addActuator("22", a1);
	a2 = new Actuator("23", "0"); //Actuator voor DeurLed buiten
	addActuator("23", a2);
	a3 = new Actuator("24", "0"); //Actuator voor Servo
	addActuator("24", a3);
	a4 = new Actuator("27", "0"); //Actuator voor de PIN Code
	addActuator("27", a4);
	a5 = new Actuator("28", "0"); //Actuator voor Enter Knop
	addActuator("28", a5);
	a6 = new Actuator("29", "0"); //Actuator voor Terugkopeling Pin validatie
	addActuator("29", a6);
	a7 = new Actuator("32", "0"); //Brandalarm Alert
	addActuator("32", a7);
	a8 = new Actuator("38", "0"); //Incorrect PIN Alert
	addActuator("38", a8);
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
s = "";

PIN = "1234"; //PIN code voor keypad defineren.

int lichtwaarde;
map<string, Sensor*>::iterator it;
map<string, Sensor*> acts = dev.at("Venster")->getSensors();

lichtwaarde = stoi(acts.at("17")->getValue());

cout << "Lichtwaarde: " << lichtwaarde << endl;

if(a5->getValue() == "1" && a4->getValue() == PIN) { //wanneer er op de client.php op "Enter" is gedrukt wordt de ingevoerde waarde geverifierd ten opzichte van de PIN.
	s = s + "24;1;27;0;28;0;";
	incorrectPinCount = 0; //als de PIN correct is worden eventuele foute pogingen verwijdert.
}
else if(a5->getValue() == "1" && a4->getValue() != PIN){
	incorrectPinCount = stoi(this->a8->getValue()); //huidige foute pogingen.
	incorrectPinCount++; //foutepogingen verhogen.
	s = s + "29;1;28;0;27;0;39;1;38;" + to_string(incorrectPinCount) + ";"; //alert aan de bewaker op de client.php tonen.
}

if(a3->getValue() == "1" && timeDoorStart == NULL){
	timeDoorStart = time(nullptr); //timer starten.
}

if(timeDoorStart != NULL) { //wanneer 2 seconden zijn verstreken gaat het de deur dicht.
	if (time(nullptr) >= timeDoorStart + 2){
			s = s + "24;0;";
			timeDoorStart = NULL;
	}

}

if(s2->getValue() == "1" && a3->getValue() != "1") { //Wanneer op de Deurknop buiten wordt gedrukt, gaat de deur open.
	s = s + "39;1;";

	cout << "Alert naar bewaker (Deur openen van buitenaf). \n";
}

if((s1->getValue() == "1" || s2->getValue() == "2") && a7->getValue() == "1") { //Wanneer Brandalarm afgaat openen beide deurknoppen de deur.
	s = s + "24;1;";

	cout << "Brandalarm is afgegaan, deur gaat open.\n";
}

if(lichtwaarde < 400){
	s = s + "22;1;";
}
else if(lichtwaarde >= 400){
	s = s + "22;0;";
}

if(lichtwaarde < 400 && s2->getValue() == "2"){ //Wanneer het nacht is (lichtintensitiet < 400) gaat snachts de buiten lamp aan voor 6 seconden.
	s = s + "39;1;23;3;"; //lED aanzetten en bewaker inlichten.
	timeStart = time(nullptr); //timer starten.

}
if( timeStart != NULL) { //wanneer 6 seconden zijn verstreken gaat het lampje uit, de melding blijft voor de bewaker staan.
	if (time(nullptr) >= timeStart + 6){
			s = s + "23;1;";
			timeStart = NULL;
	}

}
	cout << s << endl;
	return s;
}

