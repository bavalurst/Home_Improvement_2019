#include <iomanip>
#include <fstream>
#include <streambuf>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include "Control.h"

int main()
{
    Control c1;

    while(1)
    {

    	c1.compareDatabaseToDevice();		// compare data from Database to Devices (from website to database)

    }
}
