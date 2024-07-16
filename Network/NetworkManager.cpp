#include "NetworkManager.hpp"


NetworkManager::NetworkManager(short int port) {
    this->ip = "";
    this->port = port;
    this->server = false;
    this->maxClients = -1;
    this->id = -1;
}

NetworkManager::~NetworkManager() {
    for (auto& pair : clients) {
        delete pair.second;
    }
    clients.clear();
}

void NetworkManager::startServer() {
    listener.listen(port);
    listener.setBlocking(false);
    selector.add(listener);
    this->server = true;
}

void NetworkManager::stopServer() {
    for (auto& pair : clients) {
        selector.remove(*pair.second);
        pair.second->disconnect();
        delete pair.second;
    }
    clients.clear();
    listener.close();
    selector.remove(listener);
    this->server = false;
}

void NetworkManager::handleNewClients() {
    if(clients.size() < maxClients || maxClients == -1) {
        if(selector.wait(seconds(0.0001))) {
            if(selector.isReady(listener)) {
                int newClientId = generateClientID();
                if(newClientId != -1) {
                    TcpSocket* socket = new TcpSocket();
                    socket->setBlocking(false);

                    listener.accept(*socket);
                    selector.add(*socket);
                    clients[newClientId] = socket;
                    notifyClientConnection(newClientId);

                }
            }
        }
    }
}

int NetworkManager::generateClientID() {
    for(int i = 1; i <= maxClients; i++) {
        if(hasClient(i)) {
            continue;
        }
        return i;
    }

    return -1;
}

unordered_map<string, vector<string>> NetworkManager::readClients() {
    unordered_map<string, vector<string>> allDatas;
    if(selector.wait(seconds(0.0001))) {
        for(auto it = this->clients.begin(); it != this->clients.end(); ) {
            Packet receivePacket;
            int clientId = it->first;
            Socket::Status socketStatus = it->second->receive(receivePacket);

            switch(socketStatus) {
                case Socket::Done: {
                    vector<string> clientDatas;
                    while(!receivePacket.endOfPacket()) {
                        string data;
                        receivePacket >> data;
                        clientDatas.push_back(data);
                    }
                    allDatas[to_string(clientId)] = clientDatas;
                    it++;
                    break;
                }
                case Socket::Disconnected: {
                    vector<string> clientDatas;
                    clientDatas.push_back("DISCONNECTED");
                    allDatas[to_string(clientId)] = clientDatas;

                    TcpSocket* clientSocket = it->second;
                    selector.remove(*clientSocket);
                    clientSocket->disconnect();
                    it = this->clients.erase(it); 
                    delete clientSocket;

                    notifyClientDisconnection(clientId);
                    break;
                }
                default:
                    it++;
                    break;
            }
        }
    }

    return allDatas; 
}

void NetworkManager::sendToClient(int clientId, vector<string> datas) {
    Packet sendPacket;

    for(int i = 0; i < datas.size(); i++) {
        sendPacket << datas[i];
    }

    clients[clientId]->send(sendPacket);
}

void NetworkManager::sendToClients(vector<string> datas) {
    for(const auto& pair : this->clients) {
        Packet sendPacket;

        for(int i = 0; i < datas.size(); i++) {
            sendPacket << datas[i];
        }

        pair.second->send(sendPacket);
    }
}


void NetworkManager::notifyClientConnection(int clientId) {
    //Send successful connection message with data to the client freshly connected
    vector<string> datas;
    datas.push_back("CONNECTION_SUCCEED");
    datas.push_back(to_string(clientId));
    for(const auto& pair : this->clients) {
        datas.push_back(to_string(pair.first));
    }
    sendToClient(clientId, datas);

    //Then send the news of the client being connected to all other clients
    for(const auto& pair : this->clients) {
        vector<string> datas;
        datas.push_back("CLIENT_CONNECTED");
        datas.push_back(to_string(clientId));
        sendToClients(datas);
    }
}

void NetworkManager::notifyClientDisconnection(int clientId) {
    for(const auto& pair : this->clients) {
        vector<string> datas;
        datas.push_back("CLIENT_DISCONNECTED");
        datas.push_back(to_string(clientId));
        sendToClients(datas);
    }
}

bool NetworkManager::connectServer(string ip) {
    socket.setBlocking(true);
    Socket::Status status = socket.connect(ip, port, seconds(10));

    if(status == Socket::Done) {
        socket.setBlocking(false);
        return true;
    }

    return false;
}

void NetworkManager::disconnect() {
    socket.disconnect();
}

vector<string> NetworkManager::readServer() {
    vector<string> serverDatas;
    Packet receivePacket;

    Socket::Status socketStatus = socket.receive(receivePacket);

    switch(socketStatus) {
        case Socket::Done: {
            while(!receivePacket.endOfPacket()) {
                string data;
                receivePacket >> data;
                serverDatas.push_back(data);
            }
            break;
        }
        case Socket::Disconnected:
            serverDatas.push_back("DISCONNECTED");
            disconnect();
            break;
        default:
            break;
    }

    return serverDatas;
}


void NetworkManager::sendToServer(vector<string> datas) {
    Packet sendPacket;

    for(int i = 0; i < datas.size(); i++) {
        sendPacket << datas[i];
    }

    socket.send(sendPacket);
}

string NetworkManager::getIp() {
    return this->ip;
}

short int NetworkManager::getPort() {
    return this->port;
}

bool NetworkManager::isServer() {
    return this->server;
}

unordered_map<int, TcpSocket*> NetworkManager::getClients() {
    return this->clients;
}

bool NetworkManager::hasClient(int clientId) {
    if (clients.find(clientId) != clients.end()) {
            return true;
    } 
    return false;
}

int NetworkManager::getMaxClients() {
    return this->maxClients;
}

int NetworkManager::getId() {
    return this->id;
}

void NetworkManager::setIp(string ip) {
    this->ip = ip;
}

void NetworkManager::setPort(short int port) {
    this->port = port;
}

void NetworkManager::setServer(bool server) {
    this->server = server;
}

void NetworkManager::setClients(unordered_map<int, TcpSocket*> clients) {
    this->clients = clients;
}

void NetworkManager::setMaxClients(int maxClients) {
    this->maxClients = maxClients;
}

void NetworkManager::setId(int id) {
    this->id = id;
}
