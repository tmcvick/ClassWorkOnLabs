Package:  UDPEcho.tar.gz

Explanation:  

This package is a very simple UDP client and server set of Unix programs. 
Two executables are created: client1 and server.  Once the server is
started it waits forever for a message from the client.  Once the client
is started, it sends a text word to the server, waits for the server
to echo the word, displays the word and then exits.  The server runs
forever echoing back everything that it receives.

This package also provides a Makefile that handles multiple files
and building on different operating systems.

Feel free to use this package as a starting point for any
program you might need to develop. The code was originally obtained from source 
code from the Web site accompanying the textbook "TCP/IP Sockets in C  Practical
Guide for Programmers"  by Michael Donahoo and Ken Calvert.

------------------------------------------------------------------
Unpacking Instructions: 

Copy the UDPEcho.tar.gz package into a directory that you will use to
build and run the program from.  Issue the following commands:

>gzip -d UDPEcho.tar.gz
>tar -xf UDPEcho.tar

When done, you should see the following files:

DieWithError.c  Make.defines  Makefile.bak  UDPEcho.tar.gz    UDPEchoClient1.o  UDPEchoServer.o  readme.txt
DieWithError.o  Makefile      UDPEcho.h     UDPEchoClient1.c  UDPEchoServer.c   client1*         server*


------------------------------------------------------------------
Build Instructions:
When you download this package, issue the following to build:
>make clean
>make depend
>make


------------------------------------------------------------------
Invocation:


./server <UDP SERVER PORT>
  -The single parameter specifies the port the server will use.

./client1 <Server IP> <Echo Word> [<Echo Port>]
  -First parameters is the server's IP address in dotted decimal format 
   or as a domain name.
  -The second param is the word that is sent to the server
  -The third param is the server's port number



------------------------------------------------------------------
Makefile instructions:

NOTE:  If you modify the makefile, you should use TABs after the '=' on a line!!!

There is a Makefile and an additional Make.defines file that is included
by the Makefile.  

The PROGS line identifies the two targets that will be
run when a 'make' is executed.  Note that you can build just one target
by issuing a 'make client1' or 'make server'.  

The OPTIONS specifies compiler options that are included in the compiler command.

The objects and source files of code files that do not contain the main program
must be specified in the OBJECTS and SOURCES lines.

The client1: and server: targets are defined. Below is the client1: target.

client1:        UDPEchoClient1.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
                ${CC} ${LINKOPTIONS}  $@ UDPEchoClient1.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


The first line identifies all the dependencies  that the target has.  
Note that the Makefile also supports makedepend (discussed shortly) which serves
a similar purpose.  If the UDPEchoClient1.c file is modified, a 'make' will see that
the client1:  target depends on all the targets in the first line. Each of which is executed
and then the second line executes.  The idea is that all object files that are listed 
end up invoking the  following  compililation target:

.c.o:   $(HEADERS)
        $(CC) $(CFLAGS) $(OPTIONS) $<


If you want to change which compiler you are using or linker options, change the 
appropriate variables in Make.defines.


The Makefile has a backup: target.  The purpose is to facilitate creating a package. 
Issuing a 'make backup' will delete the previous package and create a new UDPEcho.tar.gz
package file.

The Makefile has a clean: target.  Issue a 'make clean' to remove all object 
and executable files.  If you issue a 'make', all files are compiled and 
all executables are created.


The Makefile has a target called 'depend:'.  This runs the makedepend utility.  
Makedepend reads each sourcefile in sequence and  parses  it
like  a  C-preprocessor,  processing  all #include, #define,
#undef, #ifdef, #ifndef, #endif, #if and #else directives so
that  it can correctly tell which #include, directives would
be used in a  compilation.   Any  #include,  directives  can
reference  files having other #include directives, and parsing 
will occur in these files as well.

It appends the information dependency information at the bottem
of the Makefile.  DO NOT MODIFY THIS!!!
As an example, one dependency for the UDPEchoClient1.c file are the 
three files listed.  If any of these files are modified, it will cause
UDPEchoClient1.c to be built with the next 'make' command.


UDPEchoClient1.o: UDPEcho.h /usr/include/stdio.h /usr/include/iso/stdio_iso.h


To handle building the package on different operating systems, the following lines
in Make.defines needs to be set correctly.  The Make.defines has a similar set of 
these lines (commented) to build on Linux and freeBSD.
# for SOLARIS
OSFLAG = -DSOLARIS
#LIBS =
LINKFLAGS = -lsocket -lnsl

Any code that is platform dependent must be surrounded by
the correct #defines:

#ifdef SOLARIS
....
#endif


