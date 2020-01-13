#include "Database.h"

Database::Database() {
	this->refreshData();
}

Database::~Database() {}

int Database::receiveMessage()
{
    return 6;
}

void Database::updateData(string key, string value) {
	//New key/value pair to be written
	data[key] = value;
	//Define file location
	ofstream Out("/home/programmer/data.json");
	//write new values to file
	writer.write(Out, data);
	Out.close();

}

void Database::refreshData() {
	//buffer.str("");
	ifstream In("/home/programmer/data.json");
	buffer << In.rdbuf();
	buffer.clear();
	cout << buffer.str();
	buffer.clear();
	cout << data["1"];
	buffer.clear();
	reader.parse(buffer, data);
	In.close();

}

string Database::readData(string key) {

	this->refreshData();
	//data[key] = "5";
	//this->updateData(key, "9");
	//cout << "ik ben een faggot";
	//usleep(100000);
	string banaan = data[key].asString();
	//cout << banaan;
	//return data[key].asString();
	return banaan;
}
