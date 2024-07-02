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



int count=0,count1=1,count2=1,count3=1,countY=0,countR=0,countB=0;
double t,x;
double bird_x=65.00,bird_y=130.00;
double angle,velocity;
double bird_ix=65.0,bird_iy=130.0;
bool musicOn=true;
int clickButton=-1;
int collision1=0,collision2=0,collision3=0;
double pig1_x=940.00,pig1_y=160.00;
double blue_x1,blue_y1,blue_x2,blue_y2,blue_x3,blue_y3;
int isTriplet,isBirdFlying;

char arr[]={"a\\Sounds0.bmp","a\\Sounds1.bmp","a\\Sounds2.bmp","a\\Sounds3.bmp","a\\Sounds4.bmp","a\\Sounds5.bmp","a\\Sounds6.bmp","a\\Sounds7.bmp","a\\Sounds8.bmp","a\\Sounds9.bmp",
	           "a\\Sounds10.bmp","a\\Sounds11.bmp","a\\Sounds12.bmp","a\\Sounds13.bmp","a\\Sounds14.bmp","a\\Sounds15.bmp","a\\Sounds16.bmp","a\\Sounds17.bmp","a\\Sounds18.bmp","a\\Sounds19.bmp",
			   "a\\Sounds20.bmp","a\\Sounds21.bmp","a\\Sounds22.bmp","a\\Sounds23.bmp","a\\Sounds24.bmp","a\\Sounds25.bmp","a\\Sounds26.bmp","a\\Sounds27.bmp","a\\Sounds29.bmp","a\\Sounds30.bmp",
			   "a\\Sound31.bmp","a\\Sounds32.bmp"};
double launchAngle(int mx,int my);
double launchVelocity(int mx,int my);
void projectileMotion();
void restart();
void music();
void levelOneCollision();
void yellowBirdPlay();
void redBirdPlay();
void blueBirdPlay();
void settingsMenu();
void playMenu();
void mainMenu();
void leaderboardMenu();
void difficultyMenu();
void soundsMenu();
void creditsMenu();
void rulesMenu();
void dotLine();
void score();
/*
	function iDraw() is called again and again by the system.

	*/
int gameState=1;


void writeScore(const std::vector<std::string>& lines) {
    std::ofstream outputFile("writeScore.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    for (const auto& currentLine : lines) {
        outputFile << currentLine << '\n';
    }

    outputFile.close();
}

void score(){
	if(gameState==7){
	std::ifstream inputFile("score.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::vector<std::string> lines;  // Container for storing lines

    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    int yCoordinate = 385;

    for (const auto& currentLine : lines) {
        iSetColor(0, 0, 0);
        iText(420, yCoordinate, const_cast<char*>(currentLine.c_str()), GLUT_BITMAP_TIMES_ROMAN_24);
        yCoordinate -= 80;
    }
	writeScore(lines);
	}
	
}

void levelOneCollision(){

	if((bird_x-40>=1280 || bird_y-40>800 || bird_y<=50)){
		PlaySound("music\\birdCollision01.wav",NULL,SND_ASYNC);
		iPauseTimer(x);
		restart();
	}		
	if(bird_x>=920 && bird_x<=985 && bird_y>=160 && bird_y<=215 && count1==1){
		collision1=1;
	    PlaySound("music\\pigletteDamage.wav",NULL,SND_ASYNC);
	    restart();
		iPauseTimer(x);
		count1=2;
		count++;
	}
	
	if(bird_x>=1040 && bird_x<=1095 && bird_y>=160 && bird_y<=215 && count2==1){
	    collision2=1;
        PlaySound("music\\pigletteDamage.wav",NULL,SND_ASYNC);
	    restart();
	    iPauseTimer(x);
	    count2=2;
	    count++;
	}
	if(bird_x>=1155 && bird_x<=1210 && bird_y>=160 && bird_y<=215 && count3==1){
	    collision3=1;
	    PlaySound("music\\pigletteDamage.wav",NULL,SND_ASYNC);  
	    restart();
	    iPauseTimer(x);
	    count3=2;
	    count++;
	}
	
}
void yellowBirdPlay(){
    if(gameState==5){
	    iShowBMP(0,0,"images\\PLay03.bmp");
		iShowBMP2(bird_x,bird_y,"images\\yellowBird.bmp",0);
	}
	if(gameState==5 && collision1!=1)
		iShowBMP2(pig1_x,pig1_y,"images\\pig02.bmp",0);
	if(gameState==5 && collision2!=1)	
		iShowBMP2(pig1_x+105,pig1_y,"images\\pig02.bmp",0);
	if(gameState==5 && collision3!=1)
		iShowBMP2(pig1_x+220,pig1_y,"images\\pig02.bmp",0);
	if((gameState==5 && countY==0) || countY==1){
		iShowBMP2(00,40,"images\\yellowBird.bmp",0);
		iShowBMP2(40,40,"images\\yellowBird.bmp",0);
		iShowBMP2(80,40,"images\\yellowBird.bmp",0);
	}
	
	if((gameState==5 && countY==2) || countY==3){
		iShowBMP2(40,40,"images\\yellowBird.bmp",0);
		iShowBMP2(80,40,"images\\yellowBird.bmp",0);
	}
    if((gameState==5 && countY==4) || countY==5)
		iShowBMP2(80,40,"images\\yellowBird.bmp",0);
		
	if(gameState==5 && countY<=10 && count==3){
		iShowBMP(0,0,"images\\PlayWin.bmp");
		PlaySound("music\\playWin.wav",NULL,SND_SYNC);
	}
	if(gameState==5 && countY>9 && count!=3){
		iShowBMP(0,0,"images\\PlayLost.bmp");
		PlaySound("music\\levelFailed.wav",NULL,SND_SYNC);
	}
	   
	printf("%d %d\n",countY,count);
}

void redBirdPlay(){
    if(gameState==4){ 
		iShowBMP(0,0,"images\\Play03.bmp");
		iShowBMP2(bird_x,bird_y,"images\\redBird.bmp",0);
	}
	if(gameState==4 && collision1!=1)
		iShowBMP2(pig1_x,pig1_y,"images\\pig02.bmp",0);
	if(gameState==4 && collision2!=1)
		iShowBMP2(pig1_x+105,pig1_y,"images\\pig02.bmp",0);
	if(gameState==4 && collision3!=1)
		iShowBMP2(pig1_x+220,pig1_y,"images\\pig02.bmp",0);
	
    if((gameState==4 && countR==0) || countR==1){
		iShowBMP2(00,40,"images\\redBird.bmp",0);
		iShowBMP2(40,40,"images\\redBird.bmp",0);
		iShowBMP2(80,40,"images\\redBird.bmp",0);
	}
	if((gameState==4 && countR==2) || countR==3){
		iShowBMP2(40,40,"images\\redBird.bmp",0);
		iShowBMP2(80,40,"images\\redBird.bmp",0);
	}
    if((gameState==4 && countR==4) || countR==5)
		iShowBMP2(80,40,"images\\redBird.bmp",0);
		
	if(gameState==4 && countR<=8 && count==3){
		iShowBMP(0,0,"images\\PlayWin.bmp");
		PlaySound("music\\levelCleared.wav",NULL,SND_SYNC);
	}
	if(gameState==4 && countR>9 && count!=3){
		iShowBMP(0,0,"images\\PlayLost.bmp");
		PlaySound("music\\levelFailed.wav",NULL,SND_SYNC);
	}
	   
	   
	
}
void blueBirdPlay(){

	if(gameState==6){
        iShowBMP(0,0,"images\\Play03.bmp");
		iShowBMP2(bird_x,bird_y,"images\\blueBird.bmp",0);
	if(gameState==6 && collision1!=1)
		iShowBMP2(pig1_x,pig1_y,"images\\pig02.bmp",0);
	if(gameState==6 && collision2!=1)
		iShowBMP2(pig1_x+105,pig1_y,"images\\pig02.bmp",0);
	if(gameState==6 && collision3!=1)
		iShowBMP2(pig1_x+220,pig1_y,"images\\pig02.bmp",0);
	}
    if((gameState==6 && countB==0) || countB==1){
		iShowBMP2(00,40,"images\\blueBird.bmp",0);
		iShowBMP2(40,40,"images\\blueBird.bmp",0);
		iShowBMP2(80,40,"images\\blueBird.bmp",0);
	}
	if((gameState==6 && countB==2) || countB==3){
		iShowBMP2(40,40,"images\\blueBird.bmp",0);
		iShowBMP2(80,40,"images\\blueBird.bmp",0);
	}
    if((gameState==6 && countB==4) || countB==5)
		iShowBMP2(80,40,"images\\blueBird.bmp",0);
		
	if(gameState==6 && countB<=10 && count==3){
		iShowBMP(0,0,"images\\PlayWin.bmp");
		PlaySound("music\\playWin.wav",NULL,SND_SYNC);
	}
	if(gameState==6 && countB>9 && count!=3){
		iShowBMP(0,0,"images\\PlayLost.bmp");
		PlaySound("music\\levelFailed.wav",NULL,SND_SYNC);
	}


}

void restart(){
	bird_ix=65.0;
	bird_iy=130.0;
	bird_x=bird_ix;
	bird_y=bird_iy;
	t=0;
	if(gameState==4)
	countR++;
	if(gameState==5)
	countY++;
	if(gameState==6)
	countB++;
}


void soundButtonOff(){
	for(int i=0; i<33; i++){
			 iShowBMP(0,0,arr[i]);
       
	}
}
void settingsMenu(){
	if(gameState==3)
		iShowBMP(0,0,"images\\MenuSettings.bmp");
}
void playMenu(){
	 if(gameState==2)
	   iShowBMP(0,0,"images\\MenuPlay.bmp");
}
void mainMenu(){
	if(gameState==1)
       iShowBMP(0,0,"images\\Menu.bmp");
}
void leaderboardMenu(){
	if(gameState==7)
        iShowBMP(0,0,"images\\MenuSettingsLeaderboard.bmp");
}
void difficultyMenu(){
	if(gameState==8)
        iShowBMP(0,0,"images\\MenuSettingsDifficulty.bmp");
}
void soundsMenu(){
	if(gameState==9)
        iShowBMP(0,0,"a\\Sounds0.bmp");
	if(clickButton%2==0){
		int y=iSetTimer(50,soundButtonOff);
	}
}
void rulesMenu(){
	if(gameState==10)
        iShowBMP(0,0,"images\\MenuSettingsRules.bmp");
}
void creditsMenu(){
	if(gameState==11)
        iShowBMP(0,0,"images\\MenuSettingsCredits.bmp");
}


void iDraw() {
	//place your drawing codes here
	iClear();
	
    mainMenu();
    playMenu();
    settingsMenu();
	redBirdPlay();
	yellowBirdPlay();
    blueBirdPlay();
    leaderboardMenu();
	difficultyMenu();
	soundsMenu();
	rulesMenu();
	creditsMenu();
	score();
    dotLine();
}

void dotLine()
{
	if(gameState==4){
		iSetColor(255,255,255);
	    iFilledCircle(bird_x,bird_y,1,10);
	}
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx1, int my1) {
	//place your codes here
	bird_x=mx1-20;
	bird_y=my1-20;
    
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

	
void projectileMotion(){
	t+=.50;
    bird_x=bird_ix+velocity*cos(45)*t;
	bird_y=bird_iy+velocity*sin(45)*t-0.5*9.8*t*t;//
	printf("%lf,%lf\n",bird_x,bird_y);
    levelOneCollision();
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int dx, int dy) {
    	int mx=dx;
		int my=dy;
		printf("%lf %lf ",mx,my);
  
		

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
           
		    
		    if(gameState==1 && dx>=29 && dx<=89 && dy>=33 && dy<=89){
                exit(0);
			}
            if(gameState==3 && dx>=24 && dx<=83 && dy>=80 && dy<=135){
                gameState=1;
				if(musicOn){
				PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				}
				
			}
			if(gameState==1 && dx>=449 && dx<=782 && dy>=335 && dy<=466){
			    gameState=2;
				if(musicOn){
				PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);	
				}
				
			}
			if(gameState==2 && dx>=301 && dx<=370 && dy>=175 && dy<=243){
				gameState=4;
				if(musicOn){
				PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);	
				}
				
			}
			if(gameState==4 && dx>=31 && dx<=90 && dy>=719 && dy<=775){
                  gameState=2;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);	
				  PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				  }
				 
			}
			if(gameState==2 && dx>=617 && dx<=685 && dy>=175 && dy<=243){
				gameState=5;
				if(musicOn){
				PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);	
				}
				
			}
			if(gameState==5 && dx>=31 && dx<=90 && dy>=719 && dy<=775){
                  gameState=2;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				  }
				  
			}
			if(gameState==2 && dx>=940 && dx<=1008 && dy>=175 && dy<=243){
				gameState=6;
				if(musicOn){
				PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);	
				}
				
			}
			if(gameState==6 && dx>=31 && dx<=90 && dy>=719 && dy<=775){
                  gameState=2;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				  }
			}
			 
			if(gameState==2 && dx>=26 && dx<=84 && dy>=35 && dy<=92){
				gameState=1;
				if(musicOn){
				PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				}
				
			}
			  
            if(gameState==3 && dx>=407 && dx<=860 && dy>=558 && dy<=643){
                  gameState=7;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==7 && dx>=36 && dx<=90 && dy>=61 && dy<=116){
                  gameState=3;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==3 && dx>=407 && dx<=860 && dy>=447 && dy<=530){
                  gameState=8;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  }
				 
			} 
			if(gameState==8 && dx>=36 && dx<=90 && dy>=61 && dy<=116){
                  gameState=3;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==9 && dx>=610 && dx<=760 && dy>=450 && dy<=500){
                  clickButton++;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  }
				 
			}
			if(gameState==3 && dx>=407 && dx<=860 && dy>=338 && dy<=422){
                  gameState=9;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  } 
			}
			
			if(gameState==9 && dx>=36 && dx<=90 && dy>=61 && dy<=116){
                  gameState=3;
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
			}
			if(gameState==3 && dx>=407 && dx<=860 && dy>=226 && dy<=310){
                  gameState=10;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  }
				 
			}
			if(gameState==10 && dx>=36 && dx<=90 && dy>=61 && dy<=116){
                  gameState=3;
				  if(musicOn){
                  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==3 && dx>=407 && dx<=860 && dy>=115 && dy<=252){
                  gameState=11;
				  if(musicOn){
				  PlaySound("music\\MenuSelect.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==11 && dx>=36 && dx<=90 && dy>=61 && dy<=116){
                  gameState=3;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  }
				  
			}
			if(gameState==3 && dx>=407 && dx<=860 && dy>=558 && dy<=643){
                  gameState=2;
				  if(musicOn){
				  PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				  PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
				  }
				  
			}

            if(gameState==1 && dx>=1187 && dx<=1247 && dy>=42 && dy<=97){
				gameState=3; 
				if(musicOn){
				PlaySound("music\\menu_back.wav",NULL,SND_SYNC);
				}
				
		    }
		
		    
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		
		
	}
	
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP){
      
	   //printf("%lf,%lf\n",bird_dx,bird_dy);

        if(gameState==4 || gameState==5 || gameState==6){
          restart();
		  angle=launchAngle(mx,my);
	      velocity=launchVelocity(mx,my);
	      PlaySound("music\\birdFlying.wav",NULL,SND_ASYNC);
	      x=iSetTimer(5,projectileMotion);
		}
    }   
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	if(musicOn)
	PlaySound("music\\background.wav",NULL,SND_LOOP | SND_ASYNC);
	iInitialize(1280,800,"Angry Birds");
	
	
	return 0;
}