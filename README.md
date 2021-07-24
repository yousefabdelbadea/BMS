# BMS
Graduation_Project
this repository is for Battery mangemet system graduatin project that consists of 6 modules and infomation about cells can be seen via a mobile app and stores historical data in a we server:
	1- data acquisition module	: reads voltage and current and temperature  from the cells
	2- thermal management module	: reads temprature and cools cells if it's high  and displays warnings if stays high and can't be cooled
	3- charge cotrol module		: decide if the baranch either charges , discharge or both
	4- cell balancing module	: try to make all branches have similar amount of charge(charged/ discharged evenly) by calculating state of charge for each cell
	5- battery backup module 	: if there's a fault in one of our 6 original batteries it's removed electriacally and replaced with a spare battery and maintainance crew are notified to fix it
	6- communication module		: sends data to mobile app by using bluetooh low energy (BLE)
the mobile app : TBD
the web server : TBD

