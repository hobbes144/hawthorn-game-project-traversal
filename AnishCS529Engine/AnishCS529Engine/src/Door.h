#include "CollisionListener.h"
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

private:
	int id;
	DoorType type;
	CollisionListener* doorListener;
};
