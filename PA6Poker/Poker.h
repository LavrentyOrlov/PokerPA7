/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 7 - Poker (5-Card Draw) - VS file is called PA6 by accident :D
Date: 11/21/2025
Description: This is a text-based version of a card game called Poker involving features like handling user input in Command Prompt,
logical decision-making, checking for valid user input, passing in values directly or by reference, and random number generation.
*/

#ifndef Poker_H
#define Poker_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card
{
	int face;
	int suit;
} Card;

typedef struct hand
{
	Card cards[5];
} Hand;

// Controls flow of gameplay
void play_game(void);

// Controls user interface interactions in
// main menu, allowing player to see game rules,
// start the game, or exit the program
void main_menu(int *keep_playing);

// displays game rules to the screen
void display_rules(void);

// goes through a deck of 52 cards and randomly determines
// a random order
void shuffle(int wDeck[][13]);

// gives a specified, adjustable number of cards to a player and
// displays results to the screen depending on the player in question
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], int cards_to_draw, int *starting_deck_location, Hand* hand, int card_to_redraw, int this_is_computer);

// change values in tables representing the frequencies of each possible suit and rank in the cards of the player's hand
void update_frequency_table(int current_player_suit_frequency_table[4], int current_player_face_frequency_table[13], Hand* current_player_hand);

// checks whether player has one pair
int has_pair(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// checks whether player has two pairs
int has_two_pairs(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// checks whether player has three of a kind
int has_three_of_a_kind(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// checks whether player has four of a kind
int has_four_of_a_kind(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// checks whether player has full house
int has_full_house(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// checks whether player has flush
int has_flush(int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7]);

// checks whether player has straight
int has_straight(int current_player_face_frequency_table[13], int current_player_combination_frequency_table[7]);

// returns highest card combination that the player has made in their hand
int determine_highest_combination(Hand* current_player_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7]);

// determines the highest-ranked card in the player's hand
int find_highest_card_in_hand(Hand* current_player_hand);

// compares strongest card combinations between the two players and deterines the winner;
// if both players have same combinations, kicker cards (strongest-ranked cards) are compared
void determine_winner(int player_one_highest_combo, int player_two_highest_combo, int player_one_highest_card, int player_two_highest_card);

//int find_card_not_in_four(Hand* computer_hand, int player_two_face_frequency_table[]);
//
//int find_first_card_not_in_three(Hand* computer_hand, int player_two_face_frequency_table[], int* frequency_table_position_first_card);
//
//int find_second_card_not_in_three(Hand* computer_hand, int player_two_face_frequency_table[], int card_one_frequency_position);

//void evaluate_computer_dealer_hand(const int Deck[][13], const char* wFace[], const char* wSuit[], Hand* player_hand, Hand* computer_hand, int computer_highest_combination, int computer_kick_card, int player_two_face_frequency_table[], int player_two_suit_frequency_table[]);

// controls the dealing of 5 random cards to computer dealer, then lets dealer re-draw 0-3 cards in their hand
void dealer_play(const int wDeck[][13], const char* wFace[], const char* wSuit[], const char* combinations[], int* starting_deck_location, Hand* dealer_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7]);

// controls the dealing of 5 random cards to player, then lets player re-draw 0-3 cards in their hand
void player_play(const int wDeck[][13], const char* wFace[], const char* wSuit[], const char* combinations[], int* starting_deck_location, Hand* player_hand, int current_player_face_frequency_table[13], int current_player_suit_frequency_table[4], int current_player_combination_frequency_table[7]);

// Implement repetitive gameplay later :D
//void gameplay(void);

#endif