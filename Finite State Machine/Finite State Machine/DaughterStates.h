#pragma once
#include "../Common/../Common/fsm/State.h"

class Daughter;

class DaughtersGlobalState : public State<Daughter>
{
private:
	DaughtersGlobalState() {}
	DaughtersGlobalState(const DaughtersGlobalState&);
	DaughtersGlobalState& operator=(const DaughtersGlobalState&);
public:
	static DaughtersGlobalState* Instance();
	virtual void Enter(Daughter* wife) {}
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife) {}
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class GoToSchool : public State<Daughter>
{
private:
	GoToSchool() {}
	GoToSchool(const GoToSchool&);
	GoToSchool& operator=(const GoToSchool&);
public:
	static GoToSchool* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class StudyingAtSchool : public State<Daughter>
{
private:
	StudyingAtSchool() {}
	StudyingAtSchool(const StudyingAtSchool&);
	StudyingAtSchool& operator=(const StudyingAtSchool&);
public:
	static StudyingAtSchool* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class EatLunchAtLunchroom : public State<Daughter>
{
private:
	EatLunchAtLunchroom() {}
	EatLunchAtLunchroom(const EatLunchAtLunchroom&);
	EatLunchAtLunchroom& operator=(const EatLunchAtLunchroom&);
public:
	static EatLunchAtLunchroom* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class GoToHome : public State<Daughter>
{
private:
	GoToHome() {}
	GoToHome(const GoToHome&);
	GoToHome& operator=(const GoToHome&);
public:
	static GoToHome* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class DoSomethingAtHome : public State<Daughter>
{
private:
	DoSomethingAtHome() {}
	DoSomethingAtHome(const DoSomethingAtHome&);
	DoSomethingAtHome& operator=(const DoSomethingAtHome&);
public:
	static DoSomethingAtHome* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class EatDinnerAtHome : public State<Daughter>
{
private:
	EatDinnerAtHome() {}
	EatDinnerAtHome(const EatDinnerAtHome&);
	EatDinnerAtHome& operator=(const EatDinnerAtHome&);
public:
	static EatDinnerAtHome* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};

class SleepForNextDay : public State<Daughter>
{
private:
	SleepForNextDay() {}
	SleepForNextDay(const SleepForNextDay&);
	SleepForNextDay& operator=(const SleepForNextDay&);
public:
	static SleepForNextDay* Instance();
	virtual void Enter(Daughter* wife);
	virtual void Execute(Daughter* wife);
	virtual void Exit(Daughter* wife);
	virtual bool OnMessage(Daughter* wife, const Telegram& msg);
};