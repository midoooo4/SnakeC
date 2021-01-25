
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////Created by:   -Mohamed IBOURK       /////////////Framed by:-M.SAFSOUF Yassine//////////////////////
/////////////////    -Nizar MORSLI         //////////////////////////////////////////////////////////////
/////////////////    -Abdelmalek MEJBAR    /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define L 20
#define C 50
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int gameover,score=0,highScore,fruitx,fruity,move,TailX[1000],TailY[1000],tail_cmpt=0;
int x=L/2; //la ligne de depart
int y=C/2; //la colonne de depart
FILE *f;
void ResetScreenPosition() 
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);
}
void setup()
{
	int x,y,gameover,fruitx,fruity;
	gameover=0;
	f=fopen("Highscore.txt","r");
    fscanf(f,"%d",&highScore);
    fclose(f);
	ETI1:               //etiquete
	fruitx=1+rand()%18;   //Donner une valeur aléatoire pour le cordonne x du fruit
 	if(fruitx==0)       //Tester si la valeur donner n'est pas 0
	goto ETI1;
	ETI2:               //etiquete
	fruity=1+rand()%38;   //Donner une valeur aléatoire pour le cordonne y du fruit
	if(fruity==0)       //Tester si la valeur donner n'est pas 0
	goto ETI2;
}
void map()
{
int i,j,k;
    	
		for(i=0;i<=C;i++)
			{
			if(i==0)
			printf("%c",201);
				
			printf("%c",205);
			if(i==C)
			printf("%c",187);
			}
			printf("\n");
		for(i=0;i<=L;i++)
			{
		    printf("%c",186);
			    for(j=0;j<=C;j++)
				{
					if(j==C)
					printf(" %c\n",186);
					else 
					{
					if(i==x && j==y)
					printf("%c",254); //pour dessiner la tete du snake
					else if (i==fruitx && j==fruity)
					printf("%c",184);
					else
					{
					int temp=0;
					for(k=0;k<tail_cmpt;k++)//Pour dessiner la queu du snake
					  	{
						if(i==TailX[k] && j==TailY[k])
						{
						printf("%c",254);
						temp=1;
					    }
						}
						if(temp==0)
						printf(" ");
				     	}
				    }
				}
	    	}
	    for(i=0;i<=C;i++)
			{
			if(i==0)
				printf("%c",200);
				
			printf("%c",205);
			if(i==C)
				printf("%c",188);
			}
			printf("\n");
	printf(" Current score: %d   ",score); //Affichage du score actuelle
}
void input()
{
	if(kbhit())      //kbhit=utiliser pour determiner si une touche a ete presser ou non
	 {	
	  switch(getch())//getch c'est la touche qui a ete presser
	   {
	   	case 'z': move=1;break;
	   	case 's': move=2;break;
	   	case 'q': move=3;break;
	   	case 'd': move=4;break;
	   }
	 }
}
void action()
{
	  int i;
	  int prevX1=TailX[0];//on a initialiser la variable prevX (c'est l'ancien enplacement du snake) par la queu dans
	                     //ce cas la valeur est zero
	  int prevY1=TailY[0];
	  int prevX2,prevY2; //prevY2 et prevX2 c'est l'avant dernier emplacement du snake
	  TailX[0]=x;   //x et y son les cordonnee de la tete du snake
	  TailY[0]=y;
	  
	  for(i=1;i<tail_cmpt;i++)//La supression de la	queue
	  {
	  prevX2=TailX[i];
	  prevY2=TailY[i];
	  TailX[i]=prevX1;
	  TailY[i]=prevY1;
	  prevX1=prevX2;
	  prevY1=prevY2;
	  }
	  
	  
	  switch(move)   //Les direction 
	   {
	   	case 1: x--;break;
	   	case 2: x++;break;
	   	case 3: y--;break;
	   	case 4: y++;break;
	   	default:break;
	   }
	   if(x==fruitx && y==fruity)
	   {//changement de l'emplacement du fruit
	   Beep(750, 80);
	   ETI3:               
	   fruitx=rand()%18;   
 	   if(fruitx==0)      
	   goto ETI3;
	   ETI4:               
	   fruity=rand()%38;   
	   if(fruity==0)       
	   goto ETI4;
	   score+=5; //quand la tete de snake passe sur le fruit le score augmente
	   tail_cmpt++;//on augmente le compteur de la taille du snake avec 1
       }
       if(x<0 || x>L || y<0 || y>C) //condition si le snake a toucher Le cadre
	   {
	   printf("\a");
	   gameover=1;
	   Sleep(1000);
	   system("cls");
	   printf("\tGameOver Hahahaha\n");
	   Sleep(2000);       //pause de 2 sec
	   if(score>highScore)
			      {
				  Sleep(1000); //pause d'une sec
			      system("cls");
                  printf(" \nCongratulation New HighScore %d!!\n\n",score);    
                  f=fopen("Highscore.txt","w");
                  fprintf(f,"%d",score);
                  fclose(f);
                  }
				  system("pause");
			      system("cls");
		   		
       }
	       for(i=0;i<tail_cmpt;i++)
	       	{
	       		if(x==TailX[i] && y==TailY[i]) //condition si le snake a toucher son corp
	       		{
	       		  gameover=1;
	       		  if(score>highScore)
			      {
				  Sleep(1000); //pause d'une sec
			      system("cls");
                  printf(" \nCongratulation New HighScore %d!!\n\n",score);    
                  f=fopen("Highscore.txt","w");
                  fprintf(f,"%d",score);
                  fclose(f);
                  }
	       		  printf("\a");
				  Sleep(6000);
			      system("cls");
		   		}	   		
	       	}	
}
int main(int argc, char *argv[]) {
	setup();               //Initialisation du jeu(Fichier highscore.txt l'emplacement des fruits...)
	while(!gameover)
	{
	map();                 //Dessiner la zone du jeu 
	ResetScreenPosition(); //Pour fixer la zone du jeu
	input();               //Le guidage du serpent
	action();              //Les action du serpent
	Sleep(100);            //La vitesse du jeu
    }
    return 0;
	
}
