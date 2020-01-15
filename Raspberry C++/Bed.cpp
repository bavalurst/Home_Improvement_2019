#include "Bed.h" 

Bed::Bed(char* ip, time_t Time) : Device(ip)
{
	timeStart = Time;
	a1 = new Actuator("1", "0");
	addActuator("1", a1);
	s1 = new Sensor("2", "0");
	addSensor(s1);
	s2 = new Sensor("3", "0");
	addSensor(s2);
}

Bed::~Bed() {}

string Bed::logic(map<string, Device*> dev)
{
	string a = this->a1->getValue();
	string s = "";

	map<string, Actuator*> acts = dev.at("Bed")->getActuators();


	if ((time(nullptr) - timeStart) > 16 && goSleep == 0 && alarm == 0) {
		s = s + "1;1;";
		timeStart = time(nullptr);
		goSleep = 1;
	}

	if (stoi(this->s2->getValue()) > 200 && goSleep == 1) {
		s = s + "1;0;";
	}

	if ((time(nullptr) - timeStart) > 8 && goSleep == 1) {
		cout << "WAKKER WORDEN TIMMY!!!1" << endl;
		alarm = 1;
		s = s + "30;1;";
		timeStart = time(nullptr);
		goSleep = 0;
	}
	if (stoi(this->s2->getValue()) < 200 && goSleep == 0 && alarm == 1) {
		s = s + "30;0;";
		alarm = 0;
	}

	/**
	if (stoi(this->s2->getValue()) > 200 && acts.at("1")->getValue() != "1") {
		s = s + "1;1;";
	}

	if (stoi(this->s2->getValue()) < 200 && acts.at("1")->getValue() != "0") {
		s = s + "1;0;";
	}
	*/

	return s;
}


