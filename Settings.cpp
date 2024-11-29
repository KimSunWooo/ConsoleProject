struct stRect
{
	int nWidth;
	int nHeight;
};

// 콘솔 관련 설정값을 들고있는 구조체
struct stConsole
{
	HANDLE hConsole;
	stRect rtConsole;
	HANDLE hBuffer[2];
	int nCurBuffer;

	stConsole() : hConsole(nullptr), hBuffer{ nullptr, }, nCurBuffer(0) {}
};

stConsole console;