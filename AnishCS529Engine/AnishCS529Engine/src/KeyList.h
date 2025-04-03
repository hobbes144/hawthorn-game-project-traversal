#ifndef KEYLIST_H
#define KEYLIST_H

#pragma once

#include "Component.h"
#include <vector>

class KeyList : public Component {
public:
	KeyList() : Component() {}
	~KeyList() = default;

	void addKey(int keyID);
	void removeKey(int keyID);
	void clearList();

	bool hasKey(int keyID);

private:
	std::vector<int> list;
};

#endif
