/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 7 - Poker (5-Card Draw) - VS file is called PA6 by accident :D
Date: 11/21/2025
Description: This is a text-based version of a card game called Poker involving features like handling user input in Command Prompt,
logical decision-making, checking for valid user input, passing in values directly or by reference, and random number generation.
*/

#include "Poker.h"

void main_menu(int *keep_playing)
{
	printf("\n**** Welcome to Five-Card Draw Poker! ****\n");
	printf("\nDesigned by CS student Lavrenty \"Larry\" Orlov\n");
	int user_choice = 0;
	do {
		printf("\n");
		printf("Would you like to (1) view the game rules, (2) play the game, or (3) exit the game? ");
		scanf("%d", &user_choice);
	} while (user_choice < 0 || user_choice > 3);
	system("cls");
	switch (user_choice)
	{
	case 1:
		display_rules();
		break;
	case 2:
		play_game();
		break;
	case 3:
		*keep_playing = 0;
		break;
	}
}

void display_rules(void)
{
	printf("**** Game Rules: ****\n");
	printf("\n");
	printf("In this simplified version of the game, there are two players: you and the computer!\n");
	printf("\n");
	printf("There is a deck of 52 cards. This deck has 4 groups of cards, each corresponding to a\n");
	printf("specific category, or \"suit:\"\n");
	printf("\n");
	printf("- Clubs\n");
	printf("- Diamonds\n");
	printf("- Hearts\n");
	printf("- Spades\n");
	printf("\n");
	printf("For each suit group, there are 13 \"ranks\" (listed here from highest to lowest value):\n");
	printf("\n");
	printf("- Ace\n");
	printf("- King\n");
	printf("- Queen\n");
	printf("- Jack\n");
	printf("- 10\n");
	printf("- 9\n");
	printf("- 8\n");
	printf("- 7\n");
	printf("- 6\n");
	printf("- 5\n");
	printf("- 4\n");
	printf("- 3\n");
	printf("- 2, called \"deuce\"\n");
	printf("\n");
	printf("This deck gets shuffled at the start of the game, and then each player receives 5 random\n");
	printf("cards. 5 cards can be used to form one or more possible combinations. Poker typically has 10\n");
	printf("combinations, but here are the 8 combinations implemented in this version of the game,\n");
	printf("listed from highest to lowest value:\n");
	printf("\n");
	printf("- Four of a Kind: 4 cards of the same rank\n");
	printf("- Full House: 3 cards of one rank and 2 cards of another rank\n");
	printf("- Flush: 5 cards of the same suit\n");
	printf("- Straight: 5 cards with ranks in sequential order\n");
	printf("- Three of a Kind: 3 cards of the same rank\n");
	printf("- Two Pairs: 2 cards of one rank and 2 cards of another rank\n");
	printf("- One Pair: 2 cards of the same rank\n");
	printf("- High Card: When none of the above combinations are made, the card with the highest rank\n");
	printf("  represents your High Card result\n");
	printf("\n");
	printf("After receiving the 5 random cards, each player can choose to re-draw 0-3 of their cards,\n");
	printf("which means replacing a specific card in their hand with a new random card from the deck.\n");
	printf("\n");
	printf("In my version of the game, the player with the stronger card wins the game! And if both\n");
	printf("players have the same type of combination, this implementation determines the winner by\n");
	printf("comparing each player's \"kicker\" cards, which is the highest-ranked card in each player's\n");
	printf("hand. If the kickers also happen to be the same, then the game ends in a draw!\n");
	printf("\n");
	printf("Ready to return to the main menu? :D\n");
	printf("\n");
	system("pause");
	system("cls");
}

void dealer_play(const int wDeck[][13], const char* wFace[], const char* wSuit[], const char* combinations[], int* starting_deck_location, Hand* dealer_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7])
{
	int dealer_highest_combo = 0, this_is_computer = 1;
	printf("\nThe computer got");
	deal(wDeck, wFace, wSuit, 5, starting_deck_location, dealer_hand, -1, this_is_computer);
	dealer_highest_combo = determine_highest_combination(dealer_hand, current_player_face_frequency_table, current_player_suit_frequency_table, current_player_combination_frequency_table);

	switch (dealer_highest_combo)
	{
	case 0:
		// high card; re-draw 3!
		printf("The computer re-drew");
		deal(wDeck, wFace, wSuit, 3, starting_deck_location, dealer_hand, 0, this_is_computer);
		break;
	case 1:
		// one pair; re-draw 3!
		deal(wDeck, wFace, wSuit, 2, starting_deck_location, dealer_hand, 0, this_is_computer);
		break;
	case 2:
		// two-pair; re-draw 1!
		deal(wDeck, wFace, wSuit, 1, starting_deck_location, dealer_hand, 0, this_is_computer);
		break;
	}

	/*update_frequency_table(current_player_suit_frequency_table, current_player_face_frequency_table, dealer_hand);
	dealer_highest_combo = determine_highest_combination(dealer_hand, current_player_face_frequency_table, current_player_suit_frequency_table, current_player_combination_frequency_table);*/

}

/* deal cards in deck */
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], int cards_to_draw, int* starting_deck_location, Hand* hand, int card_to_redraw, int this_is_computer)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	if (card_to_redraw > -1)
	{
		card = card_to_redraw;
	}

	printf(" %d random card(s)!\n", cards_to_draw);
	printf("\n");

	/* deal five cards to player one */
	for (int i = 1; i <= cards_to_draw; i++)
	{
		int deal_counter = i + *starting_deck_location;
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current dealt position of the card being dealt, display card */
				if (wDeck[row][column] == deal_counter)
				{
					hand->cards[card].suit = row;
					hand->cards[card].face = column;
					if (this_is_computer)
					{
						printf("card %d: **********\n", card + 1);
					}
					else
					{
						printf("card %d: %s of %s\n", card + 1, wFace[column], wSuit[row]); //printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
					}
					card++;
				}
			}
		}
	}
	*starting_deck_location += cards_to_draw;
}

void player_play(const int wDeck[][13], const char* wFace[], const char* wSuit[], const char* combinations[], int* starting_deck_location, Hand* player_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7])
{
	int cards_to_redraw = 0, current_card_to_redraw = 0, redraw_cards_list[] = { 0 }, previously_entered_values[3] = { 0, 0, 0 }, this_is_computer = 0, player_one_highest_combo = 0;

	printf("\n\nYou got");
	deal(wDeck, wFace, wSuit, 5, starting_deck_location, player_hand, current_card_to_redraw - 1, this_is_computer);

	update_frequency_table(current_player_suit_frequency_table, current_player_face_frequency_table, player_hand);
	player_one_highest_combo = determine_highest_combination(player_hand, current_player_face_frequency_table, current_player_suit_frequency_table, current_player_combination_frequency_table);

	printf("\nYour highest current combination is: #%d, which is %s!\n", player_one_highest_combo, combinations[player_one_highest_combo]);

	do
	{
		printf("How many cards do you wish to redraw? Please enter a value between 0-3: ");
		scanf(" %d", &cards_to_redraw);
	} while (cards_to_redraw < 0 || cards_to_redraw > 3);

	for (int i = 0; i < cards_to_redraw; i++)
	{
		do
		{
			printf("Please enter a value between 1 and 5 for the next card you wish to redraw: ");
			scanf(" %d", &current_card_to_redraw);
		} while (current_card_to_redraw < 1 || current_card_to_redraw > 5 || previously_entered_values[0] == current_card_to_redraw || previously_entered_values[1] == current_card_to_redraw);
		printf("You got");
		deal(wDeck, wFace, wSuit, 1, starting_deck_location, player_hand, current_card_to_redraw - 1, this_is_computer);
		previously_entered_values[i] = current_card_to_redraw;
	}

	/*update_frequency_table(current_player_suit_frequency_table, current_player_face_frequency_table, player_hand);
	player_one_highest_combo = determine_highest_combination(player_hand, current_player_face_frequency_table, current_player_suit_frequency_table, current_player_combination_frequency_table);*/

	/*for (int i = 0; i < cards_to_redraw; i++)
	{
		deal(wDeck, wFace, wSuit, cards_to_redraw, starting_deck_location, dealer_hand);
	}*/

}

void play_game(void)
{
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King", "Ace"};

	const char* combinations[8] = { "High Card", "One Pair", "Two Pairs", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind" };

	// Make frequnecy tables for combinations have 8 values so that the program can index through combinations
	// 1-7 based on the project specifications, and return zero if the only combination found is a high card!
	int cards_to_draw = 0, starting_deck_location = 0, player_one_suit_frequency_table[4] = { 0 },
		player_two_suit_frequency_table[4] = { 0 }, player_one_face_frequency_table[13] = { 0 },
		player_two_face_frequency_table[13] = { 0 }, player_one_combinations_frequency_table[8] = { 0 },
		player_two_combinations_frequency_table[8] = { 0 }, player_one_highest_combo = 0,
		player_two_highest_combo = 0, winner = 0, player_one_highest_card = 0, computer_highest_card = 0;

	Card player_one_card_one = { 0, 0 };
	Card player_one_card_two = { 0, 0 };
	Card player_one_card_three = { 0, 0 };
	Card player_one_card_four = { 0, 0 };
	Card player_one_card_five = { 0, 0 };

	Card player_two_card_one = { 0, 0 };
	Card player_two_card_two = { 0, 0 };
	Card player_two_card_three = { 0, 0 };
	Card player_two_card_four = { 0, 0 };
	Card player_two_card_five = { 0, 0 };

	Hand player_one_hand = { 0 };
	Hand computer_hand = { 0 };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	srand(time(NULL)); /* seed random-number generator */

	printf("The game has started!\n");

	shuffle(deck);

	cards_to_draw = 5;

	dealer_play(deck, face, suit, combinations, &starting_deck_location, &computer_hand, player_two_face_frequency_table, player_two_suit_frequency_table, player_two_combinations_frequency_table);
	update_frequency_table(player_two_suit_frequency_table, player_two_face_frequency_table, &computer_hand);
	player_two_highest_combo = determine_highest_combination(&computer_hand, player_two_face_frequency_table, player_two_suit_frequency_table, player_two_combinations_frequency_table);

	player_play(deck, face, suit, combinations, &starting_deck_location, &player_one_hand, player_one_face_frequency_table, player_one_suit_frequency_table, player_one_combinations_frequency_table);

	/*printf("\nResults before redraws:\n");*/

	/*printf("\nYour highest combination: #%d, which is %s!\n", player_one_highest_combo, combinations[player_one_highest_combo]);
	printf("\nComputer's highest combination: #%d, which is %s!\n", player_two_highest_combo, combinations[player_two_highest_combo]);*/

	if (player_one_highest_combo == player_two_highest_combo)
	{
		player_one_highest_card = find_highest_card_in_hand(&player_one_hand);
		printf("\n");
		printf("Your kicker card: %s!", face[player_one_highest_card]);
		computer_highest_card = find_highest_card_in_hand(&computer_hand);
		printf("\n");
		printf("Computer's kicker card: %s!", face[computer_highest_card]);
	}

	//evaluate_computer_dealer_hand(deck, face, suit, &player_one_hand, &computer_hand, player_two_highest_combo, computer_highest_card, player_two_face_frequency_table, player_two_suit_frequency_table);
	// give player the chance to re-draw their hand here! :D

	/*update_frequency_table(player_one_suit_frequency_table, player_one_face_frequency_table, &player_one_hand);
	update_frequency_table(player_two_suit_frequency_table, player_two_face_frequency_table, &computer_hand);*/
	
	/*player_two_face_frequency_table[0] = 0;
	player_two_face_frequency_table[1] = 0;
	player_two_face_frequency_table[2] = 0;
	player_two_face_frequency_table[3] = 0;
	player_two_face_frequency_table[4] = 3;
	player_two_face_frequency_table[5] = 0;
	player_two_face_frequency_table[6] = 1;
	player_two_face_frequency_table[7] = 0;
	player_two_face_frequency_table[8] = 0;
	player_two_face_frequency_table[9] = 1;
	player_two_face_frequency_table[10] = 0;
	player_two_face_frequency_table[11] = 0;
	player_two_face_frequency_table[12] = 0;

	computer_hand.cards[3].face = 6;
	computer_hand.cards[4].face = 9;*/

	printf("\nAfter redraws:\n");

	//update_frequency_table(player_one_suit_frequency_table, player_one_face_frequency_table, &player_one_hand);
	player_one_highest_combo = determine_highest_combination(&player_one_hand, player_one_face_frequency_table, player_one_suit_frequency_table, player_one_combinations_frequency_table);

	printf("\nYour highest combination: #%d, which is %s!\n", player_one_highest_combo, combinations[player_one_highest_combo]);
	printf("\nComputer's highest combination: #%d, which is %s!\n", player_two_highest_combo, combinations[player_two_highest_combo]);

	if (player_one_highest_combo == player_two_highest_combo)
	{
		player_one_highest_card = find_highest_card_in_hand(&player_one_hand);
		printf("\n");
		printf("Your kicker card: %s!", face[player_one_highest_card]);
		computer_highest_card = find_highest_card_in_hand(&computer_hand);
		printf("\n");
		printf("Computer's kicker card: %s!", face[computer_highest_card]);
	}

	determine_winner(player_one_highest_combo, player_two_highest_combo, player_one_highest_card, computer_highest_card);

	system("pause");
	system("cls");

	/*if (player_one_highest_combo == 0)
	{
		printf("\nPlayer 1 highest combo: %d", player_one_highest_combo);
	}*/

	// ---------

	// Temporary test code! :D
	/*player_one_face_frequency_table[0] = 0;
	player_one_face_frequency_table[1] = 0;
	player_one_face_frequency_table[2] = 0;
	player_one_face_frequency_table[3] = 0;
	player_one_face_frequency_table[4] = 0;
	player_one_face_frequency_table[5] = 1;
	player_one_face_frequency_table[6] = 1;
	player_one_face_frequency_table[7] = 0;
	player_one_face_frequency_table[8] = 0;
	player_one_face_frequency_table[9] = 0;
	player_one_face_frequency_table[10] = 0;
	player_one_face_frequency_table[11] = 0;
	player_one_face_frequency_table[12] = 0;

	player_two_face_frequency_table[0] = 0;
	player_two_face_frequency_table[1] = 0;
	player_two_face_frequency_table[2] = 0;
	player_two_face_frequency_table[3] = 0;
	player_two_face_frequency_table[4] = 0;
	player_two_face_frequency_table[5] = 0;
	player_two_face_frequency_table[6] = 0;
	player_two_face_frequency_table[7] = 0;
	player_two_face_frequency_table[8] = 0;
	player_two_face_frequency_table[9] = 0;
	player_two_face_frequency_table[10] = 0;
	player_two_face_frequency_table[11] = 0;
	player_two_face_frequency_table[12] = 0;

	int player_one_result = has_straight(player_one_face_frequency_table, player_one_combinations_frequency_table);
	printf("\nPlayer 1 result: %d\n", player_one_result);*/
	//has_two_pairs(player_one_face_frequency_table);



	// ---------
}

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

// Highest combo of zero means that the player has only received a high card
int determine_highest_combination(Hand *current_player_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7])
{
	if (has_four_of_a_kind(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 7;
	}
	else if (has_full_house(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 6;
	}
	else if (has_flush(current_player_suit_frequency_table, current_player_combination_frequency_table))
	{
		return 5;
	}
	else if (has_straight(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 4;
	}
	else if (has_three_of_a_kind(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 3;
	}
	else if (has_two_pairs(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 2;
	}
	else if (has_pair(current_player_face_frequency_table, current_player_combination_frequency_table))
	{
		return 1;
	}
	else
	{
		// last case represents high card!
		return 0;
	}

	/*int highest_combo_number = 0;
	for (int i = 0; i < 7; i++)
	{
		if (current_player_combination_frequency_table[i] != 0)
		{
			printf("\nNot zero!\n");
			highest_combo_number = i + 1;
		}
	}
	return highest_combo_number;*/
}

int find_highest_card_in_hand(Hand* current_player_hand)
{
	int highest_card = 0;
	for (int i = 0; i < 5; i++)
	{
		if (current_player_hand->cards[i].face > highest_card)
		{
			highest_card = current_player_hand->cards[i].face;
		}
	}
	return highest_card;
}

int has_pair(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int pair_found = 0;
	current_player_combination_frequency_table[0] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] >= 2)
		{
			pair_found = 1;
			current_player_combination_frequency_table[0] = 1;
		}
	}
	return pair_found;
}

int has_two_pairs(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int one_pair_found = 0, second_pair_found = 0, first_pair_value = 0;
	current_player_combination_frequency_table[1] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] >= 2)
		{
			one_pair_found = 1;
			first_pair_value = i;
			break;
		}
	}

	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] >= 2 && i != first_pair_value)
		{
			second_pair_found = 1;
			current_player_combination_frequency_table[1] = 1;
		}
	}

	return one_pair_found && second_pair_found;
}

int has_three_of_a_kind(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int three_of_a_kind_found = 0;
	current_player_combination_frequency_table[2] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] >= 3)
		{
			three_of_a_kind_found = 1;
			current_player_combination_frequency_table[2] = 1;
		}
	}
	return three_of_a_kind_found;
}

int has_four_of_a_kind(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int four_of_a_kind_found = 0;
	current_player_combination_frequency_table[3] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] >= 4)
		{
			four_of_a_kind_found = 1;
			current_player_combination_frequency_table[3] = 1;
		}
	}
	return four_of_a_kind_found;
}

int has_full_house(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int one_pair_found = 0, three_of_a_kind_found = 0, first_pair_value = 0;
	current_player_combination_frequency_table[4] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] == 2)
		{
			one_pair_found = 1;
			first_pair_value = i;
			break;
		}
	}

	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] == 3 && i != first_pair_value)
		{
			three_of_a_kind_found = 1;
			current_player_combination_frequency_table[4] = 1;
		}
	}

	return one_pair_found && three_of_a_kind_found;
}

int has_flush(int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7])
{
	int flush_found = 0;
	current_player_combination_frequency_table[5] = 0;
	for (int i = 0; i < 4; i++)
	{
		if (current_player_suit_frequency_table[i] == 5)
		{
			flush_found = 1;
			current_player_combination_frequency_table[5] = 1;
		}
	}
	return flush_found;
}

int has_straight(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7])
{
	int sequence_tracker = 0;
	current_player_combination_frequency_table[6] = 0;
	for (int i = 0; i < 13; i++)
	{
		if (current_player_face_frequency_table[i] == 1)
		{
			sequence_tracker++;
		}
		else
		{
			sequence_tracker = 0;
		}

		if (sequence_tracker == 5)
		{
			current_player_combination_frequency_table[6] = 1;
			return 1;
		}
	}
	return 0;
}

void update_frequency_table(int current_player_suit_frequency_table[4], int current_player_face_frequency_table[13], Hand *current_player_hand)
{
	// Test code! :D
	/*printf("\nOriginal suit frequency table: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", current_player_suit_frequency_table[i]);
	}
	printf("\nOriginal face frequency table: \n");
	for (int i = 0; i < 13; i++)
	{
		printf("%d ", current_player_face_frequency_table[i]);
	}*/
	
	// Go through each of the five cards for the player!
	for (int i = 0; i < 5; i++)
	{
		current_player_suit_frequency_table[current_player_hand->cards[i].suit]++;
		current_player_face_frequency_table[current_player_hand->cards[i].face]++;
	}

	// Test code! :D
	/*printf("\nUpdated suit frequency table: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", current_player_suit_frequency_table[i]);
	}
	printf("\nUpdated face frequency table: \n");
	for (int i = 0; i < 13; i++)
	{
		printf("%d ", current_player_face_frequency_table[i]);
	}*/
}

// POKER NEXT STEPS! ;D
// 1. Finish solving logical error for finding index position of card to re-draw during for-of-a-kind!
// 2. Implement similar system for finding index position of card(s) to re-draw during other hands the computer may have!
// 3. Implement the versatile draw function by seeing if you can use it by adjusting the values of the starting x-value.

// 4. Prompt user to re-draw 0-3 cards by entering the numbers of the cards they wish to redraw like 2 3 and 5 (zero if none)!
// 5. Cycle through a loop that re-draws one player card at a time!

// 6. Ensure that the full algorithm for a single game runthrough works accurately with values you expect!
// 7. Place the algorithm into a separate function you can call from main()!

// 8. Create welcome menu sysem as with previous PAs!
// 9. Other scenarios to adjust to/include?

// 10. Comment your code!

// 11. Sanity check: review project rubric!


//int find_card_not_in_four(Hand* computer_hand, int player_two_face_frequency_table[])
//{
//	int face_value_to_track = 0;
//	int position_of_card_to_replace = 0;
//	for (int i = 0; i < 13; i++)
//	{
//		//printf("Current frequency: %d\n", player_two_face_frequency_table[i]);
//		if (player_two_face_frequency_table[i] == 1)
//		{
//			printf("Face value to track: %d\n", i);
//			face_value_to_track = i;
//		}
//	}
//
//	for (int i = 0; i < 5; i++)
//	{
//		//printf("\nCurrent card's face value: %d\n", computer_hand->cards[i].face);
//		if (computer_hand->cards[i].face == face_value_to_track)
//		{
//			return i;
//		}
//	}
//}
//
//int find_first_card_not_in_three(Hand* computer_hand, int player_two_face_frequency_table[], int *frequency_table_position_first_card)
//{
//	int face_value_to_track = 0;
//	int position_of_card_to_replace = 0;
//	for (int i = 0; i < 13; i++)
//	{
//		//printf("Current frequency: %d\n", player_two_face_frequency_table[i]);
//		if (player_two_face_frequency_table[i] == 1)
//		{
//			printf("Face value to track: %d\n", i);
//			face_value_to_track = i;
//			*frequency_table_position_first_card = i;
//		}
//	}
//
//	for (int i = 0; i < 5; i++)
//	{
//		//printf("\nCurrent card's face value: %d\n", computer_hand->cards[i].face);
//		if (computer_hand->cards[i].face == face_value_to_track)
//		{
//			return i;
//		}
//	}
//}
//
//int find_second_card_not_in_three(Hand* computer_hand, int player_two_face_frequency_table[], int card_one_frequency_position)
//{
//	int face_value_to_track = 0;
//	int position_of_card_to_replace = 0;
//	for (int i = 0; i < 13; i++)
//	{
//		//printf("Current frequency: %d\n", player_two_face_frequency_table[i]);
//		if (player_two_face_frequency_table[i] == 1 && i != card_one_frequency_position)
//		{
//			printf("Face value to track: %d\n", i);
//			face_value_to_track = i;
//		}
//	}
//
//	for (int i = 0; i < 5; i++)
//	{
//		//printf("\nCurrent card's face value: %d\n", computer_hand->cards[i].face);
//		if (computer_hand->cards[i].face == face_value_to_track)
//		{
//			return i;
//		}
//	}
//}

//void evaluate_computer_dealer_hand(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand, Hand* computer_hand, int computer_highest_combination, int computer_kick_card, int player_two_face_frequency_table[], int player_two_suit_frequency_table[])
//{
//	int first_card_to_redraw = 0, second_card_to_redraw = 0, third_card_to_redraw = 0, frequency_table_position_first_card = -1;
//	printf("\nComputer analyzes his cards... and decides to redraw ");
//	
//	if (computer_highest_combination == 7) // Four of a kind!
//	{
//		printf("zero cards!\n");
//		/*first_card_to_redraw = find_card_not_in_four(computer_hand, player_two_face_frequency_table);
//		printf("\nPosition of card to re-draw: %d\n", first_card_to_redraw);
//		deal(wDeck, wFace, wSuit, 1, 11, first_card_to_redraw, player_hand, computer_hand);*/
//	}
//	else if (computer_highest_combination == 6) // Full house!
//	{
//		printf("zero cards!\n");
//	}
//	else if (computer_highest_combination == 5) // Flush!
//	{
//		printf("zero cards!\n");
//	}
//	else if (computer_highest_combination == 4) // Straight!
//	{
//		printf("zero cards!\n");
//	}
//	else if (computer_highest_combination == 3) // Three of a kind!
//	{
//		printf("two cards!\n");
//		first_card_to_redraw = find_first_card_not_in_three(computer_hand, player_two_face_frequency_table, &frequency_table_position_first_card);
//		printf("\nPosition of first card to re-draw: %d\n", first_card_to_redraw);
//		deal(wDeck, wFace, wSuit, 1, 11, first_card_to_redraw, player_hand, computer_hand);
//		
//		second_card_to_redraw = find_second_card_not_in_three(computer_hand, player_two_face_frequency_table, &frequency_table_position_first_card);
//		printf("\nPosition of second card to re-draw: %d\n", second_card_to_redraw);
//		deal(wDeck, wFace, wSuit, 1, 12, second_card_to_redraw, player_hand, computer_hand);
//	}
//	else if (computer_highest_combination == 2) // Two pairs!
//	{
//		printf("one card!\n");
//		first_card_to_redraw = find_card_not_in_four(computer_hand, player_two_face_frequency_table);
//		printf("\nPosition of card to re-draw: %d\n", first_card_to_redraw);
//		deal(wDeck, wFace, wSuit, 1, 11, first_card_to_redraw, player_hand, computer_hand);
//	}
//	else if (computer_highest_combination == 1) // Pair!
//	{
//		printf("three cards!\n");
//	}
//	else // High card!
//	{
//		printf("three cards!\n");
//	}
//}

void determine_winner(int player_one_highest_combo, int player_two_highest_combo, int player_one_highest_card, int player_two_highest_card)
{
	if (player_one_highest_combo > player_two_highest_combo)
	{
		printf("\n");
		printf("You win with the stronger hand! :D\n");
	}
	else if (player_one_highest_combo < player_two_highest_combo)
	{
		printf("\n");
		printf("Computer wins with the stronger hand!\n");
	}
	else
	{
		printf("\n");
		printf("You and the computer have the same type of combination! And...\n");
		if (player_one_highest_card > player_two_highest_card)
		{
			printf("\n");
			printf("You win with the higher kicker card! :D\n");
		}
		else if (player_one_highest_card < player_two_highest_card)
		{
			printf("\n");
			printf("The computer wins with the higher kicker card!\n");
		}
		else
		{
			printf("\n");
			printf("Wow, your kicker cards are also the same! It's a draw!\n");
		}
	}
}