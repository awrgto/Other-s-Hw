# Other-s-Hw
Hw
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ComP(i) compare(flight[i].aircraftType)

struct vAircraft {
	char manufacturer[7];
	int aircraftType;
	int wing;
};

struct vSlot {
	int number;
	int maxWing;
	int nowPlane;
};

struct vFlight {
	char line[4];
	int num[5];
	int aircraftType;
	int nowSlot;
};

int compare(int type){
	int i = 0;
	static FILE *fair = NULL;
	static struct vAircraft stype[7];

	if (fair == NULL){
		fair = fopen("C:\\Users\\Hank\\Documents\\Visual Studio 2013\\Projects\\HW8\\Debug\\aircraft.txt", "r");
		if (fair == NULL){
			printf("Cannot open file aircraft.txt\n");
			exit(-21);
		}
	}
	for (int i = 0; i < 7; i++){
		fscanf(fair, "%s %d %d", &stype[i].manufacturer, &stype[i].aircraftType, &stype[i].wing);
	}
	if (type == 0)
		return 0;
	while (1){
		if (type == stype[i].aircraftType)
			return stype[i].wing;
		if (i >= 7)
			return -1;
		i++;
	}
}
int main()
{
	FILE *fflight = NULL, *ffailed = NULL, *fassigned = NULL;
	int count(0);
	struct vFlight flight[31];
	flight[30].line[0] = 'o';
	flight[30].num[0] = '0';
	flight[30].aircraftType = 0;
	flight[30].nowSlot = -1;

	ffailed = fopen("C:\\Users\\Hank\\Documents\\Visual Studio 2013\\Projects\\HW8\\Debug\\failed.txt", "w+t");
	if (ffailed == NULL){
		printf("Cannot open file falied.txt\n");
		exit(-24);
	}
	fassigned = fopen("C:\\Users\\Hank\\Documents\\Visual Studio 2013\\Projects\\HW8\\Debug\\assigned.txt", "w+t");
	if (fassigned == NULL){
		printf("Cannot open file assigned.txt\n");
		exit(-25);
	}

	fflight = fopen("C:\\Users\\Hank\\Documents\\Visual Studio 2013\\Projects\\HW8\\Debug\\flight.txt", "r");
	if (fflight == NULL){
		printf("Cannot open file flight.txt\n");
		exit(-23);
	}


	FILE *fslot = NULL;
	struct vSlot slot[24];


	fslot = fopen("C:\\Users\\Hank\\Documents\\Visual Studio 2013\\Projects\\HW8\\Debug\\slot.txt", "r");
	if (fslot == NULL){
		printf("Cannot open file slot.txt\n");
		exit(-22);
	}

	for (int i = 0; i < 24; i++){
		fscanf(fslot, "%d %d", &slot[i].number, &slot[i].maxWing);
		slot[i].nowPlane = 30;
	}

	count = 0;

	for (int i = 0; i < 30; i++){
		fscanf(fflight, "%s %s %d", &flight[i].line, &flight[i].num, &flight[i].aircraftType);
		flight[i].nowSlot = -1;
		for (int j = 0; j < 24; j++){
			if (ComP(i) <= slot[j].maxWing && ComP(slot[j].nowPlane) == 0){
				if (j <= 0){
					if (ComP(i) + ComP(slot[j + 1].nowPlane) <= 140){
						slot[j].nowPlane = i;
						flight[i].nowSlot = j;
						break;
					}
				}
				else if (j >= 23){
					if (ComP(i) + ComP(slot[j - 1].nowPlane) <= 140){
						slot[j].nowPlane = i;
						flight[i].nowSlot = j;
						break;
					}
				}
				else{
					if (
						ComP(i) + ComP(slot[j + 1].nowPlane) <= 140 &&
						ComP(i) + ComP(slot[j - 1].nowPlane) <= 140
					){
						slot[j].nowPlane = i;
						flight[i].nowSlot = j;
						break;
					}

				}
			}
		}
		if (flight[i].nowSlot == -1){
			/*偵錯fprintf(ffailed, 
				"%3s %4s  %3d\nWing===%d\n", 
				flight[i].line, 
				flight[i].num,
				flight[i].aircraftType,
				ComP(i));*/
			fprintf(ffailed,
				"%3s %4s  %3d\n", 
				flight[i].line,
				flight[i].num, 
				flight[i].aircraftType);
			count++;
		}
	}
	fprintf(ffailed, "Total = %d", count);
	count = 0;
	for (int i(0); i < 24; i++){
		if (slot[i].nowPlane != 30){
			fprintf(fassigned,
				"Airline = %s\nFlight number = %s\nAircraft Type = %d\nAssigned to slot %2d\n===\n", 
				flight[slot[i].nowPlane].line,
				flight[slot[i].nowPlane].num,
				flight[slot[i].nowPlane].
				aircraftType,
				i);
			/*偵錯fprintf(fassigned, 
				"Airline = %s\nFlight number = %s\nAircraft Type = %d\nAssigned to slot %2d\nWing===%d\nslotwing===%d\n===\n",
				flight[slot[i].nowPlane].line,
				flight[slot[i].nowPlane].num,
				flight[slot[i].nowPlane].aircraftType,
				i,ComP(slot[i].nowPlane),
				slot[i].maxWing);*/
			count++;
		}
	}
	fprintf(fassigned, "Total = %d", count);

	fclose(fassigned);
	fclose(ffailed);
	fclose(fflight);
	fclose(fslot);
}


