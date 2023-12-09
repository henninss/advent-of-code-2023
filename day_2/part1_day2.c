#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int red_lim = 12;
const int green_lim = 13;
const int blue_lim = 14;

enum color{RED, GREEN, BLUE, NONE};

char colors[3][6] =
{
    "red",
    "green",
    "blue"
};

int parse_number(char** line)
{
    char digits[4];
    int i = 0;
    while (isdigit(**line))
    {
        digits[i] = **line;
        digits[i+1] = '\0';
        i++;
        (*line)++;
    }

    return atoi(digits);
}

// Assumes line pointer is at beginning of word
enum color parse_type(char** line)
{
    char buf[6];
    enum color type = NONE;
    int i = 0;
    while(type == NONE)
    {
        buf[i] = **line;
        buf[i+1] = '\0';

        // 3 = number of colors
        for (int j = 0; j < 3; j++)
        {
            if (strcmp(buf, colors[j]) == 0) type = j;
        }
        
        (*line)++;
        i++;
    }

    return type;
}

// Returns 0 if not a "valid" game, otherwise returns the game ID
int valid_game_id(char* line)
{
    char* l = line;
    puts(l);
    
    int quant;

    if (strcmp("\n", l) == 0) return 0;
    // And now assuming it is not immediately null-terminated
    while(!isdigit(*l)) l++;
    int game_id = parse_number(&l);
    
    // After that, *l is now at next non-digit character 
    while(!isdigit(*l)) l++;
    
    while (*l != '\0')
    {
        quant = parse_number(&l);
        // Space
        l++;
        enum color type = parse_type(&l);
       
        if (type == NONE)
        {
            printf("Error parsing type: buffer didn't match any known color");
            exit(1);
        }
    
        switch(type)
        {
            case RED:
                if (quant > red_lim) return 0;
                break;
            case GREEN:
                if (quant > green_lim) return 0;
                break;
            case BLUE:
                if (quant > blue_lim) return 0;
                break;
            default:
                printf("Error parsing type: type wasn't null, but didn't match any color enum either");
                exit(1);
                break;
        }
    
    
        // Newline or terminating characters, all checks passed: return the game ID
        if (*l == '\n' || *l == '\0') return game_id;
        // May need this later if the type becomes relevant
        // if (*l == ';')
        // {
        // }

        // Increment the pointer by two, for the character and the space that follows
        l += 2;
    }
}

int main() {
    int sum = 0;
    FILE* fp;
    char* line = NULL;
    size_t len = 0;

    fp = fopen("day2_data.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    while (getline(&line, &len, fp) != -1)
    {
        int result = valid_game_id(line);
        printf("Result: %d\n", result);
        sum += result;
    }

    printf("Sum of all game ID's: %d \n", sum);
   
    if (line) free(line);
    fclose(fp);

    return 0;
}
