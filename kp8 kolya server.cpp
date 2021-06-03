#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <ctime>
using namespace std;
int main(int argc, char* argv)
{
    srand(time(0));
    WSAData wsadata;
    WORD Dllversion = MAKEWORD(2, 1);
    if (WSAStartup(Dllversion, &wsadata) != 0) {
        cout << "the libreray hasn't downloaded" << endl;
        exit(-1);
    }
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    int sizeofaddr = sizeof(addr);

    SOCKET SListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(SListen, (SOCKADDR*)&addr, sizeofaddr);
    listen(SListen, SOMAXCONN);//2 ПАРАМЕТР МАКСИМАЛЬНОЕ КОЛИЧЕСТВО ОДНОВРЕМЕННЫХ ЗАПРОСОВ 

    SOCKET NewConnection;
    NewConnection = accept(SListen, (SOCKADDR*)&addr, &sizeofaddr);
    if (NewConnection == 0) {
        cout << "client can not connect" << endl;
        exit(2);
    }
    else {
            cout << "client have connected" << endl;
            char annotation[BUFSIZ];
            char otvet[BUFSIZ];
            char slovo[BUFSIZ];
            char letter[5];
            int n = rand() % 10;//добавить рандом
            map <string, string> words = { {"table", "furniture"},
                                           {"student", "learner"},
                                           {"cucumber", "vegetable"},
                                           {"pineapple","fruit"} ,
                                           {"lamborghini","fast expensive car"} ,
                                           {"chips","junk food"} ,
                                           {"scissors","Chancellery"} ,
                                           {"tabacco","small amount of it can kill a horse"} ,
                                           {"crusader","knight"} ,
                                           {"asshole","swear words"} ,
            };

            map <string, string> ::iterator it;
            it = words.begin();
            advance(it, n);
            strcpy(slovo, (it->first).c_str());
            strcpy(otvet, (it->first).c_str());
            strcpy(annotation, (it->second).c_str());
            send(NewConnection, annotation, sizeof(annotation), NULL);
            for (int i = 0; i < BUFSIZ; i++) {

                if (otvet[i] == '\0') {
                    break;
                }
                otvet[i] = '_';
            }
            send(NewConnection, otvet, sizeof(otvet), NULL);
            while (true) {
                recv(NewConnection, letter, sizeof(letter), NULL);
                for (int i = 0; i < BUFSIZ; i++)
                {

                    if (otvet[i] == '\0' || strcmp(letter, "Stop") == 0)
                        break;
                    if (slovo[i] == letter[0])
                        otvet[i] = letter[0];
                }
                send(NewConnection, otvet, sizeof(otvet), NULL);
            }
        }
    return 0;
}