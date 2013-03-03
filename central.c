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

	if (argc != 2){
   		printf("%d", argc);
   		printf("Incorrect number of arguments inserted.\n");
  	return 0;
	}
	else{
		//setting up variables
   		int centid, extid[4], boxnumber,stat;

   		//initializing central values
   		centm.temp = atoi(argv[1]);
   		centm.priority = 2;
   		centm.pid = 0;
   		centm.stable = 0;

	   	//central mailbox ID is set up
	   	centid = msgget(centralbox, 0600 | IPC_CREAT);
	 	//printf("Central %d sets up Central Mailbox id no. \n" ,centid);

	   	//setting up external process mailboxes boxes
	   	int i;
	   	for(i=1;i<=4;i++){
	   		extid[i-1]=msgget((centralbox+i), 0600 | IPC_CREAT);
	   	}

	   	printf("Beginning Central Process. Temperature = %d \n",centm.temp);

	   	int finish = 0;
	  	while (centm.stable!=1) {
	   		//recieve external messages
	   		int j,count=0,total=0;

	   			for(j=0;j<4;j++){
	   				stat = msgrcv(centid, &extm, sizeof(extm)-sizeof(long),2,0);
	   				//printf("Message %d received from External %d \n", extm.temp,extm.pid);
	   				total = total + extm.temp;
	   				if (centm.temp==extm.temp){
	   					count++;
	   				}
	   			}


	   			if(count==4){ //if all four processes have the same value...
	   				finish++;	// increment the finish count
	  			}

	   			if (finish==2){ //if the finish count = 2 ...
	   				centm.stable = 1;
	   				printf("The system has stabilized.\n");
	   				int l;
	   				for(l=0;l<4;l++){
	   					stat = msgsnd(extid[l], &centm, sizeof(centm)-sizeof(long), 0);
	   					//printf("%d Final Message Sent from Central to External \n", centm.temp);
	   				}
	   			}
	   			else{ //Recalculate a new central temp and send the message to external temps
	   				centm.temp = ((2*centm.temp+total)/6);
	   				int k;
	   				for(k=0;k<4;k++){ //sends messages
	   					stat = msgsnd(extid[k], &centm, sizeof(centm)-sizeof(long), 0);
	   					//printf("%d Message Sent from Central to External \n", centm.temp);
	   				}
	   			}
	   		}
	   		printf("Final Central Temperature = %d\n",centm.temp);
			stat = msgctl(centid, IPC_RMID,0);
	   		printf("Ending Central Process. \n");
	}
   	return 0;
   }



