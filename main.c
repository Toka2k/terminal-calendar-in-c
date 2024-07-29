#include	"date.h"
#include	"file.h"
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>

// MACROS

#define TRUE 1
#define FALSE 0

//

int main(int argc, char* argv[]){	
	//printf("\033[30m\033[46mHello World!\033[0m");
	
	if(argc != 2){
		printf("\033[30m\033[43mExpected 1 argument.\033[0m\n");
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("\033[30m\033[43mFailed to open specified file.\033[0m\n");
		exit(2);
	}

	int lines = _flines(fp);

	

	DATE dates[lines];
	int startHour[lines];
	int endHour[lines];

	for(int i = 0; i < lines; i++){
		 if(fscanf(fp, "%d %d %d : %d-%d", &dates[i].day, &dates[i].month, &dates[i].year, &startHour[i], &endHour[i]) != 5){
			printf("\033[30m\033[43mFailed to read from a line.\033[0m\n");	
			 exit(3);
		 };

		 dates[i].smonth = months[dates[i].month - 1];
		 dates[i].sday = getDay(&dates[i]);
	
		//printf("DAY: %d, HOURS: %d-%d\n", dates[i].day, startHour[i],endHour[i]);
	}	

	//
	// PRINTING CALENDAR
	//
	
	DATE currentDate = getDate();
	
	DATE fDOM = dates[0];
	fDOM.day = 1;
	fDOM.sday = getDay(&fDOM);

	int skips = 0;

	for(int i = 0; i < 7; i++){
		if(days[i] == fDOM.sday){
			skips = i;
			break;
		}
	}

	int x = 0;

	printf("\033[4m MO | TU | WE | TH | FR | SA | SU  \033[0m\n");

	for(int i = 0; i < skips; i++){
		printf("    |");
		x++;
	}

	for(int i = 1; i <= _months[fDOM.month-1]; i++){
		if(x % 7 == 0 && x != 0){
			printf("\n");
			x = 0;
		}

		for(int y = 0; y < lines; y++){
			if(dates[y].day == i){
				printf("\033[30m\033[42m");
				break;
			}else{
				printf("\033[32m");
			}
		}

		if(i-1 == currentDate.day && currentDate.month == dates[0].month){
			printf("\033[1m\033[3m");
		}

		if(i < 10){
			printf("  %d \033[0m|", i );
		} else{
			printf(" %d \033[0m|", i);
		}

		x++;
	}

	while(x != 7){
		printf("    |");
		x++;
	}

	printf("\n");

	printf("Month:	\033[3m\033[1m%s \033[0m\n", dates[0].smonth);
	printf("Year:	\033[3m\033[1m%d \033[0m\n", dates[0].year);

	return 0;
}
