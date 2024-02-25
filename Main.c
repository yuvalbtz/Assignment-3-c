#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main()
{
    int option;
    StrList *myList = StrList_alloc();

    do
    {
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            int numWords;
            scanf("%d", &numWords);

            for (int i = 0; i < numWords; i++)
            {
                char word[100];
                scanf("%s", word);
                StrList_insertLast(myList, word);
            }
            break;
        }
        case 2:
        {
            int index;
            char data[100];
            scanf("%d %[^\n]", &index, data);  // Read until newline
            StrList_insertAt(myList, data, index);
            break;
        }
        case 3:
            StrList_print(myList);
            break;
        case 4:
            printf("%zu\n", StrList_size(myList));
            break;
        case 5:
        {
            int index;
            scanf("%d", &index);
            StrList_printAt(myList, index);
            break;
        }
        case 6:
            printf("%d\n", StrList_printLen(myList));
            break;
        case 7:
        {
            char data[100];
            scanf(" %[^\n]", data);  // Read until newline
            printf("%d\n", StrList_count(myList, data));
            break;
        }
        case 8:
        {
            char data[100];
            scanf(" %[^\n]", data);  // Read until newline
            StrList_remove(myList, data);
            break;
        }
        case 9:
        {
            int index;
            scanf("%d", &index);
            StrList_removeAt(myList, index);
            break;
        }
        case 10:
            StrList_reverse(myList);
            break;
        case 11:
            StrList_free(myList);
            myList = StrList_alloc();
            break;
        case 12:
        {
            StrList_sort(myList);
            break;
        }
        case 13:
            if (StrList_isSortedLexicographically(myList))
            {
                printf("true\n");
            }
            else
            {
                printf("false\n");  
            }
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (option != 0);

    StrList_free(myList);
    return 0;
}
