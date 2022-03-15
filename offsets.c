/*
make offsets && ./offsets
*/

#include "base.h"

// Represents a cursor position in a document. The cursor is always positioned between two characters or at the beginning or end of a line.
typedef struct {
    int line;
    int column;
} Position;

// Create a new cursor position.
Position make_position(int line, int column) {
    require("not negative", line >= 0);
    require("not negative", column >= 0);
    Position p = { line, column };
    return p;
}

// Represents a document consisting of line_count lines.
typedef struct {
    char** lines; // an array of lines, each line is a zero-terminated string
    int line_count; // the number of lines in the document
} Document;

// Create a new document.
Document make_document(char** lines, int line_count) {
    require_not_null(lines);
    require("not negative", line_count >= 0);
    // require("no null lines", forall(i, line_count, lines[i] != NULL));
    Document d = { lines, line_count };
    return d;
}

// Checks if offset is a valid offset in the given document.
bool is_valid_offset(int offset, Document doc) {
    // todo: implement 
    int a = 0;
    for (int i = 0; i < doc.line_count; i++) {
        a += strlen(doc.lines[i]);
        if (strlen(doc.lines[i]) == 0) a++;
    }
    if (offset > a || offset < 0 || doc.line_count < 1) return false;
    else return true;
}

// Returns the position corresponding to the given offset in the given document.
Position position_at(int offset, Document doc) {
    // todo: implement
    int x = 0;
    int y = 0;
    for (int i = 0; i < offset; i++) {
        if (x < strlen(doc.lines[y])) x++;
        else {
            x = 0;
            y++;
        }
    }
    return make_position(y, x);
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
    printiln(n);
    printsln(letter[0]);
    printsln(letter[1]);
    printsln(letter[2]);
    Document doc = make_document(letter, n);
    printiln(strlen(doc.lines[0]));
    printiln(strlen(doc.lines[1]));
    printiln(strlen(doc.lines[2]));

    test_equal_b(is_valid_offset(-1, make_document(letter, 0)), false);
    test_equal_b(is_valid_offset(0, make_document(letter, 0)), false);
    test_equal_b(is_valid_offset(1, make_document(letter, 0)), false);
    test_equal_b(is_valid_offset(-1, make_document(letter, 1)), false);
    test_equal_b(is_valid_offset(0, make_document(letter, 1)), true);
    test_equal_b(is_valid_offset(13, make_document(letter, 1)), true);
    test_equal_b(is_valid_offset(14, make_document(letter, 1)), false);
    test_equal_b(is_valid_offset(14, make_document(letter, 2)), true);
    test_equal_b(is_valid_offset(15, make_document(letter, 2)), false);

    Position pos = position_at(0, doc);
    test_equal_b(pos.line == 0 && pos.column == 0, true);
    pos = position_at(1, doc);
    test_equal_b(pos.line == 0 && pos.column == 1, true);
    pos = position_at(2, doc);
    test_equal_b(pos.line == 0 && pos.column == 2, true);
    pos = position_at(13, doc);
    test_equal_b(pos.line == 0 && pos.column == 13, true);
    pos = position_at(14, doc);
    test_equal_b(pos.line == 1 && pos.column == 0, true);
    pos = position_at(15, doc);
    test_equal_b(pos.line == 2 && pos.column == 0, true);
    pos = position_at(16, doc);
    test_equal_b(pos.line == 2 && pos.column == 1, true);
    pos = position_at(51, doc);
    test_equal_b(pos.line == 3 && pos.column == 0, true);
}

int main(void) {
    test();
    return 0;
}