#include <iostream>
#include <thread>
#include <future>


void worker(std::promise<int> p ){
	std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work 
	p.set_value(10);  // set the result 
	
}


int main(){

	std::promise <int>p;
	std::future<int> f=p.get_future();
	std::thread t(worker,std::move(p)); // pass promise to the thread 
	
	std::cout<<" waiting for the result ...." <<std::endl;
	int result=f.get();
	std::cout<<" Result is :" <<result<<"\n";

	t.join();

	
	return 0;
}









