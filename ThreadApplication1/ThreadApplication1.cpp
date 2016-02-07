// ThreadApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <thread>

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout << "こんにちは" << std::endl;

	std::thread thread([](){ ; });

	thread.join(); 

	return 0;
}

