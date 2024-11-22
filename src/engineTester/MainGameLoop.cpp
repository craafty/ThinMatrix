#include "renderEngine/DisplayManager.h"
#include <iostream>


int main() {
	DisplayManager::createDisplay();
	while (!DisplayManager::isCloseRequested()) {



		DisplayManager::updateDisplay();
	}
	DisplayManager::closeDisplay();
	return 0;
}