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

const char *suits[] = {"♥", "♦", "♣", "♠"};
const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

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

// Комбинации в покере (от старшей к младшей)
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

Card deck[NUM_CARDS];
Card community_cards[NUM_COMMUNITY_CARDS];
Player players[MAX_PLAYERS];
int num_players = 0;
int pot = 0;
int current_bet = 0;
int dealer_pos = 0;
int small_blind_pos = 0;
int big_blind_pos = 0;
int current_player = 0;
int game_round = 0;
bool game_active = false;


int fallplayers = 0;
void set_color(int color);
void reset_color();
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


void clear_screen() {
    system("cls");
}

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_color() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_DEFAULT);
}


void init_deck() {
    int i = 0;
    for (int s = 0; s < NUM_SUITS; s++) {
        for (int r = 0; r < NUM_RANKS; r++) {
            deck[i].suit = s;
            deck[i].rank = r;
            deck[i].visible = true;
            i++;
        }
    }
}

void shuffle_deck() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < NUM_CARDS; i++) {
        int j = rand() % NUM_CARDS;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}


void print_card(Card card) {
    if (card.visible) {
        if (card.suit < 2) {
            set_color(COLOR_RED);
        } else {
            set_color(COLOR_GRAY);
        }
        printf("%s%s", ranks[card.rank], suits[card.suit]);
    } else {
        set_color(COLOR_DEFAULT);
        printf("XX");
    }
    reset_color();
}

void print_hand(Card hand[NUM_HAND_CARDS], bool hide_second) {
    printf(" ");
    if (hide_second) {
        Card hidde = hand[0];
        hidde.visible = false;
        Card hidden = hand[1];
        hidden.visible = false;
        print_card(hidde);
        print_card(hidden);
    } else {
        print_card(hand[0]);
        print_card(hand[1]);
    }
}


void deal_cards() {
    int card_idx = 0;

    for (int i = 0; i < num_players; i++) {
        players[i].hand[0] = deck[card_idx++];
        players[i].hand[1] = deck[card_idx++];
        players[i].folded = false;
        players[i].all_in = false;
        players[i].current_bet = 0;
    }
    

    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        community_cards[i] = deck[card_idx++];
        community_cards[i].visible = false;
    }
}

void reveal_community_cards() {
    switch (game_round) {
        case 1:
            for (int i = 0; i < 3; i++) {
                community_cards[i].visible = true;
            }
            break;
        case 2:
            community_cards[3].visible = true;
            break;
        case 3: 
            community_cards[4].visible = true;
            break;
    }
}

void print_game_state() {
    clear_screen();
    printf("=== ТЕХАССКИЙ ХОЛДЕМ ===\n\n");
    
    set_color(COLOR_YELLOW);
    printf("Банк: %d\n", pot);
    reset_color();
    
    printf("Общие карты: ");
    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        if (community_cards[i].visible) {
            print_card(community_cards[i]);
            printf(" ");
        } else {
            printf("XX ");
        }
    }
    printf("\n\n");
    
    printf("Текущая ставка: %d\n\n", current_bet);
    
    for (int i = 0; i < num_players; i++) {
        if (i == current_player) {
            set_color(COLOR_GREEN);
        }
        
        printf("%s: %d фишек | Ставка: %d | ", players[i].name, players[i].chips, players[i].current_bet);
        
        if (players[i].folded) {
            printf("Фолд");
        } else if (players[i].all_in) {
            set_color(COLOR_PURPLE);
            printf("ВА-БАНК!");
            reset_color();
            if (i == current_player) set_color(COLOR_GREEN);
        } else {
            printf("В игре");
        }
        
        printf(" | Карты: ");
        print_hand(players[i].hand, current_player != i);
        
        if (i == dealer_pos) printf(" (D)");
        if (i == small_blind_pos) printf(" (SB)");
        if (i == big_blind_pos) printf(" (BB)");
        
        printf("\n");
        reset_color();
    }
    printf("\n");
}


void place_bet(int player_idx, int amount) {
    if (amount > players[player_idx].chips) {
        amount = players[player_idx].chips;
    }
    
    players[player_idx].chips -= amount;
    players[player_idx].current_bet += amount;
    pot += amount;
    
    if (players[player_idx].current_bet > current_bet) {
        current_bet = players[player_idx].current_bet;
    }
    
    if (players[player_idx].chips == 0) {
        players[player_idx].all_in = true;
    }
}

void player_turn(int player_idx) {
    if (players[player_idx].folded || players[player_idx].all_in) {
        return;
    }
    
    current_player = player_idx;
    print_game_state();
    
    bool can_check = (players[player_idx].current_bet == current_bet);
    int call_amount = current_bet - players[player_idx].current_bet;
    
    printf("\nХод %s\n", players[player_idx].name);
    printf("1. %s\n", can_check ? "Чек" : "Фолд");
    printf("2. Колл (%d)\n", call_amount);
    printf("3. Повысить\n");
    printf("4. Ва-банк (%d)\n", players[player_idx].chips);

    int choice;
    if (scanf("%d", &choice) != 1) {
    printf("Неверный ввод. Попробуйте снова.\n");
    while (getchar() != '\n');
    player_turn(player_idx);
    return;
}
    
    switch (choice) {
        case 1:
            if (can_check) {
                printf("%s чек\n", players[player_idx].name);
            } else {
                printf("%s фолд\n", players[player_idx].name);
                players[player_idx].folded = true;
            }
            break;
        case 2:
            place_bet(player_idx, call_amount);
            printf("%s колл %d\n", players[player_idx].name, call_amount);
            break;
        case 3:
            {
                int raise_amount;
                printf("Введите сумму повышения: ");
                scanf("%d", &raise_amount);
                int total_bet = players[player_idx].current_bet + raise_amount;
                if (total_bet <= current_bet) {
                    printf("Повышение должно быть больше текущей ставки (%d)\n", current_bet);
                    player_turn(player_idx);
                    return;
                }
                place_bet(player_idx, total_bet - players[player_idx].current_bet);
                printf("%s повышает до %d\n", players[player_idx].name, total_bet);
            }
            break;
        case 4:
            place_bet(player_idx, players[player_idx].chips);
            printf("%s идет ва-банк на %d!\n", players[player_idx].name, players[player_idx].chips + players[player_idx].current_bet);
            break;
        default:
            printf("Неверный выбор\n");
            player_turn(player_idx);
    }
}


void ai_turn(int player_idx) {
    if (players[player_idx].folded || players[player_idx].all_in) {
        return;
    }
    
    current_player = player_idx;
    print_game_state();
    

    bool can_check = (players[player_idx].current_bet == current_bet);
    int call_amount = current_bet - players[player_idx].current_bet;
    int chips_left = players[player_idx].chips;
    

    HandValue hand_value;
    evaluate_hand(players[player_idx].hand, community_cards, &hand_value);
    

    double hand_strength = (double)hand_value.rank / (double)ROYAL_FLUSH;
    double pot_odds = (double)call_amount / (double)(pot + call_amount);
    

    Sleep(1000 + rand() % 2000);
    

    if (can_check) {
        if (hand_strength > 0.7 || (hand_strength > 0.4 && rand() % 100 < 30)) {
            int raise_amount = (int)(players[player_idx].chips * (0.2 + (hand_strength - 0.5) * 0.5));
            raise_amount = (raise_amount / SMALL_BLIND) * SMALL_BLIND;
            if (raise_amount < SMALL_BLIND * 2) raise_amount = SMALL_BLIND * 2;
            
            int total_bet = players[player_idx].current_bet + raise_amount;
            place_bet(player_idx, raise_amount);
            printf("%s повышает до %d\n", players[player_idx].name, total_bet);
        } else {
            printf("%s чек\n", players[player_idx].name);
        }
    } else {
        if (hand_strength > pot_odds * 1.5 || hand_strength > 0.6) {
            if (hand_strength > 0.8 && rand() % 100 < 80) {
                place_bet(player_idx, players[player_idx].chips);
                printf("%s идет ва-банк на %d!\n", players[player_idx].name, players[player_idx].chips + players[player_idx].current_bet);
            } else if (hand_strength > 0.6 || call_amount < players[player_idx].chips / 3) {
                place_bet(player_idx, call_amount);
                printf("%s колл %d\n", players[player_idx].name, call_amount);
            } else {
                printf("%s фолд\n", players[player_idx].name);
                players[player_idx].folded = true;
            }
        } else {
            printf("%s фолд\n", players[player_idx].name);
            players[player_idx].folded = true;
        }
    }
}


void betting_round() {
    int start_pos = (dealer_pos + 1) % num_players;
    int active_players = 0;
    int last_raiser = -1; 
    int statplayers = num_players -  fallplayers;    

    for (int i = 0; i < num_players; i++) {
        if (!players[i].folded && !players[i].all_in) {
            active_players++;
        }
    }

    int current_pos = start_pos;
    int players_acted = 0;
    bool betting_complete = false;
    
    while (players_acted < statplayers) {
        if (!players[current_pos].folded && !players[current_pos].all_in) {
            if (players[current_pos].is_ai) {
                ai_turn(current_pos);
            } else {
                player_turn(current_pos);
            }
            players_acted++;
            

            if (players[current_pos].current_bet > current_bet) {
                last_raiser = current_pos;
                players_acted = 0;
            }
            
            if (players[current_pos].folded || players[current_pos].all_in) {
                fallplayers+=1;
                active_players--;
            }
        }
        
        if (active_players <= 1) {
            betting_complete = true;
        } else if (players_acted > 0 && current_pos == last_raiser) {
            betting_complete = true;
        }
        
        current_pos = (current_pos + 1) % num_players;
    }
    

    for (int i = 0; i < num_players; i++) {
        players[i].current_bet = 0;
    }
    current_bet = 0;
}

void next_round() {

    int active_players = 0;
    for (int i = 0; i < num_players; i++) {
        if (!players[i].folded) {
            active_players++;
        }
    }
    
    if (active_players < 2) {
        determine_winner();
        return;
    }
    
    game_round++;
    if (game_round > 3) {
        determine_winner();
        return;
    }
    
    reveal_community_cards();
    betting_round();
}

void start_hand() {
    game_round = 0;

    for (int i = 0; i < num_players; i++) {
        players[i].folded = false;
        players[i].all_in = false;
        players[i].current_bet = 0;
    }
    pot = 0;
    current_bet = 0;
    
    dealer_pos = (dealer_pos + 1) % num_players;
    small_blind_pos = (dealer_pos + 1) % num_players;
    big_blind_pos = (dealer_pos + 2) % num_players;
    
    init_deck();
    shuffle_deck();
    deal_cards();
    
    place_bet(small_blind_pos, SMALL_BLIND);
    place_bet(big_blind_pos, SMALL_BLIND * 2);
    current_bet = SMALL_BLIND * 2;
    
    current_player = (big_blind_pos + 1) % num_players;
    
    betting_round();
    
    while (game_round < 3) {
        next_round();
    }
    
    determine_winner();
}
void print_hand_rank(HandRank rank) {
    switch (rank) {
        case HIGH_CARD: printf("Старшая карта"); break;
        case PAIR: printf("Пара"); break;
        case TWO_PAIR: printf("Две пары"); break;
        case THREE_OF_A_KIND: printf("Тройка"); break;
        case STRAIGHT: printf("Стрит"); break;
        case FLUSH: printf("Флеш"); break;
        case FULL_HOUSE: printf("Фулл-хаус"); break;
        case FOUR_OF_A_KIND: printf("Каре"); break;
        case STRAIGHT_FLUSH: printf("Стрит-флеш"); break;
        case ROYAL_FLUSH: printf("Роял-флеш"); break;
    }
}

int count_rank(Card *cards, int num_cards, int rank) {
    int count = 0;
    for (int i = 0; i < num_cards; i++) {
        if (cards[i].rank == rank) count++;
    }
    return count;
}

int count_suit(Card *cards, int num_cards, int suit) {
    int count = 0;
    for (int i = 0; i < num_cards; i++) {
        if (cards[i].suit == suit) count++;
    }
    return count;
}

int compare_cards(const void *a, const void *b) {
    Card *cardA = (Card *)a;
    Card *cardB = (Card *)b;
    return cardB->rank - cardA->rank;
}

void evaluate_hand(Card hand[NUM_HAND_CARDS], Card community[NUM_COMMUNITY_CARDS], HandValue *result) {
    Card all_cards[NUM_HAND_CARDS + NUM_COMMUNITY_CARDS];
    int num_visible_community = 0;
    

    memcpy(all_cards, hand, sizeof(Card) * NUM_HAND_CARDS);
    
    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        if (community[i].visible) {
            all_cards[NUM_HAND_CARDS + num_visible_community++] = community[i];
        }
    }
    
    int num_cards = NUM_HAND_CARDS + num_visible_community;
    if (num_cards < 5) {
        result->rank = HIGH_CARD;
        result->kickers[0] = hand[0].rank;
        result->kickers[1] = hand[1].rank;
        return;
    }
    
    qsort(all_cards, num_cards, sizeof(Card), compare_cards);
    
    bool flush = false;
    int flush_suit = -1;
    

    for (int s = 0; s < NUM_SUITS; s++) {
        if (count_suit(all_cards, num_cards, s) >= 5) {
            flush = true;
            flush_suit = s;
            break;
        }
    }
    
    bool straight = false;
    int straight_high = -1;
    
    for (int i = 0; i <= num_cards - 5; i++) {
        bool is_straight = true;
        for (int j = 1; j < 5; j++) {
            if (all_cards[i].rank - all_cards[i + j].rank != j) {
                is_straight = false;
                break;
            }
        }
        
        if (is_straight) {
            straight = true;
            straight_high = all_cards[i].rank;
            break;
        }
    }
    
    if (!straight) {
        bool low_straight = true;
        for (int r = 12; r >= 8; r--) {
            bool found = false;
            for (int i = 0; i < num_cards; i++) {
                if (all_cards[i].rank == r % NUM_RANKS) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                low_straight = false;
                break;
            }
        }
        if (low_straight) {
            straight = true;
            straight_high = 3;
        }
    }
    
    if (flush && straight) {
        Card flush_cards[NUM_CARDS];
        int num_flush_cards = 0;
        
        for (int i = 0; i < num_cards; i++) {
            if (all_cards[i].suit == flush_suit) {
                flush_cards[num_flush_cards++] = all_cards[i];
            }
        }
        
        bool straight_flush = false;
        int sf_high = -1;
        
        for (int i = 0; i <= num_flush_cards - 5; i++) {
            bool is_straight = true;
            for (int j = 1; j < 5; j++) {
                if (flush_cards[i].rank - flush_cards[i + j].rank != j) {
                    is_straight = false;
                    break;
                }
            }
            
            if (is_straight) {
                straight_flush = true;
                sf_high = flush_cards[i].rank;
                break;
            }
        }
        

        if (straight_flush && sf_high == 12) { 
            result->rank = ROYAL_FLUSH;
            return;
        }
        
        if (straight_flush) {
            result->rank = STRAIGHT_FLUSH;
            result->kickers[0] = sf_high;
            return;
        }
    }
    
    for (int r = 0; r < NUM_RANKS; r++) {
        if (count_rank(all_cards, num_cards, r) == 4) {
            result->rank = FOUR_OF_A_KIND;
            result->kickers[0] = r;

            for (int i = 0; i < num_cards; i++) {
                if (all_cards[i].rank != r) {
                    result->kickers[1] = all_cards[i].rank;
                    break;
                }
            }
            return;
        }
    }
    

    bool three = false;
    int three_rank = -1;
    bool two = false;
    int two_rank = -1;
    
    for (int r = 0; r < NUM_RANKS; r++) {
        int count = count_rank(all_cards, num_cards, r);
        if (count == 3) {
            if (!three) {
                three = true;
                three_rank = r;
            } else {
                two = true;
                two_rank = r;
            }
        } else if (count == 2) {
            two = true;
            two_rank = r;
        }
    }
    
    if (three && two) {
        result->rank = FULL_HOUSE;
        result->kickers[0] = three_rank;
        result->kickers[1] = two_rank;
        return;
    }

    if (flush) {
        result->rank = FLUSH;
        
        int kicker_idx = 0;
        for (int i = 0; i < num_cards && kicker_idx < 5; i++) {
            if (all_cards[i].suit == flush_suit) {
                result->kickers[kicker_idx++] = all_cards[i].rank;
            }
        }
        return;
    }
    
    if (straight) {
        result->rank = STRAIGHT;
        result->kickers[0] = straight_high;
        return;
    }
    
    if (three) {
        result->rank = THREE_OF_A_KIND;
        result->kickers[0] = three_rank;
        
        int kicker_idx = 1;
        for (int i = 0; i < num_cards && kicker_idx < 3; i++) {
            if (all_cards[i].rank != three_rank) {
                result->kickers[kicker_idx++] = all_cards[i].rank;
            }
        }
        return;
    }
    
    int pair_count = 0;
    int pair_ranks[2] = {-1, -1};
    int kicker = -1;
    
    for (int r = 0; r < NUM_RANKS; r++) {
        if (count_rank(all_cards, num_cards, r) == 2) {
            if (pair_count < 2) {
                pair_ranks[pair_count++] = r;
            } else if (r > pair_ranks[0] || r > pair_ranks[1]) {
                if (pair_ranks[0] < pair_ranks[1]) {
                    pair_ranks[0] = r;
                } else {
                    pair_ranks[1] = r;
                }
            }
        }
    }
    
    if (pair_count >= 2) {
        result->rank = TWO_PAIR;
        result->kickers[0] = pair_ranks[0] > pair_ranks[1] ? pair_ranks[0] : pair_ranks[1];
        result->kickers[1] = pair_ranks[0] > pair_ranks[1] ? pair_ranks[1] : pair_ranks[0];
        
        for (int i = 0; i < num_cards; i++) {
            if (all_cards[i].rank != pair_ranks[0] && all_cards[i].rank != pair_ranks[1]) {
                result->kickers[2] = all_cards[i].rank;
                break;
            }
        }
        return;
    }
    
    if (pair_count == 1) {
        result->rank = PAIR;
        result->kickers[0] = pair_ranks[0];
        
        int kicker_idx = 1;
        for (int i = 0; i < num_cards && kicker_idx < 4; i++) {
            if (all_cards[i].rank != pair_ranks[0]) {
                result->kickers[kicker_idx++] = all_cards[i].rank;
            }
        }
        return;
    }
    
    result->rank = HIGH_CARD;
    for (int i = 0; i < 5 && i < num_cards; i++) {
        result->kickers[i] = all_cards[i].rank;
    }
}

int compare_hands(const void *a, const void *b) {
    const HandValue *handA = (const HandValue *)a;
    const HandValue *handB = (const HandValue *)b;
    
    if (handA->rank != handB->rank) {
        return handB->rank - handA->rank;
    }
    
    for (int i = 0; i < NUM_HAND_CARDS; i++) {
        if (handA->kickers[i] != handB->kickers[i]) {
            return handB->kickers[i] - handA->kickers[i];
        }
    }
    
    return 0;
}

void determine_winner() {
    clear_screen();
    printf("=== ШОУДАУН ===\n\n");
    
    printf("Общие карты: ");
    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        community_cards[i].visible = true;
        print_card(community_cards[i]);
        printf(" ");
    }
    printf("\n\n");
    
    HandValue hand_values[MAX_PLAYERS];
    int active_players = 0;
    int active_player_indices[MAX_PLAYERS];
    
    for (int i = 0; i < num_players; i++) {
        if (!players[i].folded) {
            evaluate_hand(players[i].hand, community_cards, &hand_values[active_players]);
            active_player_indices[active_players] = i;
            active_players++;
            
            printf("%s: ", players[i].name);
            print_hand(players[i].hand, false);
            printf(" - ");
            print_hand_rank(hand_values[i].rank);
            printf("\n");
        }
    }
    
    for (int i = 0; i < active_players; i++) {
        for (int j = i + 1; j < active_players; j++) {
            if (compare_hands(&hand_values[i], &hand_values[j]) > 0) {
                HandValue temp_val = hand_values[i];
                hand_values[i] = hand_values[j];
                hand_values[j] = temp_val;
                
                int temp_idx = active_player_indices[i];
                active_player_indices[i] = active_player_indices[j];
                active_player_indices[j] = temp_idx;
            }
        }
    }
    
    printf("\nПобедители:\n");
    int winners = 1;
    
    for (int i = 1; i < active_players; i++) {
        if (compare_hands(&hand_values[0], &hand_values[i]) == 0) {
            winners++;
        } else {
            break;
        }
    }
    
    int win_amount = pot / winners;
    int remainder = pot % winners;
    
    for (int i = 0; i < winners; i++) {
        int player_idx = active_player_indices[i];
        players[player_idx].chips += win_amount + (i == 0 ? remainder : 0);
        
        printf("%s выигрывает %d фишек с комбинацией ", players[player_idx].name, win_amount + (i == 0 ? remainder : 0));
        print_hand_rank(hand_values[i].rank);
        printf("\n");
    }
    
    pot = 0;
}



void add_player(const char *name, bool is_ai) {
    if (num_players >= MAX_PLAYERS) return;
    
    strcpy(players[num_players].name, name);
    players[num_players].chips = START_CHIPS;
    players[num_players].folded = false;
    players[num_players].all_in = false;
    players[num_players].is_ai = is_ai;
    num_players++;
}

int main() {
    system("chcp 65001");
    system("cls");
    srand(time(NULL));
    
    printf("=== ТЕХАССКИЙ ХОЛДЕМ ===\n\n");
    
    int human_players, ai_players;
    printf("Введите количество реальных игроков (1-%d): ", MAX_PLAYERS);
    scanf("%d", &human_players);
    
    printf("Введите количество AI игроков (0-%d): ", MAX_PLAYERS - human_players);
    scanf("%d", &ai_players);
    
    if (human_players + ai_players < 2 || human_players + ai_players > MAX_PLAYERS) {
        printf("Неверное количество игроков. Должно быть от 2 до %d.\n", MAX_PLAYERS);
        return 1;
    }
    
    for (int i = 0; i < human_players; i++) {
        char name[50];
        printf("Введите имя игрока %d: ", i+1);
        scanf("%s", name);
        add_player(name, false);
    }
    
    const char *ai_names[] = {"AI-Джон", "AI-Майк", "AI-Дэйв", "AI-Сара", "AI-Эми", "AI-Пол", "AI-Том", "AI-Джек"};
    
    for (int i = 0; i < ai_players; i++) {
        add_player(ai_names[i % (sizeof(ai_names)/sizeof(ai_names[0]))], true);
    }
    
    while (1) {
        start_hand();
        
        for (int i = 0; i < num_players; i++) {
            if (players[i].chips <= 0) {
                printf("%s выбывает из игры!\n", players[i].name);
                
                for (int j = i; j < num_players - 1; j++) {
                    players[j] = players[j + 1];
                }
                num_players--;
                i--; 
            }
        }
        
        if (num_players == 1) {
            printf("\n=== ИГРА Окончена");
            printf("%s побеждает в игре!\n", players[0].name);
            break;
        }
        fallplayers = 0;
        printf("\nНажмите Enter для следующей раздачи...");
        getchar(); getchar();
    }
 return 0;
}
