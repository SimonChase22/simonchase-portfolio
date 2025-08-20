#include "CThermostat.h"

CThermostat::CThermostat()
{
	mTargetTemp = -1;
}

CThermostat::CThermostat(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, float targetTemp)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = status;
	mTargetTemp = targetTemp;
}

CThermostat::CThermostat(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false; //devices off by default
	mTargetTemp = 20;


}

void CThermostat::setData(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false; //devices off by default
	mTargetTemp = 20;
}

CThermostat::CThermostat(CThermostat& original, int newId)
{
	mId = newId;
	mName = (original.mName + "_copy");
	mType = original.mType;
	mManufacturer = original.mManufacturer;
	mRoom = (original.mRoom + "_copy");
	mStatus = false;
	mTargetTemp = original.mTargetTemp;
}

void CThermostat::interactionUserInput()
{
	kAscii = 0;
	bool keyPressed = false;

	while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
	{
		switch ((kAscii = _getch())) //waits for user input
		{
		case KEY_LEFT:
			if (mTargetTemp > 1) //if above lower range
			{
				mTargetTemp -= 0.5; //minus 0.5
			}
			keyPressed = !keyPressed;
			break;


		case KEY_RIGHT:
			if (mTargetTemp < 32) //if below higher range
			{
				mTargetTemp += 0.5; //add 0.5
			}
			keyPressed = !keyPressed;
			break;


		case SPACE:
			mDoneEditing = true; //confirms edit and exits 

			keyPressed = !keyPressed;
			break;
		}
	}
}

void CThermostat::interactionEvent()
{
	mDoneEditing = false; //resets every time interaction occurs
	system("cls");

	if (mStatus == false) //if off request the device to be powered on
	{
		std::cout << mName << " IS POWERED OFF, PLEASE POWER ON TO CHANGE SETTINGS\n\n";
		system("pause");
		system("cls");
	}
	else //if on, allow user to modify target temperature
	{
		while (!mDoneEditing) //does not exit until user presses space
		{
			std::cout << "USE THE LEFT AND RIGHT ARROWS TO CHANGE TARGET TEMPERATURE\n\n";
			std::cout << "[-]   " << mTargetTemp << "   [+]\n\n";
			std::cout << "PRESS SPACE TO CONFIRM TARGET TEMPERATURE";
			interactionUserInput();
			system("cls");
		}
	}
}

std::vector<std::string> CThermostat::menu()
{
	std::shared_ptr<std::vector<std::string>> outputVector;
	outputVector = std::make_shared<std::vector<std::string>>();

	*(outputVector) = CDevice::menu(); //calls base class function for common values

	outputVector->push_back("Target Temperature: " + (std::to_string(mTargetTemp)).erase(4, 9)); //adds thermostat specific values and sets them to 1 decimal place

	addMenuFunctions(outputVector); //adds menu buttons
	return *(outputVector);
}

std::string CThermostat::outputData()
{
	std::string output = CDevice::outputData(); //calls base class function for common values
	output += ",";
	output += std::to_string(mTargetTemp); //adds thermostat specific values
	return output;
}
