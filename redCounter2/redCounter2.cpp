/*Name Hongda Lin (lin.3235)*/
/*Date: 23/3/2021*/
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
         /* Overload operator >> for non-default constructors */
         friend istream& operator >>(istream& cin, Counter &redCounter);   

         /* public void function that do increment, (friend Counter operator --(int): version2) */
         friend void operator --(Counter &redCounter);
	 friend void operator -(Counter &redCounter);
	 friend void operator +(Counter &redCounter);
	 friend void operator ++(Counter &redCounter);
        
         /* reset private members to default */
         void reset(); 
         /* set counter mode */
         void add();
         void sub();
         /* public const function that detects overflow and underflow */
         bool overflow() const;
         bool maxoverflow() const;
         bool underZero() const;
         /* public const function that returns the current mode */
	 bool checkMode() const;
         /* public const function that display private members */
         void displayOverflow() const;
         void displayMaxOverflow() const;
         void displayMode() const;
         /* Overload operator << for display current count */
         friend ostream& operator <<(ostream& cout, Counter &redCounter);   
       
     private:
         int count;
         int units;
         int tens;
         int hundreds; 
         int thousands;
         int user_overflow;
         bool addition_mode;
         bool subtraction_mode;
};

/* function prototypes */
/* diplay alert message when overflow or underflow happened */
void displayAlert(const Counter redCounter);
/* display operating menu */
void displayMenu();
/* check user input for instruction */
bool instructionCheck(char instr[50]);
/* Reset Object memeber varaiables and local bool value by reference(address) */
void resetCounter(Counter &redCounter, bool &safe);
/* function that returns information about current count and user_overflow */
void inquireOverflow(Counter redCounter);
/* function that returns information about current count and default_overflow */
void inquireCapacityOverflow(Counter redCounter);
/* function that returns information about current count and underflow */
void inquireUnderflow(Counter redCounter);
/* check validity for user increment/decrement value (1-9) */
bool valueChecker(int value);
/* units increment/decrement, Object is passed by reference, checkValue is set as false */
void unitsModify(int value, bool checkValue, Counter &redCounter);
/* tens increment/decrement, Object is passed by reference, checkValue is set as false */
void tensModify(int value, bool checkValue, Counter &redCounter);
/* hundreds increment/decrement, Object is passed by reference, checkValue is set as false */
void hundredsModify(int value, bool checkValue, Counter &redCounter);
/* thousands increment/decrement , Object is passed by reference, checkValue is set as false */
void thousandsModify(int value, bool checkValue, Counter &redCounter);
/* clear the console */
void clearConsole();
/* function that could pause and clear the console */
void pause();
/* print error messgae when detect overflow */
void printErrorMessageOver(const Counter redCounter);
/* print error messgae when detect underflow */
void printErrorMessageUnder(const Counter redCounter);

/* default constructor, user_overflow set as 9999 */
Counter::Counter(){
     /* private members are set as default */
     reset();
     user_overflow = default_overflow;
}

/*  Overload operator >> for non-default constructors, user_overflow set as input */
istream& operator >>(istream& cin, Counter &redCounter){   
     int input;
     cout<<"USER MODE ACTIVATED."<<endl;
     cout<<endl<<"Enter a limit for the counter (1-9999): ";
     cin>>input;
     cin.clear();
     cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
     if(input > 0 && input <= default_overflow){
        redCounter.user_overflow = input;
     }else{
        cout<<"Insufficient digits to establish the overflow value. Counter is set as default."<<endl; 
        redCounter.user_overflow = default_overflow;
     }    
     /* private members are set as default */
     redCounter.reset();
     return cin;
}

/* set private members as default */
void Counter::reset(){
     units = 0;
     tens = 0;
     hundreds = 0;
     thousands = 0;
     count = 0;
     addition_mode = true;
     subtraction_mode = false; 
}

/* set counter to addtion mode */
void Counter::add(){
     if(!addition_mode){
	cout<<"Counter Mode: Addition Mode."<<endl;
        addition_mode = true;
     }else{
        cout<<"Counter is already in Addition Mode."<<endl;
     }
     subtraction_mode = false;
}

/* set counter to subtraction mode */
void Counter::sub(){
     if(!subtraction_mode){
	cout<<"Counter Mode: Subtration Mode."<<endl;
        subtraction_mode = true;
     }else{
        cout<<"Counter is already in Subtration Mode."<<endl;
     }
     addition_mode = false;
}

/* increase/decrease both count and units, Note(speical case incre: 00.99, 09.99) (special case decre: 01.00, 10.00*/
void operator --(Counter &redCounter){
     if(redCounter.addition_mode){
        redCounter.count+=1;
        /* if units => 10, modify units and increment tens by 1 */
        redCounter.units+=1;
        if(redCounter.units > digit_limit){
           redCounter.units-= (digit_limit+1);
           redCounter.tens++;
        } 
	if(redCounter.tens > digit_limit){
           redCounter.tens-= (digit_limit+1);
           redCounter.hundreds++;
        } 
	if(redCounter.hundreds > digit_limit){
           redCounter.hundreds-= (digit_limit+1);
           redCounter.thousands++;
        } 
     }else{
	redCounter.count-=1;
	if(!redCounter.underZero()){
            if(redCounter.units==0){
               redCounter.units = (digit_limit+1);
	       if(redCounter.tens==0){
                  redCounter.tens = (digit_limit+1);
	            if(redCounter.hundreds==0){
	               redCounter.hundreds = (digit_limit+1);
                       redCounter.thousands--;
                    }
                  redCounter.hundreds--;
	       }
               redCounter.tens--;
            }
	    redCounter.units--;
        }
     }
}

/* increase/decrease both count and tens, special case: 09.99, 01,00 */
void operator -(Counter &redCounter){
     if(redCounter.addition_mode){
        redCounter.count+=10;
        redCounter.tens+=1;
     /* if tens => 10, modify tens and increment hundreds by 1 */
        if(redCounter.tens > digit_limit){
           redCounter.tens-= (digit_limit+1);
           redCounter.hundreds++;
        }
        if(redCounter.hundreds > digit_limit){
           redCounter.hundreds-= (digit_limit+1);
           redCounter.thousands++;
        } 
     }else{
	redCounter.count-=10;
	if(!redCounter.underZero()){
	    if(redCounter.tens==0){
               redCounter.tens = (digit_limit+1);
	       if(redCounter.hundreds==0){
	          redCounter.hundreds = (digit_limit+1);
                  redCounter.thousands--;
               }
	       redCounter.hundreds--;
            }
	    redCounter.tens--;
        }
     }
}

/* increase/decrease both count and hundreds */
void operator +(Counter &redCounter){
     if(redCounter.addition_mode){
        redCounter.count+=100;
        redCounter.hundreds+=1;
        /* if hundreds => 10, modify hundreds and increment thousands by 1 */
        if(redCounter.hundreds > digit_limit){
           redCounter.hundreds-= (digit_limit+1);
           redCounter.thousands++;
        }
     }else{
	redCounter.count-=100;
	if(!redCounter.underZero()){
	    if(redCounter.hundreds==0){
               redCounter.hundreds = (digit_limit+1);
	       redCounter.thousands--;
            }
	    redCounter.hundreds--;
        }
     }
}

/* increase/decrease both count and thousands */
void operator ++(Counter &redCounter){
     if(redCounter.addition_mode){
        redCounter.count+=1000;
        /* if count is greater than default_overflow, don't increment thousands */
        if(!redCounter.maxoverflow()){
           redCounter.thousands+=1;
	}
     }else{
	redCounter.count-=1000;
	if(!redCounter.underZero()){
	    redCounter.thousands--;
        }
     }
}

/* Check overflow (user_overflow) */ 
bool Counter::overflow() const{
     if(count > user_overflow){
        return true;
     }else{
        return false;
     }
}

/* Check overflow (default_overflow) */ 
bool Counter::maxoverflow() const{
     if(count > default_overflow){
        return true;
     }else{
        return false;
     }
}

/* check underflow */
bool Counter::underZero() const{
     if(count < 0){
        return true;
     }else{
        return false;
     }
}

/* return true if addition, false subtraction */
bool Counter::checkMode() const{
     if(addition_mode){
	return true;
     }else{
	return false;
     }
}
         
/* display user_overflow in ##.## */
void Counter::displayOverflow() const{
    int cent = user_overflow%10;
    int ten_cent = (user_overflow/10)%10;
    int dollar = (user_overflow/100)%10;
    int ten_dollar = (user_overflow/1000)%10;
    cout<<ten_dollar<<dollar<<"."<<ten_cent<<cent<<endl;
}

/* display default_overflow in ##.## */
void Counter::displayMaxOverflow() const{
    int cent = default_overflow%10;
    int ten_cent = (default_overflow/10)%10;
    int dollar = (default_overflow/100)%10;
    int ten_dollar = (default_overflow/1000)%10;
    cout<<ten_dollar<<dollar<<"."<<ten_cent<<cent<<endl;
}

/* display current counter mode +/- */    
void Counter::displayMode() const{
    cout<<" ||Current Counter mode:";
    if(addition_mode){
       cout<<"'+'||";
    }else{ 
       cout<<"'-'||";
    }
}

/* display current count value in ##.## */
ostream& operator <<(ostream& cout, Counter &redCounter){
    cout<<"The current count value is: $";
    cout<<redCounter.thousands;
    cout<<redCounter.hundreds;
    cout<<".";
    cout<<redCounter.tens;
    cout<<redCounter.units;
    return cout;
}

/* diplay alert message when overflow or underflow happened */
void displayAlert(const Counter redCounter){
    if(redCounter.maxoverflow()){
       cout<<endl<<"     **ALERT, CAPACITY OVERFLOW, COUNT NOT ACCURATE, PRESS 'r' TO RESET**";
    }else if(redCounter.overflow()){
       cout<<endl<<"     **ALERT, OVERFLOW, COUNT NOT ACCURATE, PRESS 'r' TO RESET**";
    }else if(redCounter.underZero()){
       cout<<endl<<"     **ALERT, UNDERFLOW, COUNT NOT ACCURATE, PRESS 'r' TO RESET**";
    }
}

/* display operating menu */
void displayMenu(){
     cout<<"Enter a character first and follow, if needed, by a digit 1-9:\n"
         <<"Enter'+' if you want to add\n" 
         <<"     '-' if you want to subtract\n" 
         <<"     'a' for units\n"  
         <<"     's' for tens\n"
         <<"     'd' for hundreds\n"
         <<"     'f' for thousands\n"
         <<"     'o' for inquire about overflow\n"
         <<"     'r' for reset counter\n"
         <<"     'm' to inquire about capacity overflow\n"
         <<"     'n' to inquire about underflow\n"
         <<"     'Q' or 'q' at any time to quit,\n"
         <<"Follow by pressing the return key in each case: ";
}


/* check user input for instruction */
bool instructionCheck(char instr[50]){
     if(strcmp(instr, "+") == 0){
        return true;
     }
     if(strcmp(instr, "-") == 0){
        return true;
     }
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
     if(strcmp(instr, "n") == 0){
        return true;
     }
     if(strcmp(instr, "Q") == 0 || strcmp(instr, "q") == 0){
        return true;
     }
     cout<<endl<<"Invalid instruction detected, try Re-Enter again."<<endl;
     return false;
}

/* change addtion_mode to true */
void changeModeAdd(Counter &redCounter){
     redCounter.add();
}

/* change subtraction_mode to true */
void changeModeSub(Counter &redCounter){
     redCounter.sub();
}
/* Reset Object memeber varaiables and local bool value by reference(address) */
void resetCounter(Counter &redCounter, bool &safe){
     redCounter.reset(); 
     safe = true;
     cout<<"RESET COMPLETE!\n"<<endl;
     cout<<redCounter;
     cout<<endl;
}

/* function that returns information about current count and user_overflow */
void inquireOverflow(Counter redCounter){
     cout<<"OVERFLOW TEST REQUESTED."<<endl;
     if(redCounter.overflow()){
        cout<<endl<<"OVERFLOW HAS OCCURRED. "<<endl;
        cout<<"COUNT (UNABLE TO DISPLAY)";
        cout<<" > $";
        redCounter.displayOverflow();
        cout<<endl<<"PLEASE RESET COUNTER OR QUIT."<<endl;
     }else{
        cout<<endl<<"OVERFLOW HASN'T OCCURRED. "<<endl;
        cout<<redCounter;
        cout<<" <= $";
        redCounter.displayOverflow();
     }
}

/* function that returns information about current count and default_overflow */
void inquireCapacityOverflow(Counter redCounter){
     cout<<"CAPACITY OVERFLOW TEST REQUESTED."<<endl;
     if(redCounter.maxoverflow()){
        cout<<endl<<"CAPACITY OVERFLOW HAS OCCURRED. "<<endl;
        cout<<"COUNT (UNABLE TO DISPLAY)";
        cout<<" > $";
        redCounter.displayMaxOverflow();
        cout<<endl<<"PLEASE RESET COUNTER OR QUIT."<<endl;
     }else{
        cout<<endl<<"CAPACITY OVERFLOW HASN'T OCCURRED. "<<endl;
        cout<<redCounter;
        cout<<" <= $";
        redCounter.displayMaxOverflow();
     }
}

/* function that returns information about current count and underflow */
void inquireUnderflow(Counter redCounter){
     cout<<"UNDERFLOW TEST REQUESTED."<<endl;
     if(redCounter.underZero()){
        cout<<endl<<"UNDERFLOW HAS OCCURRED. "<<endl;
        cout<<"COUNT (UNABLE TO DISPLAY)";
        cout<<" < $00.00";
        cout<<endl<<"PLEASE RESET COUNTER OR QUIT."<<endl;
     }else{
        cout<<endl<<"UNDERFLOW HASN'T OCCURRED. "<<endl;
        cout<<redCounter;
        cout<<" >= $00.00"<<endl;
     }
}

/* check validity for user increment/decrement value (1-9) */
bool valueChecker(int value){
     if(value > 0 && value < 10){
        return true;
     }
     cout<<endl<<"Invalid increment value detected, try Re-Enter again."<<endl;
     return false;
}

/* units increment/decrement, Object is passed by reference, checkValue is set as false */
void unitsModify(int value, bool checkValue, Counter &redCounter){
     while(!checkValue){       
           if(redCounter.checkMode()){ 
               cout<<"UNITS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            }else{
	       cout<<"UNITS DECREMENT MODE.\n\nEnter the decrement value (digit 1-9): ";
            }
            cin>>value;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            checkValue = valueChecker(value);
            pause();
     }
     while(value){
         --redCounter;
         value--;
     }
}

/* tens increment/decrement, Object is passed by reference, checkValue is set as false */
void tensModify(int value, bool checkValue, Counter &redCounter){
     while(!checkValue){       
            if(redCounter.checkMode()){ 
               cout<<"TENS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            }else{
	       cout<<"TENS DECREMENT MODE.\n\nEnter the decrement value (digit 1-9): ";
            }
            cin>>value;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            checkValue = valueChecker(value);
            pause();
     }
      while(value){
         -redCounter;
         value--;
     }
}

/* hundreds increment/decrement, Object is passed by reference, checkValue is set as false */
void hundredsModify(int value, bool checkValue, Counter &redCounter){
     while(!checkValue){       
            if(redCounter.checkMode()){ 
               cout<<"HUNDREDS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            }else{
	       cout<<"HUNDREDS DECREMENT MODE.\n\nEnter the decrement value (digit 1-9): ";
            }
            cin>>value;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            checkValue = valueChecker(value);
            pause();
     }
     while(value){
         +redCounter;
         value--;
     }
}

/* thousands increment/decrement , Object is passed by reference, checkValue is set as false */
void thousandsModify(int value, bool checkValue, Counter &redCounter){
     while(!checkValue){      
            if(redCounter.checkMode()){ 
               cout<<"THOUSANDS INCREMENT MODE.\n\nEnter the increment value (digit 1-9): ";
            }else{
	       cout<<"THOUSANDS DECREMENT MODE.\n\nEnter the decrement value (digit 1-9): ";
            }
            cin>>value;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            /* check user input */
            checkValue = valueChecker(value);
            pause();
     }
     while(value){
         ++redCounter;
         value--;
     }
}
  
/* function that could pause and clear the console */
void pause(){
     cout<<endl<<"PAUSING...\n";
     for(int i=0; i<pause_constant; i++){
         i++;
         i--;
     }
     clearConsole();
}

/* clear the console */
void clearConsole(){
     cout<<"\033[2J\033[1;1H";
}

/* print error messgae when detect overflow */
void printErrorMessageOver(const Counter redCounter){
     cout<<"ALERT: COUNT IS OVER THE MAXIMUM SET TO $";
     redCounter.displayOverflow();
     cout<<endl<<"    RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE"<<endl;
     pause();
}

/* print error messgae when detect underflow */
void printErrorMessageUnder(const Counter redCounter){
     cout<<"ALERT: COUNT IS UNDER THE MINIMUM SET TO $00.00"<<endl;
     cout<<endl<<"    RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE"<<endl;
     pause();
}



int main(){
    char instr[50];
    int value = 0;
    /* declare object redCounter, invoke default constructor */
    Counter redCounter;
    bool continueProgram = true, checkValue = false, safe = true;
    /* let user decide default_overflow or user_overflow */
    cout<<"Please select your counter mode. \nPress 'n' for non-default counter, else the counter is set as default: ";
    cin>>instr;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    pause();
    /* if instruction is 'n', user_overflow, get overflow value from user */
    if(strcmp(instr, "n") == 0){   
       /* invoke non default constructor by operator >> */ 
       cin>>redCounter;
    /* else, default_overflow */
    }else{
       cout<<"DEFAULT MODE ACTIVATED.\n"<<endl;
    }
    /* display overflow value */
    cout<<"THE OVERFLOW VALUE: $"; 
    redCounter.displayOverflow();
    pause();
    /* loop until continueProgram become false */
    while(continueProgram){
          /* display current count at top */
          cout<<redCounter;
          redCounter.displayMode();
	  displayAlert(redCounter);
          cout<<endl;
          /* display menu */
          displayMenu();
          cin>>instr;
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          /* check user input */
          if(!instructionCheck(instr)){
             pause();          
          }
         
          if(strcmp(instr, "+") == 0){
             clearConsole();
             changeModeAdd(redCounter);
             pause();
          }else if(strcmp(instr, "-") == 0){
             clearConsole();
             changeModeSub(redCounter);
             pause();
          /* inquireOverflow when instruction is "o" */
          }else if(strcmp(instr, "o") == 0){
             clearConsole();
             inquireOverflow(redCounter);
             pause();
          /* resetCounter when instruction is "r" */
          }else if(strcmp(instr, "r") == 0){
             clearConsole();
             /* bool value notOverflow will be reset to true */
             resetCounter(redCounter, safe);
             pause();
          /* inquireCapacityOverflow when instruction is "m" */
          }else if(strcmp(instr, "m") == 0){
             clearConsole();
             inquireCapacityOverflow(redCounter);
             pause();
          }else if(strcmp(instr, "n") == 0){
             clearConsole();
             inquireUnderflow(redCounter);
             pause();
          /* change continueProgram to false when instruction is "Q" or "q" */
          }else if(strcmp(instr, "Q") == 0 || strcmp(instr, "q") == 0){
             clearConsole();
             cout<<"Goodbye."<<endl;
             continueProgram = false; 
             pause();    
          /* deal with increment */
          }else{ 
             /* check overflow before increment. If overflow, display error message, set notOverflow to false. User have to reset counter in order to proceed increment */
             if(redCounter.overflow()){
                clearConsole();
                printErrorMessageOver(redCounter);
                safe = false;
             }
	     if(redCounter.underZero()){
                clearConsole();
                printErrorMessageUnder(redCounter);
                safe = false;
	     }
             /* unitsIncrement when instruction is "a" and notOverflow is true */
             if(strcmp(instr, "a") == 0 && safe){
                clearConsole();
                unitsModify(value, checkValue, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessageOver(redCounter);
                }else if(redCounter.underZero()){
                   printErrorMessageUnder(redCounter);
                }
             /* tensIncrement when instruction is "s" and notOverflow is true */
             }else if(strcmp(instr, "s") == 0 && safe){
                clearConsole();
                tensModify(value, checkValue, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessageOver(redCounter);
                }else if(redCounter.underZero()){
                   printErrorMessageUnder(redCounter);
                }
             /* hundredsIncrement when instruction is "d" and notOverflow is true */
             }else if(strcmp(instr, "d") == 0 && safe){
                clearConsole();
                hundredsModify(value, checkValue, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessageOver(redCounter);
                }else if(redCounter.underZero()){
                   printErrorMessageUnder(redCounter);
                }
             /* hundredsIncrement when instruction is "f" and notOverflow is true */
             }else if(strcmp(instr, "f") == 0 && safe){
                clearConsole();
                thousandsModify(value, checkValue, redCounter);
                /* check overflow, display error message */
                if(redCounter.overflow()){
                   printErrorMessageOver(redCounter);
                }else if(redCounter.underZero()){
                   printErrorMessageUnder(redCounter);
                }
             }
          }
    }

}
