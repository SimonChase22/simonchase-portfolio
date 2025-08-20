#pragma once
#include "stdafx.h"
#include <conio.h>
#include <fstream>
#include <sstream>
#include "devices.h"
#include "Node.h"
#include "CDeviceNode.h"
#include "CDeviceInformation.h"
#include "CAddDevice.h"
#include "CRoomManager.h"
#include "CSearchNode.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define BACKSPACE '\b'

//This is the manager class, and will act as the point of call for most-all of the program

//




class progManager
{
private:
	int mIndex; //the index of the currently highlighted option, default 0 
	int kAscii; //stores the ascii value of a pressed key
	bool isRunning;
	bool searchActive;
	

	std::shared_ptr<Node> mRoot; //The root, which will change as the tree is traversed
	std::shared_ptr<Node> mMainMenu; //This will act as an anchor to bring the user back to the main menu when needed, by storing the memory address of the first root created, which is why it is shared not unique
public:
	progManager();
	void initialiseProgram();
	void initialiseTree();

	void displayPage(std::string title, int mIndex, std::shared_ptr<Node> root); //prints the page, using the name of the parent as the title and using name values of the children of the current tree node as the options
	void outputDeviceInfo(std::shared_ptr<CDevice> device);
	void userInput(int inputIndex); //takes the user input, and modifies information so that page can refresh with new information

	void saveData();
	void readInData();

	void navMain();

	~progManager();
	
};

