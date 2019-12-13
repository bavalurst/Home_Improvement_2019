/*
 * Controller.cpp
 *
 *  Created on: Dec 13, 2019
 *      Author: programmer
 */

#include "Controller.h"


Controller::Controller() {
	// TODO Auto-generated constructor stub

	// Read json file, put it in buffer as string, and in
	// data as manageable object
	ifstream In("/home/programmer/json.txt");
	buffer << In.rdbuf();
	reader.parse(buffer, data);
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::updateData(string key, string value) {
	//New key/value pair to be written
	data[key] = value;
	//Define file location
	ofstream Out("/home/programmer/json.txt");
	//write new values to file
	writer.write(Out, data);


}

void Controller::readAllData() {

	for (Value::iterator i = data.begin(); i != data.end(); i++) {
	    cout << (*i).asString() << endl;
	}
}

