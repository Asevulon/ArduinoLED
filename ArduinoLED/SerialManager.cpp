#include "pch.h"
#include "SerialManager.h"
#include <string>
#pragma comment(lib,"OneCore.lib")
using namespace std;

std::vector<CString> SerialManager::GetPortNames()
{
    GetCommPorts(ports, PortsCount, &PortsFound);
	std::vector<CString>res;

	for (int i = 0; i < PortsFound; i++)
	{
		CString str = L"COM";
		str += std::to_string(ports[i]).c_str();
		res.push_back(str);
	}
	res.erase(res.begin());
    return res;
}

void SerialManager::SetPort(CString port)
{
	Port = port;
}

CString SerialManager::GetPort()
{
	return Port;
}

SerialManagerErrors SerialManager::Send(std::string message)
{
	int size = message.size();
	if (size > MaxSize)return ExceedingSize;
	if (size <= 0)return MessageEmpty;

	DataQueueMutex.lock();
	DataQueue.push_back(message);
	DataQueueNotEmpty = true;
	DataQueueMutex.unlock();

	return ok;
}

void SerialManager::DataQueueProc()
{
	while (ContinueProcess)
	{
		if (DataQueueNotEmpty)
		{
			DataQueueMutex.lock();
			string temp = DataQueue.front();
			DataQueue.pop_front();
			DataQueueNotEmpty = !DataQueue.empty();
			DataQueueMutex.unlock();

			DestributeData(temp);
		}
	}
}

void SerialManager::DestributeData(string& source)
{
	if (source.size() <= MaxBufferSize)
	{
		PackageQueueMutex.lock();
		PackageQueue.push_back(source);
		PackageQueueMutex.unlock();
	}

	int packages = source.size() / MaxBufferSize;
	for (int i = 0; i < packages; i++)
	{
		string temp = source.substr(i * MaxBufferSize, MaxBufferSize);

		PackageQueueMutex.lock();
		PackageQueue.push_back(temp);
		PackageQueueMutex.unlock();
	}

	if (source.size() % MaxBufferSize)
	{
		string temp = source.substr(packages * MaxBufferSize, source.size() % MaxBufferSize);
		PackageQueueMutex.lock();
		PackageQueue.push_back(temp);
		PackageQueueMutex.unlock();
	}
}