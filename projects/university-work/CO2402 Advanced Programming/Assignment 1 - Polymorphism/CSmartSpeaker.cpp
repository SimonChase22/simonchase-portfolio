#include "CSmartSpeaker.h"

CSmartSpeaker::CSmartSpeaker()
{
	mVolume = -1; //set to -1 to debug improper initialisation
}

CSmartSpeaker::CSmartSpeaker(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, int volume)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = status;
	mVolume = volume;
}

CSmartSpeaker::CSmartSpeaker(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mVolume = 50; //set to 50 so to avoid confusion from user if no volume is output


}

void CSmartSpeaker::setData(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mVolume = 50;
}

CSmartSpeaker::CSmartSpeaker(CSmartSpeaker& original, int newId) //copy constructor used in copy room function
{
	mId = newId;
	mName = (original.mName + "_copy");
	mType = original.mType;
	mManufacturer = original.mManufacturer;
	mRoom = (original.mRoom + "_copy");
	mStatus = false;
	mVolume = original.mVolume;
}

void CSmartSpeaker::interactionUserInput()
{
	kAscii = 0; //resets button pressed
	bool keyPressed = false;

	while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_LEFT:
			if (mVolume > 0) //if above lower range
			{
				mVolume--; //decrement
			}
			keyPressed = !keyPressed;
			break;


		case KEY_RIGHT:
			if (mVolume < 100) //if below higher range
			{
				mVolume++; //increment
			}
			keyPressed = !keyPressed;
			break;


		case SPACE:
			std::cout << "Space\n\n";
			mDoneEditing = true; //confirm option and exit interact event

			keyPressed = !keyPressed;
			break;
		}
	}
}

void CSmartSpeaker::interactionEvent()
{
	mDoneEditing = false; //resets every time interaction event occurs
	system("cls");

	if (mStatus == false) //if powered off request user to power on
	{
		std::cout << mName << " IS POWERED OFF, PLEASE POWER ON TO CHANGE SETTINGS\n\n";
		system("pause");
		system("cls");
	}
	else
	{
		while (!mDoneEditing) //if powered on allow user to change volume
		{
			std::cout << "USE THE LEFT AND RIGHT ARROWS TO CHANGE VOLUME\n\n";
			std::cout << "[-]   " << mVolume << "   [+]\n\n";
			std::cout << "PRESS SPACE TO CONFIRM VOLUME";
			interactionUserInput();
			system("cls");
		}
	}

}

std::vector<std::string> CSmartSpeaker::menu()
{
	std::shared_ptr<std::vector<std::string>> outputVector;
	outputVector = std::make_shared<std::vector<std::string>>();

	*(outputVector) = CDevice::menu(); //calls base class for common values

	outputVector->push_back("Volume: " + std::to_string(mVolume)); //adds unique values

	addMenuFunctions(outputVector); //adds menu buttons
	return *(outputVector);
}

std::string CSmartSpeaker::outputData()
{
	std::string output = CDevice::outputData();//calls base class for common values
	output += ",";
	output += std::to_string(mVolume);//adds unique values
	return output;
}
