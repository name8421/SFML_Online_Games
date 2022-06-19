#ifndef SUBMENUSTATE_SINGLE_H
#define SUBMENUSTATE_SINGLE_H

#include "MenuState.h"
#include "server.h"

class SubmenuState_single :public MenuState {
protected:

	//Functions
	
	virtual void initGui() ;
	

public:
	SubmenuState_single(StateData* state_data);
	virtual ~SubmenuState_single() {};

	//Functions
	
	virtual void updateButtons() ;
	
};


class LAN_SubmenuState_1 :public MenuState {
protected:

	//Functions

	virtual void initGui();


public:
	LAN_SubmenuState_1(StateData* state_data);
	//LAN_SubmenuState_1(int a, StateData* state_data);
	virtual ~LAN_SubmenuState_1() {};

	//Functions

	virtual void updateButtons();

};

class LAN_SubmenuState_2 :public MenuState {
protected:

	//Functions

	virtual void initGui();


public:
	LAN_SubmenuState_2(StateData* state_data);
	//LAN_SubmenuState_2(int a, StateData* state_data);
	virtual ~LAN_SubmenuState_2() {};

	//Functions

	virtual void updateButtons();

};



class SeekingState :public MenuState {
protected:
	sf::Text text;
	enum gametype
	{
		NONE,
		TETRIS
	};
	virtual void initGui();
	void renderText();
public:
	client* guest;
	Roompage* rooms;
	std::vector<std::string> btnName;
	std::vector<int> btnRoom;
	SeekingState(StateData* state_data);
	virtual ~SeekingState();
	virtual void update(const float& dt);
	virtual void updateButtons();
	virtual void render(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget& target);
	void clearRooms();
};





class WAN_SubmenuState_1 :public LAN_SubmenuState_1 {
public:
	WAN_client* client;

	WAN_SubmenuState_1(StateData* state_data, WAN_client*);
	virtual ~WAN_SubmenuState_1();

	//Functions

	virtual void updateButtons();

};

class WAN_SubmenuState_2 :public LAN_SubmenuState_2 {
public:
	WAN_client* client;
	WAN_SubmenuState_2(StateData* state_data, WAN_client*);
	virtual ~WAN_SubmenuState_2() {};

	//Functions

	virtual void updateButtons();

};

class WAN_SeekingState :public MenuState {
protected:
	sf::Text text;
	enum gametype
	{
		NONE,
		TETRIS,
		MAHJONG
	};
	virtual void initGui();
	void renderText();
public:
	WAN_client* client;
	WAN_Roompage* rooms;
	std::vector<std::string> btnName;
	std::vector<int> btnRnum;
	std::vector<uint32_t> btnRtype;
	WAN_SeekingState(StateData* state_data, WAN_client* client);
	virtual ~WAN_SeekingState();
	virtual void update(const float& dt);
	virtual void updateButtons();
	virtual void render(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget& target);
	void clearRooms();

	std::string enum_to_string(uint32_t);
};




#endif
