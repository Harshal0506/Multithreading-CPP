#include <iostream>
#include <thread>
#include <mutex> 
#include <condition_variable>
#include <chrono>
std::mutex mutex;
std::condition_variable cv;
bool ready=false;

void waiter(){
	std::unique_lock<std::mutex> lock(mutex);
	std::cout<<" Waiter: waiting for the signal" << std::endl;
	cv.wait(lock,[]{return ready;});
	std::cout<<" Waiter : received signal . Continuing "<<std::endl;

}




void notifier(){

		std::this_thread::sleep_for(std::chrono::seconds(5));
		{	
			std::lock_guard<std::mutex> lock(mutex);
			ready=true;
			std::cout<<" Notifying the waiter "<<std::endl;
			

		}
		cv.notify_one();

}


int main(){

	std::thread t1(waiter);
	std::thread t2(notifier);
	t1.join();
	t2.join();
	return 0;
}


