#include <Windows.h>

#define	MAX_SIZE	400

int main() {
	DISPLAY_DEVICE displayDevice{ sizeof displayDevice, };
	for (auto i = 0; EnumDisplayDevices(nullptr, i, &displayDevice, EDD_GET_DEVICE_INTERFACE_NAME); i++)
	{
		WCHAR buf[MAX_SIZE]{ };
		wsprintf(buf,
			L"\r\n\
Display #%d\r\n\
Device name: %s\r\n\
Device string: %s\r\n\
Active: %d\r\n\
Mirroring: %d\r\n\
Modes pruned: %d\r\n\
Primary: %d\r\n\
Removable: %d\r\n\
VGA compatible: %d\r\n",
			i,
			displayDevice.DeviceName,
			displayDevice.DeviceString, 
			displayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE,
			displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER,
			displayDevice.StateFlags & DISPLAY_DEVICE_MODESPRUNED,
			displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE,
			displayDevice.StateFlags & DISPLAY_DEVICE_REMOVABLE,
			displayDevice.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE);
		DWORD dwSize{ 0 };
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, lstrlen(buf), &dwSize, nullptr);

		DEVMODE devMode{ {}, {}, {}, sizeof devMode, 0, };
		if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
		{
			wsprintf(buf, L"Position: {%ld, %ld}\r\n", devMode.dmPosition.x, devMode.dmPosition.y);
			dwSize = 0;
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, lstrlen(buf), &dwSize, nullptr);
		}
	}

	return 0;
}
