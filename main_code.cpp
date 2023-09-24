#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

char map[10][10];
char player = '^';
char tail = 'O';
char food = 'M';
int yFood, xFood;
int yPos = 5, xPos = 5;
int yTail[10], xTail[10]; 
int nTail = 2;
int maxTail = 10;
int score;

void generateMap(){
	int i, j;
	for(i = 0 ; i < 10 ; i++){
		for(j = 0 ; j < 10 ; j++){
			if(i == 0 || j == 0 || i == 9 || j == 9){
				map[i][j] = '*';
			} else {
				map[i][j] = ' ';
			}
		}
	}
	map[yPos][xPos] = player;
	map[yFood][xFood] = food;
	for(i = 0 ; i <= nTail ; i++){
		map[yTail[i]][xTail[i]] = tail;
	}
}

void displayMap(){
	int i, j;
	for(i = 0 ; i < 10 ; i++){
		for(j = 0 ; j < 10 ; j++){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("Score : %d\n", score);
}

void moveUp(){
	if(yPos - 1 > 0){
		yTail[0] = yPos;
		xTail[0] = xPos;
		yPos--;
	} else {
        yPos = 9;
    }
}

void moveLeft(){
	if(xPos - 1 > 0){
		yTail[0] = yPos;
		xTail[0] = xPos;
		xPos--;
	} else {
        xPos = 9;
    }
}

void moveDown(){
	if(yPos + 1 < 9){
		yTail[0] = yPos;
		xTail[0] = xPos;
		yPos++;
	} else {
        yPos = 0;
    }
}

void moveRight(){
	if(xPos + 1 < 9){
		yTail[0] = yPos;
		xTail[0] = xPos;
		xPos++;
	} else {
        xPos = 0;
    }
}

int checkCollision(){
    if(xPos == 0 || yPos == 0 || xPos == 9 || yPos == 9){
    	return 1;
	}
	
	for (int i = 1; i <= nTail; i++) {
        if (yPos == yTail[i] && xPos == xTail[i]) {
            return 1; 
        }
    }
    return 0;
}

int main(){
	score = 0;
	int i;
	time_t t;
	srand((unsigned) time(&t));
	yFood = rand() % 8 + 1;
	xFood = rand() % 8 + 1;
	yTail[0] = yPos + 1;
	xTail[0] = xPos;
	yTail[1] = yPos + 2;
	xTail[1] = xPos;
	do{
		system("cls");
		generateMap();
		displayMap();
		char command = _getch();
		switch(command){
			case 'w':{
				player = '^';
				moveUp();
				break;
			}
			case 'a':{
				player = '<';
				moveLeft();
				break;
			}
			case 's':{
				player = 'v';
				moveDown();
				break;
			}
			case 'd':{
				player = '>';
				moveRight();
				break;
			}
		}
		if (checkCollision()) {
            break;
        }
		if(yPos == yFood && xPos == xFood){
			map[yPos][xPos] = player;
			score++;
			if(nTail < 10){
				nTail++;
			}
			yFood = rand() % 8 + 1;
			xFood = rand() % 8 + 1;
		}
		for(i = 9 ; i > 0 ; i--){
			yTail[i] = yTail[i - 1];
			xTail[i] = xTail[i - 1];
		}
	} while (score < 10);
	
	if (checkCollision()) {
        	printf("Game Over! You hit your tail or border :(\n");
   	} else {
    		printf("CONGRATULATIONS!\n");
		printf("Your Score : %d\n", score-1);
	}
	
	return 0;
}
