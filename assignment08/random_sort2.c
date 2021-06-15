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
int min_year = 1950;
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

//end of template code

//now it is your turn ... 

// (a) todo: implement compare function
int compare(Car car1, Car car2){
	if(car1.year < car2.year) return 1;
	if(car1.year > car2.year) return -1;

	// car1 age == car2 age
	// check brand euqal -> return 0
	
	/*if(strcmp(car1.brand, car2.brand) == 0){
		return 0;
	}*/

	return strcmp(car1.brand, car2.brand);
	//str1 < str2 -> -1
	//str1 > str2 -> +1
	//str1 == str2 -> 0

	//BMW < MERCEDES

}

// (b) todo: write compare test function
void compare_test(void){
	Car a = {"BMW", 2017, 100, 100000.0};
	Car b = {"BMW", 2018, 100, 100000.0};
	test_equal_i(compare(a,b), 1);

	a.year = 2019;
	test_equal_i(compare(a,b), -1);
	
	a.year = 2018;
	test_equal_i(compare(a,b), 0);

	a.brand = "Mercedes";
	test_equal_i(compare(a,b), 1);

	a.brand = "Alfa Romeo";
	test_equal_i(compare(a,b), -1);
}

// (c) todo: implement sorted function
bool sorted(Car* a, int length){
	//   0    1      2     3
	//[car1, car2, car3, car4]
	//length = 4
	for(int i = 0; i < length - 1; i++){
		if(compare(a[i], a[i+1]) > 0) return false;
	}
	return true;
}

//randomly sorts an array return the number of swaps
int random_sort(Car* a, int length) {
	int swaps = 0;
	while(sorted(a, length) == false){ //everytime sorted gets called its doing "compare" length-1 times
		int i1 = i_rnd(length);
		int i2 = i_rnd(length);
		Car temp = a[i1];
		a[i1] = a[i2];
		a[i2] = temp;
		swaps++; 
	}
	return swaps;
}
/*
[car1, car2, car3, car4] length -> 4

swaps = 4;
compares? = 3 + 3 + 3 + 3 + 3

compares = (swaps + 1) * (length - 1)

length = 4
swaps = 4
compares = 15

length = 15
swaps = 100
compares = 101 * 14

A: Yes you can if the length of the array is known aswell, the formula is:
compares = (swaps + 1) * (length - 1)
*/

int main(void) {
	
	// (b) todo: test compare function
	compare_test();
	
	
	//some output
	int number_of_random_cars = 10;
	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sorting...\n");
	
	//todo: sort the car_park array.
	random_sort(car_park, 10);
	
	print_car_array(car_park, number_of_random_cars);
	
	delete_car_park(car_park);
	
	
	
	// (f) todo: compare the number of swaps and compare calls.
	for(int size = 3; size < 9; size++){
		int swaps_total = 0;
		
		for(int i = 0; i < 100; i++){
			Car* car_park = create_car_park(size);
			int swaps = random_sort(car_park, size);
			swaps_total = swaps_total + swaps;
		}
		double compares_mean = (double)((swaps_total + 1) * (size - 1)) / 100.0;

		double swaps_mean = (double)swaps_total / 100.0;
		printf("Sorting 100 car arrays of length %d took %.2f swaps and %.2f compares in average\n", size, swaps_mean, compares_mean);
	}
	
    return 0;
}
