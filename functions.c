#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "library.h"

extern Book archive[];
extern int number_of_books;

void clear_input_buffer() {while(getchar() != '\n');}
void clear_back_n(char *i) {i[strcspn(i, "\n")] = 0;}
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
int input_limit_check(char target[])
{
    if(strpbrk(target, "\n\r") == NULL)
    {
        printf("Limit exceeded!\n\n");
        clear_input_buffer();
        return 0;
    }
    else
    {
        target[strcspn(target, "\n\r")] = '\0';
        return 1;
    }
}
int y_or_n()
{
    while(1)
    {
        char letter;
        printf("\nAre you sure? (y or n): ");
        if(scanf("%c", &letter) == 1 && (letter == 'y' || letter == 'n')) return letter == 'y' ? 1 : 0;
        else printf("Invalid input! (y or n): ");
        clear_input_buffer();
    }
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
        printf("(-1 to leave without saving)\n|0| save and leave\n|1| show books (%d)\n|2| add book\n|3| remove book\n|4| search book\n|5| edit book\nPlease select an option and click \"Enter\": ", number_of_books);

        if((scanf("%d", &temp) == 1) && (temp >= -1) && (temp < case_size))
        {
            clear_input_buffer();
            return temp;
        }
        else
        {
            printf("\nInvalid input! Please choose a number between 0-%d\n\n", case_size);
            clear_input_buffer();
        }
    }
}

int force_Leave()
{
    return y_or_n();
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
    if(number_of_books < library_size)
    {
        int index = number_of_books;

        while(1)
        {
            printf("\nPlease enter the title (Max 127 characters): ");
            fgets(archive[index].title, MAX_TITLE, stdin);
            if(input_limit_check(archive[index].title)) break;
        }

        while(1)
        {
            printf("Please enter the author (Max 63 characters): ");
            fgets(archive[index].author, MAX_AUTHOR, stdin);
            if(input_limit_check(archive[index].author)) break;
        }

        while(1)
        {
            printf("Please enter page count (1 - 20000): ");
            if(scanf("%d", &archive[index].page) != 1)
            {
                printf("Please enter a valid number!\n\n");
                clear_input_buffer();
                continue;
            }

            int maxnumber = 20000;
            if(archive[index].page < 1 || archive[index].page > maxnumber)
            {
                printf("Page count must be between 1 and %d!\n\n", maxnumber);
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
    else printf("\nLibrary is full!\n");
}

void remove_Book()
{
    printf("\nPlease enter the ID of the book you want to delete (-1 to go back): ");
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
        printf("\nHow would you like to search?\n|1| title\n|2| author\n|3| ID\n(-1 to go back): ");
        int mode;
        if(scanf("%d", &mode) == 1 && (mode == -1 || mode == 1 || mode == 2 || mode == 3))
        {
            if(mode == -1) return;
            printf("Please enter the %s of the book (-1 to go back): ", (mode == 1 ? "title" : (mode == 2 ? "author" : "ID")));
        }
        else
        {
            printf("Invalid input!\n\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (mode == 1 || mode == 2)
        {
            int temp_input_size = mode == 1 ? MAX_TITLE + 2 : MAX_AUTHOR + 2;

            char input[temp_input_size];
            fgets(input, temp_input_size, stdin);
            if (input_limit_check(input))
            {
                input[strcspn(input, "\n\r")] = '\0';
                if (strcmp(input, "-1") == 0)
                    break;

                char loweredinput[temp_input_size];
                strcpy(loweredinput, input);
                lowercase_text(loweredinput);

                int found_count = 0;
                printf("\n--- SEARCH RESULTS ---\n");
                for (int i = 0; i < number_of_books; i++)
                {
                    char temp[temp_input_size - 1];
                    strcpy(temp, mode == 1 ? archive[i].title : archive[i].author);
                    lowercase_text(temp);

                    if (strstr(temp, loweredinput) != NULL)
                    {
                        found_count++;
                        printf("%d)\n", found_count);
                        printf("Title  : %s\n", archive[i].title);
                        printf("Author : %s\n", archive[i].author);
                        printf("Page   : %d\n", archive[i].page);
                        printf("ID     : %d\n\n", archive[i].ID);
                    }
                }
                if (found_count > 0)
                {
                    printf("\n------------------------------\n");
                    printf("Success: %d book(s) found.\n", found_count);
                    printf("------------------------------\n\n");
                }
                else
                    printf("\n! No matches found for your search.\n\n");
            }
        }
        else if (mode == 3)
        {
            int input;
            if (scanf("%d", &input) == 1)
            {
                int found = 0;
                for (int i = 0; i < number_of_books; i++)
                {
                    if (archive[i].ID == input)
                    {
                        found = 1;
                        printf("\n--- SEARCH RESULT ---\n");
                        printf("\nTitle  : %s\n", archive[i].title);
                        printf("Author : %s\n", archive[i].author);
                        printf("Page   : %d\n", archive[i].page);
                        printf("ID     : %d\n\n", archive[i].ID);
                        break;
                    }
                }
                if (found < 1)
                    printf("\n! No matches found for your search.\n\n");
            }
        }
    }
}

void edit_Book_Invalid(int ID)
{
    printf("\nNo books with ID %d were found.\n", ID);
}
void edit_Book()
{
    while (1)
    {
        printf("\nPlease enter the ID of the book you you want to edit (-1 to go back): ");
        int input;
        if (scanf("%d", &input) == 1)
        {
            clear_input_buffer();
            if(input == -1) return;
            if(input < 0) {edit_Book_Invalid(input); continue;}

            int found_i = -1;
            for (int i = 0; i < number_of_books; i++)
            {
                if (archive[i].ID == input)
                {
                    found_i = i;
                    break;
                }
            }

            if (found_i != -1)
            {
                printf("\nA book found! Details:\nTitle: %s\nAuthor :%s\nPage :%d\nID :%d\n\n", archive[found_i].author, archive[found_i].author, archive[found_i].page, archive[found_i].ID);
            }
            else {edit_Book_Invalid(found_i); continue;}

            int mode;
            while(1)
            {
                printf("Please choose an option that you want to edit:\n|1| title\n|2| author\n|3| page\n(-1 to go back): ");
                if(scanf("%d", &mode) == 1 && (mode == -1 || mode == 1 || mode == 2 || mode == 3))
                {
                    clear_input_buffer();
                    if(mode == -1) return;
                    break;
                }
                else
                {
                    clear_input_buffer();
                    continue;
                }
            }

            if (mode == 1)
            {
                while (1)
                {
                    printf("\nOld title: \"%s\"\nPlease enter new title (-1 to go back): ", archive[found_i].title);
                    char temp_input[MAX_TITLE + 2];
                    if(fgets(temp_input, MAX_TITLE + 2, stdin) == NULL) continue;

                    if(strcmp(temp_input, "-1") == 0) return;
                    
                    if(input_limit_check(temp_input))
                    {
                        clear_back_n(temp_input);
                        printf("\nNew title will be: %s", temp_input);
                        if(y_or_n() == 1)
                        {
                            strcpy(archive[found_i].title, temp_input);
                            printf("Updated successfully!\n\n");
                            break;
                        }
                    }
                }
            }
            
            if (mode == 2)
            {
                while (1)
                {
                    printf("\nOld author: \"%s\"\nPlease enter new author (-1 to go back): ", archive[found_i].author);
                    char temp_input[MAX_AUTHOR + 2];
                    if(fgets(temp_input, MAX_AUTHOR + 2, stdin) == NULL) continue;

                    if(strcmp(temp_input, "-1") == 0) return;
                    
                    if(input_limit_check(temp_input))
                    {
                        clear_back_n(temp_input);
                        printf("\nNew author will be: %s", temp_input);
                        if(y_or_n() == 1)
                        {
                            strcpy(archive[found_i].author, temp_input);
                            printf("Updated successfully!\n\n");
                            break;
                        }
                    }
                }
            }
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
