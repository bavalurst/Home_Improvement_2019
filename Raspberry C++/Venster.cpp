#include "Venster.h"

Venster::Venster(char* ip) : Device(ip) {

	a1 = new Actuator("14", "0");	// ledstrip		waarde 0 tot 10
	addActuator("14", a1);
	a2 = new Actuator("15", "0");	// window 		waarde 1 of 0
	addActuator("15", a2);
	
	s1 = new Sensor("16", "0");		// dimmer
	addSensor(s1);
	s2 = new Sensor("17", "0");		// LDR			onder 400 uit
	addSensor(s2);

}

Venster::~Venster() {

	delete a1;
	delete a2;
	delete s1;
	delete s2;

}

string Venster::getStatus(string key){
	if(key == "14"){
		return "De huidige waarde van de LED-strip is: " + a1->getValue();
	}
	if(key == "15"){
		if(a2->getValue() == "1"){
			return "Het raam is gesloten";
		}
	}
	if(key == "16"){
		return "De huidge waarde van de dimmer is: " + s1->getValue();
	}
	if(key == "17"){
		return "De huidige waarde van de LDR is: " + s2->getValue();
	}
	return "";
}

string Venster::logic(map<string, Device*> dev)
{
	string s = "";
	if(stoi(this->s2->getValue()) <= 400){		// als het donker is
		s = s + "15;1;22;1;";			// sluit het venster en zet de binnenlamp v/d deur aan
		cout << "turning window on" << endl;
	}
	
	else if(stoi(this->s2->getValue()) > 400 && stoi(this->a2->getValue()) != 3){
		s = s + "15;0;";			//venster open
	}

	string LedValue = (this->s1->getValue());
	s = s + "14;" + LedValue + ";";			// felheid van de LED strip staat gelijk aan de waarde van de dimmer


	return s;
}
