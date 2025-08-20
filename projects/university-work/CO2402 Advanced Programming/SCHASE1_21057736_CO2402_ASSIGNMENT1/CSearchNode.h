#pragma once
#include "Node.h"
#include "CDeviceNode.h"

class CSearchNode : public Node
{
public : 
	bool searchForDevice(std::shared_ptr<CDeviceNode> deviceNode); //allows user to search for a device name and returns true if at least one is found
	CSearchNode();
};

