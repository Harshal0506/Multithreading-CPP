#include <iostream>
#include <thread>
#include <vector>
//  Counter being 97040 Expected being 100000
int counter=0;


void incrementCounter(int times ){
	for(int i=0;i<times;i++){
		counter++;
	}
	
}

int main(){
	int numOfThreads=10;
	int countPerThread=10000;

	std::vector<std::thread> threads;
	for(int i=0;i<numOfThreads;i++){
		threads.emplace_back(incrementCounter,countPerThread);
	}
	for(int i=0;i<numOfThreads;i++){
		threads[i].join();
	}

	std::cout<<" Counter being "<< counter<<" Expected being "<<numOfThreads*countPerThread<<std::endl;
	return 0;
}

