#include "shutdown.h"

ShutDown::ShutDown(std::string target) : target(target) // target��ʽ mm:ss
{
	exec();
}

void ShutDown::getCurTime()
{
	time_t timep;

	time(&timep);
	localtime_s(&p, &timep);
}

void ShutDown::exec()
{
	getCurTime();
	if (!(getMon() < 9 && getMon() >= 4))
	{
		if (getWday() == 4 || getWday() == 5)
		{

		}
		else
		{
			std::string str = "shutdown -s -f -t ";
			std::string targStr = std::to_string(computeSec());
			//system((str + targStr).c_str());
			std::ofstream batFile("test.bat");
			if (batFile.is_open()) {
				batFile << "@echo off\n";
				batFile << "echo The system will be shut down at 23:47.\n";
				batFile << "echo " + targStr + "\n";
				batFile << str + targStr + "\n";
				batFile << "timeout /t 3 \n";
				batFile << "exit\n";
				batFile.close();
			}
			else {
				std::cerr << "Error opening file for writing." << std::endl;
			}
			system("test.bat");
		}
	}
}

int ShutDown::getWday()
{
	return p.tm_wday;
}

int ShutDown::getMon()
{
	return p.tm_mon;
}

int ShutDown::computeSec()
{
	std::vector<std::string> parts;
	int pos = 0;
	int found;

	while ((found = target.find(':', pos)) != std::string::npos)
	{
		parts.push_back(target.substr(pos, found - pos));
		pos = found + 1;
	}
	parts.push_back(target.substr(pos));

	int sum = -p.tm_sec + 1;
	sum += (std::stoi(parts[0]) - p.tm_hour) * 3600;
	sum += (std::stoi(parts[1]) - p.tm_min) * 60;
	return sum > 0 ? sum : 0;
}


//���õ�ǰ���򿪻�����
void AutoPowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1���ҵ�ϵͳ��������  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///��������       
	{
		//2���õ������������ȫ·��
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);


		//3���ж�ע������Ƿ��Ѿ�����
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, TEXT("AutoShutdown"), RRF_RT_REG_SZ, 0, strDir, &nLength);


		//4���Ѿ�����
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5�����һ����Key,������ֵ��"GISRestart"��Ӧ�ó������֣����Ӻ�׺.exe�� 
			RegSetValueEx(hKey, TEXT("AutoShutdown"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1) * sizeof(TCHAR));


			//6���ر�ע���
			RegCloseKey(hKey);
		}
	}
}


//ȡ����ǰ���򿪻�����
void CanclePowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1���ҵ�ϵͳ��������  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		//2��ɾ��ֵ
		RegDeleteValue(hKey, TEXT("AutoShutdown"));


		//3���ر�ע���
		RegCloseKey(hKey);
	}
}
