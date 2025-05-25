#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


std::mutex mutex1;
std::mutex mutex2;

void threadA(){
	std::lock(mutex1,mutex2);
	std::lock_guard<std::mutex> lock1(mutex1,std::adopt_lock);
	std::lock_guard<std::mutex> lock2(mutex2,std::adopt_lock);
	std::cout<<" ThreadA acquired both mutex"<<std::endl;
}

void threadB(){
	std::lock(mutex1,mutex2);
        std::lock_guard<std::mutex> lock1(mutex1,std::adopt_lock);
        std::lock_guard<std::mutex> lock2(mutex2,std::adopt_lock);
        std::cout<<" ThreadB acquired both mutex"<<std::endl;

}

int main(){
	std::thread t1(threadA);
	std::thread t2(threadB);

	t1.join();
	t2.join();


	return 0;
}


