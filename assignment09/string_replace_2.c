/*
    make string_replace
    ./string_replace
    make string_replace && ./string_replace
*/
#include "base.h"

char* next_occurence(char* s, char* find)
{
	while (*s) {
		char* s1 = s;
		char* f1 = find;
		    // prüft ganzes String s & find
		while (*s && *f1 && *s == *f1) {
			s++;
			f1++;
		}
		// wenn alle Emlemente von find gelesen werden, return die Beginn von Andress
		if (!*f1) return s1;
		s++;
	}
	return NULL;
}

void test_next_occurence(){
    test_equal_s(next_occurence("aabbccdd", "aa"), "aabbccdd");
    test_equal_b(next_occurence("abbccdd", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa")== NULL, true);
    test_equal_s(next_occurence("abbccdda", "a"), "abbccdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye")== NULL, true);
}


int count(char* s, char* find){
    //todo:
	
	int cnt = 0;
	int i = 0;
	for(i = 0; s[i] != '\0'; i++){
		//Jedes Mal erscheint find-String in s-String, wird es cnt um 1 gestiegt.
		if(next_occurence(&s[i], find) == &s[i]){
			cnt++;
		}
	}
    return cnt;
	
	/*
	//Another way
	int cnt = 0;
	int found;
	for(int i = 0; i< strlen(s); i++){
		found = 1;
		for(int j = 0; j < strlen(find); j++){
			if(s[i+j] != find[j]){
				found = 0;
				break;
			}
		}
		if(found == 1){
			cnt++;
		}
	}*/
	
}

void test_count(){
    test_equal_i(count("aabbccdd", "ab"), 1);
    test_equal_i(count("abbccdda", "aa"), 0);
    test_equal_i(count("aabbaadd", "aa"), 2);
    test_equal_i(count("aabbccdd", "a"), 2);
    test_equal_i(count("aabbccdd", "abbc"), 1);
    test_equal_i(count("Die Uhrzeit ist 3:10", "Uhrzeit"), 1);
    test_equal_i(count("hello, hello world", "hello"), 2);
    test_equal_i(count("hello, hello world", "ello"), 2);
}

//Hilfsfunktion: copy String to another
char* _strcpy(char* des, char* src){
	char* start = des;
	
	//liest bis Ende String s
    while(*src != '\0'){
		*des = *src; //assign alle Emlemente von src in des-String hinzufügen
		des++;
        src++;
	}

    *des = '\0';
    return start;
}

char* replace(char* s, char* find, char* replace_by){
	
    int i = 0;
	int cnt = count(s, find); //berechnet wie viele Mals find-String in s-String wiederholen.
	
	//aufgabe (c)
	char *out = (char*)xmalloc(i + cnt *(strlen(find) - strlen(replace_by)) + 1);
	
	i = 0;
	while(*s != '\0'){
		if(next_occurence(s, find) == s){
			_strcpy(&out[i], replace_by); //ersetzt out[i] durch replace_by
			i += strlen(replace_by); //index von i um strlen(replace_by) steigen.
			s += strlen(find); //gleizeitig index von s um strlen(find) steigen
		}else{
			out[i++] = *s++; //else liest es weiter und hinfügen die Elemente von s-String in out-String
		}
	}
	out[i] = '\0'; //hifügen '\0' Ende
	
    return out;
}

void test_replace(){
    test_equal_s(replace("aabbccdd", "a", "d"), "ddbbccdd");
    test_equal_s(replace("aaabbccdd", "aa", "d"), "dabbccdd");
    test_equal_s(replace("aabbccdd", "aa", "d"), "dbbccdd");
    test_equal_s(replace("aabbccdd", "b", "olo"), "aaolooloccdd");
    test_equal_s(replace("aabbccdd", "c", ""), "aabbdd");
    test_equal_s(replace("hello, hello world", "hello", "bye"), "bye, bye world");
    test_equal_s(replace("aabbccdd", "dd", "eee"), "aabbcceee");
    test_equal_s(replace("for(int x = X; x < X * 3; x++){printiln(x);}", "X", "90"), "for(int x = 90; x < 90 * 3; x++){printiln(x);}");
}

int main(void){
	printsln("*********Test Next Occurence*********");
    test_next_occurence();
	printsln("*********Test Count*********");
    test_count();
	printsln("*********Test Replace**********");
    test_replace();
    return 0;
}
    