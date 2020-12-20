#include "MarkovChain.h"
#include <ctime>
#include <iostream>


int main() {


	srand(time(NULL));

	MarkovChain<char> mark;

	mark.AddState('A');
	mark.AddState('B');
	mark.AddState('C');
	mark.AddState('D');

	mark.AddLink('A', 'A', 50);
	mark.AddLink('A', 'B', 50);

	mark.AddLink('B', 'C', 50);

	mark.AddLink('C', 'A', 90);
	mark.AddLink('C', 'D', 10);

	mark.MarkTerminus('D');

	


	mark.SetAxiom('A');
	while (!mark.HasReachedTerminus())
	{
		std::cout << mark.GetNext() << "->";
	}		
	std::cout << "end" << std::endl;
	return 0;
}