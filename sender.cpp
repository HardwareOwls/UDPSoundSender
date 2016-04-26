#include <stdio.h>
#include <stdlib.h>
//#include <thread> 
#include <time.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Så der ikke skal skrives sdt:: hele tiden
using namespace std;

// Bruges til at gemme serverens IP
int IP1, IP2, IP3, IP4;
char ip1[3], ip2[3], ip3[3], ip4[3];
char SERVER[16];
// Max length of buffer
#define BUFLEN 8
// Porten der sendes på
int PORT;
// Om den fulde IP skal indtastes eller ej
bool fullIP = false;
bool localRecord = false;

int main()
{
	if(fullIP) // Hvis hele IP'en skal tastes ind skal fullIP være true
	{
		// Input den første oktet af IP'en
		cout << "gip IP oktet 1" << endl;
		cin >> IP1;
		sprintf(ip1, "%d", IP1);
		strcat(SERVER, ip1);
		cout << SERVER << endl;
		// Input den anden oktet af IP'en
		cout << "gip IP oktet 2" << endl;
		cin >> IP2;
		sprintf(ip2, "%d", IP2);
		strcat(SERVER, ".");
		strcat(SERVER, ip2);
		cout << SERVER << endl;
		// INput den tredje oktet af IP'en
		cout << "gip IP oktet 3" << endl;
		cin >> IP3;
		sprintf(ip3, "%d", IP3);
		strcat(SERVER, ".");
		strcat(SERVER, ip3);
		cout << SERVER << endl;
	}
	else // Ellers defaulter den til følgende
	{
		strcat(SERVER, "192.168.20");
	}
	// Input den sidste oktet af IPen
	cout << "gip IP oktet 4" << endl;
	cin >> IP4;
	sprintf(ip4, "%d", IP4);
	strcat(SERVER, ".");
	strcat(SERVER, ip4);
	// Skriver IP'en der sendes til ud
	cout << "Der sendes til: " << SERVER << endl;
	// Input den port der skal sendes til
	cout << "gip port" << endl;
	cin >> PORT;

	// Opretter socket-variabel
	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in serv;
	// Opretter forbindelse til serveren
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = inet_addr(SERVER);
	socklen_t m = sizeof(serv);

	// Begynder optagelse på standard-input
	//FILE *handle = popen("arecord -D plughw:1,0 -B 1 -fs16_LE -c1 -r 44100", "r"); //PI 3
	FILE *handle = popen("arecord -B 4 -fs16_LE -c1 -r 44100", "r"); // PI 2
	// Hvis optagelse ikke startede: halt and catch fire
	if (handle == NULL) 
	{
		return 1;
	}

	// Variabler der gemmes i mens der optages
	char buf[BUFLEN];
	size_t readn;
	int i = 0;

	// Lokal kopi af optagelsen
	//FILE * pFile;
	//pFile = fopen ("myfile.wav", "wb");

	// Optager og sender
	while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0)
	{
		// Gemmer lokalt
		//if(localRecord)
		//	fwrite(buf, 1, readn, pFile);
		// Sender til server
		sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&serv,m);
		i++;
	}

	// Afslutter wav-headeren
	//std::cout << "Gemmer fil \n";
	//fclose (pFile);

	// Lukker optagelse på standard-input
	std::cout << "Lukker lyd sampleren \n";
	pclose(handle);

	// Stopper program
	return 0;
}
