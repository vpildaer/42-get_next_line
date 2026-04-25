*This project has been created as part of the 42 curriculum by vpildaer.*

# Get_Next_Line - 42 Belgium

This project is about coding a function that returns a line read from a file descriptor.

## Status

Started on April 19th 2026.

## Table of Contents

* [Description](#description)
* [Instructions](#instructions)
* [Memory Handling](#memory-handling)
* [Resources](#resources)
* [AI use](#ai-use)

## Description

Get_Next_Line is a project that aims at coding a function that reads from a file, thanks to its file descriptor, one line at a time.

Actually, the function does not read line by line. It reads characters by chunks of BUFFER_SIZE (to be defined at compile time) characters. The tricky part is that the function returns the *next* line, but might read more than that. 

Indeed, in this project, one of the only functions allowed is [read](https://man7.org/linux/man-pages/man2/read.2.html). It takes as an argument the number of bytes to be read from the file. Once read, those bytes are stored in the buffer, also sent as an argument to the function, and cannot be "re"read. 

The whole challenge is to be able to keep in memory the bytes read after a new line character (\n) is found, and the line is returned by the function, for the next call of the function.

### Personal approach

I decided to use a [linked list](https://www.geeksforgeeks.org/c/linked-list-in-c/) for this project. 

The general idea is that everytime we read BUFFER_SIZE characters, we create a new node (containing a buffer with the characters read) that we append at the end of the list, until there is a new line character found. 

Then we count the numbers of characters of the line to create the buffer that will be returned with all the characters of the line copied inside. Before returning the line, we create a new node with the charcters already read after the new line character, to store them for the next `get_next_line` call.

They will be kept in memory thanks to the **static** variable that is our pointer to the first element of the linked list.

### Bonus part

The bonus part of this project is to be able to read from different files "at the same time". That means being able to handle multiple file descriptors, by calling `get_next_line` on one, then on another, then back to the first one, then on a third one, etc.

Since I used a linked list for this project, the adjustment was pretty straightforward. Instead of using a **static** pointer, I transformed it into a static **array** of pointers, with their indexes being equal to the file descriptor they refer to. 

Thus each file descriptor has "its own static linked list".

## Instructions

`get_next_line` is a function, not a program. That means you would need a `main` function to be able to run/test the function. And obviously, you would need a file to read from. 

Let's consider a file `text.txt` containing one or multiple lines, and the following main function :

```
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY)
	while ((line = get_next))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

In this case, [open](https://man7.org/linux/man-pages/man2/open.2.html) takes two arguments : the name of the file as well as a tag, `O_RDONLY`, letting the function know that we will only be reading from the file, without executing any modifications to it.

Since `get_next_line` returns the new line characters, no need to call `printf` with a new line character after the string indicator.

And after we open a file, it is of course important to [close](https://man7.org/linux/man-pages/man2/close.2.html) it.

And here is how to run the program :

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c && ./a.out
```

I added a guard in the header file, in case the program were to be run without (re)define BUFFER_SIZE : 

```
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

```

## Memory Handling

One of the key challenges of this project is to be able to handle memory correctly.

That means using [free](https://man7.org/linux/man-pages/man3/free.3p.html) on every block of memory that has been allocated with [malloc](https://man7.org/linux/man-pages/man3/free.3.html).

Considering linked lists, that means freeing every node of a list as well as every content of each node. 

### How to use `valgrind`

[Valgrind](https://valgrind.org/info/about.html) is a tool for memory management on Linux. When run, it gives key information about memory leaks, which is something to be avoided at all costs !

Valgrind can be used on the executable once compiled with cc (and its flags).

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

```
valgrind ./a.out
```

By doing so, valgrind provides us with a "**heap summary**", a little note on how the memory was managed while running the executable and if it was done correctly = if all allocated blocks of memory were freed correctly.

For more details, in case of a memory leak for example, valgrind can be runned as following :

```
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

This is a very useful tool when programming in C language, in which memory management is a very important aspect.

## Resources

* [Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
* [Open function](https://man7.org/linux/man-pages/man2/open.2.html)
* [Read function](https://man7.org/linux/man-pages/man2/read.2.html)
* [Close function](https://man7.org/linux/man-pages/man2/close.2.html)
* [Linked List in C](https://www.geeksforgeeks.org/c/linked-list-in-c/)
* [Malloc function](https://man7.org/linux/man-pages/man3/free.3.html)
* [Free function](https://man7.org/linux/man-pages/man3/free.3p.html)
* [Valgrind](https://valgrind.org/info/about.html)

## AI use

AI was used to understand what "still reachable" memory is, and how to fix it. It turned out that no "still reachables" could be found in my function if the file is read entirely. The "still reachable" memory warning I was getting was because I was using valgrind on the compiler, by running : 
```
valgrind cc get_next_line.c get_next_line_utils.c
```

AI was also used to generate texts to test the bonus part of this project.
