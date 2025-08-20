#include "Node.h"





int Node::getData()
{
	return data;
}

Node::Node(int data, std::string pageName)
{
	this->data = data;
}

Node::Node()
{
	this->data = 0;
}

void Node::setPageName(std::string name)
{
	pageName = name;
}

void Node::setNodeType(int x)
{
	data = x;
}
