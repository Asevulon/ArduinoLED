#pragma once
#include<vector>
#include<mutex>
#include<deque>
#include<thread>
enum SerialManagerErrors
{
	//нет ошибки
	ok = 0,
	//превышение максимального размера буффера
	ExceedingSize,
	MessageEmpty
};


class SerialManager
{
private:
	CString Port;
	std::deque<std::string> DataQueue;
	std::deque<std::string> PackageQueue;

	ULONG ports[255];
	ULONG PortsCount = 255;
	ULONG PortsFound = 0;

	bool ContinueProcess = true;
	bool DataQueueNotEmpty = false;

	const int MaxSize = 255;
	const int MaxBufferSize = 64;

	std::mutex DataQueueMutex;
	std::mutex PackageQueueMutex;

	std::thread* DataQueueThread;
	std::thread* SenderThread;
protected:
	void DataQueueProc();
	void DestributeData(std::string& source);
public:
	std::vector<CString>GetPortNames();
	void SetPort(CString port);
	CString GetPort();
	SerialManagerErrors Send(std::string);
};

