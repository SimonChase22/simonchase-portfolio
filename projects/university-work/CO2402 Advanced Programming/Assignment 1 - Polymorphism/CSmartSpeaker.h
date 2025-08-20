#pragma once
#include "CDevice.h"

class CSmartSpeaker : public CDevice
{
protected:
	int mVolume;
	bool mDoneEditing; //used in user interaction to confirm setting option
public:
	CSmartSpeaker();
	CSmartSpeaker(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, int volume); //used in reading in data
	CSmartSpeaker(int id, std::string name, std::string type, std::string manufacturer, std::string room); //used in device creation
	void setData(int id, std::string name, std::string type, std::string manufacturer, std::string room);

	CSmartSpeaker(CSmartSpeaker& original, int newId);

	void interactionUserInput(); //same as user input in deviceManager

	void interactionEvent() override; //override to define functions to be specific to smart speaker
	std::vector<std::string> menu() override;
	std::string outputData() override;

};

