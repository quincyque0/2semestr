#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NUM_PLAYERS 3
#define NUM_CARDS 52
#define COMMUNITY_CARDS 5
#define HAND_SIZE 2

// Массивы для отображения карт
const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const char *suits[] = {"♥", "♦", "♣", "♠"};

// Структура карты
typedef struct {
    int rank;
    int suit;
    bool dealt;
} Card;

// Структура игрока
typedef struct {
    Card hand[HAND_SIZE];
    int chips;
    bool folded;
    bool is_ai;
} Player;

// Глобальные переменные
Card deck[NUM_CARDS];
Player players[NUM_PLAYERS];
Card community[COMMUNITY_CARDS];
int pot = 0;
int current_bet = 0;
int dealer = 0;

// Инициализация колоды
void init_deck() {
    for (int i = 0; i < NUM_CARDS; i++) {
        deck[i].rank = i % 13;
        deck[i].suit = i / 13;
        deck[i].dealt = false;
    }
}

// Перемешивание колоды
void shuffle_deck() {
    srand(time(NULL));
    for (int i = 0; i < NUM_CARDS; i++) {
        int j = rand() % NUM_CARDS;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Раздача карт
void deal_hand() {
    int card_index = 0;
    
    // Раздаем карты игрокам
    for (int i = 0; i < HAND_SIZE; i++) {
        for (int j = 0; j < NUM_PLAYERS; j++) {
            while (deck[card_index].dealt) card_index++;
            players[j].hand[i] = deck[card_index];
            deck[card_index].dealt = true;
            card_index++;
        }
    }
    
    // Раздаем общие карты
    for (int i = 0; i < COMMUNITY_CARDS; i++) {
        while (deck[card_index].dealt) card_index++;
        community[i] = deck[card_index];
        deck[card_index].dealt = true;
        card_index++;
    }
}

// Отображение карты
void print_card(Card card) {
    printf("%s%s ", ranks[card.rank], suits[card.suit]);
}

// Отображение руки игрока
void print_player_hand(int player_index) {
    printf("Игрок %d: ", player_index + 1);
    for (int i = 0; i < HAND_SIZE; i++) {
        print_card(players[player_index].hand[i]);
    }
    printf("\n");
}

// Отображение общих карт
void print_community_cards(int round) {
    printf("Общие карты: ");
    for (int i = 0; i < round; i++) {
        print_card(community[i]);
    }
    printf("\n");
}

// Логика ИИ для принятия решений
int ai_decision(int player_index) {
    // Простая логика ИИ
    if (rand() % 100 < 30) {
        return 1; // Колл
    } else if (rand() % 100 < 10) {
        return 2; // Повышение
    } else {
        return 0; // Фолд
    }
}

// Игровой раунд
void play_round() {
    int current_player = (dealer + 1) % NUM_PLAYERS;
    int round_bet = 0;
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (!players[i].folded) {
            printf("\nХод игрока %d\n", i + 1);
            print_player_hand(i);
            print_community_cards(3); // Показываем флоп
            
            int decision;
            if (players[i].is_ai) {
                decision = ai_decision(i);
            } else {
                printf("Выберите действие:\n");
                printf("0 - Фолд\n1 - Колл (%d)\n2 - Повышение\n", current_bet);
                scanf("%d", &decision);
            }
            
            switch (decision) {
                case 0: // Фолд
                    players[i].folded = true;
                    printf("Игрок %d сбрасывает карты\n", i + 1);
                    break;
                case 1: // Колл
                    players[i].chips -= current_bet;
                    pot += current_bet;
                    printf("Игрок %d делает колл\n", i + 1);
                    break;
                case 2: // Повышение
                    players[i].chips -= (current_bet + 10);
                    pot += (current_bet + 10);
                    current_bet = (current_bet + 10);
                    printf("Игрок %d повышает ставку до %d\n", i + 1, (current_bet + 10));
                    break;
            }
        }
    }
}

// Определение победителя (упрощенная версия)
void determine_winner() {
    // В реальной игре здесь была бы сложная логика сравнения комбинаций
    printf("\n--- Результаты раунда ---\n");
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (!players[i].folded) {
            printf("Игрок %d побеждает и забирает банк %d!\n", i + 1, pot);
            players[i].chips += pot;
        }
    }
    
    pot = 0;
    current_bet = 0;
}

// Основная функция
int main() {
    // Инициализация игроков
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].chips = 1000;
        players[i].folded = false;
        players[i].is_ai = (i != 0); // Первый игрок - человек, остальные ИИ
    }
    
    while (1) {
        // Подготовка нового раунда
        printf("\n=== НОВЫЙ РАУНД ===\n");
        
        init_deck();
        shuffle_deck();
        deal_hand();
        
        // Сброс состояний игроков
        for (int i = 0; i < NUM_PLAYERS; i++) {
            players[i].folded = false;
        }
        
        // Игровой процесс
        play_round();
        determine_winner();
        
        // Смена дилера
        dealer = (dealer + 1) % NUM_PLAYERS;
        
        // Проверка условий окончания игры
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (players[i].chips <= 0) {
                printf("Игрок %d выбывает из игры!\n", i + 1);
                return 0;
            }
        }
        
        // Пауза перед следующим раундом
        printf("\nНажмите Enter для продолжения...");
        getchar();
        getchar();
    }
    
    return 0;
}