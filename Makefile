all: SimpleTcpPerfClient.o SimpleTcpPerfServer.o testClient.o testServer.o testClient  testServer clean

SimpleTcpPerfClient.o: SimpleTcpPerfClient.h SimpleTcpPerfClient.cpp
	g++ -c -o SimpleTcpPerfClient.o SimpleTcpPerfClient.cpp -linet_diag

SimpleTcpPerfServer.o: SimpleTcpPerfServer.h SimpleTcpPerfServer.cpp
	g++ -c -o SimpleTcpPerfServer.o SimpleTcpPerfServer.cpp

testClient.o: testClient.cpp
	g++ -c -o testClient.o testClient.cpp

testServer.o: testServer.cpp
	g++ -c -o testServer.o testServer.cpp

testClient: testClient.o SimpleTcpPerfClient.o
	g++ -o testClient testClient.o SimpleTcpPerfClient.o

testServer: testServer.o SimpleTcpPerfServer.o
	g++ -o testServer testServer.o SimpleTcpPerfServer.o
	
clean:
	rm *.o