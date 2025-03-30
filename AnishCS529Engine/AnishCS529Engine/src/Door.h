#include "CollisionListener.h"
#include "KeyList.h"
#include "RigidBody.h"

class Door : public RigidBody {
public:
	enum DoorType {
		SLIDEUP,
		NEXTLEVEL,
		DISAPPEAR
	};

	Door(int _id, DoorType _type) : id(_id), type(_type), RigidBody() {}
	~Door() = default;

	void initialize();

	int getID();
	DoorType getType();

private:
	int id;
	DoorType type;
	CollisionListener* doorListener;
};
