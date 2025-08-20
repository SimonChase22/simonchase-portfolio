#include "CSecurityCam.h"

CSecurityCam::CSecurityCam()
{
	mQuality = "UNKNOWN";
	mPower = "UNKNOWN";
	chosenEditIndex = -1;
}

CSecurityCam::CSecurityCam(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, std::string quality, std::string power)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = status;
	mQuality = quality;
	mPower = power;
}

CSecurityCam::CSecurityCam(int id, std::string name, std::string type, std::string manufacturer, std::string room, std::string quality, std::string power)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mQuality = quality;
	mPower = power;

}

void CSecurityCam::setData(int id, std::string name, std::string type, std::string manufacturer, std::string room, std::string quality, std::string power)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mQuality = quality;
	mPower = power;
}

CSecurityCam::CSecurityCam(CSecurityCam& original, int newId) //copy constructor for use in copy room function
{
	mId = newId;
	mName = (original.mName + "_copy");
	mType = original.mType;
	mManufacturer = original.mManufacturer;
	mRoom = (original.mRoom + "_copy");
	mStatus = false;
	mQuality = original.mQuality;
	mPower = original.mPower;
}

void CSecurityCam::interactionEvent()
{
	system("cls");
	if (mStatus == false) //if powered off prompt user to power on
	{
		std::cout << mName << " IS POWERED OFF, PLEASE POWER ON TO VIEW\n\n";
	}
	else //output interaction
	{
		std::cout << "Now viewing camera: " << mName << "\n\n";
	}
	system("pause");
	system("cls");
}


void CSecurityCam::editDeviceInformation() //this is overridden only in security cam as it is the only derived class that requires it for its additional values
{
	system("cls");
	mIndex = 0;
	//Name, Manufacturer, Quality, Power

	std::vector<std::string> modifiableVariables = { "Name", "Manufacturer", "Room", "Quality", "Power", "FINISH"};
	const int unselectedIndex = -1; //used to reset chosenEditIndex if the user wishes to modify multiple variables
	const int nameIndex = 0;
	const int manufacturerIndex = 1;
	const int roomIndex = 2;
	const int qualityIndex = 3;
	const int powerIndex = 4;
	const int finishIndex = 5;

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
			std::cout << "ENTER A NEW VALUE FOR " << modifiableVariables[chosenEditIndex] << ": "; //prompts user to input new value
			//if else statements to store input in appropriate variable
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
			else if (chosenEditIndex == qualityIndex)
			{
				std::getline(std::cin, mQuality);
			}
			else if (chosenEditIndex == powerIndex)
			{
				std::getline(std::cin, mPower);
			}
		}
		else if (chosenEditIndex == finishIndex) //if user selects finish, exit
		{
			finishedEditing = true; 
		}
		chosenEditIndex = -1; //resets for further edits
		system("cls");
	}
}

std::vector<std::string> CSecurityCam::menu()  //polymorphic, redefining original function whilst calling original to add additional functionality
{
	std::shared_ptr<std::vector<std::string>> outputVector;
	outputVector = std::make_shared<std::vector<std::string>>();
		
	*(outputVector) = CDevice::menu(); //adds the bare minimum default variables for a device by using the base class function

	outputVector->push_back("Quality: " + mQuality); //adds additional derived class variables
	outputVector->push_back("Power: " + mPower);
	addMenuFunctions(outputVector); //adds functions for editing, interacting and turning on device, defined in base class


	return *(outputVector);
}

std::string CSecurityCam::outputData()
{
	std::string output = CDevice::outputData(); //calls base class function
	output += ",";
	output += mQuality; //adds additional values
	output += ",";
	output += mPower;
	return output;
}


