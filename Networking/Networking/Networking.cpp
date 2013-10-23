// Networking.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Network.hpp>
using namespace sf;
int main(int argc, char* argv[])
{
	//declare the UDP socket
	UdpSocket socket;
	socket.setBlocking(false);
	//let the OS pick a random port
	Socket::AnyPort;
	unsigned short portOut = socket.getLocalPort();
	//bind the socket to the port
	if(socket.bind(portOut) != Socket::Done) {
		return -1;
	}
	//declare the input char array and its size
	char keysPressed[] = {0};
	size_t numKeys = strlen(keysPressed);
	//declare an "IpAddress" that actually messages everyone on the network(LAN)
	IpAddress broadcast = IpAddress::Broadcast;
	//declare my curent IpAddress
	IpAddress mine = IpAddress::getLocalAddress();
	//declare the max message size that can be sent
	const size_t max = UdpSocket::MaxDatagramSize - 1;
	//Declare an array of IPs
	IpAddress ips[] = {mine};
	//Get the size of the IP array
	const int numIps = sizeof(ips)/sizeof(mine);
	//Initalize the sender's IP and port
	IpAddress sender;
	unsigned short portIn;

	//LOOP BEGINS

	//if the message is too big
	if(strlen(keysPressed) > max) {
		//allocate a new array for the remainder of the message and send it
		const size_t remain = strlen(keysPressed) - max;
		char *temp = new char[remain];
		for(int i = max; i < remain + max; i++) temp[i] = keysPressed[i];
		if(socket.send(temp,max,broadcast,portOut) != sf::Socket::Done) return -1;
		//truncate the old array
		keysPressed[max] = '\0';
	}
	//Send the keys pressed
	if(socket.send(keysPressed,numKeys,broadcast,portOut) != sf::Socket::Done) {
		return -1;
	}
	
	//Receive keys pressed
	if(socket.receive(keysPressed,max,numKeys,sender,portIn) != Socket::Done) {
		return -1;
	}
	
	//Initalize a char-converted array of the IPs
	char ipsChar[numIps];
	//Convert the IPs to char
	for(int i = 0; i < numIps; i++)
		ipsChar[i] = (char)ips[i].toString().c_str();
	//If the IP array does not contain the sender's IP...
	if(index(ipsChar, numIps, (char*)sender.toString().c_str()) == -1)  {
		//Declare a pointer to the location of ips in memory
		IpAddress *ipsTemp = ips;
		//Declare a temporary int to store the size of ips
		const int x = numIps;
		//Redeclare ips to increment it
		const int numIps = x + 1;
		//Redeclare ips
		IpAddress ips[numIps];
		//Fill ips with ipsTemp
		for(int i = 0; i < numIps; i++)
			//MIGHT BREAK because of redeclaration of ips
			ips[i] = ipsTemp[i];
		ips[numIps-1] = sender;
	}
	return 0;
}
//Determine if the char TERM is in one of the elements of the char array DATA
int index(char data[], unsigned int len, char *term) {
	unsigned int count = 0;
	int index = -1;
	for(int i = 0; i < len; i++) 
		for(int j = 0; j < sizeof(data[i])/sizeof(char); i++) {
			if(data[i] == term[count]) {
				if(count == 0) index = i;
				count++;
			}
			else {
				count = 0;
				index = -1;
			}
	}
	if(count = len) return index;
	else return -1;
}