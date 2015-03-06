#pragma once

enum class EventType {
    Input,
    Collision,
    Sound
};

enum class InputEventType {
    MouseMove,
    KeyTriggered,
    KeyDown,
    KeyRelease
};


enum class Keys {
    Jump
};

class Event {
public:
    Event(EventType type) : type(type) { };
    EventType type;
};

class InputEvent : public Event {
public:
    InputEventType itype;
    int x, y;
    Keys key;
};