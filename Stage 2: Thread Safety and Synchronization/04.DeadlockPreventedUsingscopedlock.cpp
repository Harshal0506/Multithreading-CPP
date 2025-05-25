#include <iostream>
#include <thread>
#include <mutex> 

std::mutex mutex1;
std::mutex mutex2;

void threadA(){
	std::scoped_lock lock(mutex1,mutex2);
	std::cout<<"Thread A acquired both the lock"<<std::endl;

}


void threadB(){
	std::scoped_lock lock(mutex1,mutex2);
	std::cout<<"Thread B acquired both the lock"<<std::endl;

}

int main(){
	std::thread t1(threadA);
	std::thread t2(threadB);

	t1.join();
	t2.join();
	return 0;
}
