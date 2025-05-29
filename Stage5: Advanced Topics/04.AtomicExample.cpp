#include <iostream>
#include <thread>
#include <atomic>


std::atomic<int> counter(0); // shared between threads safely 


void increment(){

	for(int i=0;i<1000;i++){
		counter++;
	}
}


int main(){

	std::thread t1(increment);
	std::thread t2(increment);
	t1.join();
	t2.join();
	std::cout<<" Counter: "<< counter << "Expected it to be 2000"<<std::endl;
	return 0;
}


