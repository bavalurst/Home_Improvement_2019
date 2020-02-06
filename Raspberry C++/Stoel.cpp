#include "Stoel.h"

Stoel::Stoel(char* ip) : Device(ip) {

	timeStart = time(nullptr);
	alarm = NULL;
	cooldown = NULL;
	oneSecond = timeStart + 1;
	a1 = new Actuator("4", "0"); //Actuator voor trilfunctie
	addActuator("4", a1);
	a2 = new Actuator("5", "0"); //Actuator voor LED
	addActuator("5", a2);
	a3 = new Actuator("40", "0"); //Actuator voor de website om de trilfunctie aan te zetten. Is nodig voor de check of de stoel aan mag of niet.
	addActuator("40", a3);
	s1 = new Sensor("6", "0"); //sensor voor druksensor
	addSensor(s1);
	s2 = new Sensor("7", "0"); //sensor voor stoelknop
	addSensor(s2);

}

Stoel::~Stoel() {

	delete a1;
	delete a2;
	delete a3;
	delete s1;
	delete s2;

}

string Stoel::getStatus(string key){
	if(key == "4"){
		if(a1->getValue() == "2"){
			return "De Massage functie van stoel staat aan.";
		}
	}
	if(key == "5"){
		if(a2->getValue() == "1"){
			return "De LED op de stoel staat aan.";
		}
	}
	if(key == "6"){
		string a = "De huidge waarde van de druksensor op de stoel is: " + s1->getValue();
		return a;
	}
	if(key == "7"){
		if(s2->getValue() == "1"){
			return "De knop op de stoel is ingedrukt";
		}
	}
}

string Stoel::logic(map<string, Device*> dev)
{
	string s = "";

	timeStart = time(nullptr);

	//massage function
	if((s2->getValue() == "1" || a3->getValue() == "1") && alarm == NULL && cooldown == NULL) { //wanneer de trilfunctie op "2" wordt gezet en het alarm en cooldown niet in gebruik zijn start de massage en wordt de 5 seconden cooldown gestart.
		s = s + "4;2;33;0;";
		alarm = timeStart + 5; //tijdsduur van de massage.
		//cout << "Massage initiated \n";
	}

	if((s2->getValue() == "1" || a3->getValue() == "1") && cooldown != NULL) {

		s = s + "33;1;"; //als hij aan wilt worden gezet terwijl de cooldown nog actief is
	}

	/*if((s2->getValue() == "0" || a3->getValue() == "0") && alarm != NULL) {
		cooldown
	}*/

	if(timeStart > alarm && alarm != NULL){ //Massage functie beindigen na 5 seconden
		alarm = NULL;
		s = s + "4;0;";

		cout << endl << endl << "IK ZET STOEL NU UIT LOL" << endl << endl;
		cooldown = timeStart + 5; //tijdsduur van de cooldown bepalen.
		//cout << "Massage ended \n";
	}

	if(timeStart > cooldown && cooldown !=NULL){ //5 seconden cooldown voor massage functie
		cooldown = NULL; //cooldown is voorbij.
		//cout << "Massage cooldown ended \n";
	}

	//seizure detection
	if (seizureLevel == -1){ // initialisatiefase. Zie Bed.h; seizurelevel begint op -1
		lastAct = stoi(this->s1->getValue()); // De huidige waarde van de druksensor wordt nu opgeslagen in "lastAct" (vage naam)
		seizureLevel = 0; // seizurelevel wordt op 0 gezet.
		s = s + "31;0;"; // Hierin wordt aan het bericht s de waardes 31;0; toegevoerd.
		// Het bericht s wordt in de functie gereturned en in control worden de juisteren actuatoren aangestuurd.
		// In dit geval wordt dus key 31 op waarde 0 gezet.
	}

	if (lastAct - stoi(this->s1->getValue()) > 50 || lastAct - stoi(this->s1->getValue()) < -50 ) {
		// is het verschil tussen de laatste en huidige druksensorwaarde groter dan 50?
		// Dan gaat seizurelevel eentje omhoog
		lastAct = stoi(this->s1->getValue());
		seizureLevel++;
	}

	if(oneSecond - time(nullptr) == 0) { // Als één seconde verstreken en nog niet hoge seizurelevel...
		oneSecond = time(nullptr) + 1;
		seizureTime++;
	}

	if (seizureTime < 10) { // Na 10 seconde meten, beginnen we opnieuw met meten op seizures
		if (seizureLevel >= 5){
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

	if(a3->getValue() == "1" && switchTimer == NULL) {
		switchTimer = timeStart + 1;
		cout << endl << "SWITCHTIMER IS AANGEZET" << endl;
	}

	if(timeStart > switchTimer && a3->getValue() == "1") {
		s = s + "40;0;";
		switchTimer = NULL;
		cout << endl << "SWITCHTIMER IS UITGEZET" << endl;
	}

	return s; //geef nieuwe actuator waarden door.
}

