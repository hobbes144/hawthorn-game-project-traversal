#pragma once
#include "Event.h"
// Interface for a explicit EventListener that the compiler can recognize
// Non-templated base interface for listeners
class IEventListener {
public:
    virtual ~IEventListener() = default;
    virtual void HandleEvent(const Event& event) = 0;
};


// Forward declaration - There's a "circular reference with EventManager"
class EventManager;

template<typename T>
class EventListener : public IEventListener {
public:
    // Default constructor
    EventListener() = default;

    // Virtual destructor - We know we will extend this class
    virtual ~EventListener();

    // Register this listener with the event manager
    void RegisterListener();

    // Pure virtual function to be implemented by derived classes
    virtual void OnEvent(const T& event) = 0;

    // Implementation of IEventListener interface
    void HandleEvent(const Event& event) override;
};

#include "EventListener.inl"