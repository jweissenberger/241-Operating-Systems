NAME: Jack Weissenberger
CSC-241 - Lab 4

The purpose of this lab is to learn more about shared memory, semaphores, mutexs and concurency.
The lab creates a process for every customer entering the barber shop. The customers check to see
if there is availble space in the room for them and if there is not, they leave. If the barber is 
asleep, the customer wakes them up and gets a haircut, then goes to pay at the cashier. If the 
barber is busy giving a haircut, the customer checks to see if there is an avaiable chair and 
takes a seat. 

Compile and execution instructions:
Compile with regular gcc comands. To execute the program include two command line arguments, the
first for the number of chairs and the second for the number of customers.