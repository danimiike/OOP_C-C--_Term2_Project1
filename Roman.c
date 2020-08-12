    /*
Program name:   roman.c
Author:         Danielle Menezes de Mello Miike
Purpose:        Convert Arabic to Roman Numbers and Roman to Arabic numerals
Date:           Jan 31, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*=========================================================================================================================
Function Name:  ArabicToRoman
Purpose:        Convert Arabic to Roman
Accept:         two integers numbers
Return:         None
===========================================================================================================================*/


void ArabicToRoman(long int number, int mod)
{
    //declare and initialize the arrays with the possibilities of roman numbers and variables to use in the conversion
    char* thousands[] = { "", "M", "MM", "MMM" };
    char* hundreds[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
    char* decimals[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
    char* units[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
    
    int count = 0, temp = 0;
    long int tNum = number;

    do
    {
        // count how many times the inputs greater than 4000 are divisible by 1000
        while (tNum >= 4000) {
            tNum = tNum / 1000;
            if (tNum >= 1)
                count++;
        }
        // prints the corresponding value in roman when the input is greater than 1000
        if (tNum >= 1000) {
            printf("%s", thousands[tNum / 1000]);
            //keep the remainder
            tNum = tNum % 1000;
        }
        // prints the corresponding value in roman when the input or remainder is greater than 100
        if (tNum >= 100) {
            printf("%s", hundreds[tNum / 100]);
            //keep the remainder
            tNum = tNum % 100;
        }
        // prints the corresponding value in roman when the input or remainder is greater than 10
        if (tNum >= 10) {
            printf("%s", decimals[tNum / 10]);
            //keep the remainder
            tNum = tNum % 10;
        }
        // prints the corresponding value in roman when the input or remainder is greater than 1
        if (tNum > 0) {
            printf("%s", units[tNum]);
            //assigns zero to variable tNum
            tNum = 0;
        }

        //if the count is bigger than zero than prints _  to demonstrate that the roman is divisible by a thousand
        if (count > 0){
            printf("%c", '_');
            //get the power of the count 
            temp = (int)pow(1000, count);
            //based in the variable temp, keep the remainder of the input
            tNum = number % temp;
            //if count is greater than one and the remainder is zero or less than a thousand prints the second _
            if((count > 1 && tNum ==0) || (count > 1 && tNum < 1000))
                printf("%c", '_');
            //assign 0 to counter
            count=0;
        }
    } while (tNum != 0);


    //if mod is bigger than zero it means that there is a fraction in the input. 
    while (mod > 0) {
        //if the fractions is bigger than 6 (1/12) than prints S and subtract 6 of the variable mod
        if (mod >= 6) {
            printf("%c", 'S');
            mod -= 6;
        }
        //case the fraction is less than 6 than prints the dots and subtract 1 (1/12)
        else if (mod < 6) {
            printf("%c", '.');
            mod -= 1;
        }
    }
}

/*=========================================================================================================================
Function Name:  RomanToArabic
Purpose:        Convert Roman to Arabic
Accept:         An array of char
Return:         a double
===========================================================================================================================*/

long double RomanToArabic(char roman_Number[]) {

    unsigned int i = -1, indexPar = -1, indexI = -1;
    double number = 0;

    //create a index to verify if there is an aspostruphus character
    for (unsigned int index = 0; index < strlen(roman_Number); index++)
    {
        if (roman_Number[index] == ')')
        {
            indexPar = index;
            if (i != 0 && indexI == -1 && roman_Number[index - 1] == 'I')
                indexI = index - 1;
        }
    }

    // check the index to evaluate the apostruphus 
    if (indexI != -1 && indexPar != -1)
    {
        // check if it is a balanced apostrophus
        if (indexI * 2 == indexPar)
            number += 1000 * pow(10, indexI - 1);

        //if it is a not balanced apostrophus
        else if (indexI * 2 != indexPar){
            // check if index of I is different of zero, if it is than add the values of index before and after the I
            if (indexI != 0){
                number += 1000 * pow(10, (double)(indexI - 1));
                number += 50 * pow(10, (double)(indexPar - indexI * 2));
            }
            else
                //if index of I is zero than add corresponding values to the indexes before I index.
                number += 50 * pow(10, (double)(indexPar - indexI * 2));

        }
        else
            number += 50 * pow(10, (double)(indexPar - indexI * 2));
    }
    // In case it is not the end of the roman numbers than update the value of the variable I 
    if (indexPar != strlen(roman_Number))
        i = indexPar + 1;
    else
        return number;

    //Verify the value of the roman letter and add the value in a number variable
    while (roman_Number[i]) {
        
        if (roman_Number[i] == '-' || roman_Number[i] == '_')
        {
            number *= 1000;
        }
        else if (roman_Number[i] == 'S' || roman_Number[i] == 's')
        {
            number += 0.5;
        }
        else if (roman_Number[i] == '.')
        {
            number += 1.0 / 12;
        }
        else if (FindValue(roman_Number[i]) >= FindValue(roman_Number[i + 1]))
        {
            number += FindValue(roman_Number[i]);
        }
        else if (FindValue(roman_Number[i]) > 0)
        {
            number += (double)(FindValue(roman_Number[i + 1])) - FindValue(roman_Number[i]);
            i++;
        }

        i++;
    }
    return number;
}//end RomanToArabic

/*=========================================================================================================================
Function Name:  FindValue
Purpose:        Evaluate roman letters
Accept:         An array of char
Return:         a integer
===========================================================================================================================*/


int FindValue(char c) {

    int value = 0;

    switch (c) {

    case 'I': value = 1; break;
    case 'V': value = 5; break;
    case 'X': value = 10; break;
    case 'L': value = 50; break;
    case 'C': value = 100; break;
    case 'D': value = 500; break;
    case 'M': value = 1000; break;
    case '-': value = 0; break;
    case '_': value = 0; break;
    case '.': value = 0; break;
    case 'S': value = 0; break;
    case 's': value = 0; break;
    case '\0': value = 0; break;

    default: value = -1;
    }

    return value;
}//end FindValue


/*=========================================================================================================================
                                                    Main function
===========================================================================================================================*/

int main() {

    int mod = 0, count = 0, countN, countL;
    long double number;
    unsigned char enterValue[50] = { 0 };
    do
    {
        countL = 0; countN = 0;
        //Ask the user to enter a roman or arabic number
        printf("Enter a roman or arabic number:");
        //Read the value
        scanf_s("%s", enterValue, sizeof(enterValue));

        //verify if the is equal to quit if it is than exit the program
        if (!strcmp(enterValue, "quit") || !strcmp(enterValue, "QUIT"))
        {
            break;
        }
        else
        {
            //count how many letter or number the user inputed
            while (enterValue[count] != '\0') {
                ++count;

            }
            //check if the first digit it not a number
            if (!isdigit(enterValue[0])) {
                
                //convert lower to upper case
                for (unsigned int i = 0; i < strlen(enterValue); i++) {
                    enterValue[i] = toupper(enterValue[i]);
                }
                //call the function to convert roman to arabic number
                number = RomanToArabic(enterValue);
                printf("The value %s is %0.15g in arabic\n", enterValue, number);
            }
            else {
                //convert the array in a float number
                number = atof(enterValue);
                //puts the fraction part in a variable
                mod = (int)((number - (int)number) * 12);
               
                //print the result of the convertion calling the function 
                printf("The value %0.15g is ", number);
                ArabicToRoman((int)number, mod);
                printf(" in roman.\n");
            }
        }
        
    } while (!strcmp(enterValue, "quit") == 0 || !strcmp(enterValue, "QUIT") == 0);

    return 0;

}//end main

