// Eamon Tracey (etracey)
// FundComp Lab 7 (2) states.h
//
// Header file for states.c
//

#define MAX_ABBR_LENGTH 3
#define MAX_NAME_LENGTH 20

typedef struct State {
	char abbr[MAX_ABBR_LENGTH];
	char name[MAX_NAME_LENGTH];
	char capital[MAX_NAME_LENGTH];
	int year;
} State;

int smain(char[]);
void fload_states(State[], FILE *);
void disp_states(State[], int);
void swap_states(State *, State *);
void disp_ostates(State[], int);
void state_from_abbr(State[], int);
void state_capital(State[], int);
void state_year(State[], int);
void states_in_year(State[], int);
void states_in_year_range(State[], int);
