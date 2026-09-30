#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_BOOK_COUNT 1024
#define MAX_TITLE_SIZE 128
#define MAX_AUTHOR_SIZE 64
#define DATA_FILE "books.data"


typedef struct
{
    int id;
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
} Book;

typedef struct
{
    Book books[MAX_BOOK_COUNT];
    int bookCount;
} Library;

Library g_library = {0};

void printBook(const Book *book)
{
    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("-------------------------\n");
}

static int readLine(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return 0;
    }

    size_t length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    return 1;
}

static int readInput2Int(const char *prompt)
{
    char charBuffer[64];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);
        if (!readLine(charBuffer, sizeof(charBuffer)))
        {
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        value = strtol(charBuffer, &end, 10);

        if (errno == 0 && end != charBuffer && *end == '\0' &&
            value >= 0 && value <= INT_MAX)
        {
            return (int)value;
        }

        printf("Please enter a non-negative integer.\n");
    }
}


static int findBookById(int id)
{
    for (int i = 0; i < g_library.bookCount; i++)
    {
        if (g_library.books[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

static void readInput2Text(char *target, size_t size, const char *prompt)
{
    printf("%s", prompt);
    if (!readLine(target, size))
    {
        exit(EXIT_SUCCESS);
    }
}
