#!/bin/bash

echo "===| CPSC 360: Testing Case Summary for HW #2 |==="
echo "Test 0: Compiling"
echo "Test 1: Simple DNS query with single answer"
echo "Test 2: TTL"
echo "Test 3: Complicated DNS query with multiple answers"
echo "Test 4: Timeout"
echo "Test 5: Retries (Your program MUST support port number 5300)"
echo -e "Test 6: Code style and readability\n"


echo -e "Below is the detail of the grading for your original submission.\n"
### Test 0: Compiling Test
echo "*** Test 0: Compiling ***"
killall -9 -q ruby &> /dev/null
tar xzf *-hw2.tar.gz &> /dev/null
make clean &> /dev/null
make
if [ -e dnsq ]; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Compiling score (10 points max): 10.0 <===\n\n\n"
  P0=10
else 
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "(Can not find the execution file ./dnsq)\n"
  echo -e "===> Test 0 score (10 points max): 0.0 <===\n\n\n"
  P0=0
fi
  

### Test 1: Simple DNS query (single answer)
echo "*** Test 1: Simple DNS query with single answer ***"
CSIP=`./dnsq @130.127.255.250 www.cs.clemson.edu | sed '/^$/d' | tail -n 1 | awk '{print $2}' & sleep 2; killall -q -9 dnsq &> /dev/null` 
GRADIP=`./dnsq @130.127.255.250 www.grad.clemson.edu | sed '/^$/d' | tail -n 1 | awk '{print $2}' & sleep 2; killall -q -9 dnsq &> /dev/null` 
rm -f /dev/shm/${USER}/RevPass &> /dev/null
/home/pxuan/software/ruby/bin/ruby ./testserver.rb & sleep 1
LOCALTTL=`./dnsq -p 5300 @127.0.0.1 www.grad.clemson.edu | sed '/^$/d' | tail -n 1 | awk '{print $3}' & sleep 2; killall -q -9 dnsq &> /dev/null`
killall -9 -q ruby &> /dev/null
if [ "$CSIP" = "130.127.201.228" ] && [ "$GRADIP" = "130.127.235.49" ]; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Test 1 score (40 points max): 40.0 <===\n\n\n"
  P1=40
elif [ -e /dev/shm/${USER}/RevPass ]; then
  echo -e "DEBUGGER: Test Result -> (only request is correct) Partially Passed.\n"
  echo -e "===> Test 1 score (40 points max): 20.0 <===\n\n\n"
  P1=20
else
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "===> Test 1 score (40 points max): 0.0 <===\n\n\n"
  P1=0
fi
rm -f /dev/shm/${USER}/RevPass &> /dev/null



### Note: you must manually test and adjust current current TTL for cs.clemson.eddu running this program
### Test 2: TTL
echo "*** Test 2: TTL ***"
/home/pxuan/software/ruby/bin/ruby ./testserver.rb & sleep 1
LOCALTTL=`./dnsq -p 5300 @127.0.0.1 www.grad.clemson.edu 2>&1 | grep 115 | wc -l & sleep 2; killall -q -9 dnsq &> /dev/null`
killall -9 -q ruby &> /dev/null
CSTTL=`./dnsq @130.127.255.250 www.cs.clemson.edu 2>&1 | grep 3600 | wc -l & sleep 2; killall -q -9 dnsq &> /dev/null` 

if [ $LOCALTTL -eq 0 ] && [ $CSTTL -eq 0 ]; then 
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "===> Test 2 score (10 points max): 0.0 <===\n\n\n"
  P2=0
elif [ $LOCALTTL -ge 1 ] && [ $CSTTL -ge 1 ]; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Test 2 score (10 points max): 10.0 <===\n\n\n"
  P2=10
else
  echo -e "DEBUGGER: Test Result -> Partially Passed.\n"
  echo -e "===> Test 2 score (10 points max): 5.0 <===\n\n\n"
  P2=5
fi
rm -f /dev/shm/${USER}/RevPass &> /dev/null


### Note: you must manually test and adjust current IP number for Google and eBay before running this program
### Test 3: Complicated DNS query (multiple answers) 
echo "*** Test 3: Complicated DNS query with multiple answers ***"
GOOGIPS=`./dnsq @8.8.8.8 www.google.com | grep IP -c & sleep 2; killall -q -9 dnsq &> /dev/null`
TWITTERIPS=`./dnsq @130.127.255.250 www.twitter.com | grep IP -c & sleep 2; killall -q -9 dnsq &> /dev/null`
if [ $GOOGIPS -lt 6 ] && [ $TWITTERIPS -lt 4 ] ; then
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "===> Test 3 score (10 points max): 0.0 <===\n\n\n"
  P3=0
elif [ $GOOGIPS -ge 6 ] && [ $TWITTERIPS -ge 4 ] ; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Test 3 score (10 points max): 10.0 <===\n\n\n"
  P3=10
else
  echo -e "DEBUGGER: Test Result -> Partially Passed.\n"
  echo -e "===> Test 3 score (10 points max): 5.0 <===\n\n\n"
  P3=5
fi


### Test 4: Timeout
echo "*** Test 4: Timeout ***"
TIMEOUT=`(time ./dnsq -t 3 -r 1 -p 5300 @127.0.0.1 www.grad.clemson.edu) 2>&1 | grep real | awk -F'm|s' '{print $2}' & sleep 13; killall -q -9 dnsq &> /dev/null`
if [ `expr "$TIMEOUT" '>' 2.0` -eq 1 ] && [ `expr "$TIMEOUT" '<' 7.0` -eq 1 ]; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Test 4 score (10 points max): 10.0 <===\n\n\n"
  P4=10
elif [ `expr "$TIMEOUT" '>' 1.5` -eq 1 ] && [ `expr "$TIMEOUT" '<' 8.5` -eq 1 ]; then
  echo -e "DEBUGGER: Test Result -> Partially Passed.\n"
  echo -e "===> Test 4 score (10 points max): 5.0 <===\n\n\n"
  P4=5
else
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "===> Test 4 score (10 points max): 0.0 <===\n\n\n"
  P4=0
fi


### Test 5: Retries
echo "*** Test 5: Retries (Your program needs to support port number 5300) ***"
/home/pxuan/software/ruby/bin/ruby ./testserver.rb -i 3 & sleep 1
LOCALIP=`./dnsq -t 1 -r 5 -p 5300 @127.0.0.1 www.grad.clemson.edu | sed '/^$/d' |  tail -n 1 | awk '{print $2}' & sleep 8; killall -q -9 dnsq`
killall -9 -q ruby &> /dev/null
if [ "$LOCALIP" = "130.127.235.49" ] || [ "$LOCALIP" = "allvirtual.clemson.edu" ]; then
  echo -e "DEBUGGER: Test Result -> Passed.\n"
  echo -e "===> Test 5 score (10 points max): 10.0 <===\n\n\n"
  P5=10
else
  echo -e "DEBUGGER: Test Result -> Failed!!!\n"
  echo -e "===> Test 5 score (10 points max): 0.0 <===\n\n\n"
  P5=0
fi
rm -f /dev/shm/${USER}/RevPass &> /dev/null
rm -f /dev/shm/${USER} &> /dev/null


### Test 6: Code style and readability
echo "*** Test 6: Code style and readability ***"
echo -e "\n===> Test 6 score (10 points max): 10.0 <==="
P6=10


### Calculate total score 
echo -e "\n\n\n------------------"
echo -e "Total Score: $[$P0+$P1+$P2+$P3+$P4+$P5+$P6]"
echo -e "------------------"
echo -e "Note: the total score displayed in this testing script is only used to measure the basic compatibility and functionality of your implementation, and does not have a direct connection with your final HW#2 grade. A fully passed test does not guarantee your HW#2 will get a full score from our grading system accordingly. In our final test, we'll use different testing values and extra testing cases to further inspect your implementation."
