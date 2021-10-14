#pragma once
#include "../Common/../Common/fsm/State.h"

class SubwayDriver;
struct Telegram;

class GoOutForDriving : public State<SubwayDriver>
{
private:
	GoOutForDriving() {}
	GoOutForDriving(const GoOutForDriving&);
	GoOutForDriving& operator=(const GoOutForDriving&);
public:
	static GoOutForDriving* Instance();
	virtual void Enter(SubwayDriver* miner);
	virtual void Execute(SubwayDriver* miner);
	virtual void Exit(SubwayDriver* miner);
	virtual bool OnMessage(SubwayDriver* agent, const Telegram& msg);
};

class RestForNextDrive : public State<SubwayDriver>
{
private:
	RestForNextDrive() {}
	RestForNextDrive(const RestForNextDrive&);
	RestForNextDrive& operator=(const RestForNextDrive&);
public:
	static RestForNextDrive* Instance();
	virtual void Enter(SubwayDriver* miner);
	virtual void Execute(SubwayDriver* miner);
	virtual void Exit(SubwayDriver* miner);
	virtual bool OnMessage(SubwayDriver* agent, const Telegram& msg);
};

class GoHomeAndSleepTilRested : public State<SubwayDriver>
{
private:
	GoHomeAndSleepTilRested() {}
	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
	GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);
public:
	static GoHomeAndSleepTilRested* Instance();
	virtual void Enter(SubwayDriver* miner);
	virtual void Execute(SubwayDriver* miner);
	virtual void Exit(SubwayDriver* miner);
	virtual bool OnMessage(SubwayDriver* agent, const Telegram& msg);
};

class EatLunchAtCafeteria : public State<SubwayDriver>
{
private:
	EatLunchAtCafeteria() {}
	EatLunchAtCafeteria(const EatLunchAtCafeteria&);
	EatLunchAtCafeteria& operator=(const EatLunchAtCafeteria&);
public:
	static EatLunchAtCafeteria* Instance();
	virtual void Enter(SubwayDriver* miner);
	virtual void Execute(SubwayDriver* miner);
	virtual void Exit(SubwayDriver* miner);
	virtual bool OnMessage(SubwayDriver* agent, const Telegram& msg);
};

class EatAndDrinkAtHome : public State<SubwayDriver>
{
private:
	EatAndDrinkAtHome() {}
	EatAndDrinkAtHome(const EatAndDrinkAtHome&);
	EatAndDrinkAtHome& operator=(const EatAndDrinkAtHome&);
public:
	static EatAndDrinkAtHome* Instance();
	virtual void Enter(SubwayDriver* miner);
	virtual void Execute(SubwayDriver* miner);
	virtual void Exit(SubwayDriver* miner);
	virtual bool OnMessage(SubwayDriver* agent, const Telegram& msg);
};