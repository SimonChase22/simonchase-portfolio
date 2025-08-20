#include "CAddDevice.h"

CAddDevice::CAddDevice()
{	
	data = 3;
	mIndex = 0;
	step = 1;

	mDeviceTypes.push_back("Security Camera"); //pushes back all currently supported device types
	mDeviceTypes.push_back("Smart Light");
	mDeviceTypes.push_back("Smart Speaker");
	mDeviceTypes.push_back("Thermostat");
}

void CAddDevice::modifiedUserInput(int inputIndex) //takes the user input, and modifies information so that page can refresh with new information
{
	kAscii = 0;
	const int mainMenuStep = 4; //used if the user does backspace to exit back to main
	bool keyPressed = false;
	while (!keyPressed) //a nested while loop is necessary here, without it _getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_UP:
			mIndex--;
			if (mIndex < 0) //if lower than lower range
			{
				mIndex = mDeviceTypes.size() - 1; //set to higher range
			}
			keyPressed = !keyPressed;
			break;



		case KEY_DOWN:
			mIndex++;
			if (mIndex > (mDeviceTypes.size() - 1)) //if higher than higher range
			{
				mIndex = 0; //set to lower range
			}

			keyPressed = !keyPressed;
			break;



		case SPACE:
			step++; //moves user along
			selectedDevice = mDeviceTypes[mIndex]; //sets device

			keyPressed = !keyPressed;
			break;


		case BACKSPACE:
			step = mainMenuStep; //breaks user from addDevice
			keyPressed = !keyPressed;
		}
	}
}


void CAddDevice::addDevice(std::shared_ptr<CDeviceNode> devicesNode)
{
	step = 1; //used to move user linearly
	const int mainMenuStep = 4; //used if the user does backspace to exit back to main

	while (step == 1) //selecting device type step
	{
		title = "Select Device";
		std::string border = "========"; //start with 8 equals to add length on either side for styling
		for (int i = 0; i < title.length(); i++)
		{
			border += "=";
		}
		std::cout << border << "\n    " << title << "    \n" << border << "\n"; //prints title with borders


		for (int i = 0; i < mDeviceTypes.size(); i++) //outputs all currently supported device types
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << mDeviceTypes[i] << "\033[0m\n";

			}
			else
			{
				std::cout << mDeviceTypes[i];

				std::cout << "\033[0m\n"; //resets colour back to default
			}
		}
		modifiedUserInput(mIndex);
		system("cls");
	}


	int selectedId = 0;
	bool validatingId = true;
	std::string selectedName;
	std::string selectedManufacturer;
	std::string selectedRoom;

	
	if (step != mainMenuStep) //if the user has not exited
	{

		title = "Enter Parameters";
		std::string border = "========"; //start with 8 equals to add length on either side for styling
		for (int i = 0; i < title.length(); i++)
		{
			border += "=";
		}
		std::cout << border << "\n    " << title << "    \n" << border << "\n"; //prints title with borders

		std::cout << "Selected Device: " << selectedDevice << "\n\n";
		std::cout << "Enter ID: ";
		while (validatingId) 
		{
			if (!(std::cin >> selectedId) || selectedId < 1 || selectedId > 2147483646) //input validation, while input is not an integer, or outside of range 1 to 2147483646 (max value an int can hold) 
			{
				std::cout << "\nInvalid ID. Please enter ID in the range 1 to 2147483646: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (!checkId(devicesNode, selectedId)) //if the id already exists
			{
				std::cout << "\nID already exists, please enter another: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				validatingId = false;
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //used to ignore the empty line that is left when cin is used for taking the ID int
		std::cout << "\nEnter Name: ";
		std::getline(std::cin, selectedName);
		std::cout << "\nEnter Manufacturer: ";
		std::getline(std::cin, selectedManufacturer);

		std::cout << "\nEnter Selected Room: ";
		bool validating = true;
		while (validating) //input validation to make sure input is not empty or only whitespace
		{
			std::getline(std::cin, selectedRoom);
			//ENTER HERE
			selectedRoom.erase(selectedRoom.begin(), std::find_if(selectedRoom.begin(), selectedRoom.end(), [](unsigned char space) //code adapted from a snippet on techiedelight https://www.techiedelight.com/remove-leading-and-trailing-spaces-from-a-string-in-cpp/
				{
					return !std::isspace(space);
				}));

			if (!selectedRoom.empty()) //if there is at least one character that is not whitespace
			{
				validating = false;
			}
			else //if only whitespace is found
			{
				std::cout << "Invalid input, every device must be placed in a room: ";
				std::cin.clear();
			}
		}


		//if else statements to get unique values before pushing back
		if (selectedDevice == "Security Camera")
		{
			std::string selectedQuality;
			std::cout << "\nEnter Selected Quality: ";
			std::getline(std::cin, selectedQuality);

			std::string selectedPower;
			std::cout << "\nEnter Selected Power: "; 
			std::getline(std::cin, selectedPower);

			std::shared_ptr<CSecurityCam> newDevice = std::make_shared<CSecurityCam>(); //creates instance of security cam
			newDevice->setData(selectedId, selectedName, selectedDevice, selectedManufacturer, selectedRoom, selectedQuality, selectedPower);

			devicesNode->devices.push_back(newDevice); //pushes back
		}
		else if (selectedDevice == "Smart Light")
		{
			std::shared_ptr<CSmartLight> newDevice = std::make_shared<CSmartLight>(); //creates instance of smart light
			newDevice->setData(selectedId, selectedName, selectedDevice, selectedManufacturer, selectedRoom); //this requires no extra input, as colour and brightness are default and changed later

			devicesNode->devices.push_back(newDevice); //pushes back
		}
		else if (selectedDevice == "Smart Speaker")
		{
			std::shared_ptr<CSmartSpeaker> newDevice = std::make_shared<CSmartSpeaker>(); //creates instance of smart speaker
			newDevice->setData(selectedId, selectedName, selectedDevice, selectedManufacturer, selectedRoom); //this requires no extra input, as volume is set to 50 by default

			devicesNode->devices.push_back(newDevice); //pushes back
		}
		else if (selectedDevice == "Thermostat")
		{
			std::shared_ptr<CThermostat> newDevice = std::make_shared<CThermostat>(); //creates instance of thermostat
			newDevice->setData(selectedId, selectedName, selectedDevice, selectedManufacturer, selectedRoom); //this requires no extra input, as target temperature is set to 20 by default

			devicesNode->devices.push_back(newDevice); //pushes back
		}
	}
	std::cout << "Press SPACE to return to Main Menu...";
	return;
}

bool CAddDevice::checkId(std::shared_ptr<CDeviceNode> devicesNode, int id)
{
	for (int i = 0; i < devicesNode->devices.size(); i++) //checks all existing devices to see if entered id already exists
	{
		if (devicesNode->devices[i]->getId() == id)
		{
			return false;
		}
	}
	return true;
}




