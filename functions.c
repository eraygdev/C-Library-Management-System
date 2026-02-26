#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "library.h"

extern Book archive[];
extern int number_of_books;

void clear_input_buffer() {while(getchar() != '\n');}
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void lowercase_text(char text[])
{
    for(int i = 0; text[i] != '\0'; i++)
        text[i] = tolower((unsigned char)text[i]);
}

void delete_index_archive(int index)
{
    if(index < 0 || index >= library_size || archive[index].ID == 0)
    {
        printf("Invalid index or book not found!");
        return;
    }

    for(int i = index; i < number_of_books - 1; i++)
    {
        archive[i] = archive[i + 1];
    }

    archive[number_of_books - 1] = (struct Book){0};
    number_of_books -= 1;
    return;
}

int ask_Q1(int case_size)
{
    int temp = 0;
    while(1)
    {
        printf("|0| save and leave\n|1| show books (%d)\n|2| add book\n|3| remove book\n|4| search book\nPlease select an option and click \"Enter\": ", number_of_books);

        if((scanf("%d", &temp) == 1) && (temp >= 0) && (temp <= case_size))
        {
            clear_input_buffer();
            printf("\n");
            return temp;
        }
        else
        {
            printf("Invalid input! Please choose a number between 0-%d\n\n", case_size);
            clear_input_buffer();
        }
    }
}

void show_Books()
{
    printf("\n--- CURRENT ARCHIVE ---\n");
    int found_count = 0;

    for(int i = 0; i < library_size; i++)
    {
        if(archive[i].ID != 0)
        {
            found_count++;
            printf("%d)\n", found_count);
            printf("Title  : %s\n", archive[i].title);
            printf("Author : %s\n", archive[i].author);
            printf("Page   : %d\n", archive[i].page);
            printf("ID     : %d\n\n", archive[i].ID);
        }
    }

    if(found_count == 0) {
        printf("The archive is empty!\n");
    }
}

void add_Book()
{
    if(number_of_books < library_size) {
        int index = number_of_books;

        while(1)
        {
            printf("Please enter the title (Max 127 characters): ");
            fgets(archive[index].title, MAX_TITLE, stdin);
            if(strpbrk(archive[index].title, "\n\r") == NULL)
            {
                printf("\nLimit exceeded!");
                clear_input_buffer();
            }
            else
            {
                archive[index].title[strcspn(archive[index].title, "\n\r")] = '\0';
                break;
            }
        }

        while(1)
        {
            printf("Please enter the author (Max 63 characters): ");
            fgets(archive[index].author, MAX_AUTHOR, stdin);
            if(strpbrk(archive[index].author, "\n\r") == NULL)
            {
                printf("\nLimit exceeded!");
                clear_input_buffer();
            }
            else
            {
                archive[index].author[strcspn(archive[index].author, "\n\r")] = '\0';
                break;
            }
        }

        while(1)
        {
            printf("Please enter page count (1 - 20000): ");
            if(scanf("%d", &archive[index].page) != 1)
            {
                printf("\nPlease enter a valid number!\n");
                clear_input_buffer();
                continue;
            }

            if(archive[index].page < 1 || archive[index].page > 20000)
            {
                printf("\nPage count must be between 1 and 20000!\n");
            }
            else
            {
                clear_input_buffer();
                break;
            }
        }

        archive[index].ID = index + 1;
        number_of_books++;

        printf("\nBook added successfully! (ID: %d)\n", archive[index].ID);
    }
    else {
        printf("\nLibrary is full!\n");
    }
}

void remove_Book()
{
    printf("Please enter the ID of the book you want to delete (-1 to go back): ");
    if(number_of_books <= 0)
    {
        printf("Library is empty! (%d)", number_of_books);
        return;
    }

    int index;
    if(scanf("%d", &index) == 1)
    {
        clear_input_buffer();
        if(index == -1) return;

        for(int i = 0; i < number_of_books; i++)
        {
            if((archive[i].ID == index))
            {
                delete_index_archive(i);
                return;
            }
        }
    }
    else
    {
        printf("Invalid input!");
        return;
    }
}

void search_Book()
{
    while(1)
    {

        printf("Please enter the name of the book you want to find (-1 to go back): ");
        char input[MAX_TITLE + 2];
        fgets(input, MAX_TITLE + 2, stdin);
        if(strpbrk(input, "\n\r") == NULL)
        {
            printf("\nLimit exceeded!");
            clear_input_buffer();
            continue;
        }
        else
        {
            input[strcspn(input, "\n\r")] = '\0';
            if (strcmp(input, "-1") == 0) break;

            char loweredinput[MAX_TITLE + 2];
            strcpy(loweredinput, input);
            lowercase_text(loweredinput);

            int found_count = 0;
            printf("\n--- SEARCH RESULTS ---\n");
            for(int i = 0; i < number_of_books; i++)
            {
                char temp[MAX_TITLE + 1];
                strcpy(temp, archive[i].title);
                lowercase_text(temp);

                if(strstr(temp, loweredinput) != NULL)
                {

                    found_count++;
                    printf("%d)\n", found_count);
                    printf("Title  : %s\n", archive[i].title);
                    printf("Author : %s\n", archive[i].author);
                    printf("Page   : %d\n", archive[i].page);
                    printf("ID     : %d\n\n", archive[i].ID);
                }
            }
            if(found_count > 0)
            {
                printf("\n------------------------------\n");
                printf("Success: %d book(s) found.\n", found_count);
                printf("------------------------------\n");
            }
            else printf("\n! No matches found for your search.\n");
        }
    }
}

void load_Library()
{
    FILE *rFile = fopen("library.dat", "rb");

    if(rFile == NULL)
    {
        number_of_books = 0;
        printf("library.dat could not be found!\nCreating a new file...\n");

        FILE *temp = fopen("library.dat", "wb");
        if(temp != NULL) fclose(temp);
    }
    else
    {
        int read_count = fread(archive, sizeof(Book), library_size, rFile);
        fclose(rFile);

        number_of_books = read_count;
        printf("Loaded %d valid books.\n", number_of_books);
    }
}

void save_Library()
{
    FILE *wFile = fopen("library.dat", "wb");
    if(wFile == NULL)
    {
        printf("Data could not be saved!");
        return;
    }

    printf("Saving...\n");
    fwrite(archive, sizeof(Book), number_of_books, wFile);
    fclose(wFile);
    printf("Successfully saved!\n");
}
