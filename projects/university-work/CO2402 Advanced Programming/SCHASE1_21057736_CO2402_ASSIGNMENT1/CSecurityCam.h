#pragma once
#include "CDevice.h"

class CSecurityCam : public CDevice
{
protected:
	std::string mQuality;
	std::string mPower;

public:
	CSecurityCam();
	CSecurityCam(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, std::string quality, std::string power); //used when reading in device data
	CSecurityCam(int id, std::string name, std::string type, std::string manufacturer, std::string room, std::string quality, std::string power); //used in device creation
	void setData(int id, std::string name, std::string type, std::string manufacturer, std::string room, std::string quality, std::string power);

	CSecurityCam(CSecurityCam& original, int newId); //copy constructor for use in copy room function

	void interactionEvent() override; //override to define functions to be specific to security camera
	void editDeviceInformation() override;
	std::vector<std::string> menu() override;
	std::string outputData() override;
};

