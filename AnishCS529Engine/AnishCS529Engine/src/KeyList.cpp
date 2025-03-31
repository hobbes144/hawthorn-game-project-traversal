#include "precompiled.h"
#include "KeyList.h"

void KeyList::addKey(int keyID) {
	list.push_back(keyID);
	return;
}

void KeyList::removeKey(int keyID) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == keyID) {
			list.erase(list.begin() + i);
			i--;
		}
	}
	return;
}

void KeyList::clearList(){
	list.clear();
	return;
}

bool KeyList::hasKey(int keyID){
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == keyID) {
			return true;
		}
	}
	return false;
}
