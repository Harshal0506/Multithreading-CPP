#include <iostream>
#include <thread>
#include <vector>


// Note cout is not synchronized , If you want to synchronize access to std::cout, we can use a std::mutex (coming up in later questions).
void PrintNumber(int num){
	std::cout<<"Thread "<<std::this_thread::get_id()<<" is printing number :"<<num<<std::endl;
}

int main(){
	std::vector<std::thread> threads;
	// create 10 threads 
	
	for(int i=1;i<=10;i++){
		threads.emplace_back(PrintNumber,i);
	}
        


	// join all threads 
	for(int i=1;i<=10;i++){
		threads[i-1].join();
	}

	std::cout<<" All threads have finished "<<std::endl;



	return 0;
}


