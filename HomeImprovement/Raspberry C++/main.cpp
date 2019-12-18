//#include <iomanip>
//#include <fstream>
//#include <streambuf>
//#include "json.h"
//#include "reader.h"
#include "Control.h"

int main()
{
    Control c1;

    while(1)
    {
    	usleep(100000);						// wait 100ms to prevent socket failure
    	c1.compareDatabaseToDevice();		// compare data from Database to Devices
    }
}
