#include <stdio.h>
#include <thread> 
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

#include <string>

#include <cstdio>
#include <vector>
#include <array>

#include <pthread.h>
#include <assert.h>

//#include <pstream.h>
//#include <iterator>

int result = 0;
int sock = socket(AF_INET, SOCK_DGRAM, 0);
char szIP[100];
sockaddr_storage addrDest = {};

int resolvehelper(const char* hostname, int family, const char* service, sockaddr_storage* pAddr)
{
    int result;
    addrinfo* result_list = NULL;
    addrinfo hints = {};
    hints.ai_family = family;
    hints.ai_socktype = SOCK_DGRAM; // without this flag, getaddrinfo will return 3x the number of addresses (one for each socket type).
    result = getaddrinfo(hostname, service, &hints, &result_list);
    if (result == 0)
    {
        //ASSERT(result_list->ai_addrlen <= sizeof(sockaddr_in));
        memcpy(pAddr, result_list->ai_addr, result_list->ai_addrlen);
        freeaddrinfo(result_list);
    }

    return result;
}

void bindtodimmer()
{
    std::cout << "Hej nu starter bind\n";
    //int result = 0;
    
    //int sock = socket(AF_INET, SOCK_DGRAM, 0);

    //char szIP[100];

    sockaddr_in addrListen = {}; // zero-int, sin_port is 0, which picks a random port for bind.
    addrListen.sin_family = AF_INET;
    result = bind(sock, (sockaddr*)&addrListen, sizeof(addrListen));
    if (result == -1)
    {
       int lasterror = errno;
       std::cout << "bind error: " << lasterror << "\n";
       //exit(1);
    }

    const char* reciverIp = "192.168.20.101";
    //char* reciverIp;
    //std::cout << "ip:" << std::endl;
    //std::cin >> reciverIp;
    
    std::cout << "Lige før resolvehelper\n";
    //sockaddr_storage addrDest = {};
    result = resolvehelper(reciverIp, AF_INET, "11000", &addrDest);
    //std::cout << "resolvehelper virker\n";
    if (result != 0)
    {
       int lasterror = errno;
       std::cout << "resolvehelper error: " << lasterror << "\n";
       //exit(1);
    }
    std::cout << "resolvehelper virker\n";
    //return 0;
}


int udpsendstring(std::string msg)
{
    //const char* msg = "Jane Doe";
    //std::cout << msg << "\n";
    size_t msg_length = msg.length();
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    return 0;

}

int udpsendstringninja(std::string lyd)
{
    const char* msg = lyd.c_str();
    //std::cout << msg << "\n";
    size_t msg_length = sizeof(msg);
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    return 0;

}

int udpsendint(int msg)
{
    //const char* msg = "Jane Doe";
    //std::cout << msg << "\n";
    size_t msg_length = sizeof(msg);
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    return 0;

}

void udpsendchar(char msg)
{
    //const char* msg = "Jane Doe";
    //std::cout << msg << "\n";
    size_t msg_length = sizeof(msg);
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    //return 0;

}

int udpsendchar2000(char msg)
{
    //const char* msg = "Jane Doe";
    //std::cout << msg << "\n";
    size_t msg_length = sizeof(msg);
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    return 0;

}

int udpsendcharstar(char* msg)
{
    //const char* msg = "Jane Doe";
    //std::cout << msg << "\n";
    size_t msg_length = sizeof(msg);
    //std::cout << "lige før det bliver sendt\n";
    result = sendto(sock, &msg, msg_length, 0, (sockaddr*)&addrDest, sizeof(addrDest));

    //std::cout << result << " bytes sent" << std::endl;

    return 0;

}

void funktion1()
{
    char lyd[2001];
    FILE *handle = popen("arecord -f S16_LE -r48000", "r");

    if (handle == NULL) 
    {
            //return 1;
    }

    char buf[128];
    const char* buf3[128];
    size_t readn;
    
    FILE * pFile;
    pFile = fopen ("askeslillediller.wav", "wb");

    const char* buf2;
    int stopper = 0;
    int antal = 0;
    //char lyd[2000];
    //char* lyd;
    //std::cout << "Før loop\n";
    std::string output;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0 && stopper < 20000) 
    {
        //Data der skal printets
        //Størlsen der skal printet
        //Hvor mange der skal printes
        //Output stream
        //fwrite(buf, 1, readn, stdout);
        fwrite(buf, 1, readn, pFile);
        
        //std::cout << "før for\n";
        //output = 0;
        //std::cout << output << "\n";

        //Kort off
        /*
        for (int i = 0; i < 128; i++)
        {
            if (buf[i] != '\0')
            {
                output += buf[i];
                //std::cout << output << "\n";
                //buf[i] = '\0';
                //std::cout << "bufbuf " << buf[i] << "\n";
            }
            else
            {
                //std::cout << "ude\n";
                i = 128;
            }
        }
        */
        //std::cout << "sender til udp\n";
        //std::cout << output << "\n";
        //output += output + buf; //øhhh??
        //std::size_t sz = std::fread(buf, 1, sizeof(buf), handle);
        for(std::size_t n = 0; n < readn; ++n) 
        {
            //std::printf("%d\n", buf[n]);
            std::thread second(udpsendchar,buf[n]);
            //udpsendchar(buf[n]); //WEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            //output += output + buf[n];
            //std::string str(buf);
            //output += str;

            
            
            if (antal == 2000)
            {
                //std::cout << output << "\n";
                //udpsendstringninja(output);
                //output = "";
                //std::cout << "Sender pakker\n";
                //std::printf("%d\n", lyd);
                /*
                for (int i = 0; i <= 2000; ++i) //TEST TEST TEST TEST
                {
                    udpsendchar(lyd[i]);
                }
                */
                //udpsendchar2000(lyd);
                //std::cout << "Har sendt pakker\n";
                //lyd = '\0';
                antal = 0;
            }
            else
            {
                //lyd +=buf[n];
                //buf2 = buf3[n];
                //output.append(buf2);
                //std::printf("%d\n", lyd);
                //lyd[antal] = buf[n];

                antal++;
            }
            
            
        }
        /*
        if (antal == 2000)
        {
            //udpsend(output)
            //output = "";
            std::cout << "Sender pakker\n";
            udpsendchar2000(lyd);
            std::cout << "Har sendt pakker\n";
            antal = 0;
        }
        */

        //Kort off
        //udpsend(output);    //ON
        //output = "";        //ON
        
        //buf = NULL;
        //std::cout << "har sent til udp\n";
        //antal++;
        //udpsendint(stopper);
        stopper++;
    }


    std::cout << "Gemmer fil \n";
    fclose (pFile);

    std::cout << "Lukker lyd sampleren \n";
    pclose(handle);

    //return 0;
}

int funktion2()
{
    /*
    bindtodimmer();
    redi::ipstream proc("arecord -f S16_LE -r48000");
    typedef std::istreambuf_iterator<char> iter;
    std::string output(iter(proc.rdbuf()), iter());
    */
}

int funktion3()
{
char* lyd;
//strcpy(msg,"12/10/12"); //8 bytes
//strcat(msg,"Kevin Fire"); //10 bytes
//strcat(msg,"abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde\r\n\r\n");


//nbytes_sent = send(sock,(char *)msg,sizeof(msg),0);


    FILE *handle = popen("arecord -f S16_LE -r48000", "r");

    if (handle == NULL) 
    {
            return 1;
    }

    char buf[128];
    size_t readn;
    
    FILE * pFile;
    pFile = fopen ("askeslillediller.wav", "wb");


    int stopper = 0;
    int antal = 0;

    std::string output;
    while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0 && stopper < 20000) 
    {
        //Data der skal printets
        //Størlsen der skal printet
        //Hvor mange der skal printes
        //Output stream
        //fwrite(buf, 1, readn, stdout);
        fwrite(buf, 1, readn, pFile);
        
        for(std::size_t n = 0; n < readn; ++n) 
        {
            if (antal == 2000)
            {
                udpsendcharstar(lyd);
                std::cout << "Har sendt pakker\n";
                lyd = '\0';
                antal = 0;
            }
            else
            {
                //læg til output
                strcpy(lyd,buf); 
                antal++;
            }
        }
        stopper++;
    }


    std::cout << "Gemmer fil \n";
    fclose (pFile);

    std::cout << "Lukker lyd sampleren \n";
    pclose(handle);

    return 0;


}

int funktion4()
{
char* msg;
strcpy(msg,"12/10/12"); //8 bytes
strcat(msg,"Kevin Fire"); //10 bytes
strcat(msg,"abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde\r\n\r\n");

udpsendcharstar(msg);

}


int main(void)
{
    int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];
    bindtodimmer();
    std::cout << "Bind lykkes\n";
    funktion1();
    //std::thread first(funktion1); 
    //first.join();                // pauses until first finishes
    std::cout << "Data sendt\n";
    return 0; 
}

