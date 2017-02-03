#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CLS system("cls")
#define FLUSH fflush(stdin)
#define PAUSE system("pause")


//	Prototype Functions Here
int awayTheyGo();
void bankMenu(double morseMoney[]);
void currentMoney(double morseMoney[]);
void horsesWon(int winners[], int numOfWinners);
void mainMenu();
void raceTime(double morseMoney[], int *winningHorses[], int raceCounter);
void raceUpdate(int advancementValue, char theRace[][25], int horseRunningNumbers[]);
int winnerCheck(char theRace[][25], int *winningHorses[], int raceCounter);
void pickHorse(int *pick);
void placeBet(double morseMoney[], double wager[]);
//	End Prototype Functions

void delay(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void main() {
	mainMenu();
}

void bankMenu(double morseMoney[]) {

	int bSelection = 0;
	double moneyAmount = 0;

	do {	// Begin Menu Loop

		CLS;

		currentMoney(morseMoney);

		printf("What would you like to do? \n");
		printf("\n 1. Make a withdrawal");
		printf("\n 2. Make a Deposit");
		printf("\n 3. Balance Inquiry");
		printf("\n 4. Cancel");

		printf("\n Enter Selection: ");
		scanf_s("%i", &bSelection); FLUSH;

		switch (bSelection) { // Begin switch

		case 1:

			printf("How much would you like to withdraw?\nAmount: ");
			scanf_s("%lf", &moneyAmount);

			if (morseMoney[1] < moneyAmount) {	//	Insufficient Funds
				printf("You don't have enough money!\n");
				PAUSE;
			}
			else {
				morseMoney[1] -= moneyAmount;	//	Transfer From Bank to Wallet
				morseMoney[0] += moneyAmount;
			}

			break;

		case 2:

			printf("How much would you like to deposit?\nAmount: ");
			scanf_s("%lf", &moneyAmount);

			if (morseMoney[0] < moneyAmount) {	//	Insufficient Funds
				printf("You don't have enough money!\n");
				PAUSE;
			}
			else {
				morseMoney[0] -= moneyAmount;	//	Transfer From Wallet to Bank
				morseMoney[1] += moneyAmount;
			}

			break;

		case 3:

			printf("Look at the top of the screen, Dummy.\n");
			PAUSE;
			break;

		case 4:
			printf("\nReturning to the main menu.\n");
			break;

		default:	//	Error Checking
			printf("Please enter a valid option \n");
			PAUSE;
			break;
		} // End switch

	} while (bSelection != 4);

}

void mainMenu() {

	int mSelection = 0;	//	Menu choice
	double morseMoney[2] = { 0 , 300 };	//	Element 0 is Wallet, Element 1 is Bank
	int *winningHorses[1000] = { 0 }, winnerCount = 0;

	double wager[2] = { 0,0 }; //Current bet held at window. Element 0 is wager, Element 1 prevents double dipping.
	int *pick = 0; //Horse picked for next Win. 


	do {	// Begin Menu Loop

		CLS;

		currentMoney(morseMoney);	//	Banner Display

		printf("What would you like to do? \n");
		printf("\n 1. Go to the Bank");
		printf("\n 2. Place a bet");
		printf("\n 3. Go to the track");
		printf("\n 4. View Past Winners");
		printf("\n 5. Go Home");

		printf("\n Enter Selection: ");
		scanf_s("%i", &mSelection); FLUSH;

		switch (mSelection) { // Begin switch

		case 1:

			bankMenu(morseMoney);	//	To the Bank
			break;

		case 2: 					//Place a Bet
			CLS;
			currentMoney(morseMoney);	//	Banner Display
			if (wager[1] > 1) {
				printf("\nAll bets are closed.");
				printf("\n\nThe race is about to start.\nYou should head to the tracks.\n\n");
			}
			else {
				pickHorse(&pick);
				placeBet(morseMoney, wager);
			}
			break;

		case 3:
			winnerCount++;
			raceTime(morseMoney, winningHorses, winnerCount);
			break;

		case 4:
			if (winnerCount == 0) {
				printf("There have been no races yet today.\n");
				break;
			}
			else {
				horsesWon(winningHorses, winnerCount);
				break;
			}

		case 5:
			printf("The Track is Closing for the Day.\n\n");
			break;

		default:	//	Error Checking
			printf("Please enter a valid option \n");
			break;
		} // End switch

		PAUSE;

	} while (mSelection != 5);

}	//	End Menu Function

void currentMoney(double morseMoney[]) {	//	Banner across top to show current money

	printf("---------------------------------------------------------------------\n\n");
	printf("\tMoney In Wallet: %.2lf\tMoney In Bank: %.2lf", morseMoney[0], morseMoney[1]);
	printf("\n\n---------------------------------------------------------------------\n\n");

}

int awayTheyGo() {

	time_t t;
	int x;	//	Dice Roll for odds

	srand((unsigned)time(&t));
	x = rand() % 100 + 1;

	if (x >= 1 && x <= 30) {	//	30% Horse 1
		return 1;
	}
	else if (x >= 31 && x <= 40) {	//	10% Horse 2
		return 2;
	}
	else if (x >= 41 && x <= 48) {	//	8% Horse 3
		return 3;
	}
	else if (x >= 49 && x <= 54) {	//	6% Horse 4
		return 4;
	}
	else if (x >= 55 && x <= 56) {	//	2% Horse 5
		return 5;
	}
	else if (x >= 57 && x <= 60) {	//	4% Horse 6
		return 6;
	}
	else if (x >= 61 && x <= 68) {	//	8% Horse 7
		return 7;
	}
	else if (x >= 69 && x <= 78) {	//	10% Horse 8
		return 8;
	}
	else if (x >= 79 && x <= 100) {	//	22% Horse 9
		return 9;
	}

}

void raceTime(double morseMoney[], int *winningHorses[], int raceCounter) {

	int didSomeoneWin = 0, advancement = 0;
	int *horseRunningNumbers[9] = { 0 };

	char theRace[9][25] = { ' ' };
	theRace[0][0] = 'A';	//	American Pharoah # 1
	theRace[1][0] = 'S';	//	Seabiscuit # 2
	theRace[2][0] = 'B';	//	Black Stalion # 3
	theRace[3][0] = 'D';	//	Dirty Hilary # 4
	theRace[4][0] = 'H';	//	Hundchuck # 5
	theRace[5][0] = 'T';	//	Trigger	# 6
	theRace[6][0] = 'E';	//	Epona # 7
	theRace[7][0] = 'R';	//	Roach # 8
	theRace[8][0] = 'b';	//	Buckwheat Grotes # 9

	do {
		CLS;
		currentMoney(morseMoney);

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 25; j++) {
				printf("%c ", theRace[i][j]);
				FLUSH;
			}
			printf("\n");
		}

		advancement = awayTheyGo();
		raceUpdate(advancement, theRace, *horseRunningNumbers);

		didSomeoneWin = winnerCheck(theRace, *winningHorses, raceCounter);

	} while (didSomeoneWin != 1);

}

int winnerCheck(char theRace[][25], int *winningHorses[], int raceCounter) {

	if (theRace[0][24] == 'A') {
		return 1;
		winningHorses[raceCounter - 1] = 1;
	}
	else if (theRace[1][24] == 'S') {
		return 1;
		winningHorses[raceCounter - 1] = 2;
	}
	else if (theRace[2][24] == 'B') {
		return 1;
		winningHorses[raceCounter - 1] = 3;
	}
	else if (theRace[3][24] == 'D') {
		return 1;
		winningHorses[raceCounter - 1] = 4;
	}
	else if (theRace[4][24] == 'H') {
		return 1;
		winningHorses[raceCounter - 1] = 5;
	}
	else if (theRace[5][24] == 'T') {
		return 1;
		winningHorses[raceCounter - 1] = 6;
	}
	else if (theRace[6][24] == 'E') {
		return 1;
		winningHorses[raceCounter - 1] = 7;
	}
	else if (theRace[7][24] == 'R') {
		return 1;
		winningHorses[raceCounter - 1] = 8;
	}
	else if (theRace[8][24] == 'b') {
		return 1;
		winningHorses[raceCounter - 1] = 9;
	}
	else {
		return 0;
	}

}

void raceUpdate(int advancementValue, char theRace[][25], int horseArray[]) {

	if (advancementValue == 1) {
		horseArray[0]++;
		theRace[0][(horseArray[0] - 1)] = '.';
		theRace[0][(horseArray[0])] = 'A';
	}
	else if (advancementValue == 2) {
		horseArray[1]++;
		theRace[0][(horseArray[1] - 1)] = '.';
		theRace[0][(horseArray[1])] = 'S';
	}
	else if (advancementValue == 3) {
		horseArray[2]++;
		theRace[0][(horseArray[2] - 1)] = '.';
		theRace[0][(horseArray[2])] = 'B';
	}
	else if (advancementValue == 4) {
		horseArray[3]++;
		theRace[0][(horseArray[3] - 1)] = '.';
		theRace[0][(horseArray[3])] = 'D';
	}
	else if (advancementValue == 5) {
		horseArray[4]++;
		theRace[0][(horseArray[4] - 1)] = '.';
		theRace[0][(horseArray[4])] = 'H';
	}
	else if (advancementValue == 6) {
		horseArray[5]++;
		theRace[0][(horseArray[5] - 1)] = '.';
		theRace[0][(horseArray[5])] = 'T';
	}
	else if (advancementValue == 7) {
		horseArray[6]++;
		theRace[0][(horseArray[6] - 1)] = '.';
		theRace[0][(horseArray[6])] = 'E';
	}
	else if (advancementValue == 8) {
		horseArray[7]++;
		theRace[0][(horseArray[7] - 1)] = '.';
		theRace[0][(horseArray[7])] = 'R';
	}
	else if (advancementValue == 9) {
		horseArray[8]++;
		theRace[0][(horseArray[8] - 1)] = '.';
		theRace[0][(horseArray[8])] = 'b';
	}


}

void horsesWon(int winners[], int numOfWinners) {
	CLS;
	printf("\nHere are the list of winners\n");

	for (int i = 0; i < numOfWinners; i++) {
		printf("Race # %i: Horse # %d won race\n", i + 1, winners[i]);
	}
	// end for loop

} // end winners


void pickHorse(int *pick) {
	int horse = &pick;

	printf("\n\n Horse Payout Odds");
	printf("\n1 American Pharoah 2-1 30%%");
	printf("\n2 Seabiscuit 5-1 10%%");
	printf("\n3 Black Stalion 10-1 8%%");
	printf("\n4 Dirty Hilary 15-1 6%%");
	printf("\n5 Hundchuck 50-1 2%%");
	printf("\n6 Trigger 20-1 4%%");
	printf("\n7 Epona 10-1 8%%");
	printf("\n8 Roach 5-1 10%%");
	printf("\n9 Buckwheat Grotes 3-1 22%%");

	printf("\nWelcome to the track window.");

	printf("\nPick the winning horse for the next race: ");
	scanf_s("%i", horse);
	if ((0>horse) || (horse<9)) {
		printf("\nThat's not a valid horse... Get outta' here!");
		horse = 0;
		
	}
}


void placeBet(double morseMoney[], double wager[]) {
	double wallet;
	double moneyAmount;
	wallet = morseMoney[0];


	printf("\nPlace your bet: ");
	scanf_s("%lf", &moneyAmount);

	if (wallet < moneyAmount) {	//	Insufficient Funds
		printf("You don't have enough money!\n");
	}
	else {
		wallet -= moneyAmount;	//	Transfer From Wallet to wager
		morseMoney[0] = wallet;
		wager[0] = moneyAmount;
		wager[1] = 10;
	}

}
