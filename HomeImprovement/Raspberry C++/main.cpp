#include "Control.h"

int main()
{
    Control c1;

    while(1)
    {
    	usleep(100000);						// wait 100ms to prevent socket failure
    	c1.compareDatabaseToDevice();		// compare data from Database to Devices (from website to database)
    	//c1.getDataFromWmos(); 			// loop for reading data and putting it in json (from wmos to database)
    }
}
