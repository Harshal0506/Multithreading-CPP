#include <iostream>
#include <thread>

void sayHello(){

   std::cout<<" Hello from the thread "<<std::endl;
}

int main(){

	// create and run a thread 
	std::thread t(sayHello);
	// wait for the thread to finish 
	t.join();
	std::cout<<" Hello from the main thread "<<std::endl;
	


	return 0;
}
