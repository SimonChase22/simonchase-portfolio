#pragma once
#include <iostream>
#include <vector>
#include "devices.h"

class CDeviceNode;

class Node
{
protected:
	int data; //this contains the type of node it is, please reference nodes.txt for the key
public:

	int getData();
	std::vector<std::shared_ptr<Node>> children;
	std::string pageName; //this is used for the menu, so when the program looks at the child nodes it has a name to display

	Node(int data, std::string pageName);
	Node();

	void setPageName(std::string name);
	void setNodeType(int x);

	virtual ~Node() = default;
};

