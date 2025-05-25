#include <iostream>
#include <thread>
#include <vector>


void printThreadID(int i){
	std::cout<<"int: "<< i<<" Current thread id is "<< std::this_thread::get_id()<<std::endl;

}
int main(){
	std::vector<std::thread> threads;
	for(int i=0;i<10;i++){

		threads.emplace_back(printThreadID,i);
	}

	for(int i=0;i<10;i++){

		threads[i].join();
	}

	std::cout<<"Ending here "<<std::endl;


	return 0;
}
