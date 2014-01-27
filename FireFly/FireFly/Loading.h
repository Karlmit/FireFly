#pragma once


class Loading
{
public:
	static Loading &getLoading();
	void loadLevel0();

private:
	Loading();
	~Loading();
	void operator=(const Loading &loading);
	static Loading loading;
};