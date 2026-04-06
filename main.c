#include <stdio.h>
#include "library.h"

extern Book archive[];
extern int number_of_books;

int main()
{
    printf("\n");
    load_Library();
    while(1)
    {

        int choice = ask_Q1(6);
        switch(choice) {
            case -1: if(force_Leave() == 1) return 0; else continue;
            case 0: save_Library(); return 0;
            case 1: show_Books(); break;
            case 2: add_Book(); break;
            case 3: remove_Book(); break;
            case 4: search_Book(); break;
            case 5: edit_Book(); break;
            default: printf("An error occurred."); save_Library(); return 0;
        }

        printf("\nPress Enter to return to the menu...");
        getchar();

        clear_screen();
    }

    save_Library();
    printf("\n\nProgram has successfully completed!");

    return 0;
}
