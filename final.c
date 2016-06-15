/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"
#include "servo.h"
#include "servodiffdrive.h"
#include "fdserial.h"

#include "ping.h" // Include ping header

#define PIN_SOUND       26 // pin for the speaker, default=26
#define PIN_XBEE_RX      0
#define PIN_XBEE_TX      1
#define PIN_SERVO_LEFT  14
#define PIN_SERVO_RIGHT 15
#define STANDARD_MOTOR 16
#define LEFT_MOTOR 14
#define RIGHT_MOTOR 15
#define PING 17
#define UNIDIS  17
int cmDist1, cmDist2, cmDist3;
int plane[10][10];
int light[10][10];
int posx_now =1, posy_now=1;
int way = 4;
void detect ();
void decide();
void findob();
void turn();
void turnleft();
void turnright();
void letsgo();
void SOUD();


int main() // main function
{
int i,k,stop = 0;
char ch;
pause(3030);
   fdserial *xbee;
	xbee = fdserial_open(PIN_XBEE_RX, PIN_XBEE_TX, 0, 9600);
	drive_pins(PIN_SERVO_LEFT, PIN_SERVO_RIGHT);

	pause(1000);
	putchar(CLS);
	fdserial_rxFlush(xbee);
  cog_run(SOUD,128);
while(stop == 0) // Repeat indefinitely
//for(stop = 0; stop<4;stop++)
{
 /*   int wL = input(7);                        // Left whisker -> wL variable
    int wR = input(8);                        // Right whisker -> wR variable
    print("%c", HOME);                        // Terminal cursor home (top-left)
    print("wL = %d  wR = %d", wL, wR);        // Display whisker variables
    if(wL == 0 || wR == 0){
      freqout(4, 2000, 3030); 
    }
  //  pause(50);                                // Pause 50 ms before repeat
*/
  plane[posx_now][posy_now] = 1;
  //cog_run(detect,128);
  servo_angle(STANDARD_MOTOR, 1800);
  pause(1000);
cmDist1 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 900);
 pause(500);
cmDist2 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 0);
 pause(500);
cmDist3 = ping_cm(17);

print("%d %d  %d %d %d\n", cmDist1,  cmDist2,  cmDist3, way, i);

//cog_run(findob,128);
if((way%4) == 0){
if(cmDist1 < UNIDIS) plane[posx_now][posy_now-1]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now+1][posy_now]=2;
 if(cmDist3 < UNIDIS) plane[posx_now][posy_now+1]=2;	
}
else if((way%4) == 1){
  if(cmDist1 < UNIDIS) plane[posx_now+1][posy_now]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now][posy_now+1]=2;
if(cmDist3 < UNIDIS) plane[posx_now-1][posy_now]=2;	
}
else if((way%4) == 2){
  if(cmDist1 < UNIDIS) plane[posx_now][posy_now+1]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now-1][posy_now]=2;
 if(cmDist3 < UNIDIS) plane[posx_now][posy_now-1]=2;
}
else if((way%4) == 3){
if(cmDist1 < UNIDIS) plane[posx_now-1][posy_now]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now][posy_now-1]=2;
 if(cmDist3 < UNIDIS) plane[posx_now+1][posy_now]=2;
}
print("%d %d  %d %d %d %d\n", plane[5][0],  plane[5][1],  plane[5][2], plane[5][3], plane[5][4], plane[5][5]);
print("%d %d  %d %d %d %d\n", plane[4][0],  plane[4][1],  plane[4][2], plane[4][3], plane[4][4], plane[4][5]);
print("%d %d  %d %d %d %d\n", plane[3][0],  plane[3][1],  plane[3][2], plane[3][3], plane[3][4], plane[3][5]);
print("%d %d  %d %d %d %d\n", plane[2][0],  plane[2][1],  plane[2][2], plane[2][3], plane[2][4], plane[2][5]);
print("%d %d  %d %d %d %d\n", plane[1][0],  plane[1][1],  plane[1][2], plane[1][3], plane[1][4], plane[1][5]);
print("%d %d  %d %d %d %d\n", plane[0][0],  plane[0][1],  plane[0][2], plane[0][3], plane[0][4], plane[0][5]);

//cog_run(decide,128);

  if((way%4) == 0){
	 if(plane[posx_now][posy_now-1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now][posy_now-1] == 2) {
		  if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
	else	  if(plane[posx_now+1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		  }
		else  if(plane[posx_now+1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		  }
	 }
 else   if(plane[posx_now][posy_now-1] == 1) {
		  if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
else		  if(plane[posx_now+1][posy_now] == 2){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			 }

		  }
    
	else	  if(plane[posx_now+1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		  }
	  }
  }
  
  
  
  
else if((way%4) == 1){
	 if(plane[posx_now+1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now+1][posy_now] == 2) {
    		if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    	else	if(plane[posx_now][posy_now+1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    		}
    	else	if(plane[posx_now][posy_now+1] == 1){               //右轉
    			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    		else	if(plane[posx_now-1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    		else	if(plane[posx_now-1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    			}
    		}
   	}
  else  if(plane[posx_now+1][posy_now] == 1) {
    		if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    else		if(plane[posx_now][posy_now+1] == 2){               //右轉
    			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
			else   if(plane[posx_now-1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			   }
			 else  if(plane[posx_now-1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			   }

		    }
	   else	if(plane[posx_now][posy_now+1] == 1){               //右轉
		    	if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		    	}
		   else 	if(plane[posx_now-1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		    	}
		  else  	if(plane[posx_now-1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
		    	}
	   	}
	   }
    }
    
    
    
else if((way%4) == 2){
  if(plane[posx_now][posy_now+1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
  else  if(plane[posx_now][posy_now+1] == 2) {
		  if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		else  if(plane[posx_now-1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		  }
		else  if(plane[posx_now-1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		  }
	 }
   else if(plane[posx_now][posy_now+1] == 1) {
		  if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		else  if(plane[posx_now-1][posy_now] == 2){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
			else if(plane[posx_now][posy_now-1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			 }

		  }
    
		else  if(plane[posx_now-1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		else	 if(plane[posx_now][posy_now-1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		  }
	  }
}






else if((way%4) == 3){
if(plane[posx_now-1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now-1][posy_now] == 2) {
    		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    		else if(plane[posx_now][posy_now-1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    		}
    		else if(plane[posx_now][posy_now-1] == 1){               //右轉
    			if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			else if(plane[posx_now+1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			else if(plane[posx_now+1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    			}
    		}
   	}
  else if(plane[posx_now-1][posy_now] == 1) {
    		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
   else	if(plane[posx_now][posy_now-1] == 2){               //右轉
    			if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
			else   if(plane[posx_now+1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			   }
			else   if(plane[posx_now+1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			   }

		    }
	  else 	if(plane[posx_now][posy_now-1] == 1){               //右轉
		    	if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		    	}
		   else 	if(plane[posx_now+1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		    	}
		  else  	if(plane[posx_now+1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
		    	}
	   	}
	   }
}

    high(5);                                  // Set P5 high
    pause(1);                                 // Wait for circuit to charge
    int t = rc_time(5, 1);                    // Measure decay time on P5
 //   print("t = %d\n", t);                     // Display decay time
    if(t > 500) light[posx_now][posy_now] = 10; 

pause(1000);
//plane[posx_now][posy_now] = 1;

stop = 1;
for (i = 1 ; i < posx_now+3; i++){
  for (k = 1 ; k < posy_now+3; k++){
    if(plane[i][k]==0 && (k != posy_now+2||i != posx_now+2)) stop = 0;
}
}
    
}

for (i = 9 ; i >= 0; i--){
  for (k = 0 ; k < 10; k++){
 //   plane[i][k] = plane[i][k] + light[i][k];//if(plane[i][k]==0){  
  if(light[i][k] == 10) ch = 'D';
  else{
  if(plane[i][k] == 0){
      ch = '?';
   }     
   if(plane[i][k] == 1){
      ch = 'O';
   } 
   if(plane[i][k] == 2){
      ch = 'X';
   } 
   } 
		fdserial_txChar(xbee, ch);
		fdserial_txFlush(xbee);
     plane[i][k] = 0;
}
}


stop = 0;
//while(stop == 0) // Repeat indefinitely
for(stop = 0; stop<5;stop++)
{
  plane[posx_now][posy_now] = 1;
  //cog_run(detect,128);
  servo_angle(STANDARD_MOTOR, 1800);
  pause(1000);
cmDist1 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 900);
 pause(500);
cmDist2 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 0);
 pause(500);
cmDist3 = ping_cm(17);

print("%d %d  %d %d %d\n", cmDist1,  cmDist2,  cmDist3, way, i);

//cog_run(findob,128);
if((way%4) == 0){
if(cmDist1 < UNIDIS) plane[posx_now][posy_now-1]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now+1][posy_now]=2;
 if(cmDist3 < UNIDIS) plane[posx_now][posy_now+1]=2;	
}
else if((way%4) == 1){
  if(cmDist1 < UNIDIS) plane[posx_now+1][posy_now]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now][posy_now+1]=2;
if(cmDist3 < UNIDIS) plane[posx_now-1][posy_now]=2;	
}
else if((way%4) == 2){
  if(cmDist1 < UNIDIS) plane[posx_now][posy_now+1]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now-1][posy_now]=2;
 if(cmDist3 < UNIDIS) plane[posx_now][posy_now-1]=2;
}
else if((way%4) == 3){
if(cmDist1 < UNIDIS) plane[posx_now-1][posy_now]=2; 
 if(cmDist2 < UNIDIS) plane[posx_now][posy_now-1]=2;
 if(cmDist3 < UNIDIS) plane[posx_now+1][posy_now]=2;
}
print("%d %d  %d %d %d %d\n", plane[5][0],  plane[5][1],  plane[5][2], plane[5][3], plane[5][4], plane[5][5]);
print("%d %d  %d %d %d %d\n", plane[4][0],  plane[4][1],  plane[4][2], plane[4][3], plane[4][4], plane[4][5]);
print("%d %d  %d %d %d %d\n", plane[3][0],  plane[3][1],  plane[3][2], plane[3][3], plane[3][4], plane[3][5]);
print("%d %d  %d %d %d %d\n", plane[2][0],  plane[2][1],  plane[2][2], plane[2][3], plane[2][4], plane[2][5]);
print("%d %d  %d %d %d %d\n", plane[1][0],  plane[1][1],  plane[1][2], plane[1][3], plane[1][4], plane[1][5]);
print("%d %d  %d %d %d %d\n", plane[0][0],  plane[0][1],  plane[0][2], plane[0][3], plane[0][4], plane[0][5]);

//cog_run(decide,128);

  if((way%4) == 0){
	 if(plane[posx_now][posy_now-1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now][posy_now-1] == 2) {
		  if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
	else	  if(plane[posx_now+1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		  }
		else  if(plane[posx_now+1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		  }
	 }
 else   if(plane[posx_now][posy_now-1] == 1) {
		  if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
else		  if(plane[posx_now+1][posy_now] == 2){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			 }

		  }
    
	else	  if(plane[posx_now+1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
		else	 if(plane[posx_now][posy_now+1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		else	 if(plane[posx_now][posy_now+1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		  }
	  }
  }
  
  
  
  
else if((way%4) == 1){
	 if(plane[posx_now+1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now+1][posy_now] == 2) {
    		if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    	else	if(plane[posx_now][posy_now+1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    		}
    	else	if(plane[posx_now][posy_now+1] == 1){               //右轉
    			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    		else	if(plane[posx_now-1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    		else	if(plane[posx_now-1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    			}
    		}
   	}
  else  if(plane[posx_now+1][posy_now] == 1) {
    		if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    else		if(plane[posx_now][posy_now+1] == 2){               //右轉
    			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
			else   if(plane[posx_now-1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			   }
			 else  if(plane[posx_now-1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			   }

		    }
	   else	if(plane[posx_now][posy_now+1] == 1){               //右轉
		    	if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		    	}
		   else 	if(plane[posx_now-1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		    	}
		  else  	if(plane[posx_now-1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
		    	}
	   	}
	   }
    }
    
    
    
else if((way%4) == 2){
  if(plane[posx_now][posy_now+1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
  else  if(plane[posx_now][posy_now+1] == 2) {
		  if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		else  if(plane[posx_now-1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		  }
		else  if(plane[posx_now-1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		  }
	 }
   else if(plane[posx_now][posy_now+1] == 1) {
		  if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		else  if(plane[posx_now-1][posy_now] == 2){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
			else if(plane[posx_now][posy_now-1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			 }

		  }
    
		else  if(plane[posx_now-1][posy_now] == 1){               //右轉
			 if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			else if(plane[posx_now][posy_now-1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		else	 if(plane[posx_now][posy_now-1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		  }
	  }
}






else if((way%4) == 3){
if(plane[posx_now-1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
   else if(plane[posx_now-1][posy_now] == 2) {
    		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    		else if(plane[posx_now][posy_now-1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    		}
    		else if(plane[posx_now][posy_now-1] == 1){               //右轉
    			if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			else if(plane[posx_now+1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			else if(plane[posx_now+1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    			}
    		}
   	}
  else if(plane[posx_now-1][posy_now] == 1) {
    		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
   else	if(plane[posx_now][posy_now-1] == 2){               //右轉
    			if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
			else   if(plane[posx_now+1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			   }
			else   if(plane[posx_now+1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			   }

		    }
	  else 	if(plane[posx_now][posy_now-1] == 1){               //右轉
		    	if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		    	}
		   else 	if(plane[posx_now+1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 else if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 else if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 else if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		    	}
		  else  	if(plane[posx_now+1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
		    	}
	   	}
	   }
}
//stop = 0;
//if(posx_now == 1 && posy_now==1) stop = 1;

}
/*
for (i = 9 ; i >= 0; i--){
  for (k = 0 ; k < 10; k++){
    plane[i][k] = plane[i][k] + light[i][k];//if(plane[i][k]==0){  
   if(plane[i][k] == 0){
      ch = '?';
   }     
   if(plane[i][k] == 1){
      ch = 'O';
   } 
   if(plane[i][k] == 2){
      ch = 'X';
   } 
   if(plane[i][k] == 3){
      ch = 'D';
   } 
		fdserial_txChar(xbee, ch);
		fdserial_txFlush(xbee);
   plane[i][k] = 0;
}
}
*/
}
     










void SOUD(){
    while(1){
    int wL = input(7);                        // Left whisker -> wL variable
    int wR = input(8);                        // Right whisker -> wR variable
  //  print("%c", HOME);                        // Terminal cursor home (top-left)
   // print("wL = %d  wR = %d", wL, wR);        // Display whisker variables
    if(wL == 0 || wR == 0){
      freqout(4, 2000, 3030); 
    }
  //  pause(50);  
}
}








void detect(){

servo_angle(STANDARD_MOTOR, 1800);
  pause(1000);
cmDist1 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 900);
 pause(500);
cmDist2 = ping_cm(17);

servo_angle(STANDARD_MOTOR, 0);
 pause(500);
cmDist3 = ping_cm(17);

print("%d %d  %d \n", cmDist1,  cmDist2,  cmDist3);

}
void decide(){

  if((way%4) == 0){
	 if(plane[posx_now-1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
    if(plane[posx_now-1][posy_now] == 2) {
		  if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		  if(plane[posx_now][posy_now+1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		  }
		  if(plane[posx_now][posy_now+1] == 1){               //右轉
			 if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			 if(plane[posx_now+1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			 if(plane[posx_now+1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
		  }
	 }
    if(plane[posx_now-1][posy_now] == 1) {
		  if(plane[posx_now][posy_now+1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		  }
		  if(plane[posx_now][posy_now+1] == 2){               //右轉
			 if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			 if(plane[posx_now+1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
			 if(plane[posx_now+1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			 }

		  }
    
		  if(plane[posx_now][posy_now+1] == 1){               //右轉
			 if(plane[posx_now+1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			 }
			 if(plane[posx_now+1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			 }
			 if(plane[posx_now+1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			 }
		  }
	  }
  }
  if((way%4) == 1){
	 if(plane[posx_now][posy_now+1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	 }
    if(plane[posx_now][posy_now+1] == 2) {
    		if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    		if(plane[posx_now+1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    		}
    		if(plane[posx_now+1][posy_now] == 1){               //右轉
    			if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			if(plane[posx_now][posy_now-1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
    			if(plane[posx_now][posy_now-1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    			}
    		}
   	}
    if(plane[posx_now][posy_now+1] == 1) {
    		if(plane[posx_now+1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
    		}
    		if(plane[posx_now+1][posy_now] == 2){               //右轉
    			if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
    			}
			   if(plane[posx_now][posy_now-1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			   }
			   if(plane[posx_now][posy_now-1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			   }

		    }
	   	if(plane[posx_now+1][posy_now] == 1){               //右轉
		    	if(plane[posx_now][posy_now-1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		    	}
		    	if(plane[posx_now][posy_now-1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		    	}
		    	if(plane[posx_now][posy_now-1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
		    	}
	   	}
	   }
    }
if((way%4) == 2){
if(plane[posx_now+1][posy_now] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	}
if(plane[posx_now+1][posy_now] == 2) {
		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		}
		if(plane[posx_now][posy_now-1] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		}
		if(plane[posx_now][posy_now-1] == 1){               //右轉
			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now-1][posy_now] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now-1][posy_now] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			}
		}
	}
if(plane[posx_now+1][posy_now] == 1) {
		if(plane[posx_now][posy_now-1] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		}
		if(plane[posx_now][posy_now-1] == 2){               //右轉
			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now-1][posy_now] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			}
			if(plane[posx_now-1][posy_now] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			}

		}
		if(plane[posx_now][posy_now-1] == 1){               //右轉
			if(plane[posx_now-1][posy_now] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now-1][posy_now] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			}
			if(plane[posx_now-1][posy_now] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			}
		}
	}
}
if((way%4) == 3){
if(plane[posx_now][posy_now-1] == 0) {               //左轉
		servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
	}
if(plane[posx_now][posy_now-1] == 2) {
		if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		}
		if(plane[posx_now-1][posy_now] == 2){               //右轉
			servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
		}
		if(plane[posx_now-1][posy_now] == 1){               //右轉
			if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now][posy_now+1] == 1) {           // turnright
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now][posy_now+1] == 2) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			}
		}
	}
if(plane[posx_now][posy_now-1] == 1) {
		if(plane[posx_now-1][posy_now] == 0){               //前行
			servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
		}
		if(plane[posx_now-1][posy_now] == 2){               //右轉
			if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now][posy_now+1] == 1) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			}
			if(plane[posx_now][posy_now+1] == 2) {           //左轉
				servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
			}

		}
		if(plane[posx_now-1][posy_now] == 1){               //右轉
			if(plane[posx_now][posy_now+1] == 0) {           //右轉
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
			}
			if(plane[posx_now][posy_now+1] == 1) {           //前行
				servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
			}
			if(plane[posx_now][posy_now+1] == 2) {           //轉180
				servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
			}
		}
	}
}
}



void findob(){
if((way%4) == 0){
  if(cmDist1 < UNIDIS) plane[posx_now][posy_now-1]=2; 
if(cmDist2 < UNIDIS) plane[posx_now+1][posy_now]=2;
if(cmDist3 < UNIDIS) plane[posx_now][posy_now+1]=2;
	
}
if((way%4) == 1){
  if(cmDist1 < UNIDIS) plane[posx_now+1][posy_now]=2; 
if(cmDist2 < UNIDIS) plane[posx_now][posy_now+1]=2;
if(cmDist3 < UNIDIS) plane[posx_now-1][posy_now]=2;
	
}
if((way%4) == 2){
  if(cmDist1 < UNIDIS) plane[posx_now][posy_now+1]=2; 
if(cmDist2 < UNIDIS) plane[posx_now-1][posy_now]=2;
if(cmDist3 < UNIDIS) plane[posx_now][posy_now-1]=2;
}
if((way%4) == 3){
if(cmDist1 < UNIDIS) plane[posx_now-1][posy_now]=2; 
if(cmDist2 < UNIDIS) plane[posx_now][posy_now-1]=2;
if(cmDist3 < UNIDIS) plane[posx_now+1][posy_now]=2;
}
}

void turn(){
	servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(1580); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 2;
}

void turnright(){
	servo_speed(14,48); //run at speed = 50 for 2s
	servo_speed(15,48); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way + 1;
}

void turnleft(){
	servo_speed(14,-46); //run at speed = 50 for 2s
	servo_speed(15,-46); // Wait 1/10 second
	pause(810); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
	way = way - 1;
}

void letsgo(){
	servo_speed(14,303); //run at speed = 50 for 2s
	servo_speed(15,-295); // Wait 1/10 second
	pause(1050); 
	servo_speed(14,0); //run at speed = 50 for 2s
	servo_speed(15,0); // Wait 1/10 second
 if((way%4) == 0){
    posx_now = posx_now +1;
    posy_now = posy_now;
}
 if((way%4) == 1){
    posx_now = posx_now;
    posy_now = posy_now +1;
}
 if((way%4) == 2){
    posx_now = posx_now -1;
    posy_now = posy_now;
}
 if((way%4) == 3){
    posx_now = posx_now;
    posy_now = posy_now -1;
}
}