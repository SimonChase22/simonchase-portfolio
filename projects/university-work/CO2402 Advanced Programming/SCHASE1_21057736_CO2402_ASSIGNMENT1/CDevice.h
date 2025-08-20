#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define SPACE 32
#define KEY_LEFT 75
#define KEY_RIGHT 77
//This will act as the base class for all devices

class CDevice
{
protected:
	int mId;
	std::string mName;
	std::string mType;
	std::string mManufacturer;
	std::string mRoom;
	bool mStatus;

	int kAscii; //used in user input for editing/interacting
	int mIndex; //same as above
	int chosenEditIndex; //used in editing variables

public:

	CDevice();
	CDevice(int id, std::string name, std::string type, std::string manufacturer, std::string room);

	CDevice(CDevice& original, int newId); //basic copy constructor
	virtual void setData(int id, std::string name, std::string type, std::string manufacturer, std::string room);

	int getId();
	std::string getName();
	std::string getType();
	std::string getManufacturer();
	std::string getRoom();
	bool getStatus();

	void setId(int id);
	void setName(std::string name);
	void setType(std::string type);
	void setManufacturer(std::string manufacturer);
	void setRoom(int room);
	void setStatus(bool status);

	virtual void interactionEvent(); //cannot be pure virtual as devices are stored as instances of CDevice, and you cannot instantiate abstract classes

	virtual void editDeviceUserInput(std::vector<std::string> modifiableVariables);
	virtual void editDeviceInformation(); //only needs overriding if a device has additional information values such as a camera having power or quality


	void addMenuFunctions(std::shared_ptr<std::vector<std::string>> menu);
	virtual std::vector<std::string> menu(); //this returned vector acts as the 'menu', so that when the page is refreshed the names for each variable can be pulled from the device

	virtual std::string outputData();
};

