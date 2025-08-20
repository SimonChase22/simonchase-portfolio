#include "CSearchNode.h"

bool CSearchNode::searchForDevice(std::shared_ptr<CDeviceNode> deviceNode)
{
	deviceNode->searchedDevices = {}; //resets searched device vector
	bool deviceFound = false;
	std::string searchInput;
	system("cls");

	std::cout << "Enter a device name to search for: ";
	std::getline(std::cin, searchInput);

	for (int i = 0; i < (deviceNode->devices.size()); i++) //for loop through all devices
	{
		if (deviceNode->devices[i]->getName().find(searchInput) != std::string::npos) //if the entered substring is present in any of the device names
		{
			deviceNode->searchedDevices.push_back(deviceNode->devices[i]); //push that device back onto searchedDevices
			deviceFound = true; //identify that at least one device has been found
		}
	}

	if (deviceFound == false) //if no devices were found
	{
		std::cout << "\n\nNo devices found with search term: " << searchInput << "\n";
	}

	return deviceFound;
}

CSearchNode::CSearchNode()
{
	data = 6;
}
