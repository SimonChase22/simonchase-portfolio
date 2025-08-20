#include "CDevice.h"


CDevice::CDevice() //used to debug improper initialisation
{
	mId = -1;
	mName = "UNKNOWN";
	mType = "UNKNOWN";
	mManufacturer = "UNKNOWN";
	mRoom = "UNKNOWN";
	mStatus = false;
	chosenEditIndex = -1; //used in information editing
}

CDevice::CDevice(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false; //all devices off by default
}

CDevice::CDevice(CDevice& original, int newId)//copy constructor
{
	mId = newId;
	mName = (original.mName + "_copy");
	mType = original.mType;
	mManufacturer = original.mManufacturer;
	mRoom = (original.mRoom + "_copy");
	mStatus = false;
}

void CDevice::setData(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;

}

int CDevice::getId()
{
	return mId;
}

std::string CDevice::getName()
{
	return mName;
}

std::string CDevice::getType()
{
	return mType;
}

std::string CDevice::getManufacturer()
{
	return mManufacturer;
}

std::string CDevice::getRoom()
{
	return mRoom;
}

bool CDevice::getStatus()
{
	return mStatus;
}

void CDevice::setId(int id)
{
	mId = id;
}

void CDevice::setName(std::string name)
{
	mName = name;
}

void CDevice::setType(std::string type)
{
	mType = type;
}

void CDevice::setManufacturer(std::string manufacturer)
{
	mManufacturer = manufacturer;
}

void CDevice::setRoom(int room)
{
	mRoom = room;
}

void CDevice::setStatus(bool status)
{
	mStatus = status;
}



void CDevice::interactionEvent() //used to debug to ensure overriding is successful in derived classes
{
	std::cout << "THIS IS THE DEFAULT INTERACTION";
}

void CDevice::editDeviceUserInput(std::vector<std::string> modifiableVariables)
{
	kAscii = 0;
	bool keyPressed = false;
	while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_UP:
			mIndex--;

			if (mIndex < 0) //if lower than lower range
			{
				mIndex = (modifiableVariables.size() - 1); //set to higher range
			}
			keyPressed = !keyPressed;
			break;



		case KEY_DOWN:
			mIndex++;

			if (mIndex > (modifiableVariables.size() - 1)) //if higher than higher range
			{
				mIndex = 0; //set to lower range
			}
			keyPressed = !keyPressed;
			break;

		case SPACE:
			chosenEditIndex = mIndex;

			keyPressed = !keyPressed;
			break;
		}
	}
}

void CDevice::editDeviceInformation() //this is used in all derived classes but security cam, as they do not require any of their unique values to be edited in this manner
{
	system("cls");
	mIndex = 0;
	//Name, Manufacturer

	std::vector<std::string> modifiableVariables = { "Name", "Manufacturer", "Room", "FINISH"};
	const int unselectedIndex = -1; //used to reset chosenEditIndex if the user wishes to modify multiple variables
	const int nameIndex = 0;
	const int manufacturerIndex = 1;
	const int roomIndex = 2;
	const int finishIndex = 3;

	bool finishedEditing = false;

	while (!finishedEditing)
	{
		std::cout << "USE UP AND DOWN ARROWS TO CHOOSE INFO TO EDIT\n\n";
		for (int i = 0; i < modifiableVariables.size(); i++)
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << (i + 1) << ". " << modifiableVariables[i] << "\033[0m\n";

			}
			else
			{
				std::cout << (i + 1) << ". " << modifiableVariables[i];

				std::cout << "\033[0m\n"; //resets colour back to default
			}
		}
		std::cout << "\nPRESS SPACE TO CONFIRM\n";
		editDeviceUserInput(modifiableVariables);
		system("cls");

		if (chosenEditIndex != unselectedIndex && chosenEditIndex != finishIndex)
		{
			std::cout << "ENTER A NEW VALUE FOR " << modifiableVariables[chosenEditIndex] << ": ";

			//if else statements to store input in appropriate variables
			if (chosenEditIndex == nameIndex)
			{
				std::getline(std::cin, mName);
			}
			else if (chosenEditIndex == manufacturerIndex)
			{
				std::getline(std::cin, mManufacturer);
			}
			else if (chosenEditIndex == roomIndex)
			{
				bool validating = true;
				bool validRoom = false;
				while (validating) //input validation to make sure input is not empty or only whitespace
				{
					std::getline(std::cin, mRoom);
					//ENTER HERE
					mRoom.erase(mRoom.begin(), std::find_if(mRoom.begin(), mRoom.end(), [](unsigned char space) //code adapted from a snippet on techiedelight https://www.techiedelight.com/remove-leading-and-trailing-spaces-from-a-string-in-cpp/
						{
							return !std::isspace(space);
						}));

					if (!mRoom.empty()) //if there is at least one character that is not whitespace
					{
						validating = false;
					}
					else //if only whitespace is found
					{
						std::cout << "Invalid input, every device must be placed in a room: ";
						std::cin.clear();
					}
				}
			}
		}
		else if (chosenEditIndex == finishIndex)
		{
			finishedEditing = true;
		}
		chosenEditIndex = -1;
		system("cls");
	}
}

void CDevice::addMenuFunctions(std::shared_ptr<std::vector<std::string>> menu) //this is used to add menu functions in the derived classes, AFTER the derived class specific attributes
{
	if (mStatus) //displays turn on/off depending on current status
	{
		menu->push_back("[TURN OFF " + mName + "]");
	}
	else
	{
		menu->push_back("[TURN ON " + mName + "]");
	}
	menu->push_back("[INTERACT]");
	menu->push_back("[EDIT INFO]");
	menu->push_back("[DELETE DEVICE]");
}

std::vector<std::string> CDevice::menu() //this function outputs a vector of names of all variables the device has, and is redefined for different device types 
{
	std::shared_ptr<std::vector<std::string>> outputVector;
	outputVector = std::make_shared<std::vector<std::string>>();

	outputVector->push_back("ID: " + std::to_string(mId));
	outputVector->push_back("Name: " + mName);
	outputVector->push_back("Type: " + mType);
	outputVector->push_back("Manufacturer: " + mManufacturer);
	outputVector->push_back("Room: " + mRoom);
	if (mStatus) //outputs status depending on mStatus value
	{
		outputVector->push_back("Status: CONNECTED");
	}
	else
	{
		outputVector->push_back("Status: DISCONNECTED");
	}



	
	return *(outputVector);
}

std::string CDevice::outputData() //used in all derived classes to output common values
{
	std::string output = "";
	output += mType;
	output += ",";
	output += std::to_string(mId);
	output += ",";
	output += mName;
	output += ",";
	output += mManufacturer;
	output += ",";
	output += mRoom;
	output += ",";
	if (mStatus) //1 = true, 0 = false when read back in
	{
		output += "1";
	}
	else
	{
		output += "0";
	}
	
	return output;
}




