
#define POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define MAX_PLAYERS 10
#define START_CHIPS 1000
#define SMALL_BLIND 10
#define NUM_COMMUNITY_CARDS 5
#define NUM_HAND_CARDS 2
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 52
#define MAX_COMBINATIONS 10

#define COLOR_RED 12
#define COLOR_GRAY 8
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_PURPLE 13
#define COLOR_DEFAULT 7

extern const char *suits[];
extern const char *ranks[];

typedef struct {
    int suit;
    int rank;
    bool visible;
} Card;

typedef struct {
    char name[50];
    Card hand[NUM_HAND_CARDS];
    int chips;
    int current_bet;
    bool folded;
    bool all_in;
    bool is_ai;
} Player;

typedef enum {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
} HandRank;

typedef struct {
    HandRank rank;
    int kickers[NUM_HAND_CARDS];
} HandValue;

extern Card deck[NUM_CARDS];
extern Card community_cards[NUM_COMMUNITY_CARDS];
extern Player players[MAX_PLAYERS];
extern int num_players;
extern int pot;
extern int current_bet;
extern int dealer_pos;
extern int small_blind_pos;
extern int big_blind_pos;
extern int current_player;
extern int game_round;
extern bool game_active;
extern int fallplayers;

// Function declarations
void set_color(int color);
void reset_color();
void clear_screen();
void init_deck();
void shuffle_deck();
void print_card(Card card);
void print_hand(Card hand[NUM_HAND_CARDS], bool hide_second);
void deal_cards();
void reveal_community_cards();
void print_game_state();
void place_bet(int player_idx, int amount);
void player_turn(int player_idx);
void ai_turn(int player_idx);
void betting_round();
void next_round();
void determine_winner();
void start_hand();
void add_player(const char *name, bool is_ai);
void evaluate_hand(Card hand[NUM_HAND_CARDS], Card community[NUM_COMMUNITY_CARDS], HandValue *result);
int compare_hands(const void *a, const void *b);
void print_hand_rank(HandRank rank);
int count_rank(Card *cards, int num_cards, int rank);
int count_suit(Card *cards, int num_cards, int suit);
int compare_cards(const void *a, const void *b);

