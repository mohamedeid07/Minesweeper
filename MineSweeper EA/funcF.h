#ifndef FUNCF_H_INCLUDED
#define FUNCF_H_INCLUDED

int getGrid(void); //function that gets the grid size
int getCoordinates(void); //function that gets the cell coordinates
int getOption(void); //function that gets the option number
int getG(void); //function that gets the main option number
int getG1(void); //like previous one without option 3 while displaying score sheet
void clean_input(void); //Reads all characters of the line until pressing enter
void clrscr(void); //function that clears printed lines in cmd
void MineSweeper(void); //function that displays the main menu

#endif // FUNCF_H_INCLUDED
