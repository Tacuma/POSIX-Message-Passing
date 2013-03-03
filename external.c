//Tacuma Solomon
//@02580808
//Lab 2 - Part 1
//Operating Systems
    	
    	
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
   	
struct {
   	long priority;
   	int temp;
   	int pid;
   	int stable;
}extm,centm;

//external processes pass extm
//central process passes centm
   	
   	
 const int centralbox = 1000;
   	
 int main(int argc, char *argv[]){
   	
 	//ensures correct number of arguments
   	if (argc != 3){
   		printf("%d", argc);
   		printf("Incorrect number of arguments inserted.\n");
   		return 0;
   	}	
   	else{
   
   		//setting up variables
   		int centid, extid, boxnumber,stat;
   		int initialTemp = atoi(argv[1]);	
  		int pid = atoi(argv[2]);
   		
   		//initializing values
   		extm.priority = 2;	
   		extm.temp=initialTemp;
   		extm.pid=pid;
   		extm.stable=0;
   			
   		//box number is assigned based on process id
   		boxnumber = centralbox+pid;
   	
   	
   		//central mailbox ID is set up
   		centid = msgget(centralbox, 0600 | IPC_CREAT);
   		//printf("External %d sets up Central Mailbox id no. %d \n" ,pid,centid);
   			
   		//external mailbox ID is set up
  		extid = msgget(boxnumber, 0600 | IPC_CREAT);
   		//printf("External %d sets up external Mailbox id no. %d \n",pid,extid);
   		printf("Beginning External Process %d. Temperature = %d \n ",extm.pid,extm.temp);	
   	
   		//While the temperatures of the System aren't stable
   		while (centm.stable!=1){		
   			//send message to central box
   			stat = msgsnd(centid, &extm, sizeof(extm)-sizeof(long), 0);
   			//printf("%d Sent from External %d to Central \n",extm.temp,extm.pid);
   			//receive sent message from external process mailbox
   			stat = msgrcv(extid, &centm, sizeof(centm)-sizeof(long),2,0);
   			//printf("New Message %d received from central in External %d \n", centm.temp,pid);
   	
   			//if the message returned is stable, exit loop
   			if (centm.stable == 1){
   				//printf("Stabilized Temperature Acquired\n");
   			}
   			else { //else calculate a new temperature
   				extm.temp = (extm.temp*3 + 2*centm.temp)/5;
   			}
   		}
   		printf("Final External Process %d Temperature = %d\n", extm.pid,centm.temp);
   		stat = msgctl(extid, IPC_RMID,0);	//closes external mailbox	
   		printf("Ending External Process %d \n",extm.pid);
   	}
   return 0;
 }
   			

