Author: Tim McVicker
Date: 30JAN2016

This project contains two executables, valueServer and valueGuesser.  It is 
the solution to CPSC3600 HW#1.

Running the programs:
	The project must be run on two seperate terminals.  First, on one 
	terminal the user must enter the command "make"
	One terminal must then run valueServer, the other must run valueGuesser

	The command line arguments for the server are:
	valueServer -p <serverPort> [-v initialValue] 

	The command line arguments for the guesser are:
	valueGuesser -s <serverIP> -p1 <serverPort1> -p2 <serverPort2>

	The server will listen for requests forever or until a CTRL-C is
	issued.
	The client will ask for integer inputs between 1 and 900000000.  It
	will then send the guess to the sever and output the accuracy of the
	guess.  It will run until either a correct guess is input, or a
	CNTRL-C is issued.

	On exit, the server will display the number of messages received,
	the number of correct guesses, and the IP addresses of the clients.
	On exit, the client will display the number of attempts, the elapsed
	time, and the last guessed value.

Design:
	The server opens a socket on the requested port, binds to that socket,
	and blocks while waiting for a UDP datagram.  It then adds the sending 
	client to the list of clients and responds with a UDP datagram 
	indicating the accuracy of the guess. It then re-blocks until the next
	message is received. On the receipt of SIGINT, it terminates the
	service and prints out the message.

	The client/guesser first finds the requested server, if it exists, by
	using getaddrinfo.  It then creates a UDP socket.  Sigaction is called 
	to handle timeout errors.  It then asks for an input value, and uses
	this to send a UDP datagram via sendto().  It then sets an alarm.  IF
	no message is received within a second, it repeats the process began
	at asking for an input.  it loops until a correct reply comes, or a 
	SIGINT is sent.  it then calculates the output data and terminates the 
	program.  
