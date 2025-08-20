#include "progManager.h"


progManager::progManager()
{
	isRunning = true; //sets program to running
	searchActive = false; //used if search device is active
	mIndex = 0; //used in menu outputting to identify which option the user has highlighted
	kAscii = 0; //used in key input
	initialiseProgram(); //calls program to initialise when progManager instance is created
}

void progManager::displayPage(std::string title, int mIndex, std::shared_ptr<Node> root) //displays a different page and calls different functions dependent on mRoot data
{
	const int mainMenuData = 0; //used in place of magic numbers in mRoot->getData() if statements
	const int deviceNodeData = 1;//used in place of magic numbers in mRoot->getData() if statements
	const int deviceInfoData = 2;//used in place of magic numbers in mRoot->getData() if statements
	const int addDeviceData = 3;//used in place of magic numbers in mRoot->getData() if statements
	const int roomManagerData = 5;//used in place of magic numbers in mRoot->getData() if statements
	const int searchDeviceData = 6;//used in place of magic numbers in mRoot->getData() if statements

	if (mRoot->getData() != addDeviceData)
	{
		std::string border = "========"; //start with 8 equals to add length on either side for styling
		for (int i = 0; i < title.length(); i++)
		{
			border += "=";
		}
		std::cout << border << "\n    " << title << "    \n" << border << "\n"; //prints title with borders
	}

	if (mRoot->getData() == mainMenuData) //displays main menu by listing children of root node
	{
		for (int i = 0; i < (mRoot->children).size(); i++) 
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m";
				std::cout << mRoot->children[i]->pageName << "\n";
				std::cout << "\033[0m"; //resets colour back to default
			}
			else
			{
				std::cout << mRoot->children[i]->pageName << "\n";
			}
		}
		std::cout << "\n\nPRESS SPACE TO SELECT OPTION, OR BACKSPACE TO EXIT\n";
	}

	else if (mRoot->getData() == deviceNodeData) //displays all devices within specified devices vector
	{
		std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot);
		std::vector<std::shared_ptr<CDevice>> devices;

		if (!searchActive) //if search is not active display all devices
		{
			devices = deviceNode->devices;
		}
		else //if search is active only show vector of searched devices
		{
			devices = deviceNode->searchedDevices;
		}

		for (int i = 0; i < devices.size(); i++)
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << (devices)[i]->getName() << "\033[0m";
				if ((devices)[i]->getStatus())
				{
					std::cout << "\033[92m" << " [CONNECTED]\n";
				}
				else
				{
					std::cout << "\033[91m" << " [DISCONNECTED]\n";
				}
				std::cout << "\033[0m"; //resets colour back to default
			}
			else
			{
				std::cout << (devices)[i]->getName();
				if ((devices)[i]->getStatus())
				{
					std::cout << "\033[92m" << " [CONNECTED]\n";
				}
				else
				{
					std::cout << "\033[91m" << " [DISCONNECTED]\n";
				}
				std::cout << "\033[0m"; //resets colour back to default
			}
		}
		std::cout << "\n\nPRESS SPACE TO SELECT DEVICE, OR BACKSPACE TO RETURN\n";
	}

	else if (mRoot->getData() == deviceInfoData) //casts mRoot to CDeviceInformation and displays selected device info
	{
		std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(mRoot);
		outputDeviceInfo(deviceInfoNode->getDevice());
		
	}
	
	else if (mRoot->getData() == addDeviceData) //casts mRoot to CAddDevice and calls function to add new device
	{
		std::shared_ptr<CAddDevice> addDeviceNode = std::dynamic_pointer_cast<CAddDevice>(mRoot);

		std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]);

		addDeviceNode->addDevice(deviceNode);

		
	}
	else if (mRoot->getData() == roomManagerData) //casts mRoot to CRoomManager and displays all unique rooms
	{
		std::shared_ptr<CRoomManager> roomManagerNode = std::dynamic_pointer_cast<CRoomManager>(mRoot);
		std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]);

		roomManagerNode->findRoomNames(deviceNode->devices); //runs a for loop with set to find unique room names and pushes them back onto vector of strings
		for (int i = 0; i < roomManagerNode->roomNames.size(); i++) //displays all unique rooms
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << (roomManagerNode->roomNames[i]) << "\033[0m" << "\n";
			}
			else
			{
				std::cout << roomManagerNode->roomNames[i] << "\n";
			}
		}
		std::cout << "\n\nPRESS SPACE TO SELECT ROOM, OR BACKSPACE TO RETURN\n";
	}
	else if (mRoot->getData() == searchDeviceData) //casts mRoot to CSearchNode and runs search function
	{
		std::shared_ptr<CSearchNode> searchNode = std::dynamic_pointer_cast<CSearchNode>(mRoot);
		std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]);
		searchActive = searchNode->searchForDevice(deviceNode); //calls function that requests substring to search for, and returns true if at least one device with that substring in the name is returned
		
		if (searchActive) //if a device has been found
		{
			mRoot = mMainMenu->children[0]; //send the user to the display devices node
		}
		else //if no device found
		{
			mRoot = mMainMenu; //send the user to main menu
		}
		std::cout << "\nPRESS THE UP OR DOWN ARROW TO BEGIN SEARCHING THROUGH FOUND DEVICES\n"; 
	}
}

void progManager::outputDeviceInfo(std::shared_ptr<CDevice> device) //outputs all device data dynamically
{
	std::vector<std::string> mMenu = device->menu();
	for (int i = 0; i < mMenu.size(); i++)
	{
		if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
		{
			std::cout << "\033[92m" << mMenu[i] << "\033[0m\n";
			
		}
		else
		{
			std::cout << mMenu[i];
			
			std::cout << "\033[0m\n"; //resets colour back to default
		}
		if (i == (mMenu.size() - 5))
		{
			std::cout << "\n"; //spaces out the function options from the device variable information
		}
	}
	std::cout << "\n\nPRESS SPACE TO CONFIRM OPTION, OR BACKSPACE TO RETURN TO MAIN MENU\n";

}

void progManager::userInput(int inputIndex) //takes the user input, and modifies information so that page can refresh with new information
{
	const int mainMenuData = 0; //used in place of magic numbers in mRoot->getData() if statements
	const int deviceNodeData = 1; //used in place of magic numbers in mRoot->getData() if statements
	const int deviceInfoData = 2; //used in place of magic numbers in mRoot->getData() if statements
	const int addDeviceData = 3; //used in place of magic numbers in mRoot->getData() if statements
	const int roomManagerData = 5; //used in place of magic numbers in mRoot->getData() if statements
	const int searchDeviceData = 6; //used in place of magic numbers in mRoot->getData() if statements

	kAscii = 0; //resets input 
	bool keyPressed = false;
	while (!keyPressed) //a nested while loop is necessary here, without it _getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_UP:
			mIndex--; //moves highlighter up by one
			if (mIndex < 0 && mRoot->getData() != deviceInfoData) //check if mIndex is still within menu range
			{
				if (mRoot->getData() == deviceNodeData)
				{
					std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot);
					std::vector<std::shared_ptr<CDevice>> devices;
					if (!searchActive) //if search is not active use size of devices vector
					{
						devices = deviceNode->devices;
					}
					else //if search is active use searchedDevices vector
					{
						devices = deviceNode->searchedDevices;
					}
					mIndex = ((devices).size() - 1); //set mIndex to upper range of vector
				}
				else
				{
					mIndex = (mRoot->children).size() - 1; //set to upper range of children

				}
			}
			else if (mRoot->getData() == deviceInfoData)
			{
				std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(mRoot);
				std::vector<std::string> mTempDeviceMenu = deviceInfoNode->getDevice()->menu();
				if (mIndex < (mTempDeviceMenu.size() - 4)) //if mIndex is less than the first button
				{
					mIndex = (mTempDeviceMenu.size() - 1); //set to upper range of buttons
				}
			}
			else if (mRoot->getData() == roomManagerData)
			{
				std::shared_ptr<CRoomManager> roomManagerNode = std::dynamic_pointer_cast<CRoomManager>(mRoot);
				if (mIndex < 0) //if mIndex is less than lower range
				{
					mIndex = (roomManagerNode->roomNames.size() - 1); //set to higher range
				}
			}
			else if (mRoot->getData() == searchDeviceData)
			{

			}
			keyPressed = !keyPressed;
			break;
			



		case KEY_DOWN:
			mIndex++; //move highlighter down by one
			if (mRoot->getData() == deviceNodeData) 
			{
				std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot);
				std::vector<std::shared_ptr<CDevice>> devices;
				if (!searchActive) //if not active use devices vector
				{
					devices = deviceNode->devices;
				}
				else //if active use searchedDevices vector
				{
					devices = deviceNode->searchedDevices;
				}

				if (mIndex > (devices).size() - 1) //sets mIndex to lower range of vector
				{
					mIndex = 0;
				}
			}
			else if (mRoot->getData() == deviceInfoData)
			{
				std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(mRoot);
				std::vector<std::string> mTempDeviceMenu = deviceInfoNode->getDevice()->menu();
				if (mIndex > mTempDeviceMenu.size() - 1) //if mIndex is more than the higher range of menu buttons
				{
					mIndex = (mTempDeviceMenu.size() - 4); //set to lower range
				}
			}
			else if (mRoot->getData() == roomManagerData)
			{
				std::shared_ptr<CRoomManager> roomManagerNode = std::dynamic_pointer_cast<CRoomManager>(mRoot);
				if (mIndex > (roomManagerNode->roomNames.size() - 1)) //if mIndex is more than higher range of unique rooms
				{
					mIndex = 0; //set to lower range
				}
			}
			else if (mRoot->getData() == searchDeviceData)
			{

			}
			else
			{
				if (mIndex > (mRoot->children).size() - 1) //if mIndex is more than higher range of children
				{
					mIndex = 0; //set to lower range
				}
			}
			
			keyPressed = !keyPressed; 
			break;


		case SPACE:

			if (mRoot->getData() == deviceNodeData)
			{
				std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot);
				std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(deviceNode->children[0]);
				std::vector<std::shared_ptr<CDevice>> devices;

				if (!searchActive) //if not active set to devices vector
				{
					devices = deviceNode->devices;
				}
				else //if active set to searchedDevices vector
				{
					devices = deviceNode->searchedDevices;
				}

				deviceInfoNode->setDevice(devices[mIndex]); //sets the child nodes device to the highlighted device
				mRoot->children[0]->setPageName(devices[mIndex]->getName()); //sets name of the child node page to the highlighted device name

				std::vector<std::string> mTempDeviceMenu = deviceInfoNode->getDevice()->menu();
				mIndex = (mTempDeviceMenu.size() - 4); //sets mIndex to the lower range of menu buttons 
				
				mRoot = mRoot->children[0]; //move mRoot into the child node to display highlighted device info

			}
			else if (mRoot->getData() == deviceInfoData)
			{
				std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]);
				std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(mRoot);
				std::vector<std::string> mTempDeviceMenu = deviceInfoNode->getDevice()->menu();
				//the following code is if highlighted menu button is pressed, call certain functions depending on button
				if (mIndex == (mTempDeviceMenu.size() - 4)) //turns device on/off  
				{
					deviceInfoNode->toggleDevice();
				}
				else if (mIndex == (mTempDeviceMenu.size() - 3)) //interacts with device
				{
					deviceInfoNode->interactEvent();
				}
				else if (mIndex == (mTempDeviceMenu.size() - 2)) //edits device attributes
				{
					deviceInfoNode->editDevice();
				}
				else if (mIndex == (mTempDeviceMenu.size() - 1)) //deletes device
				{
					deviceInfoNode->deleteDevice(deviceNode);
					mRoot = mMainMenu;
					mIndex = 0;
				}
			}
			else if (mRoot->getData() == addDeviceData) //returns the user to main menu after adding device
			{
				mRoot = mMainMenu;
			}
			else if (mRoot->getData() == roomManagerData)
			{
				std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]);
				std::shared_ptr<CRoomManager> roomManagerNode = std::dynamic_pointer_cast<CRoomManager>(mRoot);
				std::shared_ptr<CDeviceInformation> deviceInfoNode = std::dynamic_pointer_cast<CDeviceInformation>(deviceNode->children[0]);

				mRoot = roomManagerNode->navigateRooms(deviceNode->devices, mIndex, mRoot, deviceInfoNode, deviceNode); //moves the mRoot into the room, further comment in navigateRooms() definition
				if (roomManagerNode->getExitStatus()) //if user has exited the room
				{
					mIndex = 0; //set to first menu option
				}
				else //if user has gone from room to specific device
				{
					mIndex = 8; //set to the starting point for menu options
				}
			}
			else if (mRoot->getData() == searchDeviceData)
			{

			}
			else //enter the child node selected
			{
				mRoot = mRoot->children[inputIndex];
				mIndex = 0;
			}
			keyPressed = !keyPressed;
			break;


		case BACKSPACE:
			if (mRoot->getData() == mainMenuData) //if on main menu, set isRunning to false causing program to exit
			{
				isRunning = false;
			}
			if (mMainMenu) //if mainMenu still points to a valid location
			{
				mRoot = mMainMenu; //return to main menu
				mIndex = 0;
			}
			else //used to identify error if cannot return to main menu
			{
				std::cout << "MAIN MENU NO LONGER AVAILABLE";
			}
			
			searchActive = false; //resets search active once back on main menu
			keyPressed = !keyPressed;
		}
	}
}

void progManager::saveData() //saves devices after program exits successfully
{
	std::ofstream storeDevices("devices.csv"); //opens csv
	std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mMainMenu->children[0]); //casts node to CDeviceNode

	for (int i = 0; i < deviceNode->devices.size(); i++) //for all devices in the devices vector
	{
		storeDevices << deviceNode->devices[i]->outputData() << "\n"; //calls the output function to return a string in csv format of device info
	}
	storeDevices.close(); //closes csv

}

void progManager::readInData()
{
	std::ifstream readInFile("devices.csv"); //opens file
	std::string input = ""; //initialising input

	while (std::getline(readInFile, input)) //while not at the end of file
	{
		std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot->children[0]);
		int errorCounter = 0; //used for displaying if devices failed to be read

		std::vector<std::string> line;
		std::stringstream lineSeperation(input); //used to seperate the row by the commas
		std::string value; //holds each word before it is converted (if necessary) then pushed back into a device variable
		
		//start of common values, indexes remain consistent through device types
		const int typeIndex = 0;
		const int idIndex = 1;
		const int nameIndex = 2;
		const int manufacturerIndex = 3;
		const int roomIndex = 4;
		const int statusIndex = 5;

		std::string mType;
		int mId = 0;
		std::string mName;
		std::string mManufacturer;
		std::string mRoom;
		bool mStatus = 0; 
		//end of common values

		const int qualityIndex = 6;//start of values for security cam
		const int powerIndex = 7;
		std::string mQuality; 
		std::string mPower; //end of values for security cam

		int mBrightness = 0; //start of values for smart light
		std::string mColour; 
		const int brightnessIndex = 6;
		const int colourIndex = 7;//end of values for smart light

		int mVolume; //values for smart speaker
		const int volumeIndex = 6;

		float mTargetTemp; //values for thermostat
		const int targetTempIndex = 6;

		while (std::getline(lineSeperation, value, ',')) //stores line in a vector so a for loop can be used to iterate through (as some lines may have more values dependent on device)
		{
			line.push_back(value);
		}
		
		if (line.size() != 6 && line.size() != 7 && line.size() != 8) //if number of attributes is not in expected range
		{
			errorCounter++; //increment error counter
		}
		else
		{
			mType = line[typeIndex]; //start of setting common variables to input
			mId = std::stoi(line[idIndex]);
			mName = line[nameIndex];
			mManufacturer = line[manufacturerIndex];
			mRoom = line[roomIndex];
			mStatus = (line[statusIndex] == "1"); //end

			if (mType == "Security Camera") 
			{
				mQuality = line[qualityIndex]; //add extra values
				mPower = line[powerIndex];
				std::shared_ptr<CSecurityCam> tempCam = std::make_shared<CSecurityCam>(mId, mName, mType, mManufacturer, mRoom, mStatus, mQuality, mPower); //create instance of security cam with input values
				deviceNode->devices.push_back(tempCam); //pushes back onto devices vector
			}
			else if (mType == "Smart Light") 
			{
				mBrightness = std::stoi(line[brightnessIndex]); //add extra values
				mColour = line[colourIndex];
				std::shared_ptr<CSmartLight> tempLight = std::make_shared<CSmartLight>(mId, mName, mType, mManufacturer, mRoom, mStatus, mBrightness, mColour); //create instance of smart light with input values
				deviceNode->devices.push_back(tempLight); //pushes back onto device vector
			}
			else if (mType == "Smart Speaker")
			{
				mVolume = std::stoi(line[volumeIndex]); //add extra value
				std::shared_ptr<CSmartSpeaker> tempSpeaker = std::make_shared<CSmartSpeaker>(mId, mName, mType, mManufacturer, mRoom, mStatus, mVolume); //create instance of smart speaker with input values
				deviceNode->devices.push_back(tempSpeaker); //pushes back onto devices vector
			}
			else if (mType == "Thermostat")
			{
				mTargetTemp = std::stof(line[targetTempIndex]); //add extra value
				std::shared_ptr<CThermostat> tempThermostat = std::make_shared<CThermostat>(mId, mName, mType, mManufacturer, mRoom, mStatus, mTargetTemp); //create instance of thermostat with input values
				deviceNode->devices.push_back(tempThermostat); //pushes back onto devices vector
			}
			else //if no device type is found
			{
				errorCounter++; //increment error counter
			}
		}

		if (errorCounter > 0)
		{
			std::cout << errorCounter << "devices could not be read from save data\n\n"; //if any errors occur output how many
		}
	}
}

void progManager::navMain()
{
	initialiseTree(); //initialise the tree with its nodes before loop starts
	while (isRunning)
	{
 		displayPage(mRoot->pageName, mIndex, mRoot); //displays the information stored within the current note
		userInput(mIndex); //waits for input from the user
		system("cls"); //clears the page so that it can be refreshed with new information based on user input
	}
	saveData();
}

progManager::~progManager()
{
	mRoot->children.clear(); 
	/*due to the tree structure of the program and since mRoot is always set back to main menu before the program is exited,
	calling clear() here creates a cascade where the shared_ptr reference count is decreased to 0 for each type, where they then
	call the automatic memory cleanup defined in shared_ptr, meaning there are no dangling pointers*/
}




void progManager::initialiseProgram() //initialising program, present so that features can be expanded in here in future
{
	navMain();
}

void progManager::initialiseTree()
{
	mRoot = std::make_shared<Node>(); //creation of the base main menu node
	mRoot->setPageName("SMART HOME MANAGER");
	mMainMenu = mRoot; //creating an anchor back to the main menu

	//first layer
	std::shared_ptr<Node> tempDeviceNode = std::make_shared<CDeviceNode>(); //creation of a device node
	tempDeviceNode->setPageName("View Devices");

	std::shared_ptr<Node> tempAddDeviceNode = std::make_shared<CAddDevice>(); //creation of an add device node
	tempAddDeviceNode->setPageName("Add Device");

	std::shared_ptr<Node> tempRoomManager = std::make_shared<CRoomManager>(); //creation of a room manager node
	tempRoomManager->setPageName("Room Manager");

	std::shared_ptr<Node> tempSearchNode = std::make_shared<CSearchNode>(); //creation of a search node
	tempSearchNode->setPageName("Search For Device");

	mRoot->children.push_back(tempDeviceNode); //pushing all new nodes back onto the main menu node's children
	mRoot->children.push_back(tempAddDeviceNode);
	mRoot->children.push_back(tempRoomManager);
	mRoot->children.push_back(tempSearchNode);

	//second layer


	readInData(); //reads in devices from the devices.csv file

	//third layer
	std::shared_ptr<Node> deviceInfo = std::make_shared<CDeviceInformation>(); //creation of a deviceInfo node
	std::shared_ptr<CDeviceNode> deviceNode = std::dynamic_pointer_cast<CDeviceNode>(mRoot->children[0]); //casting the deviceNode so that the deviceInfo node can be pushed back
	deviceNode->children.push_back(deviceInfo);

	std::cout << "PLEASE READ README FILE BEFORE INTERACTING WITH PROGRAM\n\n";
	system("pause");
	system("cls");
	
}
