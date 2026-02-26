#ifndef LIB_H
#define LIB_H

#define MAX_TITLE 128
#define MAX_AUTHOR 64
#define library_size 100

//-----------------------------------------------------------------------------------------
/*************************************************************************
 * DATA STRUCTURES
 *************************************************************************/

/**
 * @brief Represents a single book entity within the system.
 * This structure acts as the primary data model for storage and
 * memory operations. Using typedef allows for cleaner and more
 * readable code throughout the application.
 */
struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int page;
    int ID;
};

typedef struct Book Book;

//-----------------------------------------------------------------------------------------
/*************************************************************************
 * Utility Functions
 *************************************************************************/
void clear_input_buffer();
void clear_screen();
void lowercase_text(char text[]);

//-----------------------------------------------------------------------------------------
/*************************************************************************
 * Interface Functions
 *************************************************************************/
int ask_Q1(int case_size);

//-----------------------------------------------------------------------------------------
/*************************************************************************
 * Action Functions
 *************************************************************************/

 /**
 * @brief Displays all active books in the library.
 * Iterates through the archive and prints books with a valid ID.
 * If the library is empty, it informs the user.
 */
void show_Books();

 /**
 * @brief Searches for an available slot and adds a new book to the library.
 * Performs a linear search for an empty slot (ID 0), collects user input,
 * and assigns a unique ID based on the slot index.
 */
void add_Book();

 /**
 * @brief Removes a book from the library using its unique ID.
 * Finds the book's index by its ID, then triggers the internal
 * shifting algorithm to maintain array integrity.
 */
void remove_Book();

 /**
 * @brief ...
 *
 *
 * @return ...
 */
void search_Book();

//-----------------------------------------------------------------------------------------
/*************************************************************************
 * Storage Manager Functions
 *************************************************************************/

/**
 * @brief Saves all books from memory to a binary file.
 * Ensures data is preserved by overwriting the storage file with
 * the current state of the library.
 */
void save_Library();

/**
 * @brief Loads library data from a binary file into memory.
 * Restores the previous session's data and updates the global book counter.
 * Should be called once during program startup.
 */
void load_Library();

//-----------------------------------------------------------------------------------------

#endif // LIB_H
