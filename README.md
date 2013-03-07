#POSIX Message Passing


#Data Structures/Concepts Used:
Structs, Processes, Mailboxes, Message Queues


#Description
Four external processes will commuicate temperatures to a central process, which in turn will reply with its own temperature
and will indicate whether the entire system has stabilized. Each process will receive its initial temperature upon creation
and will recalculate a new temperature according to two forumlas.

Initially, each external process will send its temperature to the mailbox for the central process. If all four temperatures
are exactly the same as those sent by the four processes during the last iteration, the system has stabilized. In this case, 
the central process will notify each external process that it is now finished (along with the central process itself), and 
each process will output the final stabilized temperature. If the system has not yet become stable, the central process
will send its new temperature to the mailbox for each of the outer processes and await their replies. The processes will 
continue to run until the temperature has stabilized.

#####Structure of External Process
*   The external process has 2 stucts, extm and centm.
    +   	The extm represents messages sent to the central process and 
    +	    The centm represents messages that are received from the central process.
*	A central box with a value of 1000 is declared and initialized.
*	When the process is run, a construct exists to make sure that there are 2 extra arguments, one for the process ID and the other for the initial temperature.
*	The ID for the central mailbox is set up
*	The ID for the external process' mailbox is set up. The ID of this mailbox is based on the process ID + the central box number which is 1000.
*	Sending and receiving: 
*	A loop is set up. While central process's message stability is != 1, the loop continues.  
    *	A message is sent to the central Mailbox.
    *	A message is received from of the external mailbox
    *	If the incoming message's stability is 1, then exit the loop and output the final temperature
    *	If it isn't, calculate a new temperature

#####Structure of the Central Process        
The Central Process' Structure is slightly more complicated. Because it sends and receives messages from  the 4 external processes, it must have the IDs for its own mailbox and for the external mailboxes it messages.
*	The central process contains 2 structs, extm and centm. The central process receives messages in the extm struct and sends messages via the centm struct. There is a construct that ensures the correct number of arguments is given.
*	When the central process runs a central ID is set up. 
*	A for loop is also run to set up the external process mailboxes.
*	The central process then goes into a loop, staying in it until the centm's stability is = 1
*	In the Loop:  
    o	The central message process reads the temperatures from its mailbox using a loop. It tallies the total and compares each external message's temp to its temperature. If the match it takes a note in a variable called finish. If they are not equal, a new central temperature is calculated and sent back to the external processes. If the temperatures of the external processes match the central process on two successive occasions, then the temperatures are stabilized. A message is then sent back to the external processes with the value of centm’s stability =1, which ends the external threads and has them print out their temperatures.





#Output:
	takuma@ubuntu:~/Desktop/C Programs$ ./run.sh   
	Beginning Central Process. Temperature = 60   
	Beginning External Process 4. Temperature = 40   
	Beginning External Process 2. Temperature = 22   
	Beginning External Process 3. Temperature = 50   
	Beginning External Process 1. Temperature = 100   
	The system has stabilized.  
	Final External Process 1 Temperature = 49   
	Final Central Temperature = 49  
	Ending External Process 1   
	Ending Central Process.   
	Final External Process 3 Temperature = 49  
	Ending External Process 3   
	Final External Process 4 Temperature = 49  
	Ending External Process 4   
	Final External Process 2 Temperature = 49  
	Ending External Process 2   
	takuma@ubuntu:~/Desktop/C Programs$   

