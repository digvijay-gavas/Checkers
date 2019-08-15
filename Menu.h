class Menu
{
public:
	Menu();
	void moveCursor(int);
	void selected();
	enum {START_SCREEN, MENU_SCREEN, GAME_SCREEN, RULE_SCREEN}; 
private:
	void showGame();
	int screen;
};