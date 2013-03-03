#POSIX Message Passing


#Data Structures/Concepts Used:
Structs, Processes, Mailboxes, Message Queues


#Description
The first part of Lab2 is a program that shows off an example of POSIX Message Passing.  In this program, there are two types of processes. The first is the central process and second is the external process.
How this program works is that 4 invocations of the external process and one invocation of the central process is run at the same time. Each external process is initialized with a temperature and a process ID number. The central process is initialized with a temperature only. The processes are started by using a simple script called run.sh. The aim of the program is to demonstrate synchronization via message passing. Each external process sends its temperature to the Central process mailbox. The central process reads the temperatures from its mailbox. If the external processes and the central process have different temperatures, the central process runs a routine which recalculates a new temperature and sends it back to external processes, which then calculate their own temperature. The program ends when all of the temperatures match.

Structure of External Process
• The external process has 2 stucts, extm and centm.
o	The extm represents messages sent to the central process and 
o	The centm represents messages that are received from the central process.
•	A central box with a value of 1000 is declared and initialized.
•	When the process is run, a construct exists to make sure that there are 2 extra arguments, one for the process ID and the other for the initial temperature.
•	The ID for the central mailbox is set up
•	The ID for the external process’ mailbox is set up. The ID of this mailbox is based on the process ID + the central box number which is 1000.
•	Sending and receiving: 
•	A loop is set up. While central process’s message stability is != 1, the loop continues.
o	A message is sent to the central Mailbox.
o	A message is received from of the external mailbox
o	If the incoming message’s stability is 1, then exit the loop and output the final temperature
o	If it isn’t, calculate a new temperature

The structure of the Central Process
The Central Process’ Structure is slightly more complicated. Because it sends and receives messages from  the 4 external processes, it must have the IDs for its own mailbox and for the external mailboxes it messages.
•	The central process contains 2 structs, extm and centm. The central process receives messages in the extm struct and sends messages via the centm struct. There is a construct that ensures the correct number of arguments is given.
•	When the central process runs a central ID is set up. 
•	A for loop is also run to set up the external process mailboxes.
•	The central process then goes into a loop, staying in it until the centm’s stability is = 1
•	In the Loop:
o	The central message process reads the temperatures from its mailbox using a loop. It tallies the total and compares each external message’s temp to its temperature. If the match it takes a note in a variable called finish. If they are not equal, a new central temperature is calculated and sent back to the external processes. If the temperatures of the external processes match the central process on two successive occasions, then the temperatures are stabilized. A message is then sent back to the external processes with the value of centm’s stability =1, which ends the external threads and has them print out their temperatures.





Output:
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

