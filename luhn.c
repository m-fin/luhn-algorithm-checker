#include <stdio.h>
#include <stdbool.h>
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
    while (ccNum > 10)
    {
        ccNum /= 10;
    }
    
    return (int) ccNum;
}

//gets second digit of ccNum
int ccSecondDigit(long ccNum)
{
    while (ccNum > 100)
    {
        ccNum /= 10;
    }
    while (ccNum > 10)
    {
        ccNum -= 10;
    }
    
    return (int) ccNum;
}

//checks if ccNum passes Luhn's algorithm
bool isValid(long ccNum)
{
    int ccNumLength = ccNumOfDigits(ccNum);
    int sum = 0;
    bool alternate = false; //starts with second to last digit
    
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

int main(void)
{   
    long ccNum;
    printf("Number: ");
    scanf( "%ld", &ccNum);

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
}
