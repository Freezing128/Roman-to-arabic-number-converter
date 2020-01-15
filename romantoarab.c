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
int romanToArab ( char * c, int len ) 
{   
    int res = 0;
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
        else /* loop is at the end and adds up the last value that remains */
        {   
            res = res + s1;
            i++;    
        }
    }
    return res; 
}
/* Prints roman number */
void printRoman ( char * buff, int len )
{
  for ( int i = 0; i < len; i++ )
  {
    if ( i == 0 ) 
        printf ( "Roman: %c", buff[i] ); 
    else 
        printf ( "%c", buff[i] );
  }
}

/* Reads input from stdin */
int readInput ( char * line, int * len )
{
  char c;
  int size = 0, load;
  while ( 666 )
  {
    load = scanf ( "%c", &c );
    if ( feof ( stdin ) )
      break;
    if ( load == 0 || ( c != 'i' && c != 'I'
                     && c != 'v' && c != 'V' && c != 'x' && c !='X'
                     && c != 'l' && c != 'L' && c != 'c' && c != 'C'
                     && c != 'd' && c != 'D' && c != 'm' && c != 'M' && c != '\n' ) )
    {
      load = 0;
      break;
    }
    if ( size >= blen || c == '\n' )
      break;
    line[size] = c;
    size++;
  }

  if ( size > 10 || load == 0 )
    return 0;
  if ( line[size - 1] == '\n' )
    line[size - 1] == '\0';
  * len = size;
  return 1;
}

/* Main function */
int main ()
{  
  int result, len;
  char line [blen];

  printf ( "Insert roman number with max length of 10 chars: \n" );
  if ( ! readInput ( line, &len ) )
  {
    printf ( "Error! Wrong input.\n" ); 
    return 1;
  }
    
  /* Prints roman value */
  printRoman ( line, len );
    
  /* Prints arabic value */
  printf ( "\nArabic: %d\n", romanToArab ( line, len ) );
  return 0;
 }
