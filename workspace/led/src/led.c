   __          _              _     _          _ 
  /__\ __ ___ | |__   ___  __| | __| | ___  __| |
 /_\| '_ ` _ \| '_ \ / _ \/ _` |/ _` |/ _ \/ _` |
//__| | | | | | |_) |  __/ (_| | (_| |  __/ (_| |
\__/|_| |_| |_|_.__/ \___|\__,_|\__,_|\___|\__,_|

///////////////////////////////////////////////////////////////////////
// Author: Clemens Maas                                              //
// Matrikelnummer: 1260892                                           //
///////////////////////////////////////////////////////////////////////
// Falls die ZIP nicht funktioniert, warum auch immer                //
//                                                                   //
// https://github.com/DubskySteam/embedded/tree/master/workspace/led //
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <time.h>

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_VAL 0x0
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_PUE 0x10
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38

#define SEQUENCE_MAX 20

// LEDS - VP-Redboard
#define GREEN_LED 18
#define BLUE_LED 21
#define YELLOW_LED 0
#define RED_LED 3
// // LEDS - HARDWARE
// #define GREEN_LED 2
// #define BLUE_LED 5
// #define YELLOW_LED 8
// #define RED_LED 11

// BUTTONS - VP-Redboard
#define GREEN_BTN 19
#define BLUE_BTN 20
#define YELLOW_BTN 1
#define RED_BTN 2
// // BUTTONS - HARDWARE
// #define GREEN_BTN 3
// #define BLUE_BTN 4
// #define YELLOW_BTN 9
// #define RED_BTN 10

// VARS
uint32_t level = 1;
uint32_t led_n = 3;
uint32_t led_t = 150000;
uint32_t sequence[SEQUENCE_MAX] = {-1};
uint32_t sequence_counter = 0;
uint32_t win = 0;
// TIMERS
const uint32_t T_SHORT = 250000;
const uint32_t T_LONG = 2 * T_SHORT;
const uint32_t T_VERY_LONG = 2 * T_LONG;

volatile void wait(const uint32_t timer) {
	for(volatile int i = 0; i < timer; i++) {}
}

typedef enum {
    STATE_STARTUP,
    STATE_IDLE,
    STATE_PREVIEW,
    STATE_PLAY,
    STATE_WIN,
    STATE_LOSE,
    STATE_END,
    STATE_SEPERATOR
} GameState;

// Globale Variablen
GameState currentState = STATE_STARTUP;
uint32_t sequence[SEQUENCE_MAX];
uint32_t sequenceLength = 0;
uint32_t currentLevel = 3;

// Prototypen der Funktionen
void setupHardware();
void processState();
void LoserMode();
void PreviewSequence();
void PlaySequence();
void ReadyMode();
void IdleMode();
void StartUp();
void WinMode();

// Hauptfunktion
int main(void) {
    setupHardware();
    while (1) {
        processState();
    }
    return 0;
}

void setupHardware() {
    // Initialisieren Sie hier LEDs und Tasten
    // SETUP LED'S
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << GREEN_LED);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << YELLOW_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << YELLOW_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1 << YELLOW_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << YELLOW_LED);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1 << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);

    // SETUP BUTTONS
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << GREEN_BTN);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << GREEN_BTN;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << GREEN_BTN;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << GREEN_BTN);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << GREEN_BTN);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << YELLOW_BTN);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << YELLOW_BTN;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << YELLOW_BTN;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << YELLOW_BTN);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << YELLOW_BTN);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_BTN);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << BLUE_BTN;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << BLUE_BTN;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << BLUE_BTN);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_BTN);

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << RED_BTN);
	REG(GPIO_BASE + GPIO_PUE) |= 1 << RED_BTN;
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << RED_BTN;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << RED_BTN);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << RED_BTN);
}

void changeState(GameState newState) {
    currentState = newState;
}

void processState() {
    switch (currentState) {
        case STATE_STARTUP:
            // Logik für den Startzustand
            StartUp();
            changeState(STATE_IDLE);
            break;
        case STATE_IDLE:
            // Logik für den Leerlaufzustand
            IdleMode();
            changeState(STATE_PREVIEW);
            break;
        case STATE_PREVIEW:
            // Logik für die Vorschau der Sequenz
            PreviewMode();
            PreviewSequence();
            changeState(STATE_PLAY);
            break;
        case STATE_PLAY:
            // Logik für das Abspielen der Sequenz
            PlaySequence();
            if (win == 0) {
                changeState(STATE_SEPERATOR);
            }
            else if (win == 1) {
                changeState(STATE_WIN);
            } else {
                changeState(STATE_LOSE);
            }
            break;
        case STATE_SEPERATOR:
            SeperatorSequence();
            changeState(STATE_PREVIEW);
            break;
        case STATE_WIN:
            // Logik für den Gewinnzustand
            win = 0;
            level = 1;
            led_n = 3;
            led_t = 150000;
            changeState(STATE_END);
            break;
        case STATE_LOSE:
            // Logik für den Verlustzustand
            LoserMode();
            changeState(STATE_IDLE);
            break;
        case STATE_END:
            // Logik für den Endzustand
            EndMode();
            changeState(STATE_IDLE);
            break;
        default:
            // Standardfall, falls nötig
            break;
    }
}

void LED_ON(const uint32_t led) {
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << led);
}

void LED_OFF(const uint32_t led) {
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << led);
}

void LED_ALL_OFF() {
	LED_OFF(YELLOW_LED);
	LED_OFF(RED_LED);
	LED_OFF(GREEN_LED);
	LED_OFF(BLUE_LED);
}

void LED_ALL_ON() {
	LED_ON(YELLOW_LED);
	LED_ON(RED_LED);
	LED_ON(GREEN_LED);
	LED_ON(BLUE_LED);
}

void LED_BLINK(const uint32_t led, const uint32_t delay) {
	LED_ON(led);
    wait(delay);
    LED_OFF(led);
    wait(delay);
}

uint32_t check_btn(const uint32_t btn) {
    if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << btn))){
        wait(10000);
        if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << btn))) {
            return 1;
        }
    }
	return 0;
}

uint32_t check_all_btn() {
	if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << GREEN_BTN))) {
		return GREEN_LED;
	} else if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << RED_BTN))) {
		return RED_LED;
	} else if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << BLUE_BTN))) {
		return BLUE_LED;
	} else if (!(REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << YELLOW_BTN))) {
		return YELLOW_LED;
	}
	return -1;
}

// Ich weiss nicht warum, aber auf Linux funktioniert es im Simulator.
// Unter Windows manchmal nicht?
void ShowBinaryLevel() {
    uint32_t binary[4] = {0};
    uint32_t tempLevel = level;

    // Berechnung der Binärdarstellung
    for (int i = 0; tempLevel > 0 && i < 4; i++) {
        binary[i] = tempLevel % 2;
        tempLevel /= 2;
    }

    // LEDs entsprechend der Binärdarstellung ein- oder ausschalten
    if (binary[0]) LED_ON(RED_LED); else LED_OFF(RED_LED);
    if (binary[1]) LED_ON(YELLOW_LED); else LED_OFF(YELLOW_LED);
    if (binary[2]) LED_ON(BLUE_LED); else LED_OFF(BLUE_LED);
    if (binary[3]) LED_ON(GREEN_LED); else LED_OFF(GREEN_LED);
}

void LoserMode() {
	for(int i = 0; i < 2; i++) {
        LED_ON(GREEN_LED);
        LED_ON(RED_LED);
        wait(T_SHORT);
        LED_OFF(GREEN_LED);
        LED_OFF(RED_LED);
        wait(T_SHORT);
	}
	ShowBinaryLevel();
	wait(T_VERY_LONG);
	LED_ALL_OFF();
}

//-----------------------------------------------------------------------
// AUSKOMMENTIERT -> srand() funktioniert auf dem Board anscheinend nicht
//-----------------------------------------------------------------------
// int getRandomLed() {
// 	srand(time(NULL));
//    	int num = (rand() % (4 + 1 - 1) + 1);
//     switch (num)
//     {
//     case 1:
//         return GREEN_LED;
//         break;
//     case 2:
//         return BLUE_LED;
//         break;
//     case 3:
//         return RED_LED;
//         break;
//     case 4:
//         return YELLOW_LED;
//         break;
//     default:
// 	return 0;
//         break;
//     }
// }

int getRandomLed() {
	uint32_t t = time(NULL);
	static unsigned int rand = 0;
	rand += t;
    rand %= 4;
	while(rand < 1){
        rand = rand + 3 - 1;
    }
    switch (rand)
    {
    case 1:
        return GREEN_LED;
        break;
    case 2:
        return BLUE_LED;
        break;
    case 3:
        return RED_LED;
        break;
    case 4:
        return YELLOW_LED;
        break;
    default:
	return 0;
        break;
    }
}

void addToSequence() {
	uint32_t led = getRandomLed();
	sequence[sequence_counter] = led;
	sequence_counter++;
	LED_BLINK(led, T_LONG);
}

void PreviewSequence() {
    for(int i = 0; i < led_n; i++) {
        addToSequence();
    }
	LED_ALL_ON();
	wait(T_SHORT);
	LED_ALL_OFF();
}

void PlaySequence() {
	for(int i = 0; i < sequence_counter; i++) {
		uint32_t btn = -1;
		while(btn == -1) {
			btn = check_all_btn();
		}
		if(btn == sequence[i]) {
			LED_ON(sequence[i]);
			wait(T_SHORT);
			LED_OFF(sequence[i]);
		} else {
			win = -1;
			break;
		}
	}
	sequence_counter = 0;
	for(int i = 0; i < SEQUENCE_MAX; i++) {
		sequence[i] = -1;
	}
}

void EndMode() {
	LED_ALL_ON();
	wait(T_SHORT);
	LED_ALL_OFF();
	wait(T_SHORT);
	LED_ALL_ON();
	wait(T_LONG);
	LED_ALL_OFF();
	wait(T_SHORT);
	LED_ALL_ON();
	wait(T_SHORT);
	LED_ALL_OFF();
	wait(T_SHORT);
	LED_ALL_ON();
	wait(T_LONG);
	LED_ALL_OFF();
}

void SeperatorSequence() {
    LED_ALL_OFF();
	for(int i = 0; i < 2; i++) {
		LED_ON(GREEN_LED);
		LED_ON(YELLOW_LED);
		wait(T_SHORT);
		LED_OFF(GREEN_LED);
		LED_OFF(YELLOW_LED);
		LED_ON(RED_LED);
		LED_ON(BLUE_LED);
		wait(T_SHORT);
		LED_OFF(RED_LED);
		LED_OFF(BLUE_LED);
	}

		level++;
        led_n++;
		if(level % 2 == 0) {
			led_t *= 0.9;
		}
        if(level > 10) {
			win = 1;
		}
}

void ReadyMode() {
	int cont = 0;
	while(cont == 0) {
		cont = check_btn(YELLOW_BTN);
	}
	LED_ON(YELLOW_LED);
	wait(T_LONG);
	LED_ALL_OFF();
}

void StartUp() {
	LED_ON(GREEN_LED);
	LED_ON(BLUE_LED);
	LED_ON(YELLOW_LED);
	LED_ON(RED_LED);
	wait(T_SHORT);
	LED_OFF(GREEN_LED);
	LED_OFF(BLUE_LED);
	LED_OFF(YELLOW_LED);
	LED_OFF(RED_LED);
	wait(T_SHORT);
}

void PreviewMode() {
    LED_ON(BLUE_LED);
    LED_ON(YELLOW_LED);
    wait(T_SHORT);
    LED_ALL_OFF();
    wait(T_SHORT);
}

void IdleMode() {
	uint32_t counter = 0;
	while(check_btn(GREEN_BTN) == 0) {
        if (counter == 0) {
            LED_ON(GREEN_LED);
            wait(T_SHORT);
            LED_OFF(GREEN_LED);
        }
        else if (counter == 1) {
            LED_ON(BLUE_LED);
            wait(T_SHORT);
            LED_OFF(BLUE_LED);
        }
        else if (counter == 2) {
            LED_ON(YELLOW_LED);
            wait(T_SHORT);
            LED_OFF(YELLOW_LED);
        }
        else if (counter == 3) {
            LED_ON(RED_LED);
            wait(T_SHORT);
            LED_OFF(RED_LED);
        }
        if (counter >= 3) {
            counter = 0;
        } else {
            counter++;
        }
	}
	LED_ALL_OFF();
}
