#ifndef KEY_H
#define KEY_H

#pragma once

#include <memory>
#include <string>

class Key {
public:
	Key(int _id) : id(_id) {}
	~Key();

	int getID() {
		return id;
	}

	bool isMatch(int doorID) {
		if (doorID == id) return true;
		else return false;
	}

private:
	int id;
};

#endif
