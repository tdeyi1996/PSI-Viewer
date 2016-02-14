#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;


// PSI readings retrieved from http://www.nea.gov.sg/anti-pollution-radiation-protection/air-pollution-control/psi/historical-psi-readings/year/2014/month/6/day/23
int PSI_Data[5][24]{
	{ 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 62, 62, 62, 62, 62, 61, 60, 60, 60, 60, 60 }, // 0. North
	{ 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 58, 58, 57, 57, 57, 58 }, // 1. South
	{ 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 61 }, // 2. East
	{ 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 61, 61, 61, 61, 60, 60, 59, 58, 59, 59 }, // 3. West
	{ 62, 62, 62, 62, 62, 61, 62, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 59, 58, 58, 58, 58, 59 }  // 4. Central
};

void GetReadings() {
	// get region
	int region = 0;
	cout << "Regions" << endl;
	cout << "=====================================================" << endl;
	cout << "1. North" << endl;
	cout << "2. South" << endl;
	cout << "3. East" << endl;
	cout << "4. West" << endl;
	cout << "5. Central" << endl;
	cout << "=====================================================" << endl;
	cout << "Please select your region: ";
	cin >> region;
	system("cls");

	// get time slot
	int time = 0;
	cout << "Time slot" << endl;
	cout << "=====================================================" << endl;
	for (int i = 1; i <= 24; i++) {
		if (i <= 11) {
			cout << i << ". " << i << " am" << endl;
		}
		else if (i == 12) {
			cout << i << ". " << i << " pm" << endl;
		}
		else if (i >= 13 && i <= 23) {
			cout << i << ". " << i-12 << " pm" << endl;
		}
		else if (i == 24) {
			cout << i << ". " << i-12 << " am" << endl;
		}
	}
	cout << "=====================================================" << endl;
	cout << "Please select your time slot: ";
	cin >> time;
	system("cls");

	// process user input & display output
	int psiReading = PSI_Data[region-1][time-1];
	cout << "Results" << endl;
	cout << "=====================================================" << endl;

	// display output region
	string regionName = "";
	switch (region - 1) {
		case 0:
			regionName = "North";
			break;
		case 1:
			regionName = "South";
			break;
		case 2:
			regionName = "East";
			break;
		case 3:
			regionName = "West";
			break;
		case 4:
			regionName = "Central";
			break;
	}
	cout << "Selected Region: " << regionName << endl;

	// display output time slot
	if (time-1 <= 11) {
		cout << "Selected Time slot: " << time << " am" << endl;
	}
	else if (time - 1 == 12) {
		cout << "Selected Time slot: " << time << " pm" << endl;
	}
	else if (time - 1 >= 13 && time - 1 <= 23) {
		cout << "Selected Time slot: " << time-12 << " pm" << endl;
	}
	else if (time - 1 == 24) {
		cout << "Selected Time slot: " << time-12 << " am" << endl;
	}

	// display output PSI
	cout << "PSI reading: " << psiReading << endl;

	// display output descriptor
	string descriptor = "NIL";
	if (psiReading >= 0 && psiReading <= 50) {
		descriptor = "Good";
	}
	else if (psiReading >= 51 && psiReading <= 100) {
		descriptor = "Moderate";
	}
	if (psiReading >= 101 && psiReading <= 200) {
		descriptor = "Unhealthy";
	}
	if (psiReading >= 201 && psiReading <= 300) {
		descriptor = "Very Unhealthy";
	}
	if (psiReading > 300) {
		descriptor = "Hazardous";
	}
	cout << "Descriptor: " << descriptor << endl;
	cout << "=====================================================" << endl;
}

void GetThreeHourReading() {
	// get region
	int region = 0;
	cout << "Regions" << endl;
	cout << "=====================================================" << endl;
	cout << "1. North" << endl;
	cout << "2. South" << endl;
	cout << "3. East" << endl;
	cout << "4. West" << endl;
	cout << "5. Central" << endl;
	cout << "=====================================================" << endl;
	cout << "Please select your region: ";
	cin >> region;
	system("cls");

	// get time slot
	int time = 0;
	cout << "Time slot" << endl;
	cout << "=====================================================" << endl;
	cout << "1. 3 am" << endl;
	cout << "2. 6 am" << endl;
	cout << "3. 9 am" << endl;
	cout << "4. 12 pm" << endl;
	cout << "5. 3 pm" << endl;
	cout << "6. 6 pm" << endl;
	cout << "7. 9 pm" << endl;
	cout << "8. 12 am" << endl;
	cout << "=====================================================" << endl;
	cout << "Please select your time slot: ";
	cin >> time;
	system("cls");

	// calculate three hourly average PSI and display output
	int averagePSI = (PSI_Data[region - 1][time * 3 - 3] + PSI_Data[region - 1][time * 3 - 2] + PSI_Data[region - 1][time * 3 - 1]) / 3;

	cout << "Results" << endl;
	cout << "=====================================================" << endl;
	cout << "3-hourly average PSI: " << averagePSI << endl;
	cout << "=====================================================" << endl;
}

void UnhealthiestRegion() {
	int regionAverage[5];

	// loop through region
	for (int i = 0; i < 5; i++) {
		int total = 0;
		// loop through time slot
		for (int j = 0; j < 24; j++) {
			total += PSI_Data[i][j];
		}
		regionAverage[i] = total / 24;
	}

	// compare 24hr PSI between regions
	int largestIndex = 0;
	for (int i = 0; i < 5; i++) {
		if (regionAverage[largestIndex] < regionAverage[i]) {
			largestIndex = i;
		}
	}
	int highestPSI = regionAverage[largestIndex];

	// display unhealtiest region(s) with their PSI reading
	cout << "Results" << endl;
	cout << "=====================================================" << endl;
	cout << "Unhealthiest Region(s): " << endl;
	for (int i = 0; i < 5; i++) {
		if (regionAverage[i] == highestPSI) {
			switch (i) {
			case 0:
				cout << "- North" << endl;
				break;
			case 1:
				cout << "- South" << endl;
				break;
			case 2:
				cout << "- East" << endl;
				break;
			case 3:
				cout << "- West" << endl;
				break;
			case 4:
				cout << "- Central" << endl;
				break;
			}
		}
	}
	cout << endl;
	cout << "PSI reading: " << highestPSI << endl;
	cout << "=====================================================" << endl;
}

void HighestPSIReadingByTime() {
	// get time slot
	int time = 0;
	cout << "Time slot" << endl;
	cout << "=====================================================" << endl;
	for (int i = 1; i <= 24; i++) {
		if (i <= 11) {
			cout << i << ". " << i << " am" << endl;
		}
		else if (i == 12) {
			cout << i << ". " << i << " pm" << endl;
		}
		else if (i >= 13 && i <= 23) {
			cout << i << ". " << i - 12 << " pm" << endl;
		}
		else if (i == 24) {
			cout << i << ". " << i - 12 << " am" << endl;
		}
	}
	cout << "=====================================================" << endl;
	cout << "Please select your time slot: ";
	cin >> time;
	system("cls");

	// compare PSI reading between regions
	int largestIndex = 0;
	for (int i = 0; i < 5; i++) {
		if (PSI_Data[largestIndex][time - 1] < PSI_Data[i][time - 1]) {
			largestIndex = i;
		}
	}
	int highestPSI = PSI_Data[largestIndex][time - 1];

	// display each region's 24 hour average PSI
	cout << "Results" << endl;
	cout << "=====================================================" << endl;
	cout << "Unhealthiest Region(s): " << endl;
	for (int i = 0; i < 5; i++) {
		if (PSI_Data[i][time - 1] == highestPSI) {
			switch (i) {
			case 0:
				cout << "- North" << endl;
				break;
			case 1:
				cout << "- South" << endl;
				break;
			case 2:
				cout << "- East" << endl;
				break;
			case 3:
				cout << "- West" << endl;
				break;
			case 4:
				cout << "- Central" << endl;
				break;
			}
		}
	}
	cout << endl;
	cout << "PSI reading: " << highestPSI << endl;
	cout << "=====================================================" << endl;
}

void PSIReadingAboveModerate() {
	cout << "Results" << endl;
	cout << "=====================================================" << endl;
	// loop for PSI reading > 100 throughout the data table
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 24; j++) {
			// check to see if PSI reading is above 'moderate' 
			if (PSI_Data[i][j] > 100) {
				// display time
				if (j + 1 <= 11) {
					cout << "- " << j + 1 << " am at ";
				}
				else if (j + 1 == 12) {
					cout << "- " << j + 1 << " pm at ";
				}
				else if (j + 1 >= 13 && j + 1 <= 23) {
					cout << "- " << j - 12 + 1 << " pm at ";
				}
				else if (j + 1 == 24) {
					cout << "- " << j - 12 + 1<< " am at ";
				}

				// display region
				switch (i) {
				case 0:
					cout << "North" << endl;
					break;
				case 1:
					cout << "South" << endl;
					break;
				case 2:
					cout << "East" << endl;
					break;
				case 3:
					cout << "West" << endl;
					break;
				case 4:
					cout << "Central" << endl;
					break;
				}
			}
		}
	}
}

void ChangePSIData() {
	// get time slot
	int time = 0;
	cout << "Time slot" << endl;
	cout << "=====================================================" << endl;
	for (int i = 1; i <= 24; i++) {
		if (i <= 11) {
			cout << i << ". " << i << " am" << endl;
		}
		else if (i == 12) {
			cout << i << ". " << i << " pm" << endl;
		}
		else if (i >= 13 && i <= 23) {
			cout << i << ". " << i - 12 << " pm" << endl;
		}
		else if (i == 24) {
			cout << i << ". " << i - 12 << " am" << endl;
		}
	}
	cout << "=====================================================" << endl;
	cout << "Please select your time slot: ";
	cin >> time;
	system("cls");

	// set North data
	cout << "North region" << endl;
	cout << "=====================================================" << endl;
	cout << "Previous value: " << PSI_Data[0][time-1] << endl;
	cout << "New value: ";

	int northValue = 0;
	cin >> northValue;
	PSI_Data[0][time - 1] = northValue;
	system("cls");

	// set South data
	cout << "South region" << endl;
	cout << "=====================================================" << endl;
	cout << "Previous value: " << PSI_Data[1][time - 1] << endl;
	cout << "New value: ";

	int southValue = 0;
	cin >> southValue;
	PSI_Data[1][time - 1] = southValue;
	system("cls");

	// set East data
	cout << "East region" << endl;
	cout << "=====================================================" << endl;
	cout << "Previous value: " << PSI_Data[2][time - 1] << endl;
	cout << "New value: ";

	int eastValue = 0;
	cin >> eastValue;
	PSI_Data[2][time - 1] = eastValue;
	system("cls");

	// set West data
	cout << "West region" << endl;
	cout << "=====================================================" << endl;
	cout << "Previous value: " << PSI_Data[3][time - 1] << endl;
	cout << "New value: ";

	int westValue = 0;
	cin >> westValue;
	PSI_Data[3][time - 1] = westValue;
	system("cls");

	// set Central data
	cout << "Central region" << endl;
	cout << "=====================================================" << endl;
	cout << "Previous value: " << PSI_Data[4][time - 1] << endl;
	cout << "New value: ";

	int centralValue = 0;
	cin >> centralValue;
	PSI_Data[4][time - 1] = centralValue;
}

// program entry point
int main()
{
	// program main menu
	bool isExit = false;
	while (!isExit)
	{
		system("cls");
		cout << "PSI Viewer" << endl;
		cout << "=====================================================" << endl;
		cout << "1. PSI readings with health advisory descriptor" << endl;
		cout << "2. 3-hourly average PSI reading" << endl;
		cout << "3. Unhealthiest regional average PSI reading and region" << endl;
		cout << "4. Highest PSI reading for selected time slot" << endl;
		cout << "5. Time period and region with PSI above 'Moderate'" << endl;
		cout << "6. Change the 5 region's data for selected hour" << endl;
		cout << "7. Exit" << endl;
		cout << "=====================================================" << endl;
		cout << "Please enter your option: ";

		// retrieve user input
		int userOption = 0;
		cin >> userOption;
		system("cls");

		// process user input
		switch (userOption) {
		case 1:
			GetReadings();
			break;
		case 2:
			GetThreeHourReading();
			break;
		case 3:
			UnhealthiestRegion();
			break;
		case 4:
			HighestPSIReadingByTime();
			break;
		case 5:
			PSIReadingAboveModerate();
			break;
		case 6:
			ChangePSIData();
			break;
		case 7:
			isExit = true;
			break;
		default:
			cout << "Invalid option." << endl;
		}
		system("pause");
	}

	// exit program
	cout << "Program is exiting" << endl;
	system("pause");
	return 0;
}

