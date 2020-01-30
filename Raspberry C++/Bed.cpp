#include "Bed.h" 


Bed::Bed(char* ip) : Device(ip)
{
	timeStart = time(nullptr); // timeStart wordt hier op de huidige tijd in secondese sinds 1 januaria 1970 gezet.
	oneSecond = timeStart - 1; // oneSecond op één seconde eerder gezet dan timeStart (zodat hij nog niet optelt)

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
		lastAct = stoi(this->s2->getValue()); // De huidige waarde van de druksensor wordt nu opgeslagen in "lastAct" (vage naam, klopt)
		seizureLevel = 0; // seizurelevel wordt op 0 gezet.
		s = s + "31;0;"; // Hierin wordt aan het bericht s de waardes 31;0; toegevoerd.
	}

	if (lastAct - stoi(this->s2->getValue()) > 50 || lastAct - stoi(this->s2->getValue()) < -50 ) {
		// is het verschil tussen de laatste en huidige druksensorwaarde groter dan 50?
		// Dan gaat seizurelevel eentje omhoog
		lastAct = stoi(this->s2->getValue());
		seizureLevel++;
	}

	if(oneSecond - time(nullptr) == 0) { // Als één seconde verstreken...
		// Door het trucje hierboven kunnen we continu loopen zonder dat we één seconde het programma stil laten staan.
		// In de loop wordt dus als het ware continu vergeleken of er al één seconde is verstreken.
		oneSecond = time(nullptr) + 1;
		seizureTime++; // Er wordt vanaf nu 10 seconde getelt waarin seizures gedetecteerd worden
	}
	//cout << "Seizure level: " << seizureLevel << endl;
	//cout << "Seizure time: " << seizureTime << endl;

	if (seizureTime < 10) { // Na 10 seconde meten, beginnen we opnieuw met meten op seizures
		if (seizureLevel >= 10){
			//cout << endl << endl << endl << "TIMMY KRIJGT EEN EPILEPTISCHE AANVAL!" << endl << endl << endl;
			s = s + "31;1;"; // notificatie seizure alert op de GUI van de bewaker
			seizureLevel = 0; // seizurelevel resetten
			seizureTime = 0; // seizuretime resetten
		}
		if (seizureLevel == 0)
			oneSecond = time(nullptr) - 1;
		if (seizureLevel == 1) // Pas beginnen met seizureTime tellen zodra er 1 seizureLevel is.
			oneSecond = time(nullptr) + 1;
	}
	else if (seizureTime > 10) { // alles resetten na 10 seconde.
		seizureTime = 0;
		seizureLevel = 0;
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
		s = s + "1;0;30;0;"; // lamp uit, alarm uit
		alarm = 0;
	}


	if(stoi(this->s1->getValue()) == 1 && acts.at("1")->getValue() == "1"){ // Lamp aan bij indrukken knop
		s = s + "1;0;";
	}
	else if(stoi(this->s1->getValue()) == 1 && acts.at("1")->getValue() == "0"){ // Lamp weer uit bij indrukken knop
		s = s + "1;1;";
	}

	return s; // alle actuatoren key en waardes returnen zodat ze in control kunnen worden verwerkt
}
