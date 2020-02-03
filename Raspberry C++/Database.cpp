#include "Database.h"

Database::Database() {
	this->refreshSensorData(); 					//read and convert json data files on class creation
	this->refreshActuatorData();

	time_t CurrentTime = time(nullptr);
	stringtime << asctime(localtime(&CurrentTime));
	ofstream logFile("logfile.txt");
	logFile << "Current Time: " << stringtime.str() << endl;
	logFile.close();
}

Database::~Database() {}

void Database::refreshActuatorData() { //refreshes 

	buffer.clear(); 			//clears the buffer before reading, just in case
	ifstream In("/home/pi/actuator.json"); //opens istream, used to read data to file (instream)
	buffer << In.rdbuf(); 			//reads instream and puts it in buffer
	reader.parse(buffer, actuator); 	//parses the data found in buffer, which updates the value object 'actuator'
	buffer.clear(); 			//clear buffer after
	In.close(); 				//close istream

}

void Database::refreshSensorData() {		//idem, for sensor
	buffer.clear(); 			
	ifstream In("/home/pi/sensor.json"); 
	buffer << In.rdbuf();
	reader.parse(buffer, sensor);
	buffer.clear();
	In.close();
}

void Database::writeSensorToFile() {
	ofstream Out("/home/pi/sensor.json");
	writer.write(Out, sensor); 		//writes the json data to file
	Out.close();
	this->refreshSensorData(); //after that, load the file into the system, having actual values for the next routine
}

void Database::updateSensorData(string key, string value) { //updates the sensor.json file with give key and value

	//this->refreshSensorData(); 			//refreshes json data into class before updating it
	sensor[key] = value; 					//updates the value object, which is part of jsoncpp to edit json files, with the corresponding key/value pair. Works like adding a value to a vector.
	//ofstream Out("/home/pi/sensor.json"); //opens ostream, used to write data to file (outstream)
	//writer.write(Out, sensor); 			//writes the json data to file
	//Out.close(); 							//close the ostream.

}

string Database::readActuatorData(string key) { //reads Actuatordata found in given key, and returns it as string

	this->refreshActuatorData();            //parse current status of file
	string value = actuator[key].asString();//get value from key as a string and return it
	return value;
}

void Database::writeActuatorData(string key, string value)  { //writes data to actuator file, idem to 'UpdateSensorData'.

	this->refreshActuatorData();
	actuator[key] = value;
	ofstream Out("/home/pi/actuator.json");
		//write new values to file
	writer.write(Out, actuator);
	Out.close();


}

void Database::createLog(string message) {
	time_t CurrentTime = time(nullptr);
	stringstream stringtimecurrent;
	stringtimecurrent << asctime(localtime(&CurrentTime));

	cout << "Writing: " << message << "To filename: logfile.txt" << endl;

	ofstream logFile("logfile.txt", ios::app);

	if(logFile.is_open()){
		string stringmessage = stringtimecurrent.str() + ": " + message + "\n";
		logFile << stringmessage << endl;
		logFile.close();
	} else {
		cout << "Unable to open file";
	}


}
