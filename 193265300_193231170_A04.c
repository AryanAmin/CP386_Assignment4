/*
This is the implementation of Banker's Algorithm
MIT License has been included to copyright the program

Authors:

Name: Aryan Amin
Student ID: 193265300
GitHub Username: AryanAmin
Name: Kush Rabadia Nanji
Student ID: 193231170
GitHub Username: KushRabadia
*/

#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

const char *FILENAME = "sample4_in.txt";

typedef struct customer{
 int customerID;
 int type1;
 int type2;
 int type3;
 int type4;

}Customer;

int totalAvailable[5];

Customer *customerAllocated = NULL;
Customer *customerNeed = NULL;
Customer *customerMaximum = NULL;

char safeSequence[5];

int readFile(char *fileName, Customer **tempCustomer);
void allocateResources(int custID, int type_1, int type_2, int type_3, int type_4, int customerCount);
void releaseResources(int custID, int type_1, int type_2, int type_3, int type_4);
int safetyAlgorithm(int numOfCustomers);
void outputValues(int numOfCustomers);
void runBankerAlgo(int numOfCustomers);
void *runThread(void *thread);

int main(int argc, void *argv[]){
 if (argc < 5){
 printf("Not enough parameters passed");
 return -1;
 }
 else{
 for (int i = 1; i < argc; i++){
 totalAvailable[i] = atoi(argv[i]);
 }
 }
 int customerCount = readFile(FILENAME, &customerMaximum);

 customerAllocated = (Customer*)malloc(sizeof(Customer)*customerCount);
 customerNeed = (Customer*)malloc(sizeof(Customer)*customerCount);

 for (int i = 0; i < customerCount; i++){
 // Initially resources of every type is set to 0
 customerAllocated[i].customerID = customerMaximum[i].customerID; // The customer ID is set to same as in the file
 customerAllocated[i].type1 = 0; // Resource type 1 is initially set to 0
 customerAllocated[i].type2 = 0; // Resource type 2 is initially set to 0
 customerAllocated[i].type3 = 0; // Resource type 3 is initially set to 0
 customerAllocated[i].type4 = 0; // Resource type 4 is initially set to 0


 // Initially the allocated resources is 0 so we can say that the need is same as the maximum need for the customer
 customerNeed[i].customerID = customerMaximum[i].customerID;
 customerNeed[i].type1 = customerMaximum[i].type1;
 customerNeed[i].type2 = customerMaximum[i].type2;
 customerNeed[i].type3 = customerMaximum[i].type3;
 customerNeed[i].type4 = customerMaximum[i].type4;
 }
 
 printf("Number of Customers: %d", customerCount);

 printf("Currenlty Available resources: %d %d %d %d", totalAvailable[1], totalAvailable[2], totalAvailable[3], totalAvailable[4]);

 printf("Maximum Resources from file:");

 for (int j = 0; j < customerCount; j++){
 printf("%d %d %d %d", customerMaximum[j].type1, customerMaximum[j].type2, customerMaximum
 [j].type3, customerMaximum[j].type4);
 }

 char command[100];

 while(1){
 printf("Enter Command ('Exit' to Exit Program):");
 fgets(command, 100, stdin);

 char *request = strstr(command, "RQ");
 char *release = strstr(command, "RL");
 char *status = strstr(command, "Status");
 char *exit = strstr(command, "Exit");
 char *run = strstr(command, "Run");

 if (request != NULL){
 printf("Call request function");
 }
 else if (release != NULL){
 printf("Call release function");
 }
 else if (status != NULL){
 printf("Call status function");
 }
 else if (exit != NULL){
 printf("Exiting from the program");
 break;
 }
 else if (run != NULL){
 printf("Call the run function");
 }
 else{
 printf("No command found. Please try RQ, RL, Run or Exit");
 }
 }
}

int readFile(char *fileName, Customer **tempCustomer){
 FILE *file = fopen(fileName, "r");

 struct stat fileStat;
 fstat(fileno(file), &fileStat);

 char *fileContent = (char*) malloc(((int)fileStat.st_size + 1) * sizeof(char));
 fileContent[0] = '\0';

 //Reading the file
 if (file == NULL){
 printf("The file cannot be open");
 return -1;
 }
 else{
 char *stringBuf;
 while(fgets(stringBuf, sizeof(stringBuf), file) != NULL){
 strncat(fileContent, stringBuf, sizeof(stringBuf));
 }
 fclose(file);
 }

 char *temp;
 int numOfCustomers;
}

void allocateResources(int custID, int type_1, int type_2, int type_3, int type_4, int customerCount){
 if (type_1<=customerNeed[custID].type1 && type_2<=customerNeed[custID].type2 &&
 type_3<=customerNeed[custID].type3 && type_4<=customerNeed[custID].type4) 
 {
 if(type_1 <= totalAvailable[1] && type_2 <= totalAvailable[2] && 
 type_3 <= totalAvailable[3] && type_4 <= totalAvailable[4])
 {

 totalAvailable[1] -= type_1;
 totalAvailable[2] -= type_2;
 totalAvailable[3] -= type_3;
 totalAvailable[4] -= type_4;


 customerAllocated[custID].type1 += type_1;
 customerAllocated[custID].type2 += type_2;
 customerAllocated[custID].type3 += type_3;
 customerAllocated[custID].type4 += type_4;

 customerNeed[custID].type1 -= type_1;
 customerNeed[custID].type2 -= type_2;
 customerNeed[custID].type3 -= type_3;
 customerNeed[custID].type4 -= type_4;

 int safe = safetyAlgorithm(customerCount);

 if (safe == 0)
 {
 totalAvailable[1] += type_1;
 totalAvailable[2] += type_2;
 totalAvailable[3] += type_3;
 totalAvailable[4] += type_4;

 customerAllocated[custID].type1 -= type_1;
 customerAllocated[custID].type2 -= type_2;
 customerAllocated[custID].type3 -= type_3;
 customerAllocated[custID].type4 -= type_4;

 customerNeed[custID].type1 += type_1;
 customerNeed[custID].type2 += type_2;
 customerNeed[custID].type3 += type_3;
 customerNeed[custID].type4 += type_4; 
 printf("Not enough resources, need to wait\n");
 }
 else
 {
 printf("request completed sucessfully\n");
 }
 

 }
 else
 {
 printf("Requesting more than available resources\n");
 }
 
 }
 else
 {
 printf("Requesting more than needed resources\n");
 }
}

void releaseResources(int custID, int type_1, int type_2, int type_3, int type_4)
{
 if (type_1<=customerAllocated[custID].type1 && type_2<=customerAllocated[custID].type2 &&
 type_3<=customerAllocated[custID].type3 && type_4<=customerAllocated[custID].type4)
 {
 totalAvailable[1] += type_1;
 totalAvailable[2] += type_2;
 totalAvailable[3] += type_3;
 totalAvailable[4] += type_4;

 customerAllocated[custID].type1 -= type_1;
 customerAllocated[custID].type2 -= type_2;
 customerAllocated[custID].type3 -= type_3;
 customerAllocated[custID].type4 -= type_4;

 customerNeed[custID].type1 += type_1;
 customerNeed[custID].type2 += type_2;
 customerNeed[custID].type3 += type_3;
 customerNeed[custID].type4 += type_4;
 printf("resources released sucessfully\n");
 }
 else
 {
 printf("Releasing more than allocated resources\n");
 }
 
 return;
}

void outputValues(int numOfCustomers){
 printf("Currently available resources: %d %d %d %d\n", totalAvailable[1], totalAvailable[2], totalAvailable[3], totalAvailable[4]);
 printf("Maximum Resources from file:\n");

 //int i=0;
 for (int i=0; i<numOfCustomers; i++) 
 {
 printf("%d, %d, %d, %d\n", customerMaximum[i].type1,customerMaximum[i].type2,customerMaximum[i].type3,customerMaximum[i].type4);
 }

 printf("Currently allocated resources to each customer\n");
 for (int i=0; i<numOfCustomers; i++)
 {
 printf("%d, %d, %d, %d\n", customerAllocated[i].type1,customerAllocated[i].type2,customerAllocated[i].type3,customerAllocated[i].type4);
 }

 printf("Still needed this much resources for each customer\n");
 for (int i=0; i<numOfCustomers; i++) 
 {
 printf("%d, %d, %d, %d\n", customerNeed[i].type1,customerNeed[i].type2,customerNeed[i].type3,customerNeed[i].type4);
 }
 return;
}

int safetyAlgorithm(int customerCount){ 
 int finish[5] = {1,1,1,1,1};
 int availableTemp[5];
 Customer* allocatedTemp = NULL;

 Customer* neededTemp = NULL;
 allocatedTemp = (Customer*) malloc(sizeof(Customer)*customerCount);
 neededTemp = (Customer*) malloc(sizeof(Customer)*customerCount);
 int customerCountTemp = customerCount;

 for(int i=1;i<5;i++)
 availableTemp[i] = totalAvailable[i];

 for(int i =0; i <customerCount;i++)
 {
 
 allocatedTemp[i].customerID = customerMaximum[i].customerID;
 allocatedTemp[i].type1 = customerAllocated[i].type1;
 allocatedTemp[i].type2 = customerAllocated[i].type2;
 allocatedTemp[i].type3 = customerAllocated[i].type3;
 allocatedTemp[i].type4 = customerAllocated[i].type4;
 
 neededTemp[i].customerID = customerMaximum[i].customerID;
 neededTemp[i].type1 = customerNeed[i].type1;
 neededTemp[i].type2 = customerNeed[i].type2;
 neededTemp[i].type3 = customerNeed[i].type3;
 neededTemp[i].type4 = customerNeed[i].type4;
 }
 int safe = 0;//0 is equal to the sequence not being safe
 int check = 0;
 int j;
 

 
 while(customerCountTemp>0)
 {
 safe = 0;//false
 for(int i=0;i<5;i++)
 {
 
 if (finish[i]==1)
 {
 check = 1;
 for (j=1;j<5;j++)
 {

 if (j ==0)
 {
 if (neededTemp[i].type1 > availableTemp[j]) {
 check = 0;
 break;
 }
 }
 if (j ==1)
 {
 if (neededTemp[i].type2 > availableTemp[j]) {
 check = 0;
 break;
 }
 }
 if( j ==2)
 {
 if (neededTemp[i].type3 > availableTemp[j]) {
 check = 0;
 break;
 }
 }
 if (j ==3)
 {
 if (neededTemp[i].type4 > availableTemp[j]) {
 check = 0;
 break;
 }
 }

 }

 if (check==1) {
 finish[i] = 0;
 safeSequence[(5-customerCountTemp)] = i;
 customerCountTemp--;
 safe = 1;

 for (j = 1; j < 5; j++){
 

 switch(j)
 {
 case 0:
 availableTemp[j] += allocatedTemp[i].type1;
 break;
 
 case 1:
 availableTemp[j] += allocatedTemp[i].type2;
 break;
 case 2:
 availableTemp[j] += allocatedTemp[i].type3;
 break;
 case 3:
 availableTemp[j] += allocatedTemp[i].type4;
 break; 
 } 
 }
 break;
 }
 }
 
 }

 if (safe == 0)
 {
 printf("not safe\n");
 break;
 }
 
 }
 return safe;
}

void runBankerAlgo(int numOfCustomers){

 int safe=safetyAlgorithm(numOfCustomers);
 if (safe==0)
 {
 printf("It is unsafe to proceed with Banker Algorithm\n");
 return;
 }
 else{

 for (int i=0;i<numOfCustomers;i++){ //create and execute threads
 int runnable = safeSequence[i];

 pthread_t threadID;
 pthread_attr_t newThread;
 pthread_attr_init(&newThread);

 pthread_create(&threadID, &newThread, runThread, (void *)&runnable);


 pthread_join(threadID, NULL);
 }
 }
 
 return;
}

void *runThread(void *thread){
 int *tid = (int*)thread;

 printf("-> Customer #: %d\n", *tid);

 printf(" Allocated Resources: ");
 printf("%d ",customerAllocated[*tid].type1);
 printf("%d ",customerAllocated[*tid].type2);
 printf("%d ",customerAllocated[*tid].type3);
 printf("%d\n",customerAllocated[*tid].type4);
 printf(" Needed Resources: ");
 printf("%d ",customerNeed[*tid].type1);
 printf("%d ",customerNeed[*tid].type2);
 printf("%d ",customerNeed[*tid].type3);
 printf("%d\n",customerNeed[*tid].type4);
 printf(" Available Resources: ");
 printf("%d ",totalAvailable[1]);
 printf("%d ",totalAvailable[2]);
 printf("%d ",totalAvailable[3]);
 printf("%d\n",totalAvailable[4]);

 printf(" Thread has started \n");
 sleep(2);
 printf(" Thread has finished \n");
 sleep(2);
 printf(" Thread is releasing resources \n");

 printf(" NEW AVAILABLE: ");

 totalAvailable[1] += customerAllocated[*tid].type1;
 printf("%d ",totalAvailable[1]);

 totalAvailable[2] += customerAllocated[*tid].type2;
 printf("%d ",totalAvailable[2]);

 totalAvailable[3] += customerAllocated[*tid].type3;
 printf("%d ",totalAvailable[3]);

 totalAvailable[4] += customerAllocated[*tid].type4;
 printf("%d\n\n",totalAvailable[4]);

 sleep(2);

 customerAllocated[0].type1=0;
 customerAllocated[1].type2=0;
 customerAllocated[2].type3=0;
 customerAllocated[3].type4=0;

 customerNeed[0].type1 = customerMaximum[0].type1;
 customerNeed[1].type2 = customerMaximum[1].type2;
 customerNeed[2].type3 = customerMaximum[2].type3;
 customerNeed[3].type4 = customerMaximum[3].type4;

 pthread_exit(0);
}
