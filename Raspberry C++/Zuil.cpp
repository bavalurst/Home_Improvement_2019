#include "Zuil.h"

Zuil::Zuil(char* ip) : Device(ip) {

	a1 = new Actuator("10", "0");
	addActuator("10", a1);
	a1 = new Actuator("11", "0");
	addActuator("11", a1);
	s1 = new Sensor("12", "0");
	addSensor(s1);
	s2 = new Sensor("13", "0");
	addSensor(s2);
	//test
			
}

Zuil::~Zuil() {
	delete a1;
	delete s1;
	delete s2;

}

string Zuil::logic(map<string, Device*> dev)
{
	string a = this->a1->getValue();
	string s = "";

	map<string, Actuator*> acts = dev.at("Zuil")->getActuators();

	if (stoi(this->s2->getValue()) < 500) {
			s = s + "10;1;";
			s = s + "32;1;";
			cout <<endl << endl << endl << "ER IS BRAND!!!!! SNEL DOE ER WAT AAN!!!!" << endl << endl << endl;
	}


	if (stoi(this->s1->getValue()) == 1) {
		s = s + "37;1;";
		cout <<endl << endl << endl << "Timmothy heeft snel hulp nodig!" << endl << endl << endl;

	}


	return s;

}

