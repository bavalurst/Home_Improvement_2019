/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Control.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"

using namespace rapidjson;

int main()
{
    FILE* rp = fopen("testJSON.json", "r"); // non-Windows use "r"
 
    char readBuffer[65536];

    FileReadStream is(rp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    cout << readBuffer << endl;

    fclose(rp);

    FILE* wp = fopen("testJSON.json", "w"); // non-Windows use "w"
 
    char writeBuffer[65536];
    FileWriteStream os(wp, writeBuffer, sizeof(writeBuffer));

    Value& s = d["Age"];
    s.SetInt(s.GetInt() + 1);
 
    PrettyWriter<FileWriteStream> writer(os);
    d.Accept(writer);
 
    fclose(wp);

    Control c1;

    while(1)
    {
    	usleep(100000);						// wait 100ms
    	c1.compareDatabaseToDevice();		// compare data from Database to Devices
    }
}
