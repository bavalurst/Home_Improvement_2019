#include "Bed.h" 


Bed::Bed(char* ip) : Device(ip)
{
	timeStart = time(nullptr); // timeStart wordt hier op de huidige tijd in secondese sinds 1 januaria 1970 gezet.
	oneSecond = timeStart + 1; // oneSecond op één seconde later dan timeStart
	// Door het trucje hierboven kunnen we continu loopen zonder dat we één seconde het programma stil laten staan.
	// In de loop wordt dus als het ware continu vergeleken of er al één seconde is verstreken.
	
	//Hieronder worden alle actuatoren en sensoren aangemaakt en op 0 gezet.
	a1 = new Actuator("1", "0");
	addActuator("1", a1);
	s1 = new Sensor("2", "0");
	addSensor(s1);
	s2 = new Sensor("3", "0");
	addSensor(s2);
}

Bed::~Bed() {
	// Bij aanroep deconstructor weer memory vrijgeven
	delete a1;
	delete s1;
	delete s2;
}

string Bed::logic(map<string, Device*> dev)
{
	string a = this->a1->getValue(); // Waarde actuator1 in "a" opslaan
	string s = ""; // Dit wordt het bericht dat gereturned wordt uit deze functie logic.

	map<string, Actuator*> acts = dev.at("Bed")->getActuators(); // acts bevat alle actuatoren uit "Bed"
	if (seizureLevel == -1){ // initialisatiefase. Zie Bed.h; seizurelevel begint op -1
		lastAct = stoi(this->s2->getValue()); // De huidige waarde van de druksensor wordt nu opgeslagen in "lastAct" (vage naam)
		seizureLevel = 0; // seizurelevel wordt op 0 gezet.
		s = s + "31;0;"; // Hierin wordt aan het bericht s de waardes 31;0; toegevoerd. 
		// Het bericht s wordt in de functie gereturned en in control worden de juisteren actuatoren aangestuurd.
		// In dit geval wordt dus key 31 op waarde 0 gezet.
	}

	if(oneSecond - time(nullptr) == 0 && seizureLevel < 3) { // Als één seconde verstreken en nog niet hoge seizurelevel...
		oneSecond = time(nullptr) + 1;
		seizureTime++;
		if (lastAct - stoi(this->s2->getValue()) > 200 || lastAct - stoi(this->s2->getValue()) < -200 ) { 
			// is het verschil tussen de laatste en huidige druksensorwaarde groter dan 200? \
			// Dan gaat seizurelevel eentje omhoog
			seizureLevel++;
		}
		lastAct = stoi(this->s2->getValue());

		if (seizureTime >= 5) { // Na 5 seconde meten, beginnen we opnieuw met meten voor seizures
			seizureTime = 0;
		}
	}

	if (seizureLevel >= 2 && seizureTime <= 3) { //Als binnen 3 seconde 2 of meer grote wijzigingen in druk meetbaar zijn, alarm!
		// cout << endl << endl << endl << "TIMMY KRIJGT EEN EPILEPTISCHE AANVAL!" << endl << endl << endl;
		s = s + "31;1;"; // notificatie seizure alert op de GUI van de bewaker
		seizureLevel = -1; // opnieuw seizurelevel initialiseren
	}

	if ((time(nullptr) - timeStart) > 16 && goSleep == 0 && alarm == 0) { // Om "11 uur" (na 16 seconde)
		s = s + "1;1;"; // lampje aan
		timeStart = time(nullptr);
		goSleep = 1;
	}

	if (stoi(this->s2->getValue()) > 200 && goSleep == 1) { // Als Timmothy op bed gaat liggen na 11 uur
		s = s + "1;0;"; // lamp weer uit
	}

	if ((time(nullptr) - timeStart) > 8 && goSleep == 1) { // Na 8 uur slapen, dus om 7 uur 's ochtends
		//cout << "WAKKER WORDEN TIMMY!" << endl;
		alarm = 1; // alarm aan
		s = s + "30;1;"; // alarm in de GUI van Timmothy.
		timeStart = time(nullptr);
		goSleep = 0;
	}
	if (stoi(this->s2->getValue()) < 200 && goSleep == 0 && alarm == 1) { // Alarm weer uitzetten als Timmothy is opgestaan
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

	return s; // alle actuatoren key en waardes returnen zodat ze in control kunnen worden verwerkt
}


