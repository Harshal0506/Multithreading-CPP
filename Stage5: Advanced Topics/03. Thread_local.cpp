#include <iostream>
#include <thread>


thread_local int counter=0;


void increment_counter(const std::string & threadName ){
	
	for(int i=0;i<3;++i){

	   ++counter;
	   std::this_thread::sleep_for(std::chrono::seconds(2));
	   std::cout<< threadName<<" Counter being "<< counter <<std::endl;

	}

}


int main(){
	
	std::thread t1(increment_counter,"thread 1");
	std::thread t2(increment_counter,"thread 2");
	t1.join();
	t2.join();

	return 0;
}




