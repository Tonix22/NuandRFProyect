#include "COM_finder.h"

std::string port_name = "Cypress";

bool get_COM_cypres_port(std::string& COM_number) //added function to find the present serial 
{
    char lpTargetPath[50]; // buffer to store the path of the COMPORTS
	
    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
		COM_number = "COM" + std::to_string(i); // converting to COM0, COM1, COM2
        DWORD test = QueryDosDevice(COM_number.c_str(), lpTargetPath, 50);
		
        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
            std::cout << COM_number << ": " << lpTargetPath << std::endl;
			std::string path_name(lpTargetPath);
			std::size_t found = path_name.find(port_name);
			if (found!=std::string::npos)
			{
				std::cout << "Cypress found" << std::endl;
				return true;
			}
        }

        if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
			return false;
        }
		
		memset(lpTargetPath, 0, sizeof(lpTargetPath));
    }
	return false;
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
