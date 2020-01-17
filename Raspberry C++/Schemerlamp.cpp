#include "Schemerlamp.h"

Schemerlamp::Schemerlamp(char* ip) : Device(ip) {

	a1 = new Actuator("8", "0");
	addActuator("8", a1);
	s1 = new Sensor("9", "0");
	addSensor(s1);
	CurrentTime = time(nullptr);
	AlarmTime = NULL;
	fluctuations = 0;

}

Schemerlamp::~Schemerlamp() {

	delete a1;
	delete s1;

}

string Schemerlamp::logic(map<string, Device*> dev)
{
	CurrentTime = time(nullptr);
    string s = "";

    cout << "Ik heb binnen: " << s1-> getValue() << endl;

	if (s1->getValue() != "0" && AlarmTime == NULL) { //if sensor is triggered
		AlarmTime = (CurrentTime + 10); //start reading inputs for 2 seconds
		fluctuations = 0;
	}

	else if (CurrentTime < AlarmTime) { //if sensor is triggered and below
		int res = stoi(s1->getValue());
		cout << "Alarm aan: pushing back: " << res << endl;
		AlarmReading.push_back(res);
	}

	else if (CurrentTime > AlarmTime && AlarmTime != NULL){
		cout << "printing alarm reading: " << endl;
		for (int i = 0; i < AlarmReading.size(); i++) {
				cout << AlarmReading[i];

			if (i < (AlarmReading.size() - 1))
			if (AlarmReading[i] != AlarmReading[i + 1]) {
				fluctuations++;
				cout << "Fluctuatie gevondenop positie: " << i << " Met waarde: " << fluctuations << endl;
				cout << "Want: " << AlarmReading[i] << "not same as " << AlarmReading[i + 1] << endl;
			}

			if (fluctuations >= 3) {
				cout << "Alarm aan! Meneer sterft." << endl;
				s = s + "10;1;"; //website popup id
		}

		}
		AlarmTime = NULL;
		AlarmReading.clear();
	}
	return s;
}








