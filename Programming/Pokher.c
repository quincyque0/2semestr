#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Масти карт
typedef enum {
    HEARTS,   // Червы
    DIAMONDS, // Бубны
    CLUBS,    // Трефы
    SPADES,   // Пики
    NUM_SUITS
} Suit;

// Достоинства карт
typedef enum {
    TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE,
    NUM_RANKS
} Rank;

// Структура карты
typedef struct {
    Suit suit;
    Rank rank;
} Card;

// Колода карт
Card deck[52];
int deck_size = 52;

// Рука игрока (5 карт)
Card hand[5];

// Инициализация колоды
void init_deck() {
    int i = 0;
    for (Suit s = HEARTS; s < NUM_SUITS; s++) {
        for (Rank r = TWO; r < NUM_RANKS; r++) {
            deck[i].suit = s;
            deck[i].rank = r;
            i++;
        }
    }
}

// Перемешивание колоды
void shuffle_deck() {
    srand(time(NULL));
    for (int i = 0; i < deck_size; i++) {
        int j = rand() % deck_size;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Раздача карт
void deal_hand() {
    for (int i = 0; i < 5; i++) {
        hand[i] = deck[i];
    }
    // "Удаляем" разданные карты из колоды
    for (int i = 0; i < deck_size - 5; i++) {
        deck[i] = deck[i + 5];
    }
    deck_size -= 5;
}

// Печать карты
void print_card(Card c) {
    const char *suits[] = {"♥", "♦", "♣", "♠"};
    const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", 
                          "J", "Q", "K", "A"};
    
    printf("%s%s", ranks[c.rank - 2], suits[c.suit]);
}

// Печать руки
void print_hand() {
    printf("Ваша рука: ");
    for (int i = 0; i < 5; i++) {
        print_card(hand[i]);
        printf(" ");
    }
    printf("\n");
}

// Определение комбинации
const char* evaluate_hand() {
    int ranks[15] = {0}; // Счетчик рангов (индекс 2-14)
    int suits[4] = {0};  // Счетчик мастей
    
    // Подсчет рангов и мастей
    for (int i = 0; i < 5; i++) {
        ranks[hand[i].rank]++;
        suits[hand[i].suit]++;
    }
    
    // Проверка комбинаций
    int pairs = 0, three = 0, four = 0;
    int flush = 0, straight = 0;
    
    // Проверка на пары, тройки, каре
    for (int i = 2; i <= 14; i++) {
        if (ranks[i] == 2) pairs++;
        if (ranks[i] == 3) three++;
        if (ranks[i] == 4) four++;
    }
    
    // Проверка на флеш (5 одной масти)
    for (int i = 0; i < 4; i++) {
        if (suits[i] == 5) flush = 1;
    }
    
    // Проверка на стрит (5 подряд)
    int count = 0;
    for (int i = 2; i <= 14; i++) {
        if (ranks[i] > 0) {
            count++;
            if (count == 5) straight = 1;
        } else {
            count = 0;
        }
    }
    
    // Специальный случай для стрита от туза до пятерки
    if (ranks[14] && ranks[2] && ranks[3] && ranks[4] && ranks[5]) {
        straight = 1;
    }
    
    // Определение комбинации
    if (straight && flush) {
        // Проверка на стрит-флеш от десятки до туза
        if (ranks[10] && ranks[11] && ranks[12] && ranks[13] && ranks[14]) {
            return "РОЯЛ-ФЛЕШ!!!";
        }
        return "СТРИТ-ФЛЕШ!";
    }
    if (four) return "КАРЕ";
    if (three && pairs) return "ФУЛЛ-ХАУС";
    if (flush) return "ФЛЕШ";
    if (straight) return "СТРИТ";
    if (three) return "ТРОЙКА";
    if (pairs == 2) return "ДВЕ ПАРЫ";
    if (pairs == 1) return "ПАРА";
    
    // Если ничего не найдено, возвращаем старшую карту
    for (int i = 14; i >= 2; i--) {
        if (ranks[i]) {
            if (i == 14) return "ТУЗ";
            if (i == 13) return "КОРОЛЬ";
            if (i == 12) return "ДАМА";
            if (i == 11) return "ВАЛЕТ";
            return "СТАРШАЯ КАРТА";
        }
    }
    
    return "НЕТ КОМБИНАЦИИ";
}

int main() {
    init_deck();
    shuffle_deck();
    deal_hand();
    print_hand();
    
    const char *combination = evaluate_hand();
    printf("У вас: %s\n", combination);
    
    return 0;
}