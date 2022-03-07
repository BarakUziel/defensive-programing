#include <iostream>
#include <fstream>
#include <string>
#include <WS2tcpip.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{	
	string actionsList = "MessageU client at your service./n 110) Register /n120) Request for clients list /n130) Request for public key /n140) Request for waiting messages /n150) Send a text message /n151) Send a request for symmetric key /n152) Send your symmetric key /n0) Exit client";
	fstream serverInfo;
	string ipAndPort;
	string ip;
	string port;
	
	serverInfo.open("server.info.txt", ios::in);
	if (serverInfo.is_open()) {
		string delimiter = ":";

		size_t pos = 0;
		std::string token;
		while ((pos = ipAndPort.find(delimiter)) != string::npos) {
			token = ipAndPort.substr(0, pos);
			port += token;
			ipAndPort.erase(0, pos + delimiter.length());
		}
		ip = ipAndPort;

		serverInfo.close();
	}

	fstream myInfo;
	myInfo.open("my.info.txt", ios::in);
	if (myInfo.is_open()) {
		string name;
		string uniqueIdentifier;
		string privateKey;
		getline(myInfo, name);
		getline(myInfo, uniqueIdentifier);
		getline(myInfo, privateKey);
		myInfo.close();
	}

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	do
	{
		// Prompt the user for some text
		cout << actionsList;
		string input;
		cin >> input;

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			doAction(input);
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}

void doAction(string opCode) {
	string userName;
	string text;
	switch (stoi(opCode)) {
	case 110:
		cout << "enter username";
		cin >> userName;
		createUserName(userName);
		break;
	case 120:
		getClientList();
		break;
	case 130:
		getPublicKey();
		break;
	case 140:
		requestWaitingMessages();
		break;
	case 150:
		cout << "enter username";
		cin >> userName;
		cout << "enter text";
		cin >> text;
		sendMessage(userName, text);
		break;
	case 151:
		cout << "enter username";
		cin >> userName;
		getMessageSymetricKey(userName);
		break;
	case 152:
		cout << "enter username";
		cin >> userName;
		getMessageSymetricKey(userName);
		break;
	case 0:
		exitProgram();
		break;
	default:
		cout << "no such action";
	}
}

	

	string createUserName(string userName) {
		server.createUser(userName)
	}

	string getClientList() {
	}

	string getPublicKey() {

	}

	string requestWaitingMessages() {

	}

	string sendMessage(string userName, string text) {

	}

	string getMessageSymetricKey(string userName) {

	}

	string sendMessageSymetricKey(string userName) {



		getMessageSymetricKey(userName);
	}

	void exitProgram() {

	}