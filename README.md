# Minitalk
This is a first mini project for the 42school, learning about signals.  
A client and a server communicate with each other only using signals.  
The client sends a string and the server prints it out.  
The detailed project description is in the pdf file.  

## I passed the project with 125%
<img src="ScreenshotSuccess.png" alt="Success Photo" width="200">

## Usage
This project was written for and compiled on a Mac.  
Execute make for both client and server program:
```
make
```
Then start the server, read the PID and execute the client:
```
./server
ps
./client pid string
```
The server should print out the string.

## Caveats
This project was a 42School project, we had to program according to a strict norm, for instance using only while loops, having only 25 lines per function, not using inline comments etc.
