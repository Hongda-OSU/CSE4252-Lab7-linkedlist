/*Name Hongda Lin (lin.3235)*/
/*Date: 23/3/2021*/
#include <iostream>
#include <ios>
#include <limits>
#include <cctype>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

#define stewSize1 5
#define stewSize2 20

class Node{  
     public:
       /* default constructor */
       Node();
       /* non-default constructor */
       Node(Node *next, char *lastName, char *firstName, unsigned int ID);
     
       /* getter functions */
       void getLastName()const;
       void getFirstName()const;
       unsigned int getId()const;
       Node *getLink()const;

       /* setter functions */
       void setId(unsigned int ID);
       void setLastName(char *lastName);
       void setFirstName(char *firstName);
       void setLink(Node *next);

     /* private data section */
     private:
       char last[30];
       char first[20];
       unsigned int id;
       Node *link;
}; 

/* default constructor */
Node::Node(){
     setLink(NULL);
}

/* non-default constructor */
Node::Node(Node *next, char *lastName, char *firstName, unsigned int ID){
     setLastName(lastName);
     setFirstName(firstName);
     setId(ID);
     setLink(next);  
}

/* return the lastName of current node */
void Node::getLastName()const{
     cout<<setw(stewSize2);
     cout<<last;
}

/* return the firstName of current node */
void Node::getFirstName()const{
     cout<<setw(stewSize2);
     cout<<first;
}

/* return the id of current node */
unsigned int Node::getId()const{
     return id;
}

/* return the address of the linked node of current node */
Node* Node::getLink()const{
     return link;
}

/* set this->id = ID */
void Node::setId(unsigned int ID){
     id = ID;
}

/* set this->lastName = lastName */
void Node::setLastName(char *lastName){
     strcpy(last, lastName);
}

/* set this->firstName = firstName */
void Node::setFirstName(char *firstName){
     strcpy(first, firstName);
}

/* set this->link = next */
void Node::setLink(Node *next){
     link = next;
} 

/* function prototypes */
void push(Node **ptr2_head, char *lastName, char *firstName, unsigned int ID);
int countNode(Node *ptr_head);
void setName(char *name, char *lastName, char *firstName);
int validId(Node *ptr_head, unsigned int ID);
int validIndex(Node *ptr_head, int index);
void displayErrorInput(int input, char *firstName, char *lastName, unsigned int ID);
void displayTable();
bool instrCheck(char instr[50]);
void displayList(Node *ptr_head);
void reverse(Node **ptr2_head);
void sortedInsert(Node **ptr2_head, Node *new_node);
void insertionSort(Node **ptr2_head);
void deleteList(Node **ptr2_head);
void insertNode(Node **ptr2_head);
void removeByIndex(Node **ptr2_head, int index);
void removeNode(Node **ptr2_head);

/* method that push a new node into linked list in reversed order */
void push(Node **ptr2_head, char *lastName, char *firstName, unsigned int ID){
     Node *temp = NULL;
     /* the linker is the head node, newNode <- head */
     temp = new Node(*ptr2_head, lastName, firstName, ID);
     /* update new node to bew head node */
     *ptr2_head = temp;
}

/* return the number of nodes in current linked list */
int countNode(Node *ptr_head){
    int count = 0;
    while(ptr_head){
          count++;
          ptr_head = ptr_head->getLink();
    }
    return count;
}

/* separate the first name and last name from the name read from file */
void setName(char *name, char *lastName, char *firstName){
     int i = 0, j = 0;
     while(name[i] != ','){
           lastName[i] = name[i];
           i++;
     }
     lastName[i] = '\0';
     i++;
     while(name[i]){
           firstName[j] = name[i];
           j++;
           i++;
     }
     firstName[j] = '\0';
}

/* id in this linkedlist must be unique, 0 means invalid id, 1 means valid id */
int validId(Node *ptr_head, unsigned int ID){
     while(ptr_head){
       if(ptr_head->getId() == ID){
          return 0;
       }
       ptr_head = ptr_head->getLink();
     }
     return 1;
}

/* check the index is in the range of linkedlist, 0 means false, 1 means true */
int validIndex(Node *ptr_head, int index){
    int result = 1;
    int maxIndex = countNode(ptr_head);
    if(index > maxIndex){
       cout<<"Index out of bounds! Current linked list only contains "<<maxIndex<<" Nodes, try Re-Enter again!"<<endl;
       result = 0;
    }else if(index <=0){
       cout<<"Invalid index! Current linked list only contains "<<maxIndex<<" Nodes, try Re-Enter again!"<<endl;
    }
    return result;
}

/* display the invalid data while reading data from file */
void displayErrorInput(int input, char *firstName, char *lastName, unsigned int ID){
     cout<<"Input: "<<(input+1)<<" last= "<<lastName<<" first= "<<firstName<<". His/her id= "<<ID<< " already exists; Not added to the list!"<<endl;
}

/* display table */
void displayTable(){
     cout<<"Enter 'p' to display the list, 'a' to add a node, 'r' to remove a node,"<<endl<<"      'd' to destory the list, 'e' to exist: ";
}

/* check user input for instruction */
bool instrCheck(char instr[50]){
     if(strcmp(instr, "p") == 0){
        return true;
     }
     if(strcmp(instr, "a") == 0){
        return true;
     }
     if(strcmp(instr, "r") == 0){
        return true;
     }
     if(strcmp(instr, "d") == 0){
        return true;
     }
     if(strcmp(instr, "e") == 0){
        return true;
     }
     if(strcmp(instr, "y") == 0){
        return true;
     }
     if(strcmp(instr, "n") == 0){
	cout<<"You could Re-Enter again!"<<endl;
        return false;
     }
     cout<<"Invalid instruction detected, try Re-Enter again!"<<endl;
     return false;
}

/* display the linkedlist in formatted list view */
void displayList(Node *ptr_head){
     int counter = 1;
     if(ptr_head == NULL){
        cout<<"List is empty"<<endl;
     }
     while(ptr_head){   
           cout<<setw(stewSize1)<<counter;
           ptr_head->getLastName();
           ptr_head->getFirstName();
           cout<<setw(stewSize2)<<ptr_head->getId()<<endl;
           ptr_head = ptr_head->getLink();
           counter++;
     }
}

/* reverse the linked list */
void reverse(Node **ptr2_head){
     Node *previous = NULL; 
     Node *current = *ptr2_head;
     Node *next = NULL;
     while(current != NULL){
           next = current->getLink();
           current->setLink(previous);
           previous = current;
           current = next;
     }
     *ptr2_head = previous;
}

/* sort the nodes in linked list by the value of id */
void sortedInsert(Node **ptr2_head, Node *new_node){
     Node *current = NULL;
     if(*ptr2_head == NULL || (*ptr2_head)->getId() >= new_node->getId()){
        new_node->setLink(*ptr2_head);
        *ptr2_head = new_node;
     }else{
        current = *ptr2_head;
        while(current->getLink() != NULL && current->getLink()->getId() < new_node->getId()){
              current = current->getLink();
        }
        new_node->setLink(current->getLink());
        current->setLink(new_node);
     }
}

/* wrapper function that sort the linked list by calling function sortedInsert */
void insertionSort(Node **ptr2_head){
     Node *sorted = NULL;
     Node *current = *ptr2_head;
     while(current != NULL){
          Node *next = current->getLink();
          sortedInsert(&sorted, current);
          current = next;
     }
     *ptr2_head = sorted;
}

/* delete the linked list */
void deleteList(Node **ptr2_head){
    Node* deleteNode = *ptr2_head;
    Node* next = NULL;
    while (deleteNode != NULL){
        next = deleteNode->getLink();
        delete(deleteNode);
        deleteNode = next;
    }
    *ptr2_head = NULL;
}

/* insert a new node to linked list */
void insertNode(Node **ptr2_head){
     char firstName[20], lastName[30], instr[50];
     int ID, idCheck = 1;
     /* get the lastName, firstName and id */
     do{
        cout<<"Enter First Last and id: ";
        cin>>firstName>>lastName>>ID;
        cout<<"You entered: "<<lastName<<" "<<firstName<<" "<<ID<<endl;
	cout<<"Is it correct (y/n): ";
	cin>>instr;
        idCheck = validId(*ptr2_head, ID);
        if(idCheck == 0 && strcmp(instr, "n") != 0){
           cout<<"ID already exists in linked list, try Re-Enter again!"<<endl;
        }
     }while(!instrCheck(instr) || idCheck == 0);
     /* create a new node, like to the head, update the head node, sort the new list */
     Node *newNode = new Node(*ptr2_head, lastName, firstName, ID);
     *ptr2_head = newNode;
     insertionSort(ptr2_head); 
}

/* remove a node from linked list by index */
void removeByIndex(Node **ptr2_head, int index){
     int counter = index - 1;
     Node *deleteNode, *previous, *next;
     /* remove head node, head address needs update */
     if(counter == 0){
        deleteNode = *ptr2_head;
        next = (*ptr2_head)->getLink();
        delete(deleteNode);
        *ptr2_head = next;
        return;
     }
     /* remove other node, head address don't change */
     deleteNode = *ptr2_head;
     for(int i=0; i<counter; i++){
         previous = deleteNode;
         deleteNode = deleteNode->getLink();
     }
     previous->setLink(deleteNode->getLink());
     delete(deleteNode);
}

/* wrapper method that get the index of removed node and call remove method removeByIndex */
void removeNode(Node **ptr2_head){
     int index, indexCheck = 1, numNode;
     char instr[50];
     /* current linked list is empty */
     if(*ptr2_head == NULL){
         cout<<"Current linked list is empty! Try to enter some nodes!"<<endl;
         return;
     }
     do{
        numNode = countNode(*ptr2_head);
        cout<<"Enter a index of Node (between 1 and "<<numNode<<") to remove: ";
        cin>>index;
	cout<<"Is it correct (y/n): ";
	cin>>instr;
        if(strcmp(instr, "n") != 0){
           indexCheck = validIndex(*ptr2_head, index);
        }
     }while(!instrCheck(instr) || indexCheck == 0); 
     removeByIndex(ptr2_head, index);
}


int main(){
    char name[50], instr[50];
    bool continueProgram = true;
    char fileName[] = "Data.7";
    int numNode = 0, input = 0;
    unsigned int ID;
    /* create the head node and the reference to it */
    Node *ptr_head = NULL;
    Node **ptr2_head = &ptr_head;
    ifstream in_stream;
    /* read the file */
    in_stream.open(fileName);
    if(in_stream.fail()){
        cout<<"Input file opening failed."<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Creating a link list using data from "<<fileName<<" file"<<endl;
    /* set up the linked list */
    while(in_stream>>name){
	 char firstName[20], lastName[30];
         setName(name, lastName, firstName);
         in_stream>>ID;
         if(validId(ptr_head, ID)){
            push(ptr2_head, lastName, firstName, ID);
         }else{
            displayErrorInput(input, firstName, lastName, ID);
         }
         input++;
    }
    /* reverse the current linked list(reverse order) */
    reverse(ptr2_head); 
    /* sort the node in reversed linked list by the value of id */
    insertionSort(ptr2_head);
    /* count the nodes */ 
    numNode = countNode(ptr_head);

    cout<<endl<<"Link list created. Number of nodes = "<<numNode<<endl;
    while(continueProgram){
          displayTable();
          cin>>instr;
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
          if(instrCheck(instr)){
             cout<<"You entered= "<<instr<<endl;          
          }
          /* print the list */
          if(strcmp(instr, "p") == 0){
             displayList(ptr_head);
          }
          /* exit the list */
          if(strcmp(instr, "e") == 0){
	     deleteList(ptr2_head);
             cout<<"Goodbye."<<endl;
             continueProgram = false;    
          }
          /* delete the list */
 	  if(strcmp(instr, "d") == 0){
             deleteList(ptr2_head);
             numNode = countNode(ptr_head);
	     cout<<"List has been destroyed; Number of nodes= "<<numNode<<endl;
          }
          /* add a node to the list */
          if(strcmp(instr, "a") == 0){
             insertNode(ptr2_head);
             numNode = countNode(ptr_head);
	     cout<<"Node added to the list; Number of nodes= "<<numNode<<endl;
          }
          /* remove a node from the list */
	  if(strcmp(instr, "r") == 0){
             removeNode(ptr2_head);
             numNode = countNode(ptr_head);
	     cout<<"Node removed from the list; Number of nodes= "<<numNode<<endl;
          }
    } 
    /* close file */
    in_stream.close();
    return 0;
}
