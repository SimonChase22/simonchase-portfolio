#pragma once
#include "CDevice.h"
class CSmartLight : public CDevice
{
protected:
	int mBrightness;
	std::string mColourType;
	int chosenInteraction; // by default 0, for brightness 1, for light colour 2
public:
	CSmartLight();
	CSmartLight(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, int brightness, std::string colour); //used in reading in data
	CSmartLight(int id, std::string name, std::string type, std::string manufacturer, std::string room); //used in new device creation
	void setData(int id, std::string name, std::string type, std::string manufacturer, std::string room);

	CSmartLight(CSmartLight& original, int newId); //copy constructor used in room copy functions


	void interactionUserInput(int indexInput, std::vector<std::string> settingOptions, std::vector<std::string> colourOptions);

	void interactionEvent() override; //override to define functions to be specific to smart light
	std::vector<std::string> menu() override;
	std::string outputData() override;
};

