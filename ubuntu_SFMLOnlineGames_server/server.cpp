#include "server.hpp"

void tcpSocket::setfd(){
    fd=this->getHandle();
}

player::player(){
    
    u_Ip=sf::IpAddress::None;
    u_Port=0;
    //status=IDLE;
    inRoom=nullptr;
}
player::~player(){
    this->tSocket.closefd();
}


room::room(player* p){
    number=1024;
    host=p;
    guest=nullptr;
    status=STOP;
    game=NONE;
}
room::~room(){

}

server::server(){
    listener.listen(9527);
    uSocket.bind(9528);//,sf::IpAddress::getLocalAddress()
    uSocket.setBlocking(false);

    maxEvents=1024;
    ev=new epoll_event[maxEvents];

    efd=epoll_create(maxEvents);
}

server::~server(){
    this->listener.close();
    delete []ev;
    this->deleteAllRoom();
    this->deleteAllUser();
    
}

void server::addUser(){
    std::cout<<"addUser"<<std::endl;
    player* p=new player();
    while(1){
        if(this->listener.accept(p->tSocket)==sf::Socket::Done){
            std::cout<<"connected!"<<std::endl;
            p->tSocket.setfd();
            //std::cout<<"new handle: "<<p->tSocket.fd<<std::endl;
            //this->Users.push_back(p);
            this->map_fd_player[p->tSocket.fd]=p;
            p->tSocket.setBlocking(false);

            epoll_event eet;
            eet.data.fd=p->tSocket.fd;
            eet.events=EPOLLIN;
            epoll_ctl(efd,EPOLL_CTL_ADD,p->tSocket.fd,&eet);
            

            p=new player();

        }
    }
}

void server::deleteUser(player* p){
    this->map_fd_player.erase(p->tSocket.fd);
    p->tSocket.closefd();
    //this->Users.erase(p);
    delete p;
}

void server::deleteAllUser(){
    for(auto p:this->map_fd_player){
        delete p.second;
    }
    this->map_fd_player.clear();
}

void server::deleteRoom(room* r){
    if(r->host)
        r->host->inRoom=nullptr;
    if(r->guest)
        r->guest->inRoom=nullptr;
    if(this->map_num_room.count(r->number))
        this->map_num_room.erase(r->number);
    delete r;
}

void server::deleteAllRoom(){
    for(auto p:this->map_num_room){
        p.second->host->inRoom=nullptr;
        if(p.second->guest)
            p.second->guest->inRoom=nullptr;
        delete p.second;
    }
    this->map_num_room.clear();
}

void server::createRoom(player* p,uint32_t g){
    room* rm = new room(p);
    p->inRoom=rm;
    rm->game = (room::gameType)g;
    uint32_t num=0;
    while(this->map_num_room.count(num)){
        ++num;
    }
    this->map_num_room[num]=rm;
    rm->number=num;
    sf::Packet pac;
    pac<<server::SUCCESS<<num;
    p->tSocket.send(pac);
}

void server::join_room(player* p,uint32_t _roomNum){
    sf::Packet pac;
    if(this->map_num_room.count(_roomNum) && p->inRoom==nullptr){
        room &rm=*this->map_num_room[_roomNum];
        if(rm.status==room::roomStatus::STOP && rm.guest==nullptr){
            p->inRoom=&rm;
            rm.guest=p;
            rm.status=room::roomStatus::BEGIN;
            pac.clear();
            pac<<TCP_DATA_TYPE::JOIN_ROOM;
            rm.host->tSocket.send(pac);
            pac.clear();
            pac<<TCP_DATA_TYPE::SUCCESS;
        }
        else{
            pac.clear();
            pac<<TCP_DATA_TYPE::FAIL;
        }
        p->tSocket.send(pac);
    }
    else{
        pac.clear();
        pac<<TCP_DATA_TYPE::ERROR;
        p->tSocket.send(pac);
    }
}

void server::leave_room(player* p){
    sf::Packet pac;
    if(p->inRoom!=nullptr){
        room &rm=*p->inRoom;
        p->inRoom=nullptr;
        rm.status=room::roomStatus::STOP;

        if(rm.host==p){
            if(rm.guest==nullptr){
                deleteRoom(&rm);
            }
            else{
                rm.host=rm.guest;
                rm.guest=nullptr;
                
                pac.clear();
                pac<<TCP_DATA_TYPE::LEAVE_ROOM;
                rm.host->tSocket.send(pac);
            }
        }
        else if(rm.guest == p){
            rm.guest=nullptr;
            
            pac.clear();
            pac<<TCP_DATA_TYPE::LEAVE_ROOM;
            rm.host->tSocket.send(pac);
        }

        
        pac.clear();
        pac<<SUCCESS;
        p->tSocket.send(pac);
    }
    else{
        pac.clear();
        pac<<TCP_DATA_TYPE::ERROR;
        p->tSocket.send(pac);
    }
}

void server::processTcp(){
    std::cout<<"processTcp"<<std::endl;

    //std::cout<<"efd: "<<efd<<std::endl;
    while(1){
        int eNum=epoll_wait(efd,ev,maxEvents,-1);
        std::cout<<"eNum: "<<eNum<<std::endl;

        // if(eNum=-1){
        //     std::cout<<"epoll wait"<<std::endl;
        //     continue;
        // }
        
        for(int i=0;i<eNum;i++){
            sf::Packet pac;
            player &p=*(this->map_fd_player[this->ev[i].data.fd]);
            //player &p=*(this->Users.vec[this->Users.mp[this->map_fd_player[this->ev[i].data.fd]]]);
            sf::Socket::Status st=p.tSocket.receive(pac);
            if(st==sf::Socket::Disconnected){
                if(p.inRoom!=nullptr){
                    leave_room(&p);
                }
                epoll_ctl(efd,EPOLL_CTL_DEL,p.tSocket.fd,nullptr);
                this->deleteUser(this->map_fd_player[p.tSocket.fd]);
                std::cout<<"deleteUser"<<std::endl;
            }
            else if(st==sf::Socket::Done){
                
                uint32_t _type;
                uint32_t _roomNum;
                uint32_t _game;
                pac>>_type;
                switch(_type){
                    case(CREATE_ROOM):
                        pac>>_game;
                        createRoom(&p,_game);

                        std::cout<<"CREATE_ROOM  "+std::to_string(_game)<<std::endl;
                        break;

                    case(LEAVE_ROOM):
                        leave_room(&p);

                        std::cout<<"LEAVE_ROOM"<<std::endl;
                        break;

                    case(SEEK_ROOM):
                        pac.clear();
                        pac<<TCP_DATA_TYPE::SEEK_ROOM_RET;
                        pac<<(uint32_t)map_num_room.size();
                        for(auto it=this->map_num_room.begin();it!=this->map_num_room.end();it++){
                            std::cout<<it->first<<" "<<it->second->game<<" "<<it->second->status<<std::endl;
                            if(it->second->status==room::roomStatus::BEGIN)
                                continue;
                            pac << it->first << it->second->game;
                            
                        }
                        p.tSocket.send(pac);

                        std::cout<<"SEEK_ROOM"<<std::endl;
                        break;

                    case(JOIN_ROOM):
                        pac>>_roomNum;
                        join_room(&p,_roomNum);

                        std::cout<<"JOIN_ROOM"<<std::endl;
                        break;

                    case(OFFLINE):
                        if(p.inRoom!=nullptr)
                            leave_room(&p);
                        deleteUser(&p);

                        std::cout<<"OFFLINE"<<std::endl;
                        break;

                    default:
                        break;
                }
            }
        }
    
    }
    

}

void server::processUdp(){
    std::cout<<"processUdp"<<std::endl;

    sf::Packet pac;
    sf::IpAddress _ip;
    unsigned short _port;
    uint32_t _rnum,_gtype;
    while(1){
        pac.clear();
        if(this->uSocket.receive(pac,_ip,_port)==sf::Socket::Done){
            //std::cout<<_ip.toString()<<std::endl;
            pac>>_rnum;
            if(!this->map_num_room.count(_rnum)){
                continue;
            }
            pac>>_gtype;
            if(!this->map_num_room[_rnum]){
                continue;
            }
            room& rm=*this->map_num_room[_rnum]; 
            if(_gtype!=rm.game||rm.status==room::roomStatus::STOP){
                continue;
            }
            if(rm.host && rm.host->tSocket.getRemoteAddress()==_ip){
                //std::cout<<1<<std::endl;
                
                rm.host->u_Ip=_ip;
                rm.host->u_Port=_port;
                if(rm.guest!=nullptr){
                    _ip=rm.guest->u_Ip;
                    _port=rm.guest->u_Port;
                    this->uSocket.send(pac,_ip,_port);
                }
                
                //this->uSocket.send(pac,rm.host->u_Ip,rm.host->u_Port);
                
            }
            else if(rm.guest && rm.guest->tSocket.getRemoteAddress()==_ip){
                //std::cout<<2<<std::endl;
                rm.guest->u_Ip=_ip;
                rm.guest->u_Port=_port;
                if(rm.host!=nullptr){
                    _ip=rm.host->u_Ip;
                    _port=rm.host->u_Port;
                    this->uSocket.send(pac,_ip,_port);
               }
            }
        }
    }
    
}