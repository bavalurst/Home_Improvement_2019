#include "Control.h"
#include "Socket.h"


int main()
{
    Control c1;

    while(1)
    {
    	usleep(50000);
    	c1.compareData();
    }
}
