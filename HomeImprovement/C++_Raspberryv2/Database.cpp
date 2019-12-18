/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Database.h"

Database::Database() {
	this->refreshData();
}

Database::~Database() {}

int Database::receiveMessage()
{
    return 6;
}

void Database::setValue(int val)
{
    value = val;
}

int Database::getValue()
{
    return value;
}

void Database::updateData(string key, string value) {
	//New key/value pair to be written
	data[key] = value;
	//Define file location
	ofstream Out("/home/programmer/json.txt");
	//write new values to file
	writer.write(Out, data);


}

void Database::refreshData() {

	ifstream In("/home/programmer/data.json");
	buffer << In.rdbuf();
	reader.parse(buffer, data);

}

string Database::readData(string key) {

	this->refreshData();
	return data[key];

}
