#pragma once
#include "../../Common/fsm/State.h"

class Wife;

class WifesGlobalState : public State<Wife>
{
private:
	WifesGlobalState() {}
	WifesGlobalState(const WifesGlobalState&);
	WifesGlobalState& operator=(const WifesGlobalState&);
public:
	static WifesGlobalState* Instance();
	virtual void Enter(Wife* wife) {}
	virtual void Execute(Wife* wife);
	virtual void Exit(Wife* wife) {}
	virtual bool OnMessage(Wife* wife, const Telegram& msg);
};

class DoHouseWork : public State<Wife>
{
private:
	DoHouseWork() {}
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);
public:
	static DoHouseWork* Instance();
	virtual void Enter(Wife* wife);
	virtual void Execute(Wife* wife);
	virtual void Exit(Wife* wife);
	virtual bool OnMessage(Wife* wife, const Telegram& msg);
};

class ShopAtTheMarket : public State<Wife>
{
private:
	ShopAtTheMarket() {}
	ShopAtTheMarket(const ShopAtTheMarket&);
	ShopAtTheMarket& operator=(const ShopAtTheMarket&);
public:
	static ShopAtTheMarket* Instance();
	virtual void Enter(Wife* wife);
	virtual void Execute(Wife* wife);
	virtual void Exit(Wife* wife);
	virtual bool OnMessage(Wife* wife, const Telegram& msg);
};

class CookMeal : public State<Wife>
{
private:
	CookMeal() {}
	CookMeal(const CookMeal&);
	CookMeal& operator=(const CookMeal&);
public:
	static CookMeal* Instance();
	virtual void Enter(Wife* wife);
	virtual void Execute(Wife* wife);
	virtual void Exit(Wife* wife);
	virtual bool OnMessage(Wife* wife, const Telegram& msg);
};