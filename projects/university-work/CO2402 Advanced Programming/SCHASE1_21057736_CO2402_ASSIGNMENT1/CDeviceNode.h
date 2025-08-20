#pragma once
#include "Node.h"

class CDeviceNode : public Node
{
protected:	
public:
	CDeviceNode();
	CDeviceNode(std::string name);

	std::vector<std::shared_ptr<CDevice>> devices; //unique pointer to a vector of shared device pointers, not necessary to protect until devices.csv is secure
	std::vector<std::shared_ptr<CDevice>> searchedDevices; //used to hold devices that have been searched for, reset after every search



};

