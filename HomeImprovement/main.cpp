/*
 * main.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: programmer
 */
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <streambuf>

#include "json.h"
#include "reader.h"
#include "Controller.h"
using namespace Json;
using namespace std;

int main () {
	Controller controller;

	cout << "old data:" << endl;
    controller.readAllData();

    cout << endl;

    controller.updateData("fruit", "Bananas");

    cout << "new data: " <<endl;

    controller.readAllData();


	return 1;

}


