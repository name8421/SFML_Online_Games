#include "server.h"

room::room() {
	packet.clear();
	
	local_add = sf::IpAddress::getLocalAddress();

	socket.bind(local_port,local_add);
	socket.setBlocking(false);

	status = WAITING;
}

void room::run() {
	sf::IpAddress _ip;
	unsigned short _port;
	sf::Socket::Status status = socket.receive(packet, _ip, _port);

	if (status == sf::Socket::Status::Done) {
		uint32_t _type;
		packet >> _type;
		if (room::status == WAITING) {
			sf::Packet pac;

			switch (_type) {
			case SEEK:
				_type = packettype::SEEKRET;
				pac << _type << (uint32_t)gtype;
				socket.send(pac, _ip, _port);
				std::cout << "send SEEKRET to " << _ip.toString() << ": " << _port << std::endl;
				break;
			case JOIN:
				_type = packettype::JOINRET;
				pac << _type;
				socket.send(pac, _ip, _port);
				room::status = GAMING;
				this->remote_add = _ip;
				this->remote_port = _port;
				std::cout << "send JOINRET to " << _ip <<": " << _port << std::endl;
				break;
			default:
				break;
			}
		}
		else if (room::status == GAMING) {
			switch (_type) {
			case GAMEDATA:
				break;
			case LEAVE:
				room::status = WAITING;
				std::cout << "receive LEAVE from " << _ip.toString() << std::endl;
				break;
			default:
				break;
			}
		}
	}
}





Roompage::Roompage() {
}
Roompage::~Roompage() {
}






client::client() {
	packet.clear();

	remote_add = sf::IpAddress::Any;
	
	local_add = sf::IpAddress::getLocalAddress();

	socket.bind(local_port, local_add);
	socket.setBlocking(false);

	status = IDLE;
}
client::~client() {
	sendleave(this->remote_add);
}

void client::serchLAN() {
	packet.clear();
	packettype _type = SEEK;
	packet << _type;
	sf::IpAddress _ip = sf::IpAddress::Broadcast;
	unsigned short _port = remote_port;
	socket.send(packet, _ip, _port);
	std::cout << "send SEEK to " << _ip << ": " << _port << std::endl;
	//this->status = SEEKING;
}

void client::sendjoin(sf::IpAddress _ip) {
	packettype _type = JOIN;
	sf::Packet pac;
	pac << _type;
	unsigned short _port = remote_port;
	socket.send(pac, _ip, _port);
	std::cout << "send JOIN to " << _ip << ": " << _port << std::endl;
}

void client::sendleave(sf::IpAddress _ip) {
	if (status == PLAYING) {
		sf::Packet pac;
		packettype _type = LEAVE;
		pac << _type;
		sf::IpAddress _ip = remote_add;
		unsigned short _port = remote_port;
		socket.send(pac, _ip, _port);
		std::cout << "send LEAVE to " << _ip << ": " << _port << std::endl;

		status = IDLE;
		remote_add = sf::IpAddress::Any;
	}
}

void client::run(Roompage* roompage) {

	sf::IpAddress _ip;
	unsigned short _port;
	sf::Socket::Status status = socket.receive(packet, _ip, _port);
	if (status == sf::Socket::Status::Done) {
		uint32_t _type;
		packet >> _type;
		if (client::status == IDLE) {
			switch (_type) {
			case SEEKRET:
				std::cout << "receive SEEKRET from " << _ip.toString() << std::endl;
				uint32_t _gtype;
				packet >> _gtype;
				if (roompage && !(roompage->ip_flag.count(_ip.toString()))) {
					roompage->ips.emplace_back(_ip);
					roompage->types.push_back((Roompage::gametype)_gtype);
					roompage->ip_flag.insert(_ip.toString());
				}
					
				break;
			case JOINRET:
				std::cout << "receive JOINRET from " << _ip << std::endl;
				client::status = PLAYING;
				remote_add = _ip;

				break;
			default:
				break;
			}
		}
	}
	
}



WAN_Roompage::WAN_Roompage() {
	
}
WAN_Roompage::~WAN_Roompage() {

}



WAN_client::WAN_client() {
	this->tSocket.setBlocking(true);
	this->uSocket.setBlocking(false);
	std::cout << sf::IpAddress::getLocalAddress().toString() << std::endl;
	//this->uSocket.bind(sf::Socket::AnyPort, sf::IpAddress::getLocalAddress());
	if (this->uSocket.bind(sf::Socket::AnyPort) != sf::Socket::Status::Done) {
		std::cout << "udp socket bind port failed!" << std::endl;
	}
	this->status = clientstatus::IDLE;

}
WAN_client::~WAN_client() {

}
bool WAN_client::connect() {
	std::ifstream ifs("Config/WANserver_addr.ini");
	if (ifs.is_open())
	{
		std::string ipaddr = "";
		unsigned short port = 0;

		if (ifs >> ipaddr >> port)
		{
			this->server_add = sf::IpAddress(ipaddr);
			this->server_port = port;
		}
	}
	sf::Socket::Status status = this->tSocket.connect(this->server_add, 9527, sf::seconds(3));
	if (status != sf::Socket::Status::Done) {
		std::cout << "connect server failed!" << std::endl;
		return false;
	}
	return true;
}

void WAN_client::seek(WAN_Roompage* roompage) {
	sf::Packet pac;
	pac << WAN_client::TCP_DATA_TYPE::SEEK_ROOM;
	if (this->tSocket.send(pac) == sf::Socket::Done) {
		std::cout << "send SEEK_ROOM" << std::endl;
	}
	pac.clear();
	if (this->tSocket.receive(pac) == sf::Socket::Done) {
		uint32_t ptype;
		pac >> ptype;
		if (ptype != TCP_DATA_TYPE::SEEK_ROOM_RET) {
			std::cout << "SEEK_ROOM_RET ERROR" << std::endl;
			return;
		}
		roompage->rooms.clear();
		roompage->types.clear();
		uint32_t size,number,gtype;
		pac >> size;
		for (uint32_t i = 0; i < size; i++) {
			pac >> number >> gtype;
			roompage->rooms.push_back(number);
			////////////
			roompage->types.push_back((WAN_Roompage::gametype)gtype);
			////////////
		}

		std::cout << "recv SEEK_ROOM_RET" << std::endl;
	}
	else {
		std::cout << "SEEK_ROOM no ret" << std::endl;
	}
}

bool WAN_client::join(uint32_t roomNum) {
	sf::Packet pac;
	pac << WAN_client::TCP_DATA_TYPE::JOIN_ROOM << roomNum;
	if (this->tSocket.send(pac) == sf::Socket::Done) {
		std::cout << "send JOIN_ROOM" << std::endl;
	}
	pac.clear();
	if (this->tSocket.receive(pac) == sf::Socket::Done) {
		uint32_t ptype;
		pac >> ptype;
		if (ptype == TCP_DATA_TYPE::SUCCESS) {
			this->status = clientstatus::PLAYING;
			this->tSocket.setBlocking(false);
			this->roomNumber = roomNum;
			std::cout << "JOIN_ROOM SUCCESS" << std::endl;
			return true;
		}
		else if (ptype == TCP_DATA_TYPE::FAIL) {
			this->status = clientstatus::IDLE;
			this->tSocket.setBlocking(true);
			std::cout << "JOIN_ROOM FAIL" << std::endl;
		}
		else {
			this->status = clientstatus::IDLE;
			this->tSocket.setBlocking(true);
			std::cout << "JOIN_ROOM ERROR" << std::endl;
		}
	}
	else {
		std::cout << "JOIN_ROOM no ret" << std::endl;
	}
	return false;
}

void WAN_client::create(uint32_t gameType) {
	sf::Packet pac;
	pac << WAN_client::TCP_DATA_TYPE::CREATE_ROOM << gameType;
	if (this->tSocket.send(pac) == sf::Socket::Done) {
		std::cout << "send CREATE_ROOM" << std::endl;
	}
	pac.clear();
	if (this->tSocket.receive(pac) == sf::Socket::Done) {
		uint32_t ptype;
		pac >> ptype;
		if (ptype == TCP_DATA_TYPE::SUCCESS) {
			pac >> this->roomNumber;
			this->status = clientstatus::WAITING;
			this->tSocket.setBlocking(false);
			std::cout << "CREATE_ROOM SUCCESS" << std::endl;
		}
	}
	else {
		std::cout << "CREATE_ROOM no ret" << std::endl;
	}
}

void WAN_client::leave() {
	this->status = clientstatus::IDLE;
	this->tSocket.setBlocking(true);
	sf::Packet pac;
	pac << WAN_client::TCP_DATA_TYPE::LEAVE_ROOM;
	if (this->tSocket.send(pac) == sf::Socket::Done) {
		std::cout << "send LEAVE_ROOM" << std::endl;
	}
	pac.clear();
	if (this->tSocket.receive(pac) == sf::Socket::Done) {
		uint32_t ptype;
		pac >> ptype;
		if (ptype == TCP_DATA_TYPE::SUCCESS) {
			std::cout << "LEAVE_ROOM SUCCESS" << std::endl;
		}
		else if (ptype == TCP_DATA_TYPE::ERROR) {
			std::cout << "LEAVE_ROOM ERROR" << std::endl;
		}
	}
	else {
		std::cout << "LEAVE_ROOM no ret" << std::endl;
	}
}

void WAN_client::offline() {
	sf::Packet pac;
	pac << TCP_DATA_TYPE::OFFLINE;
	if (this->tSocket.send(pac) == sf::Socket::Done) {
		std::cout << "send OFFLINE" << std::endl;
	}
}

void WAN_client::run() {
	sf::Packet pac;
	if (this->tSocket.receive(pac) == sf::Socket::Done) {
		uint32_t ptype;
		pac >> ptype;
		switch (ptype)
		{
		case JOIN_ROOM:
			std::cout << "recv JOIN_ROOM" << std::endl;
			if (this->status == clientstatus::WAITING) {
				this->status = clientstatus::PLAYING;
			}
			break;
		case LEAVE_ROOM:
			std::cout << "recv LEAVE_ROOM" << std::endl;
			if (this->status == clientstatus::PLAYING) {
				this->status = clientstatus::WAITING;
			}
			break;
		default:
			break;
		}
	}
}