/*
 * Controller.h
 *
 *  Created on: Dec 13, 2019
 *      Author: programmer
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Controller.h"
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <string>

#include "json.h"
#include "reader.h"
#include "Controller.h"
using namespace Json;
using namespace std;

class Controller {
public:
	Controller();
	virtual ~Controller();
	void updateData(string, string);
	void readAllData();

private:
	stringstream buffer; //Temporary string buffer for reading JSON
	Reader reader; //Needed to read and parse a string to json.
	Value data; //JSON object, where logic can be applied.
	StyledStreamWriter writer; //Writes JSON data to file
};

#endif /* CONTROLLER_H_ */
