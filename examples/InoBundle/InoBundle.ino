#include "Arduino.h"

//#include "DualFunctionButton.h"
#include "ArcadeBundle.h"
#include "Snake.h"
#include "Brick.h"
#include "Demo.h"

#include "Keyboard.h"
#include "xOS.h"

enum Game_t{
	GAME_SNAKE,
	GAME_BRICK,
	//GAME_INVADER, //not implemented yet
	//GAME_TETRIS,  //not implemented yet
	//GAME_SQUARE,  //not implemented yet
	GAME_DEMO,
	GAME_COUNT
};

void Task_Keyboard(void);
void Task_Game(void);
void Task_Screen(void);

Task_t TaskStruct[4];

Game* game = new Snake();
//Brick brick;
//Invader invader;		//not implemented yet
//Tetris tetris;		//not implemented yet
//Square square;		//not implemented yet
//Demo demo;			//not implemented yet

uint8_t currGame = GAME_SNAKE;

void setup() {
	AB_Setup();

	xInit(TaskStruct); 	//Struct with function parameters
	
	xTaskCreate(&Task_Keyboard, 10);
	xTaskCreate(&Task_Game, 10);
	xTaskCreate(&Task_Screen, 10);
}

void loop() {	
	xLoop();  //xOS task
}

void Task_Game(void){
	game->update();
}

void Task_Screen(void){
	AB_UpdateScreen();
}

void Task_Keyboard(void){
	KB_ReadAll();
	if(KB_IsKeyDownLong(VK_UP, 100)){	/* wait for 100ticks = 1000ms */
		AB_ClearDisplay();
		free(game);
		switch(++currGame) {	
			case GAME_SNAKE:
				game = new Snake();
				break;
			case GAME_BRICK:
				game = new Brick();
				break;
			case GAME_DEMO:
				game = new Demo();
				break;
			default:
				game = new Snake();
				currGame = 0;
				break;
		}
	}
}