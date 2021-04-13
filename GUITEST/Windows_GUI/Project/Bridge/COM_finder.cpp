#include "COM_finder.h"


void get_COM_list(std::vector<std::string>& vect)
{
	std::string port;
	HANDLE hSerial;
	for(int i=1;i<50;i++)
	{
		port.clear();
		port="\\\\.\\COM"+std::to_string(i);
		const TCHAR* COM = port.c_str();
		hSerial = CreateFile(COM,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
		if(hSerial==INVALID_HANDLE_VALUE)
        {
            if(GetLastError()==ERROR_FILE_NOT_FOUND)
            {
                //std::cout << "spde" << std::endl;
            }
        }else
		{
			//std::cout << "Found COM: " << i << std::endl;
			vect.push_back(port.substr(4));
			CloseHandle(hSerial);
		}
	}
}
/*
int main(void)
{
	vector<string> vect;
	get_COM_list(vect);
	for(auto it=vect.begin();it!=vect.end();it++)
	{
		std::cout << "Found " << *it << std::endl;
	}
    return 0;
}
*/