#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<stdbool.h>
#define size_x 3
#define size_y 3


int minimax(int a[][3],int,bool);
void pmove(int a[][3]);
void cmove(int a[][3]);
int win(int a[][3]);
void screen(int a[][3]);
int min(int a,int b);
int max(int a,int b);
bool isEmpty(int a[][3]);
int main(){
	int a[3][3]={ {0,0,0},
	              {0,0,0},
                  {0,0,0}};
    int turn=0;
    int player=1;
    system("cls");
    printf("player X     computer O \n");
    printf("play first :1    play second :2\n");
    int check=0;
    while(check==0){
    	scanf("%d",&player);
    	if(player==1 || player==2){
    		check=1;
		}
	}
	screen(a);
    while(turn<9 && win(a)==0){
    	if((turn+player)%2==1){
    		pmove(a);
		}else{
			cmove(a);
		}
		screen(a);
		turn+=1;
	}
	
	if(win(a)==1){
		printf("you lose\n");
	}else if(win(a)==0){
		printf("draw\n");
	}else if(win(a)==-1){
		printf("you win\n");
	}
    
    
    printf("Do you want to play again?\n");
	printf("y    n\n");
    check=0;
	char replay;
	while(check==0){
		replay=getch();
		if(replay=='y' || replay=='n'){
			check=1;
		}
	}
	if(replay=='y'){
	   main();
	}else{
		return 0;
	}
    
    
}

void screen(int a[][3]){
	system("cls");
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(a[i][j]==0){
				printf(" -");
			}
			if(a[i][j]==1){
				printf(" O");
			}
			if(a[i][j]==-1){
				printf(" X");
			}
		}
		printf("\n");
	}
}

void pmove(int a[][3]){
	int place;
    int check=0;
    while(check==0){
    	scanf("%d",&place);
        place-=1;
    	if(a[place/3][place%3]==0 && place>=0 && place<9){
    		a[place/3][place%3]=-1;
    		check=1;
		}
	}
}

void cmove(int a[][3]){
	int move=-1;
	int score=-1000;
	int i;
	for(i=0;i<9;i++){
		if(a[i/3][i%3]==0){
			a[i/3][i%3]=1;
			int tmpscore=minimax(a,0,false);
			printf("%d\n",tmpscore);
			a[i/3][i%3]=0;
			if(tmpscore>score){
				score=tmpscore;
				move=i;
			}
		}
	}
	a[move/3][move%3]=1;
	getch();
}

int minimax(int a[][3],int depth,bool isMaximising){
	int bestscore;
	int tmpscore;
	int i,j;
	int move=-1;
	int winner=win(a);
	if(winner!=0){
		return winner*(10-depth);
	}
	if(isEmpty(a)==false){
		
		return 0;
	}
	if (isMaximising){
    	//if computer move
		bestscore=-1000000;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(a[i][j]==0 ){
				
					a[i][j]=1;
					tmpscore=minimax(a,depth+1,false);
					a[i][j]=0;
					bestscore=max(tmpscore,bestscore);

				}
			}
		}
		return bestscore;
	}else{
		bestscore=1000000;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(a[i][j]==0 ){
				
					a[i][j]=-1;
					tmpscore=minimax(a,depth+1,true);
					a[i][j]=0;
					bestscore=min(tmpscore,bestscore);

				}
			}
		}
		return bestscore;
	}
}

int win(int a[][3]){
	int i;
	for(i=0;i<3;i++){
		if(a[i][0]!=0 && a[i][0]==a[i][1] && a[i][0]==a[i][2]){
			return a[i][0];
		}
	}
	for(i=0;i<3;i++){
		if(a[0][i]!=0 && a[0][i]==a[1][i] && a[0][i]==a[2][i]){
			return a[0][i];
		}
	}
	if(a[0][0]!=0 && a[0][0]==a[1][1] && a[1][1]==a[2][2]){
		return a[0][0];
	}
	if(a[0][2]!=0 && a[0][2]==a[1][1] && a[1][1]==a[2][0]){
		return a[0][2];
	}
	return 0;
}


int max(int a,int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int min(int a,int b){
	if(a<b){
		return a;
	}else{
		return b;
	}
}

bool isEmpty(int a[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(a[i][j]==0){
				return true;
			}
		}
	}
	return false;
}
