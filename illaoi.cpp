#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	if size is not more than 25 and most importantly you are not printing the tower
	program finishes in less than 1 seconds
*/

int size;
char drawChar;

int *tower;
int *heights;

void initGame(){
	tower = (int*)calloc(size*3, sizeof(int));
	heights = (int*)calloc(size, sizeof(int));
	for (int i=0; i<size; i++){
		tower[i] = i+1;		
	}
	heights[0] = size;
}

void getCharUndSize(){
	printf("Enter a character: ");
	scanf("%c", &drawChar);
	
	printf("\nEnter tower size: ");
	scanf("%d", &size);
}

int get1dof2d(int w, int x, int y){
	return y*w + x;
}

void drawN(int n, int w){
	printf("|");
	if (n == 0){
		for (int i=0; i<w; i++){
			printf(" ");
		}
		printf("|");
		return;
	}
	int blockW = n*2-1;
	int lrWidth = (w - blockW)/2;
	for (int i=0; i<lrWidth; i++){
		printf(" ");
	}
	for (int i=0; i<blockW; i++){
		printf("%c", drawChar);
	}
	for (int i=0; i<lrWidth; i++){
		printf(" ");
	}
	printf("|");
}


void printTower(){
	for (int i=0; i<(size*2+1)*3 + 3*2; i++){
		printf("-");
	}
	printf("\n");
	for (int i=0; i<size; i++){
		for (int j=0; j<3; j++){
			drawN(tower[get1dof2d(size, i, j)], size*2+1);
		}
		printf("\n");
	}
	for (int i=0; i<(size*2+1)*3 + 3*2; i++){
		printf("-");
	}
	printf("\n");
}


void moveOne(int from, int to){
	tower[get1dof2d(size, size-heights[to]-1, to)] = tower[get1dof2d(size, size-heights[from], from)];
	tower[get1dof2d(size, size-heights[from], from)] = 0;
	heights[from] -= 1; heights[to] += 1;
}

int illaoi(int n, int from, int to, int left){
	static int a = 0;
	a += 1;
	if (n == 1){
		moveOne(from, to);
		printTower();
		return a;
	}
	
	illaoi(n-1, from, left, to);
	
	moveOne(from, to);
	
	printTower();
	
	illaoi(n-1, left, to, from);
	
	return a;
	
}

int main(){
	getCharUndSize();
	initGame();
	
	printTower();
	int n = illaoi(size, 0, 2, 1);
	
	printf("%d\n", n);
	
	return 0;
}
