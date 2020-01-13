#include "Database.h"

Database::Database() {
	this->refreshSensorData();
	this->refreshActuatorData();
}

Database::~Database() {}

void Database::updateSensorData(string key, string value) {
	//New key/value pair to be written
	this->refreshSensorData(); //kan er misschien uit plz test
	sensor[key] = value;
	//Define file location
	ofstream Out("/home/pi/sensor.json");
	//write new values to file
	writer.write(Out, sensor);
	Out.close();

}

void Database::refreshActuatorData() {

	buffer.clear();
	ifstream In("/home/pi/actuator.json");
	buffer << In.rdbuf();
	reader.parse(buffer, actuator);
	buffer.clear();
	In.close();

}

void Database::refreshSensorData() {
	buffer.clear();
	ifstream In("/home/pi/sensor.json");
	buffer << In.rdbuf();
	reader.parse(buffer, sensor);
	buffer.clear();
	In.close();
}

string Database::readActuatorData(string key) {

	this->refreshActuatorData();
	string banaan = actuator[key].asString();
	return banaan;

}
