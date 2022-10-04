#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;

int main()
{
	time_point<system_clock> start, end;
	start = system_clock::now(); 
	string beseda1 = "nekaj";
	string beseda2 = "nekaj";
	cout << beseda1.append(beseda2);
	end = system_clock::now(); 

	duration<double> elapsed_seconds = end - start; 
	std::time_t end_time = system_clock::to_time_t(end); 

	std::cout << "finished computation at " << std::ctime(&end_time) 
						<< "elapsed time: " << elapsed_seconds.count() << "s\n"; 
}