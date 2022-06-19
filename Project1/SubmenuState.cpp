#include "stdafx.h"
#include "SubmenuState.h"
#include "server.h"
#include "gamecode.h"

///
///SubmenuState_single
///
void SubmenuState_single::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
	{
		throw "ERROR::SUB_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(40.0f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

	//Buttons
	this->buttons["GAME_1"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(30.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Snake", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["GAME_2"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Tetris", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["GAME_3"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(50.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Doodle Jump", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["GAME_4"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Mahjong", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(75.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}




SubmenuState_single::SubmenuState_single(StateData* state_data)
	: MenuState(0,state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}




void SubmenuState_single::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["GAME_1"]->isPressed())
	{
		SNAKE s;
		s.snake();
	}

	if (this->buttons["GAME_2"]->isPressed())
	{
		TETRIS t;
		t.tetris();
	}

	if (this->buttons["GAME_3"]->isPressed())
	{
		DOODLEJUMP d;
		d.doodlejump();
	}

	if (this->buttons["GAME_4"]->isPressed())
	{
		MAHJONG m;
		m.mahjong();
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}
}


///
///LAN_SubmenuState_1
///
void LAN_SubmenuState_1::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(40.0f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

	//Buttons
	this->buttons["CREATE"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(30.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Create", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["JOIN"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Join", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(65.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

LAN_SubmenuState_1::LAN_SubmenuState_1(StateData* state_data)
	: MenuState(0, state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	///////
	this->initGui();
	//////
	this->resetGui();
}


void LAN_SubmenuState_1::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["CREATE"]->isPressed())
	{
		//this->states->push(new GameState(this->stateData));
		this->states->push(new LAN_SubmenuState_2(this->stateData));
	}

	//Settings
	if (this->buttons["JOIN"]->isPressed())
	{
		//this->states->push(new SettingsState(this->stateData));
		//guest.status = client::clientstatus::PLAYING;
		//guest.remote_add = guest.local_add;
		SeekingState* seekstate = new SeekingState(this->stateData);
		seekstate->guest->serchLAN();
		this->states->push(seekstate);
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}
}



///
///LAN_SubmenuState_2    
///
void LAN_SubmenuState_2::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(40.0f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

	//Buttons
	this->buttons["GAME_1"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(30.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Mahjong", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["GAME_2"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Double Tetris", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["GAME_3"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(50.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Mgame3", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(43.6f, vm), gui::p2pY(85.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

LAN_SubmenuState_2::LAN_SubmenuState_2(StateData* state_data)
	: MenuState(0, state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

void LAN_SubmenuState_2::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["GAME_1"]->isPressed())
	{
		MAHJONG_S dm;
		dm.mahjong();
		
	}

	if (this->buttons["GAME_2"]->isPressed())
	{
		
		DTETRIS_S dt;
		dt.tetris();
	}

	if (this->buttons["GAME_3"]->isPressed())
	{
		
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}
}



///
///SeekingState
///
void SeekingState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 2),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(25.0f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));



	//Text
	text.setFont(this->font);
	text.setString("Find the following rooms:");
	text.setCharacterSize(gui::calcCharSize(vm));
	text.setPosition(gui::p2pX(30.0f, vm), gui::p2pY(7.0f,vm));
	text.setFillColor(sf::Color(255, 255, 255, 255));

	//Buttons
	this->buttons["ROOM_1"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(20.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_2"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(28.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_3"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(36.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_4"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(44.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_5"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(52.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_6"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_7"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(68.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "255.255.255.255", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["REFRESH"] = new gui::Button(
		gui::p2pX(45.6f, vm), gui::p2pY(85.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "refresh", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(60.6f, vm), gui::p2pY(85.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	for (int i = 0; i < btnName.size(); i++) {
		if (this->rooms->ips.size() == i)
			break;
		this->btnRoom[i] = i;
		this->buttons[this->btnName[i]]->setText(this->rooms->ips[i].toString());
	}
	
}

SeekingState::SeekingState(StateData* state_data)
	: MenuState(0, state_data)
{
	this->guest = new client;
	this->rooms = new Roompage;

	this->btnName.resize(7);
	this->btnName[0] = "ROOM_1";
	this->btnName[1] = "ROOM_2";
	this->btnName[2] = "ROOM_3";
	this->btnName[3] = "ROOM_4";
	this->btnName[4] = "ROOM_5";
	this->btnName[5] = "ROOM_6";
	this->btnName[6] = "ROOM_7";

	this->btnRoom.resize(7, 0);

	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

SeekingState::~SeekingState() {
	delete this->guest;
	delete this->rooms;
}

void SeekingState::renderText() {
	this->window->draw(text);
}

void SeekingState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->btnBackground);
	target->draw(this->text);
	this->renderButtons(*target);
}

void SeekingState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (int i = 0; i < btnName.size(); i++) {
		if (this->rooms->ips.size() == i)
			break;
		this->btnRoom[i] = i;
		this->buttons[this->btnName[i]]->setText(this->rooms->ips[i].toString());
	}

	for (auto& it : this->buttons)
	{
		if(it.second->getText()!="255.255.255.255")
			it.second->update(this->mousePosWindow);
	}
	/*auto& it = roomlist.front();
	for (auto& r : it->rooms) {
		if (r.getText() != "")
			r.update(this->mousePosWindow);
	}*/
	
	for (int i = 0; i < btnName.size(); i++) {
		if (this->buttons[btnName[i]]->getText() != "255.255.255.255" && this->buttons[btnName[i]]->isPressed()) {
			this->guest->sendjoin(this->rooms->ips[i]);
			uint32_t _gtype = this->rooms->types[this->btnRoom[i]];
			if (_gtype == room::gametype::TETRIS) {
				DTETRIS_C dt;
				dt.tetris(this->guest);
				this->guest->sendleave(this->guest->remote_add);
			}
			else if (_gtype == room::gametype::MAHJONG) {
				MAHJONG_C dm;
				dm.mahjong(this->guest);
				this->guest->sendleave(this->guest->remote_add);
			}
			
			
		}
	}

	

	if (this->buttons["REFRESH"]->isPressed())
	{
		this->clearRooms();
		this->guest->serchLAN();
		sf::sleep(sf::milliseconds(200));
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}

	/*Roompage* roompage = roomlist.front();
	for (auto& r : roompage->rooms)
		if (r.getText() != "255.255.255.255") {
			if (r.isPressed()) {
				this->guest->sendjoin(r.getText());
				DTETRIS_C dt;
				dt.tetris(this->guest);
				this->guest->sendjoinret(this->guest->remote_add);
				break;
			}
		}*/
}

void SeekingState::renderButtons(sf::RenderTarget& target) {
	for (auto& it : this->buttons)
	{
		if(it.second->getText() != "255.255.255.255")
			it.second->render(target);
	}
	/*auto& it = roomlist.front();
		for (auto& r : it->rooms)
			if (r.getText() != "255.255.255.255") {
				r.render(target);
			}*/
			
	
}

void SeekingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->guest->run(this->rooms);
	this->updateButtons();
}

void SeekingState::clearRooms() {
	for (int i = 0; i < btnName.size(); i++) {
		this->buttons[btnName[i]]->setText("255.255.255.255");
	}
	this->rooms->ips.clear();
	this->rooms->types.clear();
	this->rooms->ip_flag.clear();
}



///
///WAN_SeekingState
/// 
std::string WAN_SeekingState::enum_to_string(uint32_t type) {
	if (type == gametype::TETRIS)
		return "TETRIS";
	else if (type == gametype::MAHJONG)
		return "MAHJONG";
	return "";
}

void WAN_SeekingState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 2),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(25.0f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));



	//Text
	text.setFont(this->font);
	text.setString("Find the following rooms:");
	text.setCharacterSize(gui::calcCharSize(vm));
	text.setPosition(gui::p2pX(30.0f, vm), gui::p2pY(7.0f, vm));
	text.setFillColor(sf::Color(255, 255, 255, 255));

	//Buttons
	this->buttons["ROOM_1"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(20.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_2"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(28.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_3"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(36.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_4"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(44.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_5"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(52.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_6"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["ROOM_7"] = new gui::Button(
		gui::p2pX(35.0f, vm), gui::p2pY(68.f, vm),
		gui::p2pX(30.f, vm), gui::p2pY(6.f, vm),
		&this->font, "NONE", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["REFRESH"] = new gui::Button(
		gui::p2pX(45.6f, vm), gui::p2pY(85.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "refresh", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(60.6f, vm), gui::p2pY(85.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	for (int i = 0; i < btnName.size(); i++) {
		if (this->rooms->rooms.size() == i)
			break;
		this->buttons[this->btnName[i]]->setText("ROOM-"+std::to_string(this->rooms->rooms[i])+enum_to_string(this->rooms->types[i]));
		this->btnRnum[i] = this->rooms->rooms[i];
		this->btnRtype[i] = this->rooms->types[i];
	}

}

WAN_SeekingState::WAN_SeekingState(StateData* state_data,WAN_client* client)
	: MenuState(0, state_data)
{
	this->client =client;
	this->rooms = new WAN_Roompage;

	this->btnName.resize(7);
	this->btnName[0] = "ROOM_1";
	this->btnName[1] = "ROOM_2";
	this->btnName[2] = "ROOM_3";
	this->btnName[3] = "ROOM_4";
	this->btnName[4] = "ROOM_5";
	this->btnName[5] = "ROOM_6";
	this->btnName[6] = "ROOM_7";
	this->btnRnum.resize(7);
	this->btnRtype.reserve(7);

	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

WAN_SeekingState::~WAN_SeekingState() {
	delete this->rooms;

}

void WAN_SeekingState::renderText() {
	this->window->draw(text);
}

void WAN_SeekingState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->btnBackground);
	target->draw(this->text);
	this->renderButtons(*target);
}

void WAN_SeekingState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (int i = 0; i < btnName.size(); i++) {
		if (this->rooms->rooms.size() == i)
			break;
		this->buttons[this->btnName[i]]->setText("ROOM-" + std::to_string(this->rooms->rooms[i]) + "   " + enum_to_string(this->rooms->types[i]));
		this->btnRnum[i] = this->rooms->rooms[i];
		this->btnRtype[i] = this->rooms->types[i];
	}

	for (auto& it : this->buttons)
	{
		if (it.second->getText() != "NONE")
			it.second->update(this->mousePosWindow);
	}
	/*auto& it = roomlist.front();
	for (auto& r : it->rooms) {
		if (r.getText() != "")
			r.update(this->mousePosWindow);
	}*/

	for (int i = 0; i < btnName.size(); i++) {
		if (this->buttons[btnName[i]]->getText() != "NONE" && this->buttons[btnName[i]]->isPressed()) {
			if (this->client->join(btnRnum[i])) {
				if (btnRtype[i] == WAN_client::gamgtype::MAHJONG) {
					WAN_MAHJONG wm;
					wm.mahjong(this->client);
					this->client->leave();
				}
				else if (btnRtype[i] == WAN_client::gamgtype::TETRIS) {
					WAN_TETRIS wt;
					wt.tetris(this->client);
					this->client->leave();
				}
				
			}
			
		}
	}

	if (this->buttons["REFRESH"]->isPressed())
	{
		this->clearRooms();
		this->client->seek(this->rooms);
		sf::sleep(sf::milliseconds(200));
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}

	/*Roompage* roompage = roomlist.front();
	for (auto& r : roompage->rooms)
		if (r.getText() != "255.255.255.255") {
			if (r.isPressed()) {
				this->guest->sendjoin(r.getText());
				DTETRIS_C dt;
				dt.tetris(this->guest);
				this->guest->sendjoinret(this->guest->remote_add);
				break;
			}
		}*/
}

void WAN_SeekingState::renderButtons(sf::RenderTarget& target) {
	for (auto& it : this->buttons)
	{
		if (it.second->getText() != "NONE")
			it.second->render(target);
	}
	/*auto& it = roomlist.front();
		for (auto& r : it->rooms)
			if (r.getText() != "255.255.255.255") {
				r.render(target);
			}*/


}

void WAN_SeekingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	if (this->client->status == WAN_client::clientstatus::PLAYING) {
		this->client->run();
	}
	
	this->updateButtons();
}

void WAN_SeekingState::clearRooms() {
	for (int i = 0; i < btnName.size(); i++) {
		this->buttons[btnName[i]]->setText("NONE");
	}
	this->rooms->rooms.clear();
	this->rooms->types.clear();
}


///
///WAN_SubmenuState_1
///
WAN_SubmenuState_1::WAN_SubmenuState_1(StateData* state_data,WAN_client* client)
	: LAN_SubmenuState_1(state_data),client(client)
{}
WAN_SubmenuState_1::~WAN_SubmenuState_1() {
	if (this->client->status != WAN_client::clientstatus::IDLE) {
		this->client->leave();
		this->client->offline();
	}
	delete this->client;
}

void WAN_SubmenuState_1::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["CREATE"]->isPressed())
	{
		this->states->push(new WAN_SubmenuState_2(this->stateData,this->client));
	}

	//Settings
	if (this->buttons["JOIN"]->isPressed())
	{
		WAN_SeekingState* seekstate = new WAN_SeekingState(this->stateData,this->client);
		seekstate->client->seek(seekstate->rooms);
		this->states->push(seekstate);
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}
}


///
///WAN_SubmenuState_2
///
WAN_SubmenuState_2::WAN_SubmenuState_2(StateData* state_data, WAN_client* client)
	: LAN_SubmenuState_2(state_data),client(client)
{}


void WAN_SubmenuState_2::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["GAME_1"]->isPressed())
	{
		this->client->create(WAN_client::gamgtype::MAHJONG);
		WAN_MAHJONG wm;
		wm.mahjong(this->client);
		this->client->leave();

	}

	if (this->buttons["GAME_2"]->isPressed())
	{
		this->client->create(WAN_client::gamgtype::TETRIS);
		WAN_TETRIS dw;
		dw.tetris(this->client);
		this->client->leave();
	}

	if (this->buttons["GAME_3"]->isPressed())
	{
		
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
		//this->states->pop();
	}
}