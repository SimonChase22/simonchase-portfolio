#include "CRoomManager.h"

bool CRoomManager::getExitStatus()
{
	return exitToRooms;
}

void CRoomManager::findRoomNames(std::vector<std::shared_ptr<CDevice>> devices)
{
	roomNames = {}; //resets room names
	std::set<std::string> uniqueRooms; //used to identify unique room names
	for (int i = 0; i < devices.size(); i++) //loops through all devices
	{
		if (uniqueRooms.insert(devices[i]->getRoom()).second) //if room name has not been seen yet
		{
			roomNames.push_back(devices[i]->getRoom()); //push it back onto roomNames
		}
		
	}
	return;
}

void CRoomManager::toggleAllDevice(std::vector<std::shared_ptr<CDevice>> roomDevices, bool currentStatus) //turns all devices on or off dependent on currentStatus passed in
{
	for (int i = 0; i < roomDevices.size(); i++) //loops through all devices in room
	{
		roomDevices[i]->setStatus(currentStatus); //turns them on or off
	}
}

int CRoomManager::generateNewId(std::vector<std::shared_ptr<CDevice>> devices)
{
	int newId;
	bool isUnique = false;
	while (!isUnique)
	{
		std::random_device seed; //this mixes one random number generator with mersenne twister to decrease odds of repeat numbers
		std::mt19937 idGenerator(seed()); //uses random seed in the mersenne twister
		std::uniform_int_distribution<int> range(1, 214783645); //range is the max numbers an int can hold
		newId = range(idGenerator); //outputs new id to be checked

		for (int i = 0; i < devices.size() - 1; i++)
		{
			if (devices[i]->getId() == newId)
			{
				isUnique = false;
			}
			else
			{
				isUnique = true;
			}
		}
	}
	return newId;
}

void CRoomManager::copyRoom(std::shared_ptr<CDeviceNode> devicesNode, std::string roomName)
{
	for (int i = 0; i < devicesNode->devices.size() - 1; i++)
	{
		if (devicesNode->devices[i]->getRoom() == roomName)
		{
			int newId = generateNewId(devicesNode->devices);
			if (devicesNode->devices[i]->getType() == "Security Camera")
			{
				std::shared_ptr<CSecurityCam> securityCam = std::dynamic_pointer_cast<CSecurityCam>(devicesNode->devices[i]); //casting CDevice ptr to be a CSecurityCam so appropriate copy constructor can be called
				CSecurityCam tempCam(*(securityCam), newId); //using copy constructor
				std::shared_ptr<CSecurityCam> newCam = std::make_shared<CSecurityCam>(std::move(tempCam)); //turning device into a shared_ptr so it can be pushed back onto the devices vector
				devicesNode->devices.push_back(newCam);
			}
			else if (devicesNode->devices[i]->getType() == "Smart Light")
			{
				std::shared_ptr<CSmartLight> smartLight = std::dynamic_pointer_cast<CSmartLight>(devicesNode->devices[i]); //casting CDevice ptr to be a CSmartLight so appropriate copy constructor can be called
				CSmartLight tempLight(*(smartLight), newId); //using copy constructor
				std::shared_ptr<CSmartLight> newLight = std::make_shared<CSmartLight>(std::move(tempLight)); //turning device into a shared_ptr so it can be pushed back onto the devices vector
				devicesNode->devices.push_back(newLight);
			}
			else if (devicesNode->devices[i]->getType() == "Smart Speaker")
			{
				std::shared_ptr<CSmartSpeaker> smartSpeaker = std::dynamic_pointer_cast<CSmartSpeaker>(devicesNode->devices[i]); //casting CDevice ptr to be a CSmartSpeaker so appropriate copy constructor can be called
				CSmartSpeaker tempSpeaker(*(smartSpeaker), newId); //using copy constructor
				std::shared_ptr<CSmartSpeaker> newSpeaker = std::make_shared<CSmartSpeaker>(std::move(tempSpeaker)); //turning device into a shared_ptr so it can be pushed back onto the devices vector
				devicesNode->devices.push_back(newSpeaker);
			}
			else if (devicesNode->devices[i]->getType() == "Thermostat")
			{
				std::shared_ptr<CThermostat> thermostat = std::dynamic_pointer_cast<CThermostat>(devicesNode->devices[i]); //casting CDevice ptr to be a CThermostat so appropriate copy constructor can be called
				CThermostat tempThermostat(*(thermostat), newId); //using copy constructor
				std::shared_ptr<CThermostat> newThermostat = std::make_shared<CThermostat>(std::move(tempThermostat)); //turning device into a shared_ptr so it can be pushed back onto the devices vector
				devicesNode->devices.push_back(newThermostat);
			}
		}
	}
	std::cout << "\n" << roomName << " copied!\n";
	system("pause");
}



void CRoomManager::navigationUserInput(int inputIndex, std::vector<std::shared_ptr<CDevice>> roomDevices, std::shared_ptr<Node> mRoot, std::shared_ptr<CDeviceNode> devicesNode)
{
	kAscii = 0;
	bool keyPressed = false;
	
	while (!keyPressed) //a nested while loop is necessary here, without it _getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_UP:
			mIndex--;
			if (mIndex < 0) //if lower than lower range
			{
				if (inRoom == true)
				{
					mIndex = roomDevices.size() + 2; //set to higher range
				}
			}
			keyPressed = !keyPressed;
			break;



		case KEY_DOWN:
			mIndex++;
			if (inRoom == true && mIndex > (roomDevices.size() + 2)) //if higher than higher range
			{
				mIndex = 0; //set to lower range
			}
			

			keyPressed = !keyPressed;
			break;



		case SPACE:
			if (inRoom == true && (mIndex >= 0 && mIndex < (roomDevices.size()))) //if the user is in the room and index is within range
			{
				inRoom = false; //exits room
			}
			else if (mIndex == roomDevices.size()) //toggle all devices on
			{
				toggleAllDevice(roomDevices, true);
			}
			else if (mIndex == roomDevices.size() + 1) //toggle all devices off
			{
				toggleAllDevice(roomDevices, false);
			}
			else if (mIndex == roomDevices.size() + 2) //copies room
			{
				copyRoom(devicesNode, roomName);
			}
			keyPressed = !keyPressed;
			break;


		case BACKSPACE:
			inRoom = false; //exits room
			exitToRooms = true; //takes the user back to room page
			keyPressed = !keyPressed;
		}
	}
}


std::shared_ptr<Node> CRoomManager::navigateRooms(std::vector<std::shared_ptr<CDevice>> devices, int chosenRoom, std::shared_ptr<Node> mRoot, std::shared_ptr<CDeviceInformation> deviceInfoNode, std::shared_ptr<CDeviceNode> devicesNode)
{
	std::vector<std::string> userMenu; //outputs room values
	int step = 1; //used to move user along linearly
	exitToRooms = false; //used to step back to rooms
	inRoom = true; //if user is in a room
	mIndex = 0;
	roomName = roomNames[chosenRoom];
	std::vector<std::shared_ptr<CDevice>> roomDevices; //stores all devices in selected room

	system("cls");
	for (int i = 0; i < devices.size(); i++) //loops through devices
	{
		if (devices[i]->getRoom() == roomNames[chosenRoom]) //if device is in chosen room
		{
			roomDevices.push_back(devices[i]); //push back onto roomDevices
			userMenu.push_back(devices[i]->getName()); //pushes name onto menu
		}
	}
	userMenu.push_back("[TOGGLE ALL DEVICES ON]"); //menu buttons
	userMenu.push_back("[TOGGLE ALL DEVICES OFF]");
	userMenu.push_back("[DUPLICATE ROOM]");

	while (inRoom) //while user is in room
	{
		
		std::string border = "========"; //start with 8 equals to add length on either side for styling
		for (int i = 0; i < roomName.length(); i++)
		{
			border += "=";
		}
		std::cout << border << "\n    " << roomName << "    \n" << border << "\n"; //prints title with borders


		for (int i = 0; i < userMenu.size(); i++) //outputs menu similar to deviceNode
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				if (i < (roomDevices.size()))
				{
					std::cout << "\033[92m" << userMenu[i] << "\033[0m";
					if (roomDevices[i]->getStatus())
					{
						std::cout << "\033[92m" << "  [CONNECTED]";;
					}
					else
					{
						std::cout << "\033[91m" << "  [DISCONNECTED]";
					}
					std::cout << "\033[0m\n";
				} 
				else
				{
					std::cout << "\033[92m" << userMenu[i] << "\033[0m\n";
				}
			}
			else
			{
				if (i < (roomDevices.size()))
				{
					std::cout << userMenu[i] << "\033[0m";
					if (roomDevices[i]->getStatus())
					{
						std::cout << "\033[92m" << "  [CONNECTED]";;
					}
					else
					{
						std::cout << "\033[91m" << "  [DISCONNECTED]";
					}
				}
				else
				{
					std::cout << userMenu[i] << "\033[0m";
				}
				std::cout << "\033[0m\n"; //resets colour back to default
			}
			if (i == (userMenu.size() - 4))
			{
				std::cout << "\n"; //spacing for menu buttons
			}
		}
		std::cout << "\n\nPRESS SPACE TO VIEW DEVICE INFO OR USE BUTTON, PRESS BACKSPACE TO RETURN\n";
		
		navigationUserInput(mIndex, roomDevices, mRoot, devicesNode);
		system("cls");
	}
	if (exitToRooms) //if user has chosen to exit
	{
		return mRoot; //take back to rooms
	}
	else //if user has selected a device in the room
	{
		deviceInfoNode->setDevice(roomDevices[mIndex]); //set device info node to the selected device
		return deviceInfoNode; //move them to the device info node
	}
}

CRoomManager::CRoomManager()
{
	data = 5;
}
