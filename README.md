# thread
Doing this task incrementally to implement threads in a better way. 

Objective of the program: Find the key for the hash given in the command line argument of the program (Exe file).

Key space can be defined by length and characters of ASCII code used.
1. Length: It is the number of characters in the key. Minimum and maximum length can be defined here. Just leave a space between them.
2. Range : It is the characters of the ASCII code used. Ranges can be defined here in ASCII values. 
So, a range of 65-90 will fill the range parameter with all the letter from uppercase 'A' to 'Z'.
ASCII value of smaller element-ASCII value of largest element in range


Command line arguments: 1 3        65-90:97-122    e1faffb3e614e6c2fba74296962386b7
Explanation for args  : key length  range          128 bit hexdecimal hash to be decoded by the keys

Default arguments     : 1 3        a-z:A-Z    e1faffb3e614e6c2fba74296962386b7
Default answer        : AAA for the hash code e1faffb3e614e6c2fba74296962386b7


You can use https://www.md5hashgenerator.com/ to get hash code for a key. Give the proper range to the program and the key will be generated.




