/*
make document_iterator && ./document_iterator
*/

#include "base.h"

// Represents a document, made up of lines of ASCII letters.
typedef struct {
    char** lines; // array of lines, each line is a zero-terminated string
    int line_count; // number of lines
} Document;

// Create a new document.
Document make_document(char** lines, int line_count) {
    require_not_null(lines);
    require("not negative", line_count >= 0);
    require("no null lines", forall(i, line_count, lines[i] != NULL));
    Document d = { lines, line_count };
    return d;
}

// Represents the state of a document iterator. Iterates character by character.
typedef struct {
    Document* document; // the document to iterate over
    int line; // zero-based line number
    int column; // zero-based column number
} DocumentIterator;

// Initializes an iterator for the given document. Iterates character by character.
DocumentIterator make_document_iterator(Document* doc) {
    require_not_null(doc);
    DocumentIterator it = { doc, 0, -1 };
    return it;
}

// Checks if the iterator has more characters to iterate.
bool iter_has_next(DocumentIterator* it) {
    // todo: implement
    if (it->line == it->document->line_count && it->column == s_length(it->document->lines[it->line]) - 1) return false;
    else return true;
} 

// Represents the current iteration state that is returned from the iterator.
typedef struct {
    int line; // zero-based line number
    int column; // zero-based column number
    char c; // the current character
} CharAndPosition;

// Returns the next character of the document and its position.
CharAndPosition iter_next(DocumentIterator* it) {
    // todo: implement
    
        if (it->line < it->document->line_count) {
            if (it->document->lines[it->line][it->column + 1] != '\0') {
                it->column++;
            }
            else {
                it->line++;
                it->column = 0;
            }
        }
        else {
            it->column++;
        }
    CharAndPosition result = {it->line, it->column, it->document->lines[it->line][it->column]};
    return result;
}

void test(void) {
    char* letter[] = {
        "Dear Grandma,",
        "",
        "My first semester at the university",
        "is now over. I very much liked",
        "Programming 1. What I did not like",
        "so much was that all courses were",
        "online. All the best!",
        "",
        "Yours,",
        "Otto"
    };
    int n = sizeof(letter) / sizeof(char*);
    Document doc = make_document(letter, n);

    DocumentIterator it;
    
    it = make_document_iterator(&doc);
    while (iter_has_next(&it)) {
        CharAndPosition cp = iter_next(&it);
        printf("%c(%d:%d) ", cp.c, cp.line, cp.column);
    }
    println();
    
    it = make_document_iterator(&doc);
    test_equal_b(iter_has_next(&it), true);
    CharAndPosition cp = iter_next(&it);
    test_equal_b(cp.c == 'D' && cp.line == 0 && cp.column == 0, true);
    test_equal_c(cp.c, 'D');
    test_equal_i(cp.line, 0);
    test_equal_i(cp.column, 0);
    cp = iter_next(&it);
    test_equal_b(cp.c == 'e' && cp.line == 0 && cp.column == 1, true);
    test_equal_c(cp.c, 'e');
    test_equal_i(cp.line, 0);
    test_equal_i(cp.column, 1);
    for (int i = 0; i < 13; i++) { //(int i = 0; i < 12; i++)
        cp = iter_next(&it);
    }
    test_equal_b(cp.c == 'M' && cp.line == 2 && cp.column == 0, true);
    test_equal_c(cp.c, 'M');
    test_equal_i(cp.line, 2);
    test_equal_i(cp.column, 0);
    cp = iter_next(&it);
    test_equal_b(cp.c == 'y' && cp.line == 2 && cp.column == 1, true);
    test_equal_c(cp.c, 'y');
    test_equal_i(cp.line, 2);
    test_equal_i(cp.column, 1);
    cp = iter_next(&it);
    test_equal_b(iter_has_next(&it), true);
    for (int i = 0; i < 162; i++) { //(int i = 0; i < 160; i++)
        cp = iter_next(&it);
    }
    test_equal_b(iter_has_next(&it), false);
}

int main(void) {
    test();
    char* letter[] = {
        "Dear Grandma,",
        "",
        "My first semester at the university",
        "is now over. I very much liked",
        "Programming 1. What I did not like",
        "so much was that all courses were",
        "online. All the best!",
        "",
        "Yours,",
        "Otto"
    };
    int n = sizeof(letter) / sizeof(char*);
    Document doc = make_document(letter, n);

    DocumentIterator it;
    it = make_document_iterator(&doc);
    int i = s_length(it.document->lines[0]);
    printf("%i\n", i);
    return 0;
}