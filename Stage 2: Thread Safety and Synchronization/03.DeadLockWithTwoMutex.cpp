#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


std::mutex mutex1;
std::mutex mutex2;

void threadA(){
	std::lock_guard<std::mutex> lock1(mutex1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate  work
	std::cout<<" Thread A trying to lock mutex2 "<<std::endl;
	std::lock_guard<std::mutex> lock2(mutex2);
	std::cout<<"Thread A acquired both the lock"<<std::endl;
	
	

}

void threadB(){
	std::lock_guard<std::mutex> lock1(mutex2);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate  work
        std::cout<<" Thread B trying to lock mutex1 "<<std::endl;
        std::lock_guard<std::mutex> lock2(mutex1);
        std::cout<<"Thread B acquired both the lock"<<std::endl;


}



int main(){

	std::thread t1(threadA);
	std::thread t2(threadB);

	t1.join();
	t2.join();

	return 0;
}
