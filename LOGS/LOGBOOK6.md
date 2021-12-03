# Week 6

## Task 1

To crash the program, we provided the following string: `hello %s`. This string will tell `printf` function that it's expecting an string argument (because of the *%s*). Since there is none, the program will read a invalid address for the string from the argument pointer and it will crash the program.

![Task1 Pic1](../Week6/img/task1_1.PNG)

![Task1 Pic1](../Week6/img/task1_1.PNG)


## Task 2
In this task we try to read variables from the stack. First we discover the length of the input so we can, with the "%x", read our input from the stack. After "%x" 64 times the printf pointer is pointing to the first values we passed to the server.
![Task2 Pic1](../Week6/img/task2_1.PNG)
![Task2 Pic2](../Week6/img/task2_2.PNG)

The Next step was to read the value of the secret message(quite a funny content...."Secret Message"XD). To do so, the 4 first bytes are the address of the Secret address, then we add 63 "%x"(it makes the pointer move) and the a "%s".This takes the next value(it assumes it is an address) pointed by the pointer and prints the content of that address.  Since the next value is the first value we put on the server, the "%s" prints the value of the address we chose.

![Task2 Pic3](../Week6/img/task2_3.PNG)
![Task2 Pic4](../Week6/img/task2_4.PNG)


## Task 3

USing the knoledge of the previous task, we put the fisrt values to be the address we want to change. then use "%x" to move the pointer and use "%x" that will save a number(number of read char until that %n appeared) into the address specified on the next value on th epointer. As mentioned before, the first value is the address of the variable we want to change. Given that we are able to change the value of the address we want.


![Task3 Pic1](../Week6/img/task3_1.PNG)
![Task3 Pic2](../Week6/img/task2_2.PNG)

At a first glance, the value "%n" puts on the address cannot be defined, however we are able to use dummy char that allow us to print more char than the size of the string. Using that we can simulate that the printf read an arbitrary number of char.
We used the number 19980 that was the result of 0x5000 in decimal subtracted by the padding number of "%x" values time 8.
"%.19980u" allow us to print a huge number of things(19980) without having to have them all specified in the input we send to the server.


![Task3 Pic3](../Week6/img/task3_3.PNG)
![Task3 Pic4](../Week6/img/task3_4.PNG)
