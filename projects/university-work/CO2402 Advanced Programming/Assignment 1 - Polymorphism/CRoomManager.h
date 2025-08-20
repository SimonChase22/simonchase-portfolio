#pragma once
#include "Node.h"
#include "CDeviceNode.h"
#include "CDeviceInformation.h"
#include "devices.h"
#include <set>
#include <random>


#define KEY_UP 72
#define KEY_DOWN 80
#define SPACE 32
#define BACKSPACE '\b'

class CRoomManager : public Node
{
protected:
	int kAscii;//used for the navigation loop
	int mIndex;//used for the navigation loop
	bool inRoom;//used for the navigation loop
	bool exitToRooms;// used to backtrack
	std::string roomName;
public:
	bool getExitStatus(); //checks if the user has exited the room

	std::vector<std::string> roomNames; //stores unique room names
	void findRoomNames(std::vector<std::shared_ptr<CDevice>> devices); //parses devices to find unique room names to store in roomNames

	void toggleAllDevice(std::vector<std::shared_ptr<CDevice>> devices, bool currentStatus); //function used for both turn all on and turn all off buttons
	int generateNewId(std::vector<std::shared_ptr<CDevice>> devices); //generates a unique id for copy room function
	void copyRoom(std::shared_ptr<CDeviceNode> devicesNode, std::string roomName); //copies all devices in room and appends _copy onto the room name and device name

	void navigationUserInput(int inputIndex, std::vector<std::shared_ptr<CDevice>> roomDevices, std::shared_ptr<Node> mRoot, std::shared_ptr<CDeviceNode> devicesNode);
	std::shared_ptr<Node> navigateRooms(std::vector<std::shared_ptr<CDevice>> devices, int chosenRoom, std::shared_ptr<Node> mRoot, std::shared_ptr<CDeviceInformation> deviceInfoNode, std::shared_ptr<CDeviceNode> devicesNode); //allows user to parse unique rooms
	CRoomManager();
};

