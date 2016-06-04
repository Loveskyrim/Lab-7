#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <condition_variable>
void f1();
void f2();



bool ready=0;
std::mutex m;
std::condition_variable cv;


int main(int argc, char* argv[])
{

	std::unique_lock<std::mutex> lock(m);
	std::thread t1(f1);
	//while(!ready){ cv.wait(lock);}
	std::thread t2(f2);
	t1.join();
	t2.join();

	
	system("pause");
	return 0;
}





void f1()
{
	{std::lock_guard<std::mutex> lock(m);}
	for (int i=1; i<=100; i+=2) 
		 {
			std::cout<<i<<' ';
			std::this_thread::sleep_for(std::chrono::milliseconds(100));	
	
	if (i==51) {ready=1; 
	cv.notify_one();}
	}
}

	
	
	void f2()
	{
		{std::lock_guard<std::mutex> lock(m);}
	for (int i=2; i<=100; i+=2) 
		
		{
			std::cout<<i<<' ';
			std::this_thread::sleep_for(std::chrono::milliseconds(100));	
			}
std::cout<<std::endl;
}