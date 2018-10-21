# RG044-drincpp
drincpp


-Drincpp is a drinking simulation written in c++

-You wake up inside an empty tavern with no memory of how you got there, and no way to leave. There is only one thing to do - pick up your tankard and drink as much beer as you can!

controls:

	w - move forward

	s - move backward
	
	a - move left 
	
	d - move right
	
	mouse - look around
	
	f - interact

	SPACE - get up

	esc - quit


Instructions:

To compile the program, type 'make' in terminal. To run it, type './main'

Walktrough:

When the program loads, player begins on the floor, unable to move. To be able to move, player must press 'SPACE' key and get up. After he gets up, the player can move to the tankard nearby, and press 'f' key to pick it up. To drink one of 3 types of beer, the player needs to put the tankard on the slot in the tap machine (by pressing 'f' key when he is in front of the machine), and pour the beer by pulling the lever (also 'f' key). When tankard is full, player can drink the beer(by pressing 'f' key again, this action puts tankard in players inventory). Bar door can be opened and closed by using the 'f' key when standing in front of the door. Tankard contains 1l of beer, and every beer increases players blood-alcohol level. Drinking enough beer in short period of time will result in a blackout and the game resets. Enjoy :)