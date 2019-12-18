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
#include "Device.h"
#include "Database.h"
#include "Control.h"
#include "Bed.h"
#include "Control.h"

using namespace Json;
using namespace std;

int main () {
	Control control;

	while(1) {
		control.getData();
		usleep(100000);
	}

	return 1;

}


