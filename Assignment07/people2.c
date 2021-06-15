/*
Compile: make people
Run: ./people
*/

#include "base.h"
#include "string.h"

// a) struct Statistics ...
struct Statistics {
	int mean_year;
	int number_males;
	int number_females;
	double mean_height_males;
	double mean_height_females;
};
typedef struct Statistics Statistics;

// b) ... make_statistics...
Statistics make_statistics(void) {
	Statistics stats = {0, 0, 0, 0.0, 0.0};
	return stats;
}

// c) ... print_statistics...
void print_statistics(Statistics s) {
	printf("mean year:           %4d \n", s.mean_year);
	printf("number males:        %4d \n", s.number_males);
	printf("number females:      %4d \n", s.number_females);
	printf("mean height males:   %1.2fm \n", s.mean_height_males);
	printf("mean height females: %1.2fm \n", s.mean_height_females);
}

// d) ... compute_statistics...
Statistics compute_statistics(String table){
	Statistics stats = make_statistics();
	int i = 0, j = 0; //int i, j = 0; => s_get precondition index in range violated
	int n = s_length(table);

	while (s_get(table, i) != '\n') i++; //skip header

	while (i < n) {
		j = i;
		while (j < n && s_get(table, j) != '\t') j++; //skip 1st whitespace
		int year = i_of_s(s_sub(table, i, j)); //convert year in txt to integer
		stats.mean_year = stats.mean_year + year; //sum of all years

		i = j + 1;
		char sex = s_get(table, i);
		if (sex == 'm')				
			stats.number_males++;
		else
			stats.number_females++;
		
		i = i + 2; //skip 2nd whitespace
		j = i;
		while (j < n && s_get(table, j) != '\n') j++;
		double height = d_of_s(s_sub(table, i, j)); //convert height in txt to double
		if (sex == 'm')
			stats.mean_height_males = stats.mean_height_males + height;
		else if (sex == 'f')
			stats.mean_height_females = stats.mean_height_males + height;
		i = j + 1;
	}
	stats.mean_year = stats.mean_year / (stats.number_males + stats.number_females); //avg year = year sum / number of both sexes
	stats.mean_height_males = stats.mean_height_males / stats.number_males;
	stats.mean_height_females = stats.mean_height_females / stats.number_females;
	return stats;
}

int main(void) {
	String people = s_read_file("people.txt");
	printsln(people);
	//Format of the table:
	//printsln("Year\tSex\tHeight\n1234\tm\t1.70\n......");
	compute_statistics(people);
	print_statistics(compute_statistics(people));
	//printf("%4d", s_length(people));
	return 0;
}