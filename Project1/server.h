#ifndef SERVER_H
#define	SERVER_H

#include "stdafx.h"
#include "Gui.h"
class room {
public:
	enum roomstatus
	{ 
		WAITING,
		GAMING 
	}status;
	enum packettype
	{
		SEEK,
		SEEKRET,
		JOIN,
		JOINRET,
		LEAVE,
		GAMEDATA
	};
	enum gametype
	{
		NONE,
		TETRIS,
		MAHJONG
	}gtype;
	


	sf::Packet packet;
	sf::UdpSocket socket;
	sf::IpAddress remote_add;
	sf::IpAddress local_add;
	unsigned short remote_port = 9528;
	const unsigned short local_port = 9527;

	room();
	void run();
};

class Roompage {
public:
	enum gametype
	{
		NONE,
		TETRIS,
		MAHJONG
	};
	std::vector<sf::IpAddress> ips;
	std::set<std::string> ip_flag;
	std::vector<gametype> types;
	Roompage();
	~Roompage();
};
class client {
public:
	enum clientstatus
	{
		IDLE,
		PLAYING
	};
	enum packettype
	{
		SEEK,
		SEEKRET,
		JOIN,
		JOINRET,
		LEAVE,
		GAMEDATA
	};
	enum gametype
	{
		NONE,
		TETRIS,
		MAHJONG
	};

	clientstatus status;
	sf::Packet packet;
	sf::UdpSocket socket;
	sf::IpAddress remote_add;
	sf::IpAddress local_add;
	const unsigned short remote_port = 9527;
	const unsigned short local_port = 9528;

	client();
	~client();
	void serchLAN();
	void sendjoin(sf::IpAddress _ip);
	void sendleave(sf::IpAddress _ip);
	void run(Roompage* roompage = nullptr);
};




class WAN_Roompage {
public:
	enum gametype
	{
		NONE,
		TETRIS,
		MAHJONG
	};
	enum roomStatus {
		STOP,
		BEGIN
	};
	std::vector<uint32_t> rooms;
	std::vector<gametype> types;
	WAN_Roompage();
	~WAN_Roompage();
};
class WAN_client {
public:
	enum clientstatus {
		IDLE,
		WAITING,
		PLAYING,
	}status;
	enum gamgtype
	{
		NONE,
		TETRIS,
		MAHJONG
	};
	enum TCP_DATA_TYPE {
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

	sf::TcpSocket tSocket;
	sf::UdpSocket uSocket;
	sf::IpAddress server_add;
	unsigned short server_port;
	UINT32 roomNumber = 1024;

	bool connect();
	void seek(WAN_Roompage*);
	bool join(uint32_t roomNum);
	void create(uint32_t gameType);
	void leave();
	void offline();
	void run();
	WAN_client();
	~WAN_client();
};

#endif