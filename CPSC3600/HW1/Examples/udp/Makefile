include Make.defines

PROGS =	 client1 server

OPTIONS = -DUNIX  -DUSE_SIGACTION -DANSI


COBJECTS =	DieWithError.o 
CSOURCES =	DieWithError.c 

CPLUSOBJECTS = 

COMMONSOURCES =

CPLUSSOURCES =

all:	${PROGS}


client1:	UDPEchoClient1.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
		${CC} ${LINKOPTIONS}  $@ UDPEchoClient1.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


server:		UDPEchoServer.o $(CPLUSOBJECTS) $(COBJECTS)
		${CC} ${LINKOPTIONS} $@ UDPEchoServer.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


.cc.o:	$(HEADERS)
	$(CPLUS) $(CPLUSFLAGS) $(OPTIONS) $<

.c.o:	$(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) $<



backup:
	rm -f UDPEcho.tar.gz
	tar -cf UDPEcho.tar *
	gzip -f UDPEcho.tar

clean:
		rm -f ${PROGS} ${CLEANFILES}

depend:
		makedepend UDPEchoClient1.c UDPEchoServer.c  $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)
#		mkdep $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)

# DO NOT DELETE

UDPEchoClient1.o: UDPEcho.h /usr/include/stdio.h /usr/include/features.h
UDPEchoClient1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
UDPEchoClient1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
UDPEchoClient1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
UDPEchoClient1.o: /usr/include/libio.h /usr/include/_G_config.h
UDPEchoClient1.o: /usr/include/wchar.h /usr/include/bits/wchar.h
UDPEchoClient1.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
UDPEchoClient1.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
UDPEchoClient1.o: /usr/include/sys/types.h /usr/include/time.h
UDPEchoClient1.o: /usr/include/endian.h /usr/include/bits/endian.h
UDPEchoClient1.o: /usr/include/sys/select.h /usr/include/bits/select.h
UDPEchoClient1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
UDPEchoClient1.o: /usr/include/sys/sysmacros.h
UDPEchoClient1.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
UDPEchoClient1.o: /usr/include/errno.h /usr/include/bits/errno.h
UDPEchoClient1.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
UDPEchoClient1.o: /usr/include/asm-generic/errno.h
UDPEchoClient1.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
UDPEchoClient1.o: /usr/include/netinet/in.h /usr/include/stdint.h
UDPEchoClient1.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
UDPEchoClient1.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
UDPEchoClient1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
UDPEchoClient1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
UDPEchoClient1.o: /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h
UDPEchoClient1.o: /usr/include/bits/byteswap.h /usr/include/arpa/inet.h
UDPEchoClient1.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
UDPEchoClient1.o: /usr/include/bits/netdb.h /usr/include/unistd.h
UDPEchoClient1.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
UDPEchoClient1.o: /usr/include/getopt.h /usr/include/signal.h
UDPEchoClient1.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
UDPEchoClient1.o: /usr/include/bits/sigaction.h
UDPEchoClient1.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
UDPEchoClient1.o: /usr/include/bits/sigthread.h
UDPEchoServer.o: UDPEcho.h /usr/include/stdio.h /usr/include/features.h
UDPEchoServer.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
UDPEchoServer.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
UDPEchoServer.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
UDPEchoServer.o: /usr/include/libio.h /usr/include/_G_config.h
UDPEchoServer.o: /usr/include/wchar.h /usr/include/bits/wchar.h
UDPEchoServer.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
UDPEchoServer.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
UDPEchoServer.o: /usr/include/sys/types.h /usr/include/time.h
UDPEchoServer.o: /usr/include/endian.h /usr/include/bits/endian.h
UDPEchoServer.o: /usr/include/sys/select.h /usr/include/bits/select.h
UDPEchoServer.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
UDPEchoServer.o: /usr/include/sys/sysmacros.h
UDPEchoServer.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
UDPEchoServer.o: /usr/include/errno.h /usr/include/bits/errno.h
UDPEchoServer.o: /usr/include/netinet/in.h /usr/include/stdint.h
UDPEchoServer.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
UDPEchoServer.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
UDPEchoServer.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
UDPEchoServer.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
UDPEchoServer.o: /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h
UDPEchoServer.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
UDPEchoServer.o: /usr/include/arpa/inet.h /usr/include/netdb.h
UDPEchoServer.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
UDPEchoServer.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
UDPEchoServer.o: /usr/include/bits/confname.h /usr/include/getopt.h
DieWithError.o: /usr/include/stdio.h /usr/include/features.h
DieWithError.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
DieWithError.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
DieWithError.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
DieWithError.o: /usr/include/libio.h /usr/include/_G_config.h
DieWithError.o: /usr/include/wchar.h /usr/include/bits/wchar.h
DieWithError.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
DieWithError.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
DieWithError.o: /usr/include/sys/types.h /usr/include/time.h
DieWithError.o: /usr/include/endian.h /usr/include/bits/endian.h
DieWithError.o: /usr/include/sys/select.h /usr/include/bits/select.h
DieWithError.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
DieWithError.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
DieWithError.o: /usr/include/alloca.h
