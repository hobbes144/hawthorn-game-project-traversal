#pragma once

#include "Event.h"
#include "GameObject.h"

class CollisionEvent : public Event {
public:
  CollisionEvent(
    std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2, Vector3 pnt)
    : object1(obj1), object2(obj2), point(pnt) {}

  std::shared_ptr<GameObject> object1;
  std::shared_ptr<GameObject> object2;
  Vector3 point;
};