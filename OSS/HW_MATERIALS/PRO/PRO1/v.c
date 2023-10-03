#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *fp_niv;

int matching(char *bible, char *find, char option);

char *read_a_line()
{
    static char buf[BUFSIZ];
    static int buf_n = 0;
    static int curr = 0;

    if (feof(fp_niv))
        return 0x0;

    char *s = 0x0;
    size_t s_len = 0;
    do
    {
        int end = curr;
        while (!(end >= buf_n || !iscntrl(buf[end])))
        {
            end++;
        }
        curr = end;
        while (!(end >= buf_n || iscntrl(buf[end])))
        {
            end++;
        }
        if (s == 0x0)
        {
            s = strndup(buf + curr, end - curr);
            s_len = end - curr;
        }
        else
        {
            s = realloc(s, s_len + end - curr + 1);
            s = strncat(s, buf + curr, end - curr);
            s_len = s_len + end - curr;
        }
        if (end < buf_n)
        {
            curr = end + 1;
            break;
        }

        buf_n = fread(buf, 1, sizeof(buf), fp_niv);
        curr = 0;
    } while (buf_n > 0);
    return s;
}

char *getLine()
{
    char *input = ""; // declare and initialize an empty string
    char c;
    int inQuotation = 0;

    input = (char *)malloc(sizeof(char) * 100);
    while ((c = getchar()) != EOF)
    { // loop until the control-d (EOF) character is detected
        if (c == '\n')
            c = ' ';

        if (inQuotation)
        {
            if (c == ' ')
                c = '&';
        }

        if (c == '\"')
            inQuotation = !inQuotation;

        strncat(input, &c, 1); // append the current character to the input string
    }

    return input;
}

char *getTolower(char *str)
{
    char *temp = {0};

    temp = (char *)malloc(sizeof(char) * 100);
    for (; *str; ++str)
        *temp = tolower(*str);

    return temp;
}

int main(int argc, char **argv)
{
    fp_niv = fopen("NIV.txt", "r");

    char *s = 0x0;
    char *inputString;
    char *parse;
    char *stringTokens[8] = {0};
    int countParsed = 0;
    int countToken = 0;

    inputString = getLine();

    parse = strtok(inputString, " ");

    while (parse != NULL)
    {
        if (countParsed > 7)
            break;

        stringTokens[countParsed] = parse;
        parse = strtok(NULL, " ");
        countParsed++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("\n%d : %s\n", i + 1, stringTokens[i]);
    }

    while (s = read_a_line())
    {
        // strstr : find if there is a string2 in string1
        // char * strstr(char* str1, char* str2)

        // atoi : change character to integer
        // int atoi (const char* cStr)

        // int tolower(char)
        printf("\nho\n");
        // token => in case-insensitive
        // token* => prefix matches with token in case-insensitive
        // -token => only if the verse has no matches with token in case-insensitive
        // "string" => satisfies this condition only if a substring is identical to string
        // book : code => a verse satisfies this condition only if it is in the book of code
        // chapter : num => a verse satisfies this condition only if its chatper number is num (positive integer)

        // getTolower(s) and getTolower(stringTokens[countToken])
        // and then compare in token, token*, -token type

        // Check each condition in order
        int tokenMatch = 0;
        int prefixMatch = 0;
        int noMatch = 0;
        int stringMatch = 0;
        int bookMatch = 0;
        int chapterMatch = 0;

        printf("hits");
        char *lowercase = getTolower(s);
        printf("%s", lowercase);

        for (int i = 0; i < 8; i++)
        {
            if (stringTokens[i] = NULL)
                break;

            char *tempstr = {0};
            char *tokenLowerCase = getTolower(stringTokens[i]);
            if (strchr(stringTokens[i], '*') != NULL)
                prefixMatch = matching(lowercase, tokenLowerCase, 'p');

            else if (strchr(stringTokens[i], '-') != NULL)
                noMatch = matching(lowercase, tokenLowerCase, 'n');

            else if (strchr(stringTokens[i], '\"') != NULL)
                stringMatch = matching(s, stringTokens[i], 's');

            else if (strchr(stringTokens[i], ':') != NULL)
            {
                tempstr = strtok(stringTokens[i], ":");
                if (atoi(tempstr) == 0)
                    bookMatch = matching(s, stringTokens[i], 'b');
                else
                    chapterMatch = matching(s, stringTokens[i], 'c');
            }

            else
                matching(lowercase, tokenLowerCase, '#');

            free(tempstr);
        }

        // If all specified conditions are met, print the verse
        if (tokenMatch || prefixMatch || stringMatch || bookMatch || chapterMatch)
        {
            printf("%s\n", s);
        }

        tokenMatch = 0;
        prefixMatch = 0;
        noMatch = 0;
        stringMatch = 0;
        bookMatch = 0;
        chapterMatch = 0;

        free(s);
    }

    fclose(fp_niv);
}
int matching(char *bible, char *find, char option)
{
    // options p, n, s, b, c, #
    char *checking;
    char *throw1, throw2;
    char *book, *chapter, *verse;

    switch (option)
    {
    case 'p' || '#':
        printf("\np or #\n");
        checking = strstr(bible, find);
        return checking != NULL ? 1 : 0;
        break;

    case 'n':
        printf("\nn\n");
        checking = strstr(bible, find);
        return checking == NULL ? 1 : 0;
        break;

    case 's':
        printf("\ns\n");
        return strcmp(bible, find) == 0 ? 1 : 0;
        break;

    case 'b':
        printf("\nb\n");
        sscanf("%s %s:%s %s", book, chapter, verse, throw1);
        strcat(book, " ");
        strcat(book, chapter);
        if (strstr(bible, book))
        {
            if (strcmp(book, find) == 0)
                return 1;
            else
                return 0;
        }
        break;

    case 'c':
        printf("\nc\n");
        sscanf("%s %s:%s %s", book, chapter, verse, throw1);
        strcat(chapter, ":");
        strcat(chapter, verse);
        return strstr(bible, chapter) != NULL ? 1 : 0;
        break;

    default:
        return 0;
        break;
    }
}