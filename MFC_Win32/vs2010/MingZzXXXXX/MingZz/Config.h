#pragma once
class CConfig
{
public:
	CConfig(void);
	~CConfig(void);

	UINT GetSound();
	UINT GetMax();
	UINT GetPort();
	void WriteDefaultInfo();
};

