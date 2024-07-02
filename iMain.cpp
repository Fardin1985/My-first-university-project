
# include "iGraphics.h"
# include <stdio.h>
# include <iostream>
# include <windows.h>
# include <mmsystem.h>
# include <stdlib.h>
# include <cmath>
# include <math.h> 
# include <fstream>
# include <vector>
# pragma comment(lib,"winmm.lib")

#define pi 3.14159265358;
#define g .4;

double t, x;
double bird_x = 100.00, bird_y = 90.00;
double angle, velocity;
double bird_ix = 100.00, bird_iy = 90.00;
int clickButton = -1;
int collisionA = 0, collisionB = 0, collisionC = 0;
int countA=1,countB=1,countC=1;
int count=0;
int PlayerScore=0;
double pig1_x = 940.00, pig1_y = 160.00;
int indexNumber=0;
char playername[100];
char scoreShow[10];
int p;
int flag = 1;
int m2x, m2y;
int t1=0,t2=0,t3=0;
int blue_x1,blue_x2,blue_x3;
int blue_y1,blue_y2,blue_y3;
double dotVelocity;
double dotAngle;
double dot_x,dot_ix=100;
double dot_y,dot_iy=90;
double dotT;
double launchAngle(int mx, int my);
double launchVelocity(int mx, int my);
void projectileMotion();
void Collision1();
void Collision2();
void Collision3();
void redBirdPlay();
void dotLine();
void restart();
void checkCollision();
void score();
void leaderboard();
void nameInput();
void showScore();
int  isFlying=0;
 int  isThree=0;
  int isSpeed=0;
  int music=0;
  int fardin=0;


/*
	function iDraw() is called again and again by the system.
*/
void dotLine(){
	if(flag==10 || flag==11 || flag==12){
		double vel = dotVelocity;
		double ang = dotAngle;
		dot_x=100;
		dot_y=90;
		dotT=0;
        while(dot_y>40){
			dot_x = dot_ix + vel*cos(ang)*dotT;
	        dot_y = dot_iy+vel*sin(ang)*dotT-6*dotT*dotT;
			iSetColor(0,0,0);
	        iPoint(dot_x+10,dot_y+10,1);
			dotT+=0.5;
		}
	}	   	
}
void restart(){
	isFlying=0;
	isThree=0;
	t=0;
	t1=0;
	t2=0;
	t3=0;
	bird_x=bird_ix;
	bird_y=bird_iy;
	iPauseTimer(x);

}
void score()
{
	FILE *fptr;
	char names[100][50];
	int HighScores[100];

	fptr = fopen("highscore.txt", "r");
	int i = 0;
	while (fscanf(fptr, "%s %d", names[i], &HighScores[i]) != EOF)
	{
		i++;
		if (i == 100)
			break;
	}
	fclose(fptr);

	// bubble sort diye data sorting
	for (int m = 0; m < i - 1; m++)
	{
		for (int n = 0; n < i - m - 1; n++)
		{
			if (HighScores[n] < HighScores[n + 1])
			{
				int tempScore = HighScores[n];
				HighScores[n] = HighScores[n + 1];
				HighScores[n + 1] = tempScore;
				char tempName[50];
				strcpy(tempName, names[n]);
				strcpy(names[n], names[n + 1]);
				strcpy(names[n + 1], tempName);
			}
		}
	}
	iSetColor(255, 255, 255);
	for (int j = 0; j < i && j < 5; j++)
	{
		iText(350, 395 - j * 55, names[j], GLUT_BITMAP_TIMES_ROMAN_24);
	}
	for (int j = 0; j < i && j < 5; j++)
	{

		char StrScore[10];
		sprintf(StrScore, "%d", HighScores[j]);
		iText(650, 395 - j * 55, StrScore, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
void leaderboard()
{
	FILE *fptr;
	char names[100][50];
	int HighScores[100];
	fptr = fopen("highscore.txt", "r");
	int i = 0;
	while (fscanf(fptr, "%s %d", names[i], &HighScores[i]) != EOF)
	{
		i++;
		if (i >= 100)
			break;
	} // now we have extracted score data from highscore file
	fclose(fptr);

	// new playername ar score ke add korbo
	int j;
	for (j = i - 1; j >= 0; j--)
	{
		if (PlayerScore > HighScores[j])
		{
			strcpy(names[j + 1], names[j]);
			HighScores[j + 1] = HighScores[j];
		}
		else
		{
			break;
		}
	}
	strcpy(names[j + 1], playername);
	HighScores[j + 1] = PlayerScore;

	// now we have our sorted arrays with the new score added
	// modified scoreboard ekhon txt file e push korbo
	fptr = fopen("highscore.txt", "w");
	for (int k = 0; k < i + 1 && k < 100; ++k)
	{
		fprintf(fptr, "%s %d\n", names[k], HighScores[k]);
	}
	fclose(fptr);
}
void showScore(){
	if(flag==10 || flag==11 || flag==12){
		iSetColor(0,0,0);
		sprintf(scoreShow," SCORE IS %d",PlayerScore);
		iText(100,480,scoreShow,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if(flag==6){
		iSetColor(0,0,0);
		sprintf(scoreShow," SCORE IS %d",PlayerScore);
		iText(444,320,scoreShow,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
void nameInput(){
	if(flag==6){
		iSetColor(255,255,255);
		iText(200,200,playername,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}	
void iDraw()
{
	// place your drawing codes here.

	if (flag == 1)
	{
		iClear();
		iShowBMP(0, 0, "image//start.bmp");
		iSetColor(0, 0, 0);
	}

	if (flag == 2)
	{
		iShowBMP(0, 0, "image//1.bmp");
		
		iSetColor(0, 255, 10);
		iFilledRectangle(100, 290, 194, 29);
		iFilledRectangle(100, 232, 194, 29);
		iFilledRectangle(100, 168, 194, 29);
		iFilledRectangle(103, 126, 194, 29);
		iSetColor(255, 0, 0);
		iText(160, 303, "NEW  GAME", GLUT_BITMAP_HELVETICA_18);
		iText(160, 245, "HIGH SCORE", GLUT_BITMAP_HELVETICA_18);
		iText(160, 182, "   EXIT", GLUT_BITMAP_HELVETICA_18);
		iText(160, 135, "  CREDITS ", GLUT_BITMAP_HELVETICA_18);
	}
	if (flag == 3)
	{
		iClear();
		iShowBMP(0, 0, "image//bck.bmp");
		iFilledRectangle(100, 290, 194, 29);
		iFilledRectangle(100, 232, 194, 29);
		iFilledRectangle(100, 168, 194, 29);
		iSetColor(255, 0, 0);
		iText(160, 303, "  RED BIRD ", GLUT_BITMAP_HELVETICA_18);
		iText(160, 245, "  BLUE BIRD", GLUT_BITMAP_HELVETICA_18);
		iText(160, 182, " YELLOW BIRD", GLUT_BITMAP_HELVETICA_18);
		iFilledRectangle(870, 450, 150, 32);
		iSetColor(0, 0, 0);
		iText(890, 458, " BACK ", GLUT_BITMAP_HELVETICA_18);
	}
	// if (flag == 4)
	// {
	// 	iText(520, 458, "PLAY AGAIN");
	// 	iSetColor(0, 255, 0);
	// 	iFilledRectangle(300, 450, 150, 32);
	// 	iSetColor(255, 0, 0);
	// 	iText(320, 458, "NEXT LEVEL");
	// 	iSetColor(0, 255, 0);
	// 	iFilledRectangle(870, 450, 150, 32);
	// 	iSetColor(255, 0, 0);
	// 	iText(890, 458, "EXIT");
	// 	iSetColor(0, 210, 0);
	// 	iFilledRectangle(0, 450, 150, 32);
	// 	iPauseTimer(0);
	// }
	if (flag == 5)
	{
		iShowBMP(0, 0, "image//credits.bmp");
		iSetColor(0, 255, 10);
		iFilledRectangle(100, 290, 194, 29);
		iFilledRectangle(100, 232, 194, 29);
		iSetColor(255, 0, 0);
		iText(160, 303, "SOUNDS ON", GLUT_BITMAP_HELVETICA_18);
		iText(160, 245, "SOUNDS OFF", GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 0, 0);
		iText(890, 458, " BACK ");
	}
	if (flag == 6)
	{
		iClear();
		iShowBMP(0, 0, "image//11.bmp");
		iSetColor(255, 0, 0);
		iFilledRectangle(400, 400, 150, 32);
		iSetColor(0, 0, 255);
		iText(420, 408, "GAME OVER", GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 0, 0);
		iFilledRectangle(400, 350, 150, 32);
		iSetColor(0, 0, 255);
		iText(420, 358, "MAIN MENU", GLUT_BITMAP_HELVETICA_18);
	}
	if (flag == 7)
	{
		iClear();
		iShowBMP(0, 0, "image//credits.bmp");
		iSetColor(178, 190, 181);
		iFilledRectangle(331, 740, 185, 152);
		iSetColor(255, 0, 0);
		iText(420, 408, "Name:Md.Fardin Fuad", GLUT_BITMAP_HELVETICA_18);
		iText(420, 370, "ID:2205084", GLUT_BITMAP_HELVETICA_18);
		iText(420, 350, "Supervisor:Mushtari Sadia(MUS) Madam ", GLUT_BITMAP_HELVETICA_18);
		iFilledRectangle(870, 450, 150, 32);
		iSetColor(0, 0, 0);
		iText(890, 458, " BACK ", GLUT_BITMAP_HELVETICA_18);
	}
	if (flag == 9) // score
	{
		iClear();
		iShowBMP(0, 0, "image//bck.bmp");
		iFilledRectangle(870, 450, 150, 32);
		iSetColor(255, 0, 0);
		iText(890, 458, " BACK ");
		score();
	}
	if (flag == 10) // red bird
	{
		iClear();
		iShowBMP(0, 0, "image//dem.bmp");
		iShowBMP2(100, 0, "image//21.bmp", 0);
		iShowBMP2(bird_x, bird_y, "image//18.bmp", 0);
		iShowBMP2(700, 0, "image//12.bmp", 0);
		iShowBMP2(770, 130, "image//box.bmp", 0);
		
		iFilledRectangle(870, 450, 150, 32);
		iSetColor(255, 0, 0);
		iText(890, 458, " BACK ", GLUT_BITMAP_HELVETICA_18);
		if(countA==1){
        iShowBMP2(720, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(720, 130, "image//20.bmp", 0);
		}
		if(countB==1){
        iShowBMP2(800, 255, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(800, 255, "image//20.bmp", 0);
		}
		if(countC==1){
        iShowBMP2(900, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(900, 130, "image//20.bmp", 0);
		}

	}
	if (flag == 11) // level 2
	{
		iClear();
		iShowBMP(0, 0, "image//demo1.bmp");
		iShowBMP2(100, 0, "image//21.bmp", 0);
		iShowBMP2(700, 0, "image//12.bmp", 0);
		iShowBMP2(770, 130, "image//box.bmp", 0);
		iShowBMP2(720, 130, "image//19.bmp", 0);
		iShowBMP2(800, 255, "image//19.bmp", 0);
		iShowBMP2(900, 130, "image//19.bmp", 0);
		iFilledRectangle(870, 450, 150, 32);
		if(isThree==0){
			iShowBMP2(bird_x,bird_y, "image//b2.bmp", 0);
		}
		else{
			iShowBMP2(blue_x1,blue_y1, "image//b2.bmp", 0);
			iShowBMP2(blue_x2,blue_y2, "image//b2.bmp", 0);
			iShowBMP2(blue_x3,blue_y3, "image//b2.bmp", 0);	
		}
		if(countA==1){
        iShowBMP2(720, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(720, 130, "image//20.bmp", 0);
		}
		if(countB==1){
        iShowBMP2(800, 255, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(800, 255, "image//20.bmp", 0);
		}
		if(countC==1){
        iShowBMP2(900, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(900, 130, "image//20.bmp", 0);
		}
		iSetColor(255, 0, 0);
		iText(890, 458, " BACK ", GLUT_BITMAP_HELVETICA_18);
	}
	if (flag == 12) // level 3
	{
		iClear();
		iShowBMP(0, 0, "image//lvl3.bmp");
		iShowBMP2(100, 0, "image//21.bmp", 0);
		iShowBMP2(700, 0, "image//12.bmp", 0);
		iShowBMP2(770, 130, "image//box.bmp", 0);
		iShowBMP2(720, 130, "image//19.bmp", 0);
		iShowBMP2(800, 255, "image//19.bmp", 0);
		iShowBMP2(900, 130, "image//19.bmp", 0);
		if(isSpeed!=0){
        iShowBMP2(bird_x,bird_y, "image//b3.bmp", 0);
		}
		if(isSpeed==0){
        iShowBMP2(bird_x,bird_y, "image//b3.bmp", 0);
		}
		if(countA==1){
        iShowBMP2(720, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(720, 130, "image//20.bmp", 0);
		}
		if(countB==1){
        iShowBMP2(800, 255, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(800, 255, "image//20.bmp", 0);
		}
		if(countC==1){
        iShowBMP2(900, 130, "image//19.bmp", 0);
		}
		else{
		iShowBMP2(900, 130, "image//20.bmp", 0);
		}
		iFilledRectangle(870, 450, 150, 32);
		iSetColor(255, 0, 0);
		iText(890, 458, " BACK ", GLUT_BITMAP_HELVETICA_18);
	}
	dotLine();
	showScore();
	nameInput();
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx1, int my1)
{
	 bird_x=mx1-20;
	 bird_y=my1-20;
     
	 dotVelocity=launchVelocity(mx1,my1);
	 dotAngle=launchAngle(mx1,my1);

	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(isFlying==1 && flag==11 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isThree=1;
	}
	if(isFlying==1 && flag==11 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isSpeed=1;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
		printf("%d %d\n", mx, my);
		if (mx > 405 && mx < 615 && my > 175 && my < 251 && flag == 1)
		{
			flag = 2;
		}
		if (mx > 816 && mx < 876 && my < 50 && my > 12 && flag == 1)
		{
			flag = 5;
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 5) // exit
		{
			flag = 1;
		}
		// b
		if (mx > 100 && mx < 292 && my > (290 - 2 * 58) && my < (319 - 2 * 58) && flag == 2)
		{
			flag = 1;
		}
		if (mx > 100 && mx < 300 && my > 123 && my < 160 && flag == 2)
		{
			flag = 7; // credits
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 7 || flag == 9) // exit
		{
			flag = 2;
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 3) // exit
		{
			flag = 2;
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 10) // exit
		{
			flag = 3;
			restart();
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 11) // exit
		{
			flag = 3;
			restart();
		}
		if (mx > 870 && mx < 1070 && my > 450 && my < 480 && flag == 12) // exit
		{
			flag = 3;
			restart();
		}
		if (mx > 101 && mx < 293 && my < 260 && my > 232 && flag == 2)
		{
			flag = 9;
		}
		if (mx > 103 && mx < 320 && my < 320 && my > 293 && flag == 3)
		{
			flag = 10;
		}
		if(flag == 10 && count == 3)
		{
		  leaderboard();
           flag = 6;
		   
	       PlaySound("music\\Game Completed.wav",NULL,SND_ASYNC);
		}
		if(flag == 11 && count == 3)
		{
		  
		  leaderboard();
		   flag = 6;
	       PlaySound("music\\Game Completed.wav",NULL,SND_ASYNC);
		   
		}
		if(flag==12 && count == 3)
		{
		   leaderboard();
		   flag = 6;
		    if(music==1)
	       PlaySound("music\\Game Completed.wav",NULL,SND_ASYNC);
		}
		if (mx > 102 && mx < 291 && my < 257 && my > 235 && flag == 3)
		{
			flag = 11;
		}
		if (mx > 101 && mx < 289 && my < 195 && my > 173 && flag == 3)
		{
			flag = 12;
		}
		if (mx > 100 && mx < 290 && my < 320 && my > 290 && flag == 2)
		{
			flag = 3;
			restart();
		}
		if (mx >398 && mx <550 && my <382 && my >353 && flag == 6)
	     {
		   flag = 2;
		   restart();
		}
		if (mx >400 && mx <546 && my <433 && my >405 && flag == 6)
	    {
		   exit(0);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if(flag==10 || flag==11 ||flag==12)
		{
		isFlying=1;
		restart();
		angle = launchAngle(mx,my);
		velocity = launchVelocity(mx,my);
		PlaySound("music\\Birds Flying.wav", NULL,SND_ASYNC);
		x=iSetTimer(5,projectileMotion);
		}
		
		
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

	

	if(key!='\b'){
		playername[indexNumber]=key;
		indexNumber++;
		playername[indexNumber]='\0';
	}
	else{
	    if(indexNumber<=0)
			indexNumber=0;
		else
			indexNumber--;

		playername[indexNumber]='\0';      
	}
		if (key == 'm')
		{
		PlaySound(0, 0, 0);
		}
		if(key == 'r')
		{		
		PlaySound("music\\Entry.wav", NULL, SND_LOOP | SND_ASYNC);
		}
}

// place your codes for other keys here

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
}

double launchVelocity(int mx,int my){
       double m = (bird_iy-my)/(bird_ix-mx);
       double a = atan(m);
	   double d = sqrt((bird_ix-mx)*(bird_iy-mx)+(bird_ix-my)*(bird_iy-my));
       double v = d*2;
	   return v;
}

double launchAngle(int mx,int my){
       double m = (bird_iy-my)/(bird_ix-mx);
       double a = atan(m);
	   return a;
}
void projectileMotion()
{
	if(flag==10){
	t +=.50;
	bird_x = bird_ix + velocity * cos(angle) * t;				
	bird_y = bird_iy + velocity * sin(angle) * t - 6* t * t; 
	printf("%lf,%lf\n", bird_x, bird_y);
	}

	if(flag==11){
	if(isThree==0){
	t +=.50;
	bird_x = bird_ix + velocity * cos(angle) * t;				
	bird_y = bird_iy + velocity * sin(angle) * t - 6* t * t; 
	
	}

	if(isThree==1){
	t1 +=.60;
	t2 +=.50;
	t3 +=.70;

	blue_x1 = bird_x + 1.1*velocity * cos(angle) * t1;				
	blue_y1 = bird_y + 1.1*velocity * sin(angle) * t1 - 6* t1 * t1;

	blue_x2 = bird_x + velocity * cos(angle) * t2;				
	blue_y2 = bird_y + velocity * sin(angle) * t2 - 6* t2 * t2;

	blue_x3 = bird_x + 0.9*velocity * cos(angle) * t3;				
	blue_y3 = bird_y + 0.9*velocity * sin(angle) * t3 - 6* t3 * t3;
	
	}	
	}
	if(flag==12){
	if(isSpeed==0){
	t +=.50;
	bird_x = bird_ix + velocity * cos(angle) * t;				
	bird_y = bird_iy + velocity * sin(angle) * t - 6* t * t;
	}	
	if(isSpeed==1){
	t +=.50;
	bird_x = bird_ix + 2*velocity * cos(angle) * t;				
	bird_y = bird_iy + 2*velocity * sin(angle) * t - 6* t * t;
	}
	}
	checkCollision();
	printf("%d %d \n",blue_x1,blue_y1);
}
void checkCollision(){
	if(bird_x>=1024 || bird_y>=512 || bird_y<=0){
		restart();
	}
	if(bird_x>=725-20 && bird_x<=777-20 && bird_y>=136-20 && bird_y<=195-20 && countA==1){
		collisionA=1;
		 if(music==1)
		 {
	    PlaySound("music\\dm.wav",NULL,SND_ASYNC);
		 }
	    restart();
		countA=2;
		count++;
		PlayerScore+=100;

	}
	
	if(bird_x>=800-20 && bird_x<=860-20 && bird_y>=258-20 && bird_y<=317-20 && countB==1){
	    collisionB=1;
		 if(music==1)
		 {
	    PlaySound("music\\dm.wav",NULL,SND_ASYNC);
		 }
	    restart();
	    countB=2;
	    count++;
		PlayerScore+=100;
	}
	if(bird_x>=900-20 && bird_x<=955-20 && bird_y>=132-20 && bird_y<=190-20 && countC==1){
	    collisionC=1;
	 if(music==1)
		 {
	    PlaySound("music\\dm.wav",NULL,SND_ASYNC);
		 }
	    restart();
	    countC=2;
	    count++;
		PlayerScore+=100;
	}		
}

int main()
{



	// place your own initialization codes here.
	if (flag == 1)
	{ 
		PlaySound("music\\Entry.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	iInitialize(1024, 512, "Angry Birds");

	return 0;
}
