// ThreadApplication1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
	std::condition_variable nofityEvent;
	std::mutex mutex;
	//std::lock_guard<std::mutex> lock(mutex);
	//std::unique_lock<std::mutex> uniqeLock(mutex);

	std::wcout << "こんにちは" << std::endl;

	bool notified = false;

	std::vector<std::thread> vector;

	for (int i = 0; i < 5; i++) {
		//std::thread thread([=](std::condition_variable nofityEvent, std::unique_lock<std::mutex> uniqeLock){
		vector.push_back(std::thread ([&](){

			std::unique_lock<std::mutex> uniqeLock(mutex);

			std::wcout << "こんにちは by thread[" << std::this_thread::get_id() << "]" << std::endl;

			//uniqeLock.lock();
			nofityEvent.wait(uniqeLock, [&](){return notified;});
			//nofityEvent.wait(uniqeLock);
			//uniqeLock.lock();
			//uniqeLock.unlock();

			std::wcout << "notify event dispatch.[" << std::this_thread::get_id() << "]" << std::endl;
		}));
	}

	std::thread threadNofity([&nofityEvent, &mutex, &notified](){

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		std::unique_lock<std::mutex> uniqeLock(mutex);

		std::wcout << "notify.[" << std::this_thread::get_id() << "]" << std::endl;
		//uniqeLock.lock();

		notified = true;

		uniqeLock.unlock();

		//nofityEvent.notify_one();	// 1スレッド解除
		nofityEvent.notify_all();	// 全スレッド解除
	});
	threadNofity.detach();

	for (auto &thread : vector) {
		//thread.join();
		thread.detach();
	}
	
	std::wcout << "terminate..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20000));

	return 0;
}

