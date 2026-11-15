#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gets number of digits in ccNum
int ccNumOfDigits(long ccNum)
{
    int count = 0;
    
    while (ccNum != 0)
    {
        ccNum /= 10;
        count++;
    }
    
    return count;
}

//gets sum of digits in a number
int sumOfDigits(int n)
{
    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n /= 10;        
    }
    
    return sum;
}

//gets first digit of ccNum
int ccFirstDigit(long ccNum)
{
    while (ccNum >= 10)
    {
        ccNum /= 10;
    }
    
    return (int) ccNum;
}

//gets second digit of ccNum
int ccSecondDigit(long ccNum)
{
    while (ccNum >= 100)
    {
        ccNum /= 10;
    }

    return (int) (ccNum % 10);
}

//checks if ccNum passes Luhn's algorithm
bool isValid(long ccNum)
{
    int ccNumLength = ccNumOfDigits(ccNum);
    int sum = 0;
    bool alternate = false; // rightmost digit is the check digit and is not doubled
    
    for (int i = ccNumLength - 1; i >= 0; i--)
    {
        int currentDigit = ccNum % 10; //gets digits from LAST to FIRST
        
        if (alternate)
        {
            sum += sumOfDigits(currentDigit * 2);
        }
        else
        {
            sum += currentDigit;
        }
        
        ccNum /= 10;
        alternate = !alternate;
    }
    
    if (sum % 10 == 0)
        return true;
    else
        return false;
}

// Accepts one non-negative integer. Leading whitespace is ignored.
// Any other trailing character (aside from whitespace) is rejected.
static int parse_number(const char *text, long *cc_num)
{
    char *end;
    long value;

    errno = 0;
    value = strtol(text, &end, 10);
    if (end == text || errno == ERANGE || value < 0)
    {
        return 0;
    }

    while (*end != '\0')
    {
        if (!isspace((unsigned char) *end))
        {
            return 0;
        }
        end++;
    }

    *cc_num = value;
    return 1;
}

int main(void)
{
    char text[128];
    long ccNum;

    printf("Number: ");
    fflush(stdout);

    if (fgets(text, sizeof text, stdin) == NULL)
    {
        printf("INVALID\n");
        return 0;
    }

    // A full buffer with no newline means the line was longer than we accept.
    if (strchr(text, '\n') == NULL && !feof(stdin))
    {
        printf("INVALID\n");
        return 0;
    }

    if (!parse_number(text, &ccNum))
    {
        printf("INVALID\n");
        return 0;
    }

    if (isValid(ccNum))
    {   
        if (ccNumOfDigits(ccNum) == 15 && ccFirstDigit(ccNum) == 3 && 
            (ccSecondDigit(ccNum) == 4 || ccSecondDigit(ccNum) == 7))
        {
            printf("AMEX\n");
        }
        else if (ccNumOfDigits(ccNum) == 16 && ccFirstDigit(ccNum) == 5 &&
                (ccSecondDigit(ccNum) == 1 || ccSecondDigit(ccNum) == 2 || ccSecondDigit(ccNum) == 3 ||
                 ccSecondDigit(ccNum) == 4 || ccSecondDigit(ccNum) == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((ccNumOfDigits(ccNum) == 13 || ccNumOfDigits(ccNum) == 16) && ccFirstDigit(ccNum) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
