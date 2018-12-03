NAME: Jack Weissenberger
CSC- 241 - Lab 7

The purpose of this lab is to gain a better understanding of shared memory and the use of 
semaphores. In this problem there is a unisex bathroom. The rules for using the bathroom are that
if a person of one gender is using the room another may enter as long as there is an available 
stall. If a person of another gender shows up, they have to wait for all of the people from the 
opposite gender to leave before they enter. This is all done using separate processes and 
semaphores controlling 

Compile instructions:
Compile with gcc and then when running the executable, the first argument should be the number of 
stalls you want to have and then the second argument is the number of people you want to have 
in total. The program also reads in a file called unisex.txt. The path of that file on your 
computer needs to be specified as well.