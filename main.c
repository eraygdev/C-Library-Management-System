#include <stdio.h>
#include "library.h"

extern Book archive[];
extern int number_of_books;

int main()
{
    load_Library();
    while(1)
    {

        int choice = ask_Q1(4);
        switch(choice) {
            case 0: save_Library(); return 0;
            case 1: show_Books(); break;
            case 2: add_Book(); break;
            case 3: remove_Book(); break;
            case 4: search_Book(); break;
            default: printf("An error occurred."); save_Library(); return 0;
        }

        printf("\nMenuye donmek icin Enter'a basin...");
        getchar();

        clear_screen();
    }

    save_Library();
    printf("\n\nProgram has successfully completed!");

    return 0;
}
