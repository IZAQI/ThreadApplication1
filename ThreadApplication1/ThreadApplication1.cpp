// ThreadApplication1.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <thread>

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout << "����ɂ���" << std::endl;

	std::thread thread([](){ ; });

	thread.join(); 

	return 0;
}

