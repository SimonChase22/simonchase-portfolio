#pragma once
#include "Node.h"
#include "CDeviceNode.h"
#include "devices.h"
#include <conio.h>
#include <limits>

#define KEY_UP 72
#define KEY_DOWN 80
#define SPACE 32
#define BACKSPACE '\b'


class CAddDevice : public Node
{
protected:
	std::vector<std::string> mDeviceTypes;
	int kAscii; //used in navigation
	int mIndex; //used in navigation
	int step; //used to dictate which screen is shown in the device adding process
	std::string title;
	std::string selectedDevice;
public:


	CAddDevice();

	void modifiedUserInput(int inputIndex);
	void addDevice(std::shared_ptr<CDeviceNode> devicesNode); //adds device to devices vector
	bool checkId(std::shared_ptr<CDeviceNode> devicesNode, int id); //if false, id is free, if true, id is in use

};

