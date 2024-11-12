#pragma once

// Base Event class that all specific events will inherit from
class Event {
public:
    virtual ~Event() = default;
};