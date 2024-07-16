//
//  NetworkManager.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef NetworkManager_hpp
#define NetworkManager_hpp

#include <iostream>
#include <unordered_map>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;


class NetworkManager {

    public:
        NetworkManager(short int port);
        ~NetworkManager();

        //Core Server
        void startServer();
        void stopServer();
        void handleNewClients();
        int generateClientID();
        unordered_map<string, vector<string>> readClients();
        void sendToClient(int clientId, vector<string> datas);
        void sendToClients(vector<string> datas);
        void notifyClientConnection(int clientId);
        void notifyClientDisconnection(int clientId);

        //Core Client
        bool connectServer(string ip);
        void disconnect();
        vector<string> readServer();
        void sendToServer(vector<string> datas);
        

        //Getter
        string getIp();
        short int getPort();
        bool isServer();
        unordered_map<int, TcpSocket*> getClients();
        bool hasClient(int clientId);
        int getMaxClients();
        int getId();

        //Setter
        void setIp(string ip);
        void setPort(short int port);
        void setServer(bool server);
        void setClients(unordered_map<int, TcpSocket*> clients);
        void setMaxClients(int maxClients);
        void setId(int id);

    private:
        //Core var
        string ip;
        short int port;
        bool server;

        //Server var
        TcpListener listener;
        SocketSelector selector;
        unordered_map<int, TcpSocket*> clients;
        int maxClients;

        //Client var
        int id;
        TcpSocket socket;

};


#endif