#include <stdint.h>
#include <stdlib.h> 
#include<time.h>	
#define RAND_MAX 32767
#define MULTIPLIER 1103515245
#define INCREMENT 12345
#define LINE_THICKNESS 6
void start();
void display(int SW_value);
void write_pixel(int x , int y , int color);
void vertical_line(int x , int y1 , int y2 , int thick , int color);
void horizontal_line(int y , int x1 , int x2 , int thick , int color);
void diagonal_line(int x1, int y1, int x2, int y2, int thick, int color);
void clear_screen();
void clear_screen2();
int my_rand();
void write_char(int x , int y , char c );
void draw_line(int x1, int y, int x2, short color);
void game();
void processing(int SW_value);
void instructions();
void final_page();
volatile int * SW_switch_ptr = (int *) 0xFF200040; // SW slider switch address
volatile int * KEY_ptr = (int *) 0xFF200050;       // pushbutton KEY address

// Global variable to store the current seed
unsigned int seed = 0;

// Custom random number generator function
int my_rand() {
    seed = (MULTIPLIER * seed + INCREMENT) % RAND_MAX;
    return seed % 10; // Return a number between 0 and 9
}

void write_pixel(int x , int y , int color){
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = color;
}

void clear_screen(){
    for(int x = 0; x < 320 ; x++) {
        for(int y = 0; y < 240 ; y++) {
            write_pixel(x, y, 0);
        }
    }
}

void clear_screen2(){
    // Clear pixel data
    for(int x = 0; x < 320 ; x++) {
        for(int y = 0; y < 240 ; y++) {
            write_pixel(x, y, 0);
        }
    }
    // Clear text area
    for(int x = 0; x < 80 ; x++) {
        for(int y = 0; y < 60 ; y++) {    
            volatile char * char_buffer = (char*)(0x09000000 + (y << 7) + x);
            *char_buffer = 0; // Clear character
        }
    }
}

void write_char(int x , int y , char c ){
    volatile char * char_buffer = (char*)(0x09000000 + (y << 7) + x);
    *char_buffer = c;
}

void vertical_line(int x , int y1 , int y2 , int thick , int color){
	for(int p = x ; p <(x + thick + 1) ; p++){
	  for(int q = y1 ; q <= y2 ; q++){
	     write_pixel(p,q,color);
	  }
	}

}

void horizontal_line(int y , int x1 , int x2 , int thick , int color){
	for(int p = y ; p <(y + thick + 1) ; p++){
	  for(int q = x1 ; q <= x2 ; q++){
	     write_pixel(q,p,color);
	  }
	}
}

void draw_line(int x1, int y, int x2, short color) {
    for (int i = 0; i < LINE_THICKNESS; i++) {
        for (int x = x1; x <= x2; x++) {
            write_pixel(x, y + i, color);
        }
    }
}

void game(){
    vertical_line(2,2,238,5,0xafc0);
    vertical_line(313,2,238,5,0xafc0);
    horizontal_line(2,2,318,5,0xafc0);
	horizontal_line(233,2,318,5,0xafc0);
//u	
	vertical_line(50,60,110,5,0xffff);
	vertical_line(65,60,110,5,0xffff);
	horizontal_line(105,55,65,5,0xffff);
//s	
    vertical_line(85,88,110,5,0xffff);
    vertical_line(80,60,83,5,0xffff);
    horizontal_line(60,80,90,5,0xffff);
	horizontal_line(83,80,90,5,0xffff);
	horizontal_line(105,80,90,5,0xffff);
//E	
    vertical_line(100,60,110,5,0xffff);
    horizontal_line(60,100,120,5,0xffff);
	horizontal_line(83,100,120,5,0xffff);
	horizontal_line(105,100,120,5,0xffff);
//r
	 vertical_line(130,60,110,5,0xffff);
	horizontal_line(60,130,145,5,0xffff);
	horizontal_line(83,130,145,3,0xffff);
	vertical_line(145,60,86,5,0xffff);
	horizontal_line(91,130,145,3,0xffff);	
	vertical_line(145,91,110,5,0xffff);
 //I
	vertical_line(170,60,110,5,0xffff);
//n
	vertical_line(185,60,110,5,0xffff);
	vertical_line(195,60,110,5,0xffff);
	horizontal_line(60,185,195,5,0xffff);	
	//p
	
	vertical_line(205,60,110,5,0xffff);
    horizontal_line(60,205,215,5,0xffff);
	horizontal_line(83,205,215,5,0xffff);
	vertical_line(215,60,88,5,0xffff);
	//u
	vertical_line(230,60,110,5,0xffff);
	vertical_line(240,60,110,5,0xffff);
	horizontal_line(105,230,240,5,0xffff);
	//t
   vertical_line(260,60,110,5,0xffff);
	horizontal_line(60,250,270,4,0xffff);
	
	  for(int x = 90 ; x < 219 ; x=x+2){
        write_pixel(x, 140, 0xf800);
        write_pixel(x, 190, 0xf800);
    }

    for(int y = 140 ; y < 190 ; y=y+2){
        write_pixel(90, y, 0xf800);
        write_pixel(218, y,0xf800);
    }
   int SW_value;    
    while(1){
        if (*KEY_ptr != 0){
            SW_value = *(SW_switch_ptr);
            while(*KEY_ptr != 0);
			display(SW_value);
        }
    }
}

void display(int SW_value){
	int k = SW_value;
	if(k==0){
    vertical_line(155,150,180,5,0xffff);
	vertical_line(165,150,180,5,0xffff);
    horizontal_line(150,155,165,5,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
	}
	if(k==1){
    vertical_line(155,150,180,5,0xffff);
	}
	if(k==2){
	 vertical_line(155,170,180,5,0xffff);
	vertical_line(165,150,169,5,0xffff);
    horizontal_line(150,155,165,5,0xffff);
	horizontal_line(165,155,170,4,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
	}
	if(k==3){ 
	vertical_line(165,150,180,5,0xffff);
    horizontal_line(150,155,165,5,0xffff);
	horizontal_line(165,155,170,4,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
	}
	if(k==4){
    vertical_line(165,170,180,5,0xffff);
	vertical_line(155,150,169,5,0xffff);    
	horizontal_line(165,155,170,4,0xffff);
	}
	
	if(k==5){
	 vertical_line(165,170,180,5,0xffff);
	vertical_line(155,150,169,5,0xffff);
    horizontal_line(150,155,170,5,0xffff);
	horizontal_line(165,155,170,4,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
	}
	
	if(k==6){
		vertical_line(165,170,180,5,0xffff);
	vertical_line(155,150,180,5,0xffff);
    horizontal_line(150,155,170,5,0xffff);
	horizontal_line(165,155,170,4,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
	}
	if(k==7){
		vertical_line(165,150,180,5,0xffff);
		horizontal_line(150,155,170,5,0xffff);
	}
	if(k==8){
		vertical_line(155,150,180,5,0xffff);
	vertical_line(165,150,180,5,0xffff);
    horizontal_line(150,155,165,5,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
		horizontal_line(165,155,170,5,0xffff);
	}
	
	if(k==9){
		vertical_line(155,150,165,5,0xffff);
	vertical_line(165,150,180,5,0xffff);
    horizontal_line(150,155,165,5,0xffff);
	horizontal_line(180,155,170,5,0xffff);	
		horizontal_line(165,155,170,5,0xffff);
	}
	while(1){
		
        if (*KEY_ptr != 0){
            SW_value = *(SW_switch_ptr);
            while(*KEY_ptr != 0);
			processing(SW_value);
        }
    }
}

void processing(int SW_value){
    srand(time(NULL));
	int k = SW_value;
	int random_number = my_rand() ;
	if(random_number == k){
	final_page();
	}	
	else {
	char *b = "TRY AGAIN! :)";
		clear_screen2();
	vertical_line(2,2,238,5,0xafc0);
    vertical_line(313,2,238,5,0xafc0);
    horizontal_line(2,2,318,5,0xafc0);
	horizontal_line(233,2,318,5,0xafc0);
		
		vertical_line(40,30,180,3,0x91f7);
    vertical_line(270,30,180,3,0x91f7);
    horizontal_line(30,40,270,5,0x91f7);
	horizontal_line(180,40,273,3,0x91f7);
   int x = 24;
    while(*b){
        write_char(x, 20, *b);
        x++;
        b++;
    }
		char *c = "Num Was -";
		x = 24;
    while(*c){
        write_char(x, 25, *c);
        x++;
        c++;
    }
		if(random_number ==0){
		  write_char(35,25,'0');
		}
		if(random_number ==1){
		  write_char(35,25,'1');
		}
		if(random_number ==2){
		  write_char(35,25,'2');
		}
		if(random_number ==3){
		  write_char(35,25,'3');
		}
		if(random_number ==4){
		  write_char(35,25,'4');
		}
		if(random_number ==5){
		  write_char(35,25,'5');
		}
		if(random_number ==6){
		  write_char(35,25,'6');
		}
		if(random_number ==7){
		  write_char(35,25,'7');
		}
		if(random_number ==8){
		  write_char(35,25,'8');
		}
		if(random_number ==9){
		  write_char(35,25,'9');
		}
	}
	char *v = "Press Any key to Play Again Game";
   int x = 34;
    while(*v){
        write_char(x, 40, *v);
        x++;
        v++;
    }
	
		while(1){
        if (*KEY_ptr != 0){   
            clear_screen2();
            while(*KEY_ptr != 0);
            instructions();		 
        }
    }
}

void final_page(){
	clear_screen2();
	 vertical_line(2,2,238,5,0xafc0);
    vertical_line(313,2,238,5,0xafc0);
    horizontal_line(2,2,318,5,0xafc0);
	horizontal_line(233,2,318,5,0xafc0);
	 for(int x = 0 ; x < 4 ; x++){
        for(int y = 0 ; y < 240 ; y=y+5){
            write_pixel(x,y,0xafc0);
        }
    }

    for(int x = 317 ; x < 321 ; x++){
        for(int y = 0 ; y < 240 ; y=y+5){
            write_pixel(x,y,0xafc0);
        }
    }

    for(int y = 0 ; y<4 ; y++){
        for(int x = 0 ; x < 320 ; x=x+5){
            write_pixel(x,y,0xafc0);
        }
    }

    for(int y = 237  ; y<241 ; y++){
        for(int x = 0 ; x < 320 ; x=x+5){
            write_pixel(x,y,0xafc0);
        }
    }
	
	vertical_line(40,30,180,3,0xf900);
    vertical_line(270,30,180,3,0xf900);
    horizontal_line(30,40,270,5,0xf900);
	horizontal_line(180,40,273,3,0xf900);
	 char *q = "CONGRADULATIONS ! YOU WON";
    int x = 24;
    while(*q){
        write_char(x, 20, *q);
        x++;
        q++;
    }
	
	char *v = "Press Any key to Play Again Game";
     x = 34;
    while(*v){
        write_char(x, 40, *v);
        x++;
        v++;
    }
	
		while(1){
        if (*KEY_ptr != 0){   
            clear_screen2();
            while(*KEY_ptr != 0);
            instructions();		 
        }
    }
	
}
void instructions(){
    vertical_line(2,2,238,5,0xafc0);
    vertical_line(313,2,238,5,0xafc0);
    horizontal_line(2,2,318,5,0xafc0);
	horizontal_line(233,2,318,5,0xafc0);

    char *q = "INSTRUCTIONS:";
    int x = 8;
    while(*q){
        write_char(x, 12, *q);
        x++;
        q++;
    }
	
	horizontal_line(54,30,90,0,0xffff);

    char *p = "1)To begin, you'll need to enter a number between 0 and 9.";
    x = 3;
    while(*p){
        write_char(x, 20, *p);
        x++;
        p++;
    }

    char *r = "2)The PC will generate a random number.";
    x=3;
    while(*r){
        write_char(x, 22, *r);
        x++;
        r++;
    }

    char *s = "3)If number matches the PC's number, CONGO ! You've won the game!";
    x = 3;
    while(*s){
        write_char(x, 24, *s);
        x++;
        s++;
    }

    char *t = "4)If number doesn't match the PC's number, you've lost this round.";
    x = 3;
    while(*t){
        write_char(x, 26, *t);
        x++;
        t++;
    }

    char *u = "5)You can play as many rounds as you'd like to try and beat the computer.";
    x = 3;
    while(*u){
        write_char(x, 28, *u);
        x++;
        u++;
    }

    char *v = "Press Any Key to Enter the Game";
    x = 45;
    while(*v){
        write_char(x, 50, *v);
        x++;
        v++;
    }

    while(1){
        if (*KEY_ptr != 0){   
            clear_screen2();
            while(*KEY_ptr != 0);
            game();
        }
    }

}

void start(){
    
    for(int x = 90 ; x < 220 ; x = x + 2){
        write_pixel(x, 30, 0xf800);
        write_pixel(x, 100, 0xf800);
    }

    for(int x = 90 ; x < 219 ; x++){
        write_pixel(x, 190, 0x001F);
        write_pixel(x, 195, 0x001F);
    }

    for(int y = 190 ; y < 196 ; y++){
        write_pixel(90, y, 0x001F);
        write_pixel(218, y, 0x001F);
    }

    draw_line(90, 190, 179, 0xffdc);

    char *p = "WELCOME TO";
    int x = 34;
    while(*p){
        write_char(x, 15, *p);
        x++;
        p++;
    }

    char *q = "Num Gusher";
    x = 34;
    while(*q){
        write_char(x, 17, *q);
        x++;
        q++;
    }

    char *r = "Loading...";
    x = 34;
    while(*r){
        write_char(x, 45, *r);
        x++;
        r++;
    }

    char *s = "Press key[0] to Enter the Game";
    x = 25;
    while(*s){
        write_char(x, 38, *s);
        x++;
        s++;
    }

    while(1){
        if (*KEY_ptr != 0){   
            while(*KEY_ptr != 0);
			clear_screen2();
            instructions();
			 
        }
    }
}

int main(){
    clear_screen2();
    start();
    return 0;
}