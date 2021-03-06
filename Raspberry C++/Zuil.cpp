#include "Zuil.h"

Zuil::Zuil(char* ip) : Device(ip) {

	// Hieronder worden de actuatoren en sensoren benoemd met key en worden ze op 0 gezet.
	a1 = new Actuator("10", "0");
	addActuator("10", a1);
	a2 = new Actuator("11", "0");
	addActuator("11", a2);
	s1 = new Sensor("12", "0");
	addSensor(s1);
	s2 = new Sensor("13", "0");
	addSensor(s2);

}

Zuil::~Zuil() {
	// Bij aanroepen deconstructor, memory vrijmaken
	delete a1;
	delete a2;
	delete s1;
	delete s2;

}

string Zuil::getStatus(string key){
	if(key == "10"){
		if(a1->getValue() == "1"){
			return "De zoemer staat aan.";
		}
	}
	if(key == "11"){
		if(a2->getValue() == "2"){
			return "De LED op de zuil staat aan.";
		}
	}
	if(key == "12"){
		if(s1->getValue() == "1"){
			return "De knop op de zuil is ingedrukt.";
		}
	}
	if(key == "13"){
		return "De waarde van de rook sensor is: " + s2->getValue();
	}
	return "";
}

string Zuil::logic(map<string, Device*> dev)
{

	string a = this->a1->getValue(); // Waarde rookdetector oproepen en in "a" zetten.
	string s = ""; // bericht dat gereturned wordt en in logic verwerkt wordt.

	if (stoi(this->s2->getValue()) < 150) { // Bij een waarde van onder de 500 voor de rookmelder...
			s = s + "10;1;"; // Buzzer aan
			s = s + "32;1;"; // Melding BRAND! op de GUI.
			//cout <<endl << endl << endl << "ER IS BRAND!" << endl << endl << endl;
	}

	if (stoi(this->s1->getValue()) == 1) { // Als de noodknop wordt ingedrukt...
		s = s + "37;1;"; // melding naar de GUI van de bewaker.
		//cout <<endl << endl << endl << "Timmothy heeft snel hulp nodig!" << endl << endl << endl;

	}
	return s; // bericht s terugsturen en laten verwerken door Control

}

