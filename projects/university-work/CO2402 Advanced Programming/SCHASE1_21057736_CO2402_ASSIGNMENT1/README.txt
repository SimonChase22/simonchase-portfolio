CO2402 ASSIGNMENT - SMART HOME MANAGER APPLICATION
SIMON CHASE, SCHASE1, 21057736

This solution is a proof of concept smart home manager application, allowing the user to view devices, add devices, filter by room, search for devices and interact with devices

There is an accompanying video contained within the file upload that demonstrates the program and covers requirements that have been met that could not be illustrated in the report

This solution also comes preloaded with one device for each type (Security Camera, Smart Light, Smart Speaker and Thermostat) that are saved within the devices.csv file

This solution implements key inputs for navigation, your current menu selection is highlighted in green:
-You may use UP and DOWN arrows to navigate the menu
-Press SPACE to select your option
-Press BACKSPACE to return to the main menu




MARKING - To make marking easier due to the sheer amount of code within the solution, here are the files and lines where you will find code relevant to the following requirements that are not demonstrated in the video

If a requirement is not in this list it is demonstrated in the video or visible within the command interface:

MUST HAVE:
2a. CAddDevice.cpp (Lines 208-218), CRoomManager.cpp (Lines 31-55) (UNIQUE ID CHECKS)
2b. CSecurityCam.cpp (Lines 59-72), CSmartLight.cpp (Lines 184-249), CSmartSpeaker.cpp (Lines 91-115), CThermostat.cpp (Lines 90-112)
3a. CDeviceInformation.cpp (Lines 22-25)
3b. Same as 2b
4. CDeviceInformation.cpp (Entirety), progManager.cpp (Lines 148-171)
5. Same as 4


SHOULD HAVE:
1. progManager.cpp (Lines 50-93)
2. CAddDevice.cpp (Entirety)
3. CDevice.cpp (Lines 152-233), CSecurityCam.cpp (Lines 75-165)
4. CDeviceInformation (Lines 37-49)
5. CDevice.cpp (Lines 71-74), this is fed to the user via the connected/disconnected next to the device name on the menu


COULD HAVE:
1. CSearchNode.cpp (Entirety)
2. CAddDevice.cpp (Lines 208-218)
3a. CAddDevice.cpp (Lines 145-163), CDevice.cpp (Lines 201-225) Devices must be in a room, room name can be changed and it will automatically create that new room in the rooms list
3b. CRoomManager.cpp (Lines 189-250)
3c. CRoomManager.cpp (Lines 23-29)
3e. Same as 3a, devices required to be placed in a room by the user
4. CRoomManager.cpp (Lines 31-96), there are also copy constructors in all relevant derived device classes
5. progManager.cpp (Lines 397-511)


I believe all requirements have been met, if there are any questions please feel free to message me
