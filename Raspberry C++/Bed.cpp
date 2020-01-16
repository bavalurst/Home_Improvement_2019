#include "Bed.h" 


// Schakelaar bedient lamp ???
//     Wat moet hij anders doen ???
// Seizure alarm moet uit via de GUI ???

Bed::Bed(char* ip) : Device(ip)
{
	timeStart = time(nullptr);
	oneSecond = timeStart + 1;
	a1 = new Actuator("1", "0");
	addActuator("1", a1);
	s1 = new Sensor("2", "0");
	addSensor(s1);
	s2 = new Sensor("3", "0");
	addSensor(s2);
}

Bed::~Bed() {
	delete a1;
	delete s1;
	delete s2;
}

string Bed::logic(map<string, Device*> dev)
{
	string a = this->a1->getValue();
	string s = "";

	map<string, Actuator*> acts = dev.at("Bed")->getActuators();
	if (seizureLevel == -1){
		lastAct = stoi(this->s2->getValue());
		seizureLevel = 0;
		s = s + "31;0;";
	}

	if(oneSecond - time(nullptr) == 0 && seizureLevel < 3) {
		oneSecond = time(nullptr) + 1;
		seizureTime++;
		if (lastAct - stoi(this->s2->getValue()) > 200 || lastAct - stoi(this->s2->getValue()) < -200 ) {
			seizureLevel++;
		}
		lastAct = stoi(this->s2->getValue());

		if (seizureTime >= 5) {
			seizureTime = 0;
		}
	}

	if (seizureLevel >= 2 && seizureTime <= 3) {
		cout << endl << endl << endl << "TIMMY GAAT DEAUDDDDD!!!!!11" << endl << endl << endl;
		s = s + "31;1;";
		seizureLevel = -1;
	}

	if ((time(nullptr) - timeStart) > 16 && goSleep == 0 && alarm == 0) {
		s = s + "1;1;";
		timeStart = time(nullptr);
		goSleep = 1;
	}

	if (stoi(this->s2->getValue()) > 200 && goSleep == 1) {
		s = s + "1;0;";
	}

	if ((time(nullptr) - timeStart) > 8 && goSleep == 1) {
		cout << "WAKKER WORDEN TIMMY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1" << endl;
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


