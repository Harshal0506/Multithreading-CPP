#include <iostream>
#include <thread>
#include <future>
#include <chrono>


void worker(std::promise<int>p){
	std::this_thread::sleep_for(std::chrono::seconds(2));
	p.set_value(42);
}



int main(){
	std::promise<int> p;
	std::future<int> f=p.get_future();
	std::thread t(worker,std::move(p));

	while(f.wait_for(std::chrono::milliseconds(0))!= std::future_status::ready){
		std::cout<<" Doing my own work , also keeping an eye for the promise to be set ...."<<std::endl;
	}

	std::cout<<" Promise is set! Result : "<<f.get() <<std::endl;
	t.join();

       return 0;
}


