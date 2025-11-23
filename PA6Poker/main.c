/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 7 - Poker (5-Card Draw) - VS file is called PA6 by accident :D
Date: 11/21/2025
Description: This is a text-based version of a card game called Poker involving features like handling user input in Command Prompt,
logical decision-making, checking for valid user input, passing in values directly or by reference, and random number generation.
*/

#include "Poker.h"

// controlls the process of running through the overall program
int main(void)
{
	int keep_playing = 1;
	do
	{
		main_menu(&keep_playing);

	} while (keep_playing);
	printf("\nThanks for playing! See ya next time :D\n");

	return 0;
}