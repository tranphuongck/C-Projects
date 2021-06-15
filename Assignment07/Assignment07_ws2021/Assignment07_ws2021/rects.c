#include "base.h"
/*
    make rects
    ./rects
    make rects && ./rects
*/

enum FillProperty{
    RANGE,
    SIMPLE,
    PATTERN
} typedef TFillProperty;

struct RangeFill{
    char start;
    char end;
} typedef RangeFill;

struct SimpleFill{
    char c;
} typedef SimpleFill;

struct PatternFill{
    String pattern;
} typedef PatternFill;

struct Fill{
    TFillProperty tag;
    union{
        PatternFill pf;
        SimpleFill sf;
        RangeFill rf;  
    };
}typedef Fill;

struct Rect{
    int x, y;
    int width, height;
    Fill fill;    
} typedef Rect;

Fill make_range_fill(char lower, char upper){
    //todo:
    require("valid input", lower <= upper && lower >= 1 && lower <= 127 && upper >= 1 && upper <= 127);
    Fill fill;
    fill.tag = RANGE;
    fill.rf.start = lower;
    fill.rf.end = upper;
    return fill;
}

Fill make_pattern_fill(String s){
    require("valid input", s_length(s) > 0);
    Fill fill;
    fill.tag = PATTERN;
    fill.pf.pattern = s;
    return fill;
}

Fill make_simple_fill(char c){
    //todo:
    require("valid input", c >= 1 && c <= 127);
    Fill fill;
    fill.tag = SIMPLE;
    fill.sf.c = c;
    return fill;
    
}

Rect make_rect(int x, int y, int width, int height, Fill fill){
    //todo:
    require("valid input", x >= 0 && y >= 0 && width > 0 && height > 0);
    Rect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    rect.fill = fill;
    return rect;
}    

void printcs(char c, int n) {
    for (int x = 0; x < n; x++) printc(c);
}

void printstr(String s, int n){
	int lg = s_length(s);
	int k = n/lg; //berechnet man wie viele Mals das String s wiederholen
	String s1 = "";
	for(int i = 0; i < k; i++){
		s1 = s_concat(s1, s); //verschmerzeln k mals String s als ein String s1
	}
	
	int r = n%lg; //berechnet viele Characters zu fehlen noch, um mit der Länge n zu erfüllen
	String s2 = s_sub(s, 0, r); //teilt diesen Characters als String s2 auf
	
	String s3 = s_concat(s1, s2);//verschmerzeln String s1, String s2 als String s3
	for(int j = 0; j < s_length(s3); j++){
		printc(s3[j]); //druckt jedes Character aus
	}
}


void print_in_range(char start, char end, int width, int height, int x){
	
	
	String s = s_range(start, end +1);
	int lg = s_length(s);
	int k = (width*height)/lg; //berechnet man wie viele Mals das String s wiederholen in Matrix width*height
	int q = 0;
	String s1  = "";
	for(int i = 0; i < k; i++){
		s1 = s_concat(s1, s); //verschmerzeln k mals String s als ein String s1
	}
	
	int r = (width*height)%lg; //berechnet viele Characters zu fehlen noch, um mit der Länge width*height zu erfüllen
	String s2 = s_sub(s, 0, r); //teilt diesen Characters als String s2 auf
	
	String s3 = s_concat(s1, s2); //verschmerzeln String s1, String s2 als String s3
	int lg3 = s_length(s3);
	int col = lg3/width;
	
	char maxtri[col][width]; //erstellt ein zwei Dimensional Matrix[][]
	
	
	for(int i = 0; i < col; i++){
		for(int j = 0; j < width; j++){
			maxtri[i][j] = s3[q]; //füllt String s3 in Matrix
			q++;
		}
	}
	
	for(int i = 0; i < col; i++){
		printf("%*s", x, "");
		printc('|');
		for(int j = 0; j < width; j++){
			if(maxtri[i][j] == ' ') //duckt in neue Zeile
				break;
			printc(maxtri[i][j]); //duckt jedes Character aus
		}
		if(width > 1) printf("|\n");
	}

	
}

	
void print_outer_row(int width) {
	
    printc('+');
    printcs('-', width - 2);
    if (width > 1) {
        printc('+');
    }
    println();
}

void print_inner_row(int width, int height, int x, Fill fill) {

	if(fill.tag == SIMPLE){
		printc('|');
		printcs(fill.sf.c, width -2); //minus 2 Zeichen "|" in erste und "|" letzte
		if (width > 1) {
			printc('|');
		}
		println();
	}
	
	if(fill.tag == PATTERN){
		printc('|');
		printstr(fill.pf.pattern, width-2); //minus 2 Zeichen "|" in erste und "|" letzte
		if (width > 1) {
			printc('|');
		}
		println();
	}
	
	if(fill.tag == RANGE){
		print_in_range(fill.rf.start, fill.rf.end, width-2, height-2, x);
	}
	
}

void draw_rect(Rect rect){
    for (int j = 0; j < rect.y; j++) println();
    printf("%*s", rect.x, "");
    print_outer_row(rect.width);
    for (int k = 1; k < rect.height - 1; k++) {
        if(rect.fill.tag == SIMPLE){
			printf("%*s", rect.x, "");
			print_inner_row(rect.width, rect.height, rect.x, rect.fill);
		}
		
		if(rect.fill.tag == PATTERN){
			printf("%*s", rect.x, "");
			print_inner_row(rect.width, rect.height, rect.x, rect.fill);
		}
    }
	
	if(rect.fill.tag == RANGE){
		print_inner_row(rect.width, rect.height, rect.x, rect.fill);
	}
    printf("%*s", rect.x, "");
	
    print_outer_row(rect.width);
}
/*
width = 1, height = 1
+

width = 1, height = 2
+
+

width = 2, height = 1
++

width = 2, height = 2
++
++

width = 3, height = 2
+-+
+-+

width = 3, height = 3, x = 1, y = 0, fill = simple with 'o'

 +-+
 |o|
 +-+
 
width = 15, height = 10, x = 15, y = 0, fill = pattern with ".o"
               +-------------+
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               +-------------+
*/
int main(void){
    // Mindestens 6 verschiedene Rechtecke mit unterschiedlichen Position, Fuellungen und Groeßen.
    draw_rect(make_rect(3, 1, 3, 2, make_simple_fill('o')));
	draw_rect(make_rect(1, 0, 3, 3, make_simple_fill('o')));
	draw_rect(make_rect(10, 0, 15, 10, make_simple_fill('x')));
	draw_rect(make_rect(0, 0, 15, 10, make_pattern_fill(".o")));
	draw_rect(make_rect(10, 0, 15, 10, make_pattern_fill(".:.")));
	draw_rect(make_rect(0, 0, 7, 9, make_range_fill('0', '9')));
	draw_rect(make_rect(3, 5, 7, 9, make_range_fill('1', '8'))); //Nach rechts x = 3 und nach unter y = 5
    
    return 0;
}