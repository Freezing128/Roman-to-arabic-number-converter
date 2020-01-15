/*  
* Roman to arabic number converter
* @Author: Freezing
* @Date: 14/01/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define blen 16 /* buffer length + little extra */

/* Converts char to numeric value */
int value ( char c )
{   
   switch ( c )
     {   
         case 'I':
         case 'i':
            return 1;
         break;
         
         case 'V':
         case 'v':
            return 5;
         break;
         
         case 'X':
         case 'x':
            return 10;
         break;
         
         case 'L':
         case 'l':
            return 50;
         break;
         
         case 'C':
         case 'c':
            return 100;
         break;
         
         case 'D':
         case 'd':
            return 500;
         break;

         case 'M':
         case 'm':
            return 1000;
         break;
     }
}
 
/* 
* Roman to arabic number converting algorithm
* Reads char array (string) from stdin and goes through it char by char 
*/
int romanToArab ( char c [] ) 
{   
    int res = 0;
    int len = strlen ( c );
    for ( int i = 0; i < len ; i++ )
    {   
        /* value of one char from string */
        int s1 = value ( c [ i ] );
        /* checks if cycle overlapped length of string */
        if ( i + 1 < len ) 
        {  
           /* gets value of char that's one position further than the char obtained before
            * because roman numbers can be tricky and eg. 40 is interpreted as XL, 400 as CD, 900 as CM etc. */
            int s2 = value ( c [ i + 1 ] );
            
            /* if the char one position further has the same of lower value, char on current position is added to result */
            if ( s1 >= s2 ) 
            { 
                res = res + s1; 
            }
            else /* char one position further is higher, so it's eg. XL, CD and so on */
            {  
                res = res + ( s2 - s1 ); /* difference of s2 and s1 is added to result */
                i++;   /* can't forget to cycle one position further in the loop 
                        so it doesn't recognize number on next position as new one */
            }
        }
        else /* cyklus je na konci a pricita posledni hodnotu, ktera jeste zbyva */
        {   res = res + s1;
            i++;    /* posune se na dalsi hodnotu, 
                      nicmene protoze i uz je ted vetsi nez delka stringu, cyklus skonci */
        }
    }
    return res; 
}

 int main ()
 {  
    char buff[blen];
    int result = 0;

    printf ( "Insert roman number with max length of 10 chars: \n" );
    /* Reading input with fgets */
    while ( fgets ( buff, blen, stdin ) != NULL ) 
    {   
        /* 10 + 1 znak is always '\n' => 11 in if */
        if ( strlen ( buff ) > 11 ) 
        { 
            printf ( "Error! Input longer than 10 chars.\n" ); 
            return 0;
        }
        if ( buff [ strlen ( buff ) - 1 ] == '\n' ) 
        { 
            buff [ strlen ( buff ) - 1 ] = '\0'; 
        }
        break; 
    }
    
    /* Prints roman value */
    int len = strlen ( buff );
    for ( int i = 0; i < len; i++ ) 
    {   if ( i == 0 ) 
            printf ( "Roman:\n%c", buff[i] ); 
        else 
            printf ( "%c", buff[i] );
    }
    
    /* Prints arabic value */
    printf ( "\nArabic: %d\n", romanToArab ( buff ) );
    return 0;
 }
