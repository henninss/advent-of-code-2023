#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 5 + null-terminator
char number_names[9][6] = 
{
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int extract_number(char* line)
{
    char* l = line;
    // Assume there are no more than 20 digits in a line
    // Could be done on stack but want to practice mallocs
    char* digits = (char*) malloc(20 * sizeof(char));
    // Can potentially contain the whole line
    char* buf = (char*) malloc(150 * sizeof(char));
    size_t d_size = 0;
    size_t b_size = 0;
    if (digits == NULL || buf == NULL)
    {
        printf("Malloc fail");
        exit(1);
    }


    while (*l != '\n')
    {
        if (isdigit(*l))
        {
            digits[d_size] = *l;
            digits[d_size+1] = '\0';
            ++d_size;
            b_size = 0;
        }
        else
        {
            buf[b_size] = *l;
            buf[b_size+1] = '\0';
            ++b_size;

            // Check all numbers for a match in buffer
            for (int i = 0; i < 9; ++i)
            {
			    char* match = strstr(buf, number_names[i]);	

                if (match != NULL)
                {
                    digits[d_size] = '1' + i;
                    digits[d_size+1] = '\0';
                    ++d_size;
                    i = 9;
                    // sevenine is supposed to be 79
                    // Courtesy of /u/Zefick on the advent of code subreddit, because this baffled me
                    // So leave the last letter in the buffer
                    b_size = 1;
                    buf[0] = *l;
                    buf[1] = '\0';
                }
            }

        }

        ++l;
    }

    char number[3];
    number[2] = '\0';

    if (d_size == 0) return 0;
    if (d_size == 1)
    {
        number[0] = digits[0];
        number[1] = digits[0];
        return atoi(number);
    }
    else
    {
        number[0] = digits[0];
        number[1] = digits[d_size-1];
        return atoi(number);
    }

    free(digits);
    free(buf);
}

int main()
{
    printf("At start of program\n");
    int sum = 0;
    FILE* fp;
    char* line = NULL;
    size_t len = 0;

    fp = fopen("day1_data.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    
    while (getline(&line, &len, fp) != -1)
    {
        sum += extract_number(line);
    }

    printf("Sum of all digits: %d \n", sum);
    if (line) free(line);
    fclose(fp);

    return 0;
}
