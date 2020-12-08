#include "KeyboardManager.h"
void KeyboardManager::registerKbListener(KeyboardEventListener * pKbListener)
{
	int index;
	const char * chars = pKbListener->getKbChars();
	size_t numCharToRegister = strlen(chars);
	for (size_t i = 0; i < numCharToRegister; ++i) {
		index = getIndex(chars[i]);
		if (index != -1) {
			kbListeners[index].push_back(pKbListener);
		}
	}
}
void KeyboardManager::handleKeyboard()
{
	if (_kbhit()) {
		char k = _getch();
		int index = getIndex(k);
		if (index != -1) {
			for (auto pKbListener : kbListeners[index]) {
				pKbListener->handleKey(k);
			}
		}
	}
}