/*Name Hongda Lin (lin.3235)*/
/*Date: 28/2/2021*/
#include <iostream>
#include <ios>
#include <limits>
#include <cctype>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
using namespace std;

#define digitSize 4
#define fileSize 10
#define lineMaxSize 4
#define lineMaxSizeOdd 6
#define fbMaxSize 19

void printErrorMessage();
void printErrorMessage2();
void printErrorMessage3();
void printErrorMessage4();
void printErrorMessage5();
void printErrorMessage6(int i);
/* method reverse reverses a array by the size of digit */
void reverse(char *ptr_digitArr, int size);
/* function convertToDigit convert an valid array of digit to its int value */
int convertToDigit(char *ptr_digitArr, int size);
/* check if fileName contains not alpha and digit */
int checkFormat(char *ptr_fileName, int nameLength);
/* find the median fb number */
double computeMedian(unsigned long int *ptr_fibArr, int input);
/* calculate Fibonacci number */
void fib(unsigned long int *ptr_fibArr, int i);

void printErrorMessage(){
     cout<<"Invaild character detected. Enter integer only. Program terminated."<<endl;
}

void printErrorMessage2(){
     cout<<"Invalid integer size. Enter 4 digits number only. Program terminated."<<endl;
}

void printErrorMessage3(){
     cout<<"Invalid digit format. Cannot start with 0 at beginning. Program terminated."<<endl;
}

void printErrorMessage4(){
     cout<<"Invalid file name format. Cannot contain other than alphabatic or numeric value. Program terminated."<<endl;
}

void printErrorMessage5(){
     cout<<"Invalid file name format. 10 digits and letters only. Program terminated."<<endl;
}

void printErrorMessage6(int i){
     cout<<"Overflow happend during "<<i<<"th Fibonacci addition. Stop and Proceed step 2."<<endl;
}

/* reverse the array by the given size */
void reverse(char *ptr_digitArr, int size){
     for(int i=0; i<size/2; i++){
        char temp = *(ptr_digitArr+i);
        *(ptr_digitArr+i) = *(ptr_digitArr+size-i-1);
        *(ptr_digitArr+size-i-1) = temp;
     }
}

/* converse the reversed array to its digit form */
int convertToDigit(char *ptr_digitArr, int size){
     long result = 0;
     int digit, constent = 10;
     for(int i=0; i<size; i++){
         digit = *(ptr_digitArr+i) - '0';
         result += digit * pow(constent, i);
     }
     return result;

}

/* file name should only consists alphbetical and numeric value */
int checkFormat(char *ptr_fileName, int nameLength){
    int result = 0;
    for(int i=0; i<nameLength; i++){
       char ch = *(ptr_fileName + i);
       if(!isalpha(ch)&&!isdigit(ch)){
         result = -1;
         break;
       }
    }
    return result;
}

/* calculate Fibonacci number and store them into fib array */
void fib(unsigned long int *ptr_fibArr, int i){
     unsigned long int constent = 1;
     if((i==0)||(i==1)){
        *(ptr_fibArr+i) = constent;
     }else{
        /* if i is not 0 or 1, then fb number array[i] is array[i-2]+array[i-1] */
        *(ptr_fibArr+i) = *(ptr_fibArr+i-2)+ *(ptr_fibArr+i-1);
     }
}

/* compute the median number by fb array */
double computeMedian(unsigned long int *ptr_fibArr, int input){
     /* if array size is even, then median = array[size/2-1]/2 + array[size/2]/2 */
     if(input%2==0){
        double median = (*(ptr_fibArr+input/2-1) + *(ptr_fibArr+input/2))/2.0;
        return median;
     /* if array size is odd, then median = array[size/2] */
     }else{
        double median = *(ptr_fibArr+input/2);
        return median;
     }
}


int main(){
    char digit;
    int count = 0, oddFb = 0, evenFb = 0, countOdd = 0, countEven = 0, countIn = 0, countOut = 0, line = 0, input, nameLength, medianEvenCheck, medianOddCheck;
    ifstream in_stream;
    ofstream out_stream;
    unsigned long int fbNumber, fbNumberEven, fbNumberEvenNext, fbNumberOdd, fbNumberOddNext, fbEvenIn, fbOddOut;
    double median, medianEven, medianOdd;
    char digitArr[digitSize], fileName[50], fileNameOdd[50], fileNameEven[50], odd[] = ".odd", even[] = ".even";
    char *ptr_digitArr = digitArr, *ptr_fileName = fileName;
    
    /* read input digit, positive and max size 4, and store them in ptr_digit */
    cout<<"Enter positive integer N (up to 4 digits): ";
    cin.get(digit);
    while(digit !='\n'){
          /* deal with not digit */
          if(!isdigit(digit)){
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              printErrorMessage();
              exit(EXIT_FAILURE);
          }
          /* deal with exceed max size */
          if(count > digitSize){
              cin.clear();
              cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
              printErrorMessage2();
              exit(EXIT_FAILURE);
          }
          *(ptr_digitArr+count) = digit;
          /* count to record the digit size */
          count++;
          cin.get(digit);
     }
     /* deal with invaild input like 0000 */
     if(count > 1 && digitArr[0] == '0'){
        printErrorMessage3();
        exit(EXIT_FAILURE);
     }
     /* reverse ptr_digit */
     reverse(ptr_digitArr, count);
     /* convert ptr_digit to its numeric form */
     input = convertToDigit(ptr_digitArr, count);
     /*reset count to 0 */
     count = 0;
     /* display user input */
     cout<<"N = "<<input<<endl;
     /* read output file name, store as string */
     cout<<"Enter file name(up to 10 digits or/and letters ONLY): ";
     cin>>fileName;
     /* length of file name cannot exceed 10 */
     nameLength = strlen(fileName);
     if(nameLength > fileSize){
        printErrorMessage5();
        exit(EXIT_FAILURE);
     }
     /* file name cannot contain value other than numeric and alphbetically value */
     if(checkFormat(ptr_fileName, nameLength)){
        printErrorMessage4();
        exit(EXIT_FAILURE);
     }
     /* becasue output file may or may not exist, don't check Stream error */
     cout<<"File name = "<<fileName<<endl;
     out_stream.open(fileName);

     const int fibSize = input;
     unsigned long int fibArr[fibSize];
     unsigned long int *ptr_fibArr = fibArr;
     
     /* Generate Fibonacci numbers and immediately written into file and displayed on the screen*/
     cout<<"1. File "<<fileName<<" contents:"<<endl;
     for(int i=0; i<input; i++){
          /* check overflow */
          if((*(ptr_fibArr+i-2)>0)&&(*(ptr_fibArr+i-1)>0)&&(*(ptr_fibArr+i-2)+*(ptr_fibArr+i-1)<0)){
             printErrorMessage6(i);
             break;
          }
          /* method fib generate fb numbers and store them into fb array */
          fib(ptr_fibArr, i);
          /* new line when dipaly/print 4 fb number */
          if(count == lineMaxSize){
             putchar('\n');
             out_stream<<'\n';
             count = 0;
          }
          /* create space for output */
          cout<<setw(fbMaxSize);
          out_stream<<setw(fbMaxSize);
          /* write and dispaly fb numbers */
          cout<<*(ptr_fibArr+i);
          out_stream<<*(ptr_fibArr+i);
          count++;
     } 
     /* close file *FILE , *FILE exist */
     out_stream.close();
     /* display number of generated Fibonacci numbers */
     cout<<"\nTotal number in "<<fileName<<" file = "<<fibSize<<endl;
     /* compute the median of generated fb numbers */ 
     median = computeMedian(ptr_fibArr, input);       
     cout<<"2. The median number in "<<fileName<<" file is: "<<median<<endl;     
     
     /* create two file name string "*FILE.odd" and "*FILE.even" */
     strcpy(fileNameOdd, fileName);
     strcpy(fileNameEven, fileName);
     strcat(fileNameOdd, odd);
     strcat(fileNameEven, even);

     /* open *FILE and check stream */
     in_stream.open(fileName);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     /* create file *FILE.even, and store even fb number */
     out_stream.open(fileNameEven);
     while(in_stream>>fbNumber){
         /* check even */
         if(fbNumber%2 == 0){
            /* new line when print 4 fb number */
            if(countEven == lineMaxSize){
             out_stream<<'\n';
             countEven = 0;
            }
             out_stream<<setw(fbMaxSize);
             out_stream<<fbNumber;
             countEven++;
            /* count fb even number */
             evenFb++;
          }
     }
     /* close *FILE and *FILE.even, *FILE.even exist */
     in_stream.close();
     out_stream.close();
  
     /* open *FILE and check stream */
     in_stream.open(fileName);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     /* create file *FILE.odd, and store odd fb number */
     out_stream.open(fileNameOdd);
     while(in_stream>>fbNumber){
         /* check odd */
         if(fbNumber%2 != 0){
            if(countOdd == lineMaxSize){
             out_stream<<'\n';
             countOdd = 0;
            }
             out_stream<<setw(fbMaxSize);
             out_stream<<fbNumber;
             countOdd++;
             /* count fb odd number */
             oddFb++;
          }
     }
    /* close *FILE and *FILE.odd, *FILE.odd exist */
     in_stream.close();
     out_stream.close();

    /* report fb even and fb odd counts */
     cout<<"3. Total numbers in "<<fileNameEven<<" file = "<<evenFb<<endl;
     cout<<"   Total numbers in "<<fileNameOdd<<" file = "<<oddFb<<endl;

    /* open *FILE.even and check stream */
     in_stream.open(fileNameEven);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
    /* get median index */
     medianEvenCheck = evenFb/2;
     /* if total number of even fb is even, find fb value at median and median+1 */
     if(evenFb%2==0){     
        for(int j=0; j<medianEvenCheck; j++){
            in_stream>>fbNumberEven;
        }
        in_stream>>fbNumberEvenNext;
        medianEven = (fbNumberEven+fbNumberEvenNext)/2;
     /* if total number of even fb is odd, find fb value at median */
     }else{
        for(int k=0; k<medianEvenCheck; k++){
            in_stream>>fbNumberEven;
        }
        medianEven = fbNumberEven;
     }
     /* dispaly fb even median */
     cout.precision(1);
     cout.setf(ios::fixed);
     cout<<"   The median number in "<<fileNameEven<<" file is: "<<medianEven<<endl;
     /* close *FILE.even */
     in_stream.close();

     /* open *FILE.odd and check stream */
     in_stream.open(fileNameOdd);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     /* get median index */
     medianOddCheck = oddFb/2;
     /* if total number of odd fb is even, find fb value at median and median+1 */
     if(oddFb%2==0){     
        for(int t=0; t<medianOddCheck; t++){
            in_stream>>fbNumberOdd;
        }
        in_stream>>fbNumberOddNext;
        medianOdd = (fbNumberOdd+fbNumberOddNext)/2;
     /* if total number of odd fb is odd, find fb value at median */
     }else{
        for(int g=0; g<medianOddCheck; g++){
            in_stream>>fbNumberOdd;
        }
        medianOdd = fbNumberOdd;
     }
     /* dispaly fb even median */
     cout.precision(1);
     cout.setf(ios::fixed);
     cout<<"   The median number in "<<fileNameOdd<<" file is: "<<medianOdd<<endl;
     /* close *FILE.odd */
     in_stream.close();

     /* open *FILE.even as input file and check stream */
     in_stream.open(fileNameEven);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     /* open *FILE.odd as output file, make data append at the end of the file and check stream */
     out_stream.open(fileNameOdd, ios::app);
     if(out_stream.fail()){
        cout<<"output file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     out_stream<<'\n';
     /* read until the end of input file */
     while(in_stream>>fbEvenIn){
          if(countIn == lineMaxSizeOdd){
             out_stream<<'\n';
             countIn = 0;
            }
            out_stream<<setw(fbMaxSize-5);
            out_stream<<fbEvenIn;
            countIn++;
            /* record the fb numbers in *FILE.odd */
            oddFb++;
     }
     /* close *FILE.even and *FILE.odd */
     in_stream.close();
     out_stream.close();
     /* report the fb numbers in *FILE.odd */
     cout<<"4. Total numbers in "<<fileNameOdd<<" file is now: "<<oddFb<<endl;

     /* display the content in *FILE.odd */
     cout<<"5. File "<<fileNameOdd<<" content:"<<endl;
     in_stream.open(fileNameOdd);
     if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
     }
     /* display by two parts */
     while(in_stream>>fbOddOut){
         /* part 1 display fb odd number, 4 numbers per line */
         if(line < (oddFb-evenFb)){
           if(countOut == lineMaxSize){
              cout<<'\n';
              countOut = 0;
             }
           cout<<setw(fbMaxSize);
           cout<<fbOddOut;
           countOut++;
           line++;
        }else{
           /* begin to display fb even number, reset countOut = 0, print new line */
           if(line == (oddFb-evenFb)){
               cout<<'\n';
               countOut = 0;
           }
           /* part 2 display fb even number, 6 numbers per line */
           if(countOut == lineMaxSizeOdd){
              cout<<'\n';
              countOut = 0;
             }
           cout<<setw(fbMaxSize - 5);
           cout<<fbOddOut;
           countOut++;
           line++;
        }
     }
    in_stream.close();
    cout<<endl;
    return 0;
}
