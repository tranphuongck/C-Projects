/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a) struct Statistics ...
     typedef struct  {
		int D_Geburtsjahr;
        int Anzahl_m;
        int Anzahl_f; //Das durchschnittliche Geburtsjahr (gerundet auf ganze Jahre), Die Anzahl Männer in der Tabelle, Die Anzahl Frauen in der Tabelle.
		double DDKDM;
        double DDKDF; // Die durchschnittliche Körpergröße der Männer, Die durchschnittliche Körpergröße der Frauen.
	 }Statistics;
	 
// b) ... make_statistics...
    Statistics make_statistics(){
        Statistics list = {0,0,0,0.0,0.0};
        
	return list;
	}
		
// c) ... print_statistics...

 	int print_statistics( int D_Geburtsjahr,int Anzahl_m,int Anzahl_f,double DDKDM,double DDKDF ){
		 printf("mean year: %d\n",D_Geburtsjahr);
		 printf("number males: %d\n",Anzahl_m);
		 printf("number females: %d\n",Anzahl_f);
		 printf("mean height males: %.2f\n",DDKDM);
		 printf("mean height females: %.2f\n",DDKDF);
		 
		 return 0;
	 }
	 
	 
// d) ... compute_statistics...
// ... compute_statistics(table);
int main() {
    Statistics list;
    make_statistics(list);
	String table = s_read_file("people.txt");
	int i,y,b,c = 0;
	for(i = 15,y = 20; i < y && y < s_length(table); i = i + 12,y = y + 12){
		String Jahr = s_sub( table,i,y);
		int a = i_of_s(Jahr);
		b = b + a;
		c++;
		}
	list.D_Geburtsjahr = b / c;
	int e,f,g;
	double j = 0, h = 0;
	list.Anzahl_f = 0;
    for(e = 21,f = 23, g = 27; e <= s_length(table) && f < g; e = e + 12,f = f + 12,g = g + 12){
		char Sex = s_get(table,e);
		if( Sex == 'm'){ 
			String Size = s_sub( table,f,g);
			double a = d_of_s(Size);
			j = j + a;
			list.Anzahl_m++;
			} else {
				String Size = s_sub( table,f,g);
				double a = d_of_s(Size);
				h = h + a;
				list.Anzahl_f++;	
				}
			}

	list.DDKDM = j / list.Anzahl_m;
	list.DDKDF = h / list.Anzahl_f;
	
	// print_statistics(...);
	print_statistics(list.D_Geburtsjahr,list.Anzahl_m,list.Anzahl_f,list.DDKDM,list.DDKDF);
	return 0;
}
