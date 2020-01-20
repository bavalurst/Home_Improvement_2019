#include "Stoel.h"

Stoel::Stoel(char* ip) : Device(ip) {

	timeStart = time(nullptr);
	alarm = NULL;
	cooldown = NULL;
	oneSecond = timeStart + 1;
	a1 = new Actuator("4", "0"); //Actuator voor trillfunctie
	addActuator("4", a1);
	a2 = new Actuator("5", "0"); //Actuator voor LED
	addActuator("5", a1);
	s1 = new Sensor("6", "0"); //sensor voor druksensor
	addSensor(s1);
	s2 = new Sensor("7", "0"); //sensor voor stoelknop
	addSensor(s2);

}

Stoel::~Stoel() {

	delete a1;
	delete s1;
	delete s2;

}

string Stoel::logic(map<string, Device*> dev)
{
	string s = "";

	timeStart = time(nullptr);

	//massage function
	if(s1->getValue() == "2" && alarm == NULL && cooldown == NULL) { //wanneer de trilfunctie op "2" wordt gezet en het alarm en cooldown niet in gebruik zijn start de massage en wordt de 5 seconden cooldown gestart.
		s = "4;1;5;1;33;1;";
		alarm = timeStart + 5; //tijdsduur van de massage.
		cout << "Massage initiated \n";
	}

	if(timeStart > alarm && alarm != NULL){ //Massage functie beindigen na 5 seconden
		alarm = NULL;
		s = "4;0;5;0;33;0;";
		cooldown = timeStart + 5; //tijdsduur van de cooldown bepalen.
		cout << "Massage ended \n";
	}

	if(timeStart > cooldown && cooldown !=NULL){ //5 seconden cooldown voor massage functie
		cooldown = NULL; //cooldown is voorbij.
		cout << "Massage cooldown ended \n";
	}

	//seisure detection
	if(seizureTime == 0){
		previousPressure = stoi(this->s1->getValue()); //eerste waarde meten van de druksensor
		seizureTime++;
	}

	if(seizureTime >= 1){
		currentPressure = stoi(this->s1->getValue()); //nieuwe waarde meten van de druksensor
		if((currentPressure - previousPressure > 200 || currentPressure - previousPressure > -200) && seizureTime < 3){ //wanneer de nieuwe waarde ten opzichte van de basis waarde een afwijking heeft dan 200 wordt de seizureLevel verhoogt.
			seizureLevel++;
			previousPressure = currentPressure;
		}
		else{
			seizureLevel = 0; //wanders wordt het process herstart.
			seizureTime = 0;
		}

		if(seizureLevel == 3 && seizureTime >= 3){ //wanneer er meer dan 3 iteraties een groot verschil is er sprake van een beroerte.
			s = s + "33;1;"; //seizure alarm wordt geactiveerd.
			cout << "Seizure Detected";
		}
	}

	return s; //geef nieuwe actuator waarden door.
}

