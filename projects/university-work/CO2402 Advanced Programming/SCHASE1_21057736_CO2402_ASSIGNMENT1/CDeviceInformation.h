#pragma once
#include "Node.h"
#include "CDevice.h"
#include "CDeviceNode.h"
class CDeviceInformation : public Node
{
protected:
	std::string eName;
	std::shared_ptr<CDevice> mDevice;
public:

	std::shared_ptr<CDevice> getDevice();
	void setDevice(std::shared_ptr<CDevice> device);


	CDeviceInformation();

	void toggleDevice(); //used to in buttons in device info page
	void interactEvent();//used to in buttons in device info page
	void editDevice();//used to in buttons in device info page
	void deleteDevice(std::shared_ptr<CDeviceNode> devicesNode); //you are figuring out how to backtrack to the devices vector to manipulate it
};

