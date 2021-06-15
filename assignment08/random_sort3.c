/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"
#include <math.h>

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;//1950
int max_year = 2017;
int max_km = 250000;


struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}


// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
} 

// (a) todo: implement compare function
int compare(Car car1, Car car2) {
	if (car1.year > car2.year) return 1;
	else if (car1.year < car2.year) return -1;
	else return s_compare(car1.brand, car2.brand);
	return 0;
}

// (b) todo: write compare test function
int compare_test(void) {
	Car Ford_Ranger;
	Ford_Ranger.year = 1983;
	Ford_Ranger.brand = "Ford";

	Car Audi_TT;
	Audi_TT.year = 1999;
	Audi_TT.brand = "Audi";

	Car BMW_M3;
	BMW_M3.year = 1999;
	BMW_M3.brand = "BMW";
	
	Car Mercedes_AMG;
	Mercedes_AMG.year = 2009;
	Mercedes_AMG.brand = "Mercedes";

	Car VW_Golf;
	VW_Golf.year = 2009;
	VW_Golf.brand = "VW";

	test_equal_i(compare(Ford_Ranger, BMW_M3), -1);
	test_equal_i(compare(BMW_M3, Audi_TT), 1);
	test_equal_i(compare(Mercedes_AMG, VW_Golf), -1);
	test_equal_i(compare(Mercedes_AMG, Mercedes_AMG), 0);
	test_equal_i(compare(Audi_TT, Ford_Ranger), 1);
	return 0;
}

// (c) todo: implement sorted function
bool sorted(Car* a, int length) {
	if (length == 0 || length == 1) return false;
	for (int i = 0; i < length - 1; i++) {
		Car* car1 = a + i;
		Car* car2 = a + i + 1;
		if (compare(*car1, *car2) != -1) return false; //loop until the end of array, comparing index to its successor
	}
	return true;
}

// (d,e) todo: implement random_sort function
void swap(Car* a, Car* b){
	Car car;
	car = *a;
	*a = *b;
	*b = car;
}
int random_sort(Car* a, int length) {
	int counter = 0;
	if (!sorted(a, length)) {
		for(int i = 0; i < length - 1; i++){ //Sorting nach BubbleSort
			for (int j = 0; j < length - i -1; j++){
				Car* car1 = a + j;
				Car* car2 = a + j +1;
				if(compare(*car1, *car2) == 1) {
					swap(car1, car2);
					counter += 1;
				}
			}
			
		}
	}
	return counter;
}

int main(void) {
	
	// (b) todo: test compare function
	compare_test();
	//some output
	for(int i = 1; i < 100; i++){
		printf("%d. Carpark\n", i);
		int number_of_random_cars = i_rnd(7) + 3;
		Car* car_park = create_car_park(number_of_random_cars);
		print_car_array(car_park, number_of_random_cars);
		
		//todo: sort the car_park array.
		printf("Sorting...\n");
		int count = random_sort(car_park, number_of_random_cars);
		printf("Durchschnittswert von swap: %d\n", count);
		random_sort(car_park, number_of_random_cars);
		print_car_array(car_park, number_of_random_cars);
		delete_car_park(car_park);
	}
    return 0;
}
