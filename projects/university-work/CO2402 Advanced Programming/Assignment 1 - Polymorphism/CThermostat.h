#pragma once
#include "CDevice.h"	
class CThermostat : public CDevice
{
protected:
	float mTargetTemp;
	bool mDoneEditing; //used in user interaction to confirm setting option

public:
	CThermostat();
	CThermostat(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, float targetTemp); //used in reading in data
	CThermostat(int id, std::string name, std::string type, std::string manufacturer, std::string room); //used in device creation
	void setData(int id, std::string name, std::string type, std::string manufacturer, std::string room);

	CThermostat(CThermostat& original, int newId); //copy constructor to use in copy room functions

	void interactionUserInput();
	void interactionEvent() override; //override to define functions to be specific to thermostat
	std::vector<std::string> menu() override; 
	std::string outputData() override;

};

