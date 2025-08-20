#include "CSmartLight.h"

CSmartLight::CSmartLight()
{
	mBrightness = -1;
	mColourType = "UNKNOWN";
	chosenInteraction = 0;
}

CSmartLight::CSmartLight(int id, std::string name, std::string type, std::string manufacturer, std::string room, bool status, int brightness, std::string colour)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = status;
	mBrightness = brightness;
	mColourType = colour;
}

CSmartLight::CSmartLight(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mBrightness = 50; //default brightness should be 50, not 0 as otherwise they wouldn't know the light was on
	mColourType = "White";
}

void CSmartLight::setData(int id, std::string name, std::string type, std::string manufacturer, std::string room)
{
	mId = id;
	mName = name;
	mType = type;
	mManufacturer = manufacturer;
	mRoom = room;
	mStatus = false;
	mBrightness = 50; //default brightness should be 50, not 0 as otherwise they wouldn't know the light was on
	mColourType = "White";


}

CSmartLight::CSmartLight(CSmartLight& original, int newId) //copy constructor used in copy room function
{
	mId = newId;
	mName = (original.mName + "_copy");
	mType = original.mType;
	mManufacturer = original.mManufacturer;
	mRoom = (original.mRoom + "_copy");
	mStatus = false;
	mBrightness = original.mBrightness;
	mColourType = original.mColourType;
}

void CSmartLight::interactionUserInput(int indexInput, std::vector<std::string> settingOptions, std::vector<std::string> colourOptions)
{
	const int selectingSetting = 0;
	const int selectingBrightness = 1; //these three consts are used for changing the keys the user is able to use based on the interaction
	const int selectingColour = 2;
	const int doneSelecting = 3; //this const is for breaking out of the external while loop
	kAscii = 0;
	bool keyPressed = false;

	if (chosenInteraction == selectingSetting)
	{
		while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
		{
			switch ((kAscii = _getch())) //waits for user input
			{
			case KEY_UP:
				mIndex--;

				if (mIndex < 0) //if below lower range
				{
					mIndex = (settingOptions.size() - 1); //set to higher range
				}
				keyPressed = !keyPressed;
				break;



			case KEY_DOWN:
				mIndex++;

				if (mIndex > (settingOptions.size()-1)) //if above higher range
				{
					mIndex = 0; //set to lower range
				}
				keyPressed = !keyPressed;
				break;

			case SPACE:

				if (mIndex == 0) //the corresponding menu index for the brightness option
				{
					chosenInteraction = selectingBrightness;
				}
				else if (mIndex == 1)
				{
					chosenInteraction = selectingColour;
					mIndex = 0; //resets back to start for next page
				}
				keyPressed = !keyPressed;
				break;
			}
		}
	}
	else if (chosenInteraction == selectingBrightness)
	{
		while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
		{
			switch ((kAscii = _getch())) //waits for user input
			{
			case KEY_LEFT:
				if (mBrightness > 0) //if above lower range
				{
					mBrightness--; //decrement
				}
				keyPressed = !keyPressed;
				break;


			case KEY_RIGHT:
				if (mBrightness < 100) //if below higher range
				{
					mBrightness++; //increment
				}
				keyPressed = !keyPressed;
				break;


			case SPACE:
				chosenInteraction = doneSelecting; //once confirmed exit program
				
				keyPressed = !keyPressed;
				break;
			}
		}
	}
	else if (chosenInteraction == selectingColour)
	{
		while (!keyPressed) //nested while loop is necessary otherwise getch skips every other input
		{
			switch ((kAscii = _getch())) //waits for user input
			{
			case KEY_UP:
				mIndex--;
				if (mIndex < 0) //if below lower range
				{
					mIndex = (colourOptions.size() - 1); //set to higher range
				}
				
				keyPressed = !keyPressed;
				break;



			case KEY_DOWN:
				mIndex++;
				if (mIndex > (colourOptions.size() - 1)) //if above higher range
				{
					mIndex = 0; //set to lower range
				}
			
				keyPressed = !keyPressed;
				break;

			case SPACE:
				mColourType = colourOptions[mIndex];
				chosenInteraction = doneSelecting; //once confirmed exit interaction event
				
				keyPressed = !keyPressed;
				break;
			}
		}
	}
}

void CSmartLight::interactionEvent()
{
	system("cls");
	mIndex = 0;
	chosenInteraction = 0; //0 for default, 1 for brightness, 2 for colour
	std::vector<std::string> optionalSettings = { "1. Brightness", "2. Colour"}; // used for presenting menu to the user
	std::vector<std::string> colourSettings = { "Warm White", "Cool White", "RGB" };
	
	if (mStatus == false) //if powered off request user to power on
	{
		std::cout << mName << " IS CURRENTLY POWERED OFF, PLEASE POWER IT ON BEFORE INTERACTION\n\n";
		chosenInteraction = 4; //moves user to the end
		system("pause");
		system("cls");
	}
	while (chosenInteraction == 0) //outputs first menu to select value to modify
	{
		std::cout << "USE THE UP AND DOWN ARROWS TO SELECT A SETTING TO CHANGE\n\n";
		for (int i = 0; i < optionalSettings.size(); i++)
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << optionalSettings[i] << "\033[0m\n";

			}
			else
			{
				std::cout << optionalSettings[i];

				std::cout << "\033[0m\n"; //resets colour back to default
			}
		}
		std::cout << "\nPRESS SPACE TO CONFIRM SETTING";
		interactionUserInput(mIndex, optionalSettings, colourSettings);
		system("cls");
	}
	while (chosenInteraction == 1) //allows user to interact to change brightness
	{
		std::cout << "USE THE LEFT AND RIGHT ARROWS TO CHANGE BRIGHTNESS\n\n";
		std::cout << "[-]   " << mBrightness << "   [+]\n\n";
		std::cout << "PRESS SPACE TO CONFIRM BRIGHTNESS";
		interactionUserInput(mIndex, optionalSettings, colourSettings);
		system("cls");
	}
	while (chosenInteraction == 2) //allows user to interact to change colour
	{
		std::cout << "USE THE UP AND DOWN ARROWS TO SELECT A COLOUR SETTING\n\n";
		for (int i = 0; i < colourSettings.size(); i++)
		{
			if (i == mIndex) //if this index is the one currently highlighted by the user, change it's colour to green
			{
				std::cout << "\033[92m" << colourSettings[i] << "\033[0m\n";

			}
			else
			{
				std::cout << colourSettings[i];

				std::cout << "\033[0m\n"; //resets colour back to default
			}
		}
		std::cout << "PRESS SPACE TO CONFIRM CHOICE\n\n";
		interactionUserInput(mIndex, optionalSettings, colourSettings);
		system("cls");
	}
}

std::vector<std::string> CSmartLight::menu()
{
	std::shared_ptr<std::vector<std::string>> outputVector;
	outputVector = std::make_shared<std::vector<std::string>>();

	*(outputVector) = CDevice::menu(); //calls base class function

	outputVector->push_back("Brightness: " + std::to_string(mBrightness)); //adds unique values
	outputVector->push_back("Colour Type: " + mColourType);

	addMenuFunctions(outputVector); //adds menu buttons
	return *(outputVector);
}

std::string CSmartLight::outputData()
{
	std::string output = CDevice::outputData(); //calls base class function for common values
	output += ",";
	output += std::to_string(mBrightness); //adds unique values
	output += ",";
	output += mColourType;
	return output;
}
