#include "Control.h"

Control::Control(/* args */) {}

Control::~Control() {}

void Control::compareData()
{
    map<int, Database*> dataBase = d1.getDatabase();
    map<int, Wemos*> dataWemos = w1.getWemos();
    map<int, Wemos*>::iterator iter = dataWemos.begin();

    for (map<int, Database*>::iterator it = dataBase.begin(); it != dataBase.end(); ++it)
    {
        if(!(it->first == iter->first && it->second->getData() == iter->second->getData()))
        {
        	// logica
        	w1.sendData(iter->first);
        }
        iter++;
    }
}
