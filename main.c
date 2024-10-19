#include <stdio.h>
#include <stdlib.h> // importing the library that contains the function sleep
#include <time.h>  //library needed to use the srand and rand methods
#include <Windows.h> //Windows header for console attributes. Among which is colours
#include <ctype.h> //library that contains the toupper function


int RandomNo(int NoFaces)  //User-defined function to generate a random number, taking NoFaces as parameter, returning an int value
{
    int LowerBound= 1;
    int Randomnum = (rand()%(NoFaces)) + LowerBound;  //Will generate a random number between LowerBound and NoFaces inclusive
    return Randomnum;
}


void rolling(){
    printf("Rolling.........");
    for (int i = 0; i<3; i++){
        printf("..................................");
        sleep(1); // to stop execution of program for one second.

        fflush(stdout); // to make sure that the printed value is displayed on the screen
    }
}

// creating a procedure to set text color
void colors(int color){
    // calling a widows API function that sets the attributes of characters written in the console screen buffer
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // GetStdHandle retrieves the standard output handle and the attribute color.
    // colour Guide:
    // Red + Intensity = Light Red
    // Green + Intensity = Light Green
    // Red + Green + Intesity = Yellow
    // Red + Green + Blue = White
}


int main()
{
 int NoThrows,NoFaces,Result;
 int count, index,i;
 int MaxResult,MinResult,MaxFace,MinFace;
 char StartChoice,EndChoice,StartPrompt;
 float MaxChance, MinChance;
 srand(time(NULL));  //Sets the starting point for random number generation



 for(i=0; i<1; i++)
  {
   colors(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); // Intensity adds lightness to color and makes it yellow not brown.
   printf("************************************* \n");
   printf("*Welcome to the Dice Roll Simulator*\n");
   printf("************************************* \n" );  //Title screen encased in a box of stars
   Sleep(500);  //sleep for 500 ms
   system("cls"); //Used to clear the screen
    Sleep(500);
  }  //This block of code will make the title screen blink 2 times

 printf("************************************* \n");
 printf("*Welcome to the Dice Roll Simulator*\n");
 printf("************************************* \n" );
 printf("\nPress Enter to start!");
 scanf("%C",&StartPrompt);
 colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);// resets text color to white


 do {
     MaxChance = 0;  //Will initialize the value of MaxChance to 0 for each iteration
     MinChance= 999;  //Will initialize the value of MinChance to 999 for each iteration
   do {
     do {
       printf("Enter the Number of faces of the dice (Between 2 and 24 inclusive): ");
       scanf("%d",&NoFaces);
       getchar();  //in case the user inputs a character by mistake instead of an integer
       //Will perform a validation check to see if the value entered is between 2 and 24 inclusive

       if(NoFaces <=1){
         colors(FOREGROUND_RED | FOREGROUND_INTENSITY);  //turns the text red
         printf("\nThis is Vegas not Game of Thrones. We do not have faceless dice.\n");
         colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
         }else if (NoFaces >=25) {
              colors(FOREGROUND_RED | FOREGROUND_INTENSITY);
              printf("\nWe don't have an Infinity Die. Enter a value less than 25.\n");
              colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
         }

       }while (NoFaces>24||NoFaces<2); //Will continuously prompt the user until the value entered is between 2 and 24 inclusive


    do {
       printf("Enter the Number of throws of the dice(Between 2 and 499 inclusive): ");
       scanf("%d",&NoThrows);
       getchar();  //in case the user inputs a character by mistake instead of an integer

       if (NoThrows >= 500 || NoThrows <=1){

         if(NoThrows>=500){
            colors(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\nWhat....really!! You think we got that much time? The number of throws must be less than 500.\n");
            colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
            } else {
                  colors(FOREGROUND_RED | FOREGROUND_INTENSITY);
                  printf("\nDid you quit gambling? Enter a value greater than 1.\n");
                  colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
            }

       }

      } while (NoThrows>499||NoThrows<2); //Will continuously prompt the user until the value entered is between 2 and 499 inclusive


     do {
       printf("Are you sure you want to proceed with these values? <Y/N>");
       scanf(" %c",&StartChoice);
       StartChoice=toupper(StartChoice);  //Will convert the value entered by user to upper case before doing validation

       if (StartChoice!='Y'&&StartChoice!='N') {  //Will perform a validation to check if the user has prompted either 'Y' or 'N'
          printf("Invalid choice! Please retry! \n");
        }

       } while (StartChoice!='Y'&&StartChoice!='N');  //Will continuously prompt the user until the value entered is either 'Y' or 'N'

     } while (StartChoice != 'Y');  //The block of code will be repeated until the choice input is 'Y', i.e. the user wants to proceed
    system("cls");


    int ThrowResult[NoFaces];   // array used to store the occurrence of each throw
    float ThrowChance[NoFaces];  // array used to store the probability of each throw

    for (count=0;count<NoFaces;count++) {
       ThrowResult[count]=0; //Each element in the array is initialized to 0
    }

   printf("\n");  //Will leave a line blank
   colors(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

   rolling();

   colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
   printf("\n");  //Will leave a line blank

   for (count=1;count<(NoThrows+1);count++) {
     Result = RandomNo(NoFaces); //The user-defined function RandomNo is called, passing NoFaces as parameter
     printf("Throw %d: %d\n",count,Result);
     ++ThrowResult[Result-1];  //The value in the array at position [Result-1] (as the array starts from 0) is incremented
   }

  printf("\n");   //Will leave a line blank

  for (count=0;count<NoFaces;count++) {
     index = count+1;  //index will store the value of the actual number as the array starts from 0 and not 1
     ThrowChance[count] = (float) (ThrowResult[count])/NoThrows*100;  //Will convert the amount of each number occurring to float, else the percentage would always be 0
     printf("Occurrences of %d: %.2f%%\n",index,ThrowChance[count]); //Displaying the probabilities of each throw to 2 d.p.

       if (ThrowChance[count]<MinChance) {  //Will perform a comparison with MinChance and if it's lower than it, it will store its probability,occurrence and face
         MinChance = ThrowChance[count];
         MinResult = ThrowResult[count];
         MinFace = index;
        }

      if (ThrowChance[count]>MaxChance) {  //Will perform a comparison with MaxChance and if it's higher than it, it will store its probability,occurrence and face
        MaxChance = ThrowChance[count];
        MaxResult = ThrowResult[count];
        MaxFace = index;
       }
    }

   printf("\n");  //Will leave a line blank

   colors(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

   printf("Your lucky number is %d - occurred %d times (%.2f%%) \n",MaxFace,MaxResult,MaxChance); //Will display the number with the highest occurrence

   for (count=0;count<NoFaces;count++) {
      index = count+1;

      if ((ThrowResult[count]==MaxResult)&&(index!=MaxFace)){  //will check if there is another number with the same occurrence as the one with highest occurrence
        printf("Your other lucky number is %d - occurred %d times (%.2f%%) \n",index,ThrowResult[count],ThrowChance[count]); //Will display the other number with the highest occurrence
      }
   }

  colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

  printf("\n");  //Will leave a line blank

  colors(FOREGROUND_RED | FOREGROUND_INTENSITY);

  printf("Your unlucky number is %d - occurred %d times (%.2f%%)\n",MinFace,MinResult,MinChance);  //Will display the number with the lowest occurrence
  for (count=0;count<NoFaces;count++) {
        index = count+1;

    if ((ThrowResult[count]==MinResult)&&(index!=MinFace)){  //will check if there is another number with the same occurrence as the one with lowest occurrence
        printf("Your other unlucky number is %d - occurred %d times (%.2f%%) \n",index,ThrowResult[count],ThrowChance[count]); //Will display the other number with the lowest occurrence
    }
   }

  printf("\n");  //Will leave a line blank

  colors(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

  do {
     printf("Do you want to play again? <Y/N>: ");  //Will prompt the user to play again
     scanf(" %c",&EndChoice);
     EndChoice=toupper(EndChoice);  //Will convert the value entered by user to upper case before doing validation

     if (EndChoice!='Y'&&EndChoice!='N') {     //Will perform a validation to check if the user has prompted either 'Y' or 'N'
        printf("invalid choice! Please retry! \n"); //Will perform a validation to check if the user has prompted either 'Y' or 'N'
     }

    } while (EndChoice!='Y'&&EndChoice!='N');

    if (EndChoice=='Y') {
        system("cls");
     }

  } while (EndChoice != 'N');  //The entire program will run again until the user inputs 'N' at the end


 printf("\n");  //Will leave a line blank
 printf("Goodbye!");
 return (0);
}
