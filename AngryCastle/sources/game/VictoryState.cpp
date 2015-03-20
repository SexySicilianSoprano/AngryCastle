#include "VictoryState.h"

VictoryState::VictoryState(Window *window) :
	window(window),
	slideShowText(new Font("fonts//AveriaSerif-Bold.ttf", 14), Color("white")),
	slide_index(0) {
		// Slide #1
		backgrounds.push_back(new Texture(window, "graphics//ui//credits_slide_1.png"));
		texts.push_back("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
		
		// Slide #2
		backgrounds.push_back(new Texture(window, "graphics//ui//credits_slide_1.png"));
		texts.push_back("Phasellus et dolor at lorem tincidunt sodales non sit amet urna.");
		
		backgrounds.push_back(new Texture(window, "graphics//ui//credits_slide_1.png"));
		texts.push_back("Curabitur vel facilisis diam.");

		slideTimer.start();
}

VictoryState::~VictoryState() {
}

stateStatus VictoryState::update() {
	stateStatus status;
	status.status = STATE_CONTINUE;
	status.prepend = false;

	if(slide_index >= backgrounds.size()-1 && slideTimer.getTicks() > 
	  (SLIDE_TIME * (slide_index+1))) {
		status.status = STATE_MENU;
		return status;

	}

	if (slideTimer.getTicks() > (SLIDE_TIME * (slide_index+1))) {
		slide_index++;
	}

	return status;
}

void VictoryState::render() {
	backgrounds[slide_index]->render(0, 0);
	slideShowText.print(window, texts[slide_index], 60, 150);

}