struct stRect
{
	int nWidth;
	int nHeight;
};

// �ܼ� ���� �������� ����ִ� ����ü
struct stConsole
{
	HANDLE hConsole;
	stRect rtConsole;
	HANDLE hBuffer[2];
	int nCurBuffer;

	stConsole() : hConsole(nullptr), hBuffer{ nullptr, }, nCurBuffer(0) {}
};

stConsole console;