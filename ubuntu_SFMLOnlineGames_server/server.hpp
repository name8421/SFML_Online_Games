#include "stdafx.hpp"

class tcpSocket:public sf::TcpSocket{
public:
    int fd=this->getHandle();
    void setfd();
    void closefd(){
        this->close();
    }
};

class room;

class player{
public:
    tcpSocket tSocket;
    sf::IpAddress u_Ip;
    unsigned short u_Port;
    // enum playerStatus{
    //     IDLE,
    //     PLAYING
    // }status;
    room* inRoom;
    player();
    ~player();
};
class room{
public:
    player* host;
    player* guest;
    uint32_t number;
    enum roomStatus{
        STOP,
        BEGIN
    }status;
    enum gameType{
        NONE,
        TETRIS,
        MAHJONG
    }game;
    room(player* p);
    ~room();
};

class server{
public:
    enum TCP_DATA_TYPE{
        ERROR,
        SUCCESS,
        FAIL,
        SEEK_ROOM,
        SEEK_ROOM_RET,
        JOIN_ROOM,
        CREATE_ROOM,
        LEAVE_ROOM,
        OFFLINE
    };
    sf::TcpListener listener;
    sf::UdpSocket uSocket;

    //myvec<player*> Users;
    std::map<int,player*> map_fd_player;

    //myvec<room*> Rooms;
    std::map<uint32_t,room*> map_num_room;
    
    int maxEvents;
    int efd;
    epoll_event* ev;

    server();
    ~server();
    void addUser();
    void deleteUser(player*);
    void deleteAllUser();
    void deleteRoom(room*);
    void deleteAllRoom();
    void createRoom(player*,uint32_t);
    void join_room(player*,uint32_t);
    void leave_room(player*);
    void processTcp();
    void processUdp();
};