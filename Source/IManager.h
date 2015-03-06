#pragma once 

class Core;
class Message;

class IManager {
public:
    Core *core;
    IManager(Core *core) : core(core) { };
	virtual ~IManager() {};
	virtual void Init() { };
	virtual void CleanUp() { };
	virtual void Update(double frameTime) { };
};