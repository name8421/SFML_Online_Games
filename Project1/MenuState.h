#ifndef MENUSTATE_H
#define MENUSTATE_H


//#include "EditorState.h"
//#include "SettingsState.h"
#include "Gui.h"
#include "State.h"

class MenuState :
	public State
{
protected:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	sf::RectangleShape btnBackground;
	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	virtual void initGui();
	void resetGui();

	friend class SettingsState;

public:
	MenuState(StateData* state_data);
	MenuState(int, StateData* state_date);
	virtual ~MenuState();

	//Functions
	void updateInput(const float& dt);
	virtual void updateButtons();
	virtual void update(const float& dt);
	virtual void renderButtons(sf::RenderTarget& target);
	virtual void render(sf::RenderTarget* target = NULL);
	sf::Font* getFont();
};

#endif
