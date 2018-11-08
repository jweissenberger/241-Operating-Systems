NAME: Jack Weissenberger
CSC-241 - Lab 5

The purpose of this lab is to use three processes and shared memory to solve Conway's Problem. 
The first process is the producer which reads in a text file character by charcter and feeds 
each letter into a shared memory. It also replaces any new lines with "<EOL>". The second process
is the squasher which reads in each character from the first shared memory and replaces any 
adjacent ** with a #. It then feeds these character by character into the second shared memory. 
The final process is the printer which reads in each character from the second shared memory and 
prints out each character on 20 character long lines.

To complie this program all you need is a proper text file to read in.