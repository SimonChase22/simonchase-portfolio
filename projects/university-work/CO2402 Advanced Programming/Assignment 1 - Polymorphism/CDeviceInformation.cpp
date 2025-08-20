#include "CDeviceInformation.h"



std::shared_ptr<CDevice> CDeviceInformation::getDevice()
{
	return mDevice;
}

void CDeviceInformation::setDevice(std::shared_ptr<CDevice> device)
{
	mDevice = device;
}

CDeviceInformation::CDeviceInformation()
{
	mDevice = std::make_shared<CDevice>();
	pageName = "Device Information";
	data = 2;
}

void CDeviceInformation::toggleDevice()
{
	mDevice->setStatus(!(mDevice->getStatus())); 
}

void CDeviceInformation::interactEvent()
{
	mDevice->interactionEvent(); //calls device event (polymorphic, mDevice is a CDevice but this works if device is a derived class device) 
}

void CDeviceInformation::editDevice()
{
	mDevice->editDeviceInformation(); //calls device event (polymorphic, mDevice is a CDevice but this works if device is a derived class device) 
}

void CDeviceInformation::deleteDevice(std::shared_ptr<CDeviceNode> devicesNode) //deletes the device from devices vector
{
	for (int i = 0; i < devicesNode->devices.size(); i++) //loops through devices vector
	{
		if ((devicesNode->devices[i]->getId()) == mDevice->getId()) //if device matches current device id
		{
			std::cout << "\n" << devicesNode->devices[i]->getName() << " has been deleted\n";
			system("pause");
			devicesNode->devices.erase(devicesNode->devices.begin() + i); //delete the device from the vector
		}
	}
	return;
}

