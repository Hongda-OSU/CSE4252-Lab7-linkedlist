/*Name Hongda Lin (lin.3235)*/
/*Date: 14/2/2021*/
#include <iostream>
#include <ios>
#include <limits>
#include <cctype>
#include <math.h>
using namespace std;

const int maxDigitSize = 19;
const int Ldigits = 10;

char tempDigit1[maxDigitSize];
char tempDigit2[maxDigitSize];

char positiveSign = '+';
char negativeSign = '-';

void printErrorMessage1();
void printErrorMessage2();
void printErrorMessage3();
void restartMessage();
/* above methods are message information */

int validChecker(char *ptr_tempDigit1, int fDigitSize);
/* function validChecker check if the digit contains '0' as first character or non-digit characters */

void reverse(char *ptr_tempDigit, int DigitSize);
/* method reverse reverse a array by the size of digit */

long convertToDigit(char *ptr_tempDigit, int DigitSize);
/* function convertToDigit convert an valid array of digit to its long value */

int countDigits(long number);
/* function countDigits takes the addition or subtraction and return how many digits in it */

void storeToArrayPt(char *ptr_myArr, long input, int digitSize);
/* this method will store the digits and put '+' at front */

void storeToArrayNt(char *ptr_myArr, long input, int digitSize);
/* this method will store the digits and put '-' at front */

void printErrorMessage1(){
     cout<<"\nIllegal characters(s)"<<endl;
}

void printErrorMessage2(){
     cout<<"\nToo many characters"<<endl;
}

void printErrorMessage3(){
     cout<<"The number is too large that long cannot hold."<<endl;
}

void restartMessage(){
     cout<<"Q or q to exit: ";
}

int validChecker(char *ptr_tempDigit1, int fDigitSize){
    if(*ptr_tempDigit1=='0'){
       return -1;
    }
    for(int i = 0; i < fDigitSize; i++){
       if(!isdigit(*(ptr_tempDigit1+i))){
         return -1;
       }
    }
    return 0;
}

void reverse(char *ptr_tempDigit, int DigitSize){
     for(int i=0; i<DigitSize/2; i++){
        char temp = *(ptr_tempDigit+i);
        *(ptr_tempDigit+i) = *(ptr_tempDigit+DigitSize-i-1);
        *(ptr_tempDigit+DigitSize-i-1) = temp;
     }
}

long convertToDigit(char *ptr_tempDigit, int DigitSize){
     long result = 0;
     int digit, constent = 10;
     for(int i=0; i<DigitSize; i++){
         digit = *(ptr_tempDigit+i) - '0';
         result += digit * pow(constent, i);
     }
     return result;
}

int countDigits(long number){
    int count = 0;
    while(number!=0){
         number = number/10;
         count++;
    }
    return count;
}

void storeToArrayPt(char *ptr_myArr, long input, int digitSize){
     char cDigit;
     int i = 0, digit;
     while(input!=0){
         digit = input%10; 
         input = input/10;
         cDigit = digit + '0';
         *(ptr_myArr+i) = cDigit;
         i++;
     }
     reverse(ptr_myArr, digitSize);
     *ptr_myArr = positiveSign;
}

void storeToArrayNt(char *ptr_myArr, long input, int digitSize){
     char cDigit;
     int i = 0, digit;
     while(input!=0){
         digit = input%10; 
         input = input/10;
         cDigit = digit + '0';
         *(ptr_myArr+i) = cDigit;
         i++;
     }
     reverse(ptr_myArr, digitSize);
     *ptr_myArr = negativeSign;
}

int main(){
   char digit, instr;
   char *ptr_tempDigit1 = tempDigit1, *ptr_tempDigit2 = tempDigit2;
   do{
mark: int fDigitSize = 0, fDigitIndex = 0, sDigitSize = 0, sDigitIndex = 0;
      cout<<"Enter A integer (up to 10 digits): ";
      cin.get(digit);
      /* Read all characters of first digit */
      while(digit!='\n'){
           /* size could not larger than maxDigitSize, meaning that we could not store value that is larger than 19 digits */
           if(fDigitSize > maxDigitSize-1){
              /* clear the input buffer */
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              printErrorMessage3();
              restartMessage();
              cin>>instr;
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              if(instr !='Q'&& instr != 'q'){
                 goto mark;
              }else{
                 break;
              }
           }
           /* store each character to array and re-get digit */
           *(ptr_tempDigit1+fDigitSize) = digit;
           cin.get(digit);
           /* keep record how many characters in the digit */
           fDigitSize++;          
      }
      /* print first digit */
      cout<<"A = ";
      for(; fDigitIndex < fDigitSize; fDigitIndex++){
          cout<<*(ptr_tempDigit1 + fDigitIndex);
      }
      /* check if first digit contains characters more than 10 */ 
      if(fDigitSize > Ldigits){
          printErrorMessage2();
          restartMessage();
          cin>>instr;
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          if(instr !='Q'&& instr != 'q'){
             goto mark;
          }else{
             break;
          }
      }
      /* Check if first integer contains invalid characters */
      if(validChecker(ptr_tempDigit1, fDigitSize)){
         printErrorMessage1();
         restartMessage();
         cin>>instr;
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
         if(instr !='Q'&& instr != 'q'){
            goto mark;
         }else{
            break;
         }
      }
      /* use the same way above to get the second digit */
      cout<<"\nEnter B integer (up to 10 digits): ";
      cin.get(digit);
      /* Read all characters of second digit */
      while(digit!='\n'){
           /* size could not larger than maxDigitSize, meaning that we could not store value that is larger than 19 digits */
           if(sDigitSize > maxDigitSize-1){
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              printErrorMessage3();
              restartMessage();
              cin>>instr;
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              if(instr !='Q'&& instr != 'q'){
                 goto mark;
              }else{
                 break;
              }
           }
           *(ptr_tempDigit2+sDigitSize) = digit;
           cin.get(digit);
           sDigitSize++;          
      }
      /* print second digit */
      cout<<"B = ";
      for(; sDigitIndex < sDigitSize; sDigitIndex++){
          cout<<*(ptr_tempDigit2 + sDigitIndex);
      }
      /* check if second digit is too large for int to hold */ 
      if(sDigitSize > Ldigits){
          printErrorMessage2();
          restartMessage();
          cin>>instr;
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          if(instr !='Q'&& instr != 'q'){
             goto mark;
          }else{
             break;
          }
      }
      /* Check if second integer contains invalid characters */
      if(validChecker(ptr_tempDigit2, sDigitSize)){
         printErrorMessage1();
         restartMessage();
         cin>>instr;
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
         if(instr !='Q'&& instr != 'q'){
            goto mark;
         }else{
            break;
         }
      }
     
      /* now we reverse the digit by its size, ex: 123 will become 321 noew */
      reverse(ptr_tempDigit1, fDigitSize);
      reverse(ptr_tempDigit2, sDigitSize);
      
      /* we could use the reversed digit array to get the input digits */
      long digit1 = convertToDigit(ptr_tempDigit1, fDigitSize);
      long digit2 = convertToDigit(ptr_tempDigit2, sDigitSize);
      
      /* addition of two digit will always be positive */
      long addition = digit1+digit2;
      /* for subtraction, it is possible to get positive/negative output or 0, if digit1 > digit2, the subtraction is positive and flag will be 0, if digit1 < digit2, the subtraction is negative and we use digit2 - digit1 to represent the value that is going to be negative, flag will be 0, if two digits are same value, flag will be -1.*/
      long subtraction;
      int flag = 0;
      if(digit1 > digit2){
        subtraction = digit1-digit2;
      }else if(digit1 < digit2){
        subtraction = digit2-digit1;
        flag = 1;
      }else if(digit1 == digit2){
        flag = -1;
      }

      /* we set the size of output array one character more than output digit size (for store sign) */
      int pMax = countDigits(addition) + 1;
      int nMax = 1;
      /* if flag is not -1, then the subtraction is not 0, we do as above */
      if(flag != -1){
         nMax = countDigits(subtraction) + 1;
      }

      const int cpMax = pMax;
      const int cnMax = nMax;
      
      char my_Addition[cpMax];
      char my_Subtraction[cnMax];
      char *ptr_myAddition = my_Addition;
      char *ptr_mySubtraction = my_Subtraction;
      /* the addition calls the method storeToArrayPt */
      storeToArrayPt(ptr_myAddition, addition, pMax);

      if(flag == 0){
         /* flag is 0 means subtration is positive, we call storeToArrayPt */
         storeToArrayPt(ptr_mySubtraction, subtraction, nMax);
      }else if(flag == 1){
         /* flag is 1 means subtration is negative, we call storeToArrayNt */
         storeToArrayNt(ptr_mySubtraction, subtraction, nMax);
      }else if(flag ==-1){
         /* if flag is -1, then the output subtraction array size is 1 with '0' as value */
         *ptr_mySubtraction = '0';
      }
       
      /* print addition and subtraction */
      cout<<"\nA+B = ";
      for(int i = 0 ; i < pMax; i++){
          cout<<*(ptr_myAddition + i);
      }
      
      cout<<"\nA-B = ";
      for(int j = 0 ; j < nMax; j++){
          cout<<*(ptr_mySubtraction + j);
      }
      
      /* ask the user to play again */
      cout<<endl;
      restartMessage();
      cin>>instr;
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
   }while(instr!='Q'&& instr!='q');
   return 0;
}
