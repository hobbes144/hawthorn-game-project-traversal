#include "CollisionListener.h"
#include "RigidBody.h"

class Door : public RigidBody {
public:
	enum DoorType {
		SLIDEUP,
		NEXTLEVEL,
		DISAPPEAR
	};

	Door(int _id) : id(_id), RigidBody() {}
	~Door() = default;

	void initialize();

private:
	int id;
	CollisionListener* doorListener;
};
