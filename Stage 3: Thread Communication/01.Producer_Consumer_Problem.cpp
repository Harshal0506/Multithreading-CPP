#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>



const int MAX_BUFFER_SIZE=5;

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer(int id , int count ){
	for(int i=0;i<count;i++){
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock,[]{return buffer.size() < MAX_BUFFER_SIZE ;} );


		int item=id*100+i;
		buffer.push(item);
		std::cout<<" Producer "<< id <<" produced "<< item <<"\n";
		cv.notify_all(); // notify consumers 

		std::this_thread::sleep_for(std::chrono::milliseconds(100));



	}


}

void consumer( int id , int count ){

	for(int i=0;i<count;i++){
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock,[]{ return !buffer.empty();}); 
		int item=buffer.front();
		buffer.pop();
		std::cout<<" Consumer "<<id <<" consumed: "<<item<<" \n ";
		cv.notify_all(); // notify producers
	        std::this_thread::sleep_for(std::chrono::milliseconds(150));


	}
}


int main(){

	std::thread p1(producer,1,10);
	std::thread p2(producer,2,10);
	std::thread c1(consumer,1,10);
	std::thread c2(consumer,2,10);
	p1.join();
	p2.join();
	c1.join();
	c2.join();

	return 0;
}
