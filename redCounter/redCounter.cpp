/*Name Hongda Lin (lin.3235)*/
/*Date: 11/3/2021*/
#include <iostream>
#include <ios>
#include <limits>
#include <cctype>
#include <stdlib.h>
#include <cstring>

using namespace std;

#define default_overflow 9999
#define pause_constant 400000000
#define digit_limit 9
#define double_constant 100.0

class Counter{
     public: 
         /* defualt constructors */ 
         Counter();
         /* User input constructors */
         Counter(int input);   

         /* public function that do inrement */
         void incr1(int digit);
         void incr10(int digit);
         void incr100(int digit);
         void incr1000(int digit);
        
         /* reset private members to default */
         void reset();
         /* public function that detects overflow */
         bool overflow();
         bool maxoverflow();
         /* public function that display private members */
         void displayCent();
         void displayDime();
         void displayDollar();
         void displayTenDollar();
         void displayOverflow();
         void displayMaxOverflow();
         void displayCount(Counter redCounter);
         /* some helper public function */
         void displayMenu();
         void pause();
       
     private:
         int count;
         int units;
         int tens;
         int hundreds; 
         int thousands;
         int user_overflow;
};

/* function prototypes */
bool instructionCheck(char instr[50]);
void resetCounter(Counter &redCounter, bool &notOverflow);
void inquireOverflow(Counter redCounter);
void inquireCapacityOverflow(Counter redCounter);
bool incrementCheck(int increment);
void unitsIncrement(int increment, bool increCheck, Counter &redCounter);
void tensIncrement(int increment, bool increCheck, Counter &redCounter);
void hundredsIncrement(int increment, bool increCheck, Counter &redCounter);
void thousandsIncrement(int increment, bool increCheck, Counter &redCounter);
void clearConsole();
void printErrorMessage(Counter redCounter);

/* default constructor, user_overflow set as 9999 */
Counter::Counter(){
     /* private members are set as default */
     reset();
     user_overflow = default_overflow;
}

/* non-default constructor, user_overflow set as input */
Counter::Counter(int input){
     if(input > 0 && input <= default_overflow){
        user_overflow = input;
     }else{
        cout<<"Insufficient digits to establish the overflow value. Counter is set as default."<<endl; 
        user_overflow = default_overflow;
     }     
     /* private members are set as default */
     reset();
}

/* set private members as default */
void Counter::reset(){
     units = 0;
     tens = 0;
     hundreds = 0;
     thousands = 0;
     count = 0;
}

/* increase both count and units */
void Counter::incr1(int digit){
     count+=digit;
     /* if units => 10, modify units and increment tens by 1 */
     units+=digit;
     if(units > digit_limit){
        units-= (digit_limit+1);
        tens++;
     } 
     if(tens > digit_limit){
        tens-= (digit_limit+1);
        hundreds++;
     } 
     if(hundreds > digit_limit){
        hundreds-= (digit_limit+1);
        thousands++;
     } 
}

/* increase both count and tens */
void Counter::incr10(int digit){
     count+=10*digit;
     tens+=digit;
     /* if tens => 10, modify tens and increment hundreds by 1 */
     if(tens > digit_limit){
        tens-= (digit_limit+1);
        hundreds++;
     }
     if(hundreds > digit_limit){
        hundreds-= (digit_limit+1);
        thousands++;
     } 
}

/* increase both count and hundreds */
void Counter::incr100(int digit){
     count+=100*digit;
     hundreds+=digit;
     /* if hundreds => 10, modify hundreds and increment thousands by 1 */
     if(hundreds > digit_limit){
        hundreds-= (digit_limit+1);
        thousands++;
     }
}

/* increase both count and thousands */
void Counter::incr1000(int digit){
     count+=1000*digit;
     /* if count is greater than default_overflow, don't increment thousands */
     if(!maxoverflow()){
        thousands+=digit;
     }
}

/* Check overflow (user_overflow) */ 
bool Counter::overflow(){
     if(count > user_overflow){
        return true;
     }else{
        return false;
     }
}

/* Check overflow (default_overflow) */ 
bool Counter::maxoverflow(){
     if(count > default_overflow){
        return true;
     }else{
        return false;
     }
}
         
/* display units */
void Counter::displayCent(){
     cout<<units;
}
     
/* display tens */    
void Counter::displayDime(){
     cout<<tens;
}
  
/* display hundreds */        
void Counter::displayDollar(){
     cout<<hundreds;
}

/* display thousands */ 
void Counter::displayTenDollar(){
     cout<<thousands;
} 

/* display user_overflow in ##.## */
void Counter::displayOverflow(){
    int cent = user_overflow%10;
    int ten_cent = (user_overflow/10)%10;
    int dollar = (user_overflow/100)%10;
    int ten_dollar = (user_overflow/1000)%10;
    cout<<ten_dollar<<dollar<<"."<<ten_cent<<cent<<endl;
}

/* display default_overflow in ##.## */
void Counter::displayMaxOverflow(){
    int cent = default_overflow%10;
    int ten_cent = (default_overflow/10)%10;
    int dollar = (default_overflow/100)%10;
    int ten_dollar = (default_overflow/1000)%10;
    cout<<ten_dollar<<dollar<<"."<<ten_cent<<cent<<endl;
}
        
/* display current count value in ##.## */
void Counter::displayCount(Counter redCounter){
    cout<<"The current count value is: $";
    redCounter.displayTenDollar();
    redCounter.displayDollar();
    cout<<".";
    redCounter.displayDime();
    redCounter.displayCent();
}

/* display operating menu */
void Counter::displayMenu(){
     cout<<"Enter a character first and follow, if needed, by a digit 1-9:\n"
         <<"     'a' for units\n"  
         <<"     's' for tens\n"
         <<"     'd' for hundreds\n"
         <<"     'f' for thousands\n"
         <<"     'o' for inquire about overflow\n"
         <<"     'r' for reset counter\n"
         <<"     'm' to inquire about capacity overflow\n"
         <<"     'Q' or 'q' at any time to quit,\n"
         <<"Follow by pressing the return key in each case: ";
}

/* check user input for instruction */
bool instructionCheck(char instr[50]){
     if(strcmp(instr, "a") == 0){
        return true;
     }
     if(strcmp(instr, "s") == 0){
        return true;
     }
     if(strcmp(instr, "d") == 0){
        return true;
     }
     if(strcmp(instr, "f") == 0){
        return true;
     }
     if(strcmp(instr, "o") == 0){
        return true;
     }
     if(strcmp(instr, "r") == 0){
        return true;
     }
     if(strcmp(instr, "m") == 0){
        return true;
     }
     if(strcmp(instr, "Q") == 0 || strcmp(instr, "q") == 0){
        return true;
     }
     cout<<endl<<"Invalid instruction detected, try Re-Enter again."<<endl;
     return false;
}

/* Reset Object memeber varaiables and local bool value by reference(address) */
void resetCounter(Counter &redCounter, bool &notOverflow){
     redCounter.reset(); 
     notOverflow = true;
     cout<<"RESET COMPLETE!\n"<<endl;
     redCounter.displayCount(redCounter);
     cout<<endl;
}

/* function that returns information about current count and user_overflow */
void inquireOverflow(Counter redCounter){
     cout<<"OVERFLOW TEST REQUESTED."<<endl;
     if(redCounter.overflow()){
        cout<<endl<<"OVERFLOW HAS OCCURRED. "<<endl;
        redCounter.displayCount(redCounter);
        cout<<" > $";
        redCounter.displayOverflow();
        cout<<endl<<"PLEASE RESET COUNTER OR QUIT."<<endl;
     }else{
        cout<<endl<<"OVERFLOW HASN'T OCCURRED. "<<endl;
        redCounter.displayCount(redCounter);
        cout<<" <= $";
        redCounter.displayOverflow();
     }
}

/* function that returns information about current count and default_overflow */
void inquireCapacityOverflow(Counter redCounter){
     cout<<"CAPACITY OVERFLOW TEST REQUESTED."<<endl;
     if(redCounter.maxoverflow()){
        cout<<endl<<"CAPACITY OVERFLOW HAS OCCURRED. "<<endl;
        redCounter.displayCount(redCounter);
        cout<<" > $";
        redCounter.displayMaxOverflow();
        cout<<endl<<"PLEASE RESET COUNTER OR QUIT."<<endl;
     }else{
        cout<<endl<<"CAPACITY OVERFLOW HASN'T OCCURRED. "<<endl;
        redCounter.displayCount(redCounter);
        cout<<" <= $";
        redCounter.displayMaxOverflow();
     }
}

/* check validity for user increment value (1-9) */
bool incrementCheck(int increment){
     if(increment > 0 && increment < 10){
        return true;
     }
     cout<<endl<<"Invalid increment value detected, try Re-Enter again."<<endl;
     return false;
}

/* function does units increment, Object is passed by reference, increCheck is set as false */
void unitsIncrement(int increment, bool increCheck, Counter &redCounter){
     while(!increCheck){       
            cout<<"UNITES INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            cin>>increment;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            increCheck = incrementCheck(increment);
            redCounter.pause();
     }
     redCounter.incr1(increment);
}

/* function does tens increment, Object is passed by reference, increCheck is set as false */
void tensIncrement(int increment, bool increCheck, Counter &redCounter){
     while(!increCheck){       
            cout<<"TENS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            cin>>increment;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            increCheck = incrementCheck(increment);
            redCounter.pause();
     }
     redCounter.incr10(increment);
}

/* function does hundreds increment, Object is passed by reference, increCheck is set as false */
void hundredsIncrement(int increment, bool increCheck, Counter &redCounter){
     while(!increCheck){       
            cout<<"HUNDREDS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            cin>>increment;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            increCheck = incrementCheck(increment);
            redCounter.pause();
     }
     redCounter.incr100(increment);
}

/* function does thousands increment, Object is passed by reference, increCheck is set as false */
void thousandsIncrement(int increment, bool increCheck, Counter &redCounter){
     while(!increCheck){       
            cout<<"THOUSANDS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            cin>>increment;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            increCheck = incrementCheck(increment);
            redCounter.pause();
     }
     redCounter.incr1000(increment);
}
  
/* helper function that could pause and clear the console */
void Counter::pause(){
     cout<<endl<<"PAUSING...\n";
     for(int i=0; i<pause_constant; i++){
         i++;
         i--;
     }
     cout<<"\033[2J\033[1;1H";
}

/* clear the console */
void clearConsole(){
     cout<<"\033[2J\033[1;1H";
}

/* print error messgae when detect overflow */
void printErrorMessage(Counter redCounter){
     cout<<"ALERT: COUNT IS OVER THE MAXIMUM SET TO $";
     redCounter.displayOverflow();
     cout<<endl<<"    RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE"<<endl;
     redCounter.pause();
}

int main(){
    char instr[50];
    int input = 0, increment = 0;
    /* declare object redCounter, invoke default constructor */
    Counter redCounter;
    bool continueProgram = true, increCheck = false, notOverflow = true;
    /* let user decide default_overflow or user_overflow */
    cout<<"Please select your counter mode. \nPress 'n' for non-default counter, else the counter is set as default: ";
    cin>>instr;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    redCounter.pause();
    /* if instruction is 'n', user_overflow, get overflow value from user */
    if(strcmp(instr, "n") == 0){
       cout<<"USER MODE ACTIVATED."<<endl;
       cout<<endl<<"Enter a limit for the counter (1-9999): ";
       cin>>input;
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');   
       /* re-invoke non default constructor */ 
       redCounter = Counter(input);
    /* else, default_overflow */
    }else{
       cout<<"DEFAULT MODE ACTIVATED.\n"<<endl;
    }
    /* display overflow value */
    cout<<"The overflow value is set as: $"; 
    redCounter.displayOverflow();
    redCounter.pause();
    /* loop until continueProgram become false */
    while(continueProgram){
          /* display current count at top */
          redCounter.displayCount(redCounter);
          cout<<endl;
          /* display menu */
          redCounter.displayMenu();
          cin>>instr;
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          /* check user input */
          if(!instructionCheck(instr)){
             redCounter.pause();          
          }
          /* inquireOverflow when instruction is "o" */
          if(strcmp(instr, "o") == 0){
             clearConsole();
             inquireOverflow(redCounter);
             redCounter.pause();
          /* resetCounter when instruction is "r" */
          }else if(strcmp(instr, "r") == 0){
             clearConsole();
             /* bool value notOverflow will be reset to true */
             resetCounter(redCounter, notOverflow);
             redCounter.pause();
          /* inquireCapacityOverflow when instruction is "m" */
          }else if(strcmp(instr, "m") == 0){
             clearConsole();
             inquireCapacityOverflow(redCounter);
             redCounter.pause();
          /* change continueProgram to false when instruction is "Q" or "q" */
          }else if(strcmp(instr, "Q") == 0 || strcmp(instr, "q") == 0){
             clearConsole();
             cout<<"Goodbye."<<endl;
             continueProgram = false; 
             redCounter.pause();    
          /* deal with increment */
          }else{ 
             /* check overflow before increment. If overflow, display error message, set notOverflow to false. User have to reset counter in order to proceed increment */
             if(redCounter.overflow()){
                clearConsole();
                printErrorMessage(redCounter);
                notOverflow = false;
             }
             /* unitsIncrement when instruction is "a" and notOverflow is true */
             if(strcmp(instr, "a") == 0 && notOverflow){
                clearConsole();
                unitsIncrement(increment, increCheck, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessage(redCounter);
                }
             /* tensIncrement when instruction is "s" and notOverflow is true */
             }else if(strcmp(instr, "s") == 0 && notOverflow){
                clearConsole();
                tensIncrement(increment, increCheck, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessage(redCounter);
                }
             /* hundredsIncrement when instruction is "d" and notOverflow is true */
             }else if(strcmp(instr, "d") == 0 && notOverflow){
                clearConsole();
                hundredsIncrement(increment, increCheck, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessage(redCounter);
                }
             /* hundredsIncrement when instruction is "f" and notOverflow is true */
             }else if(strcmp(instr, "f") == 0 && notOverflow){
                clearConsole();
                thousandsIncrement(increment, increCheck, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessage(redCounter);
                }
             }
          }
    }

}
