#include <iostream>
#include <sstream>
#include <automata/cellular_automata_base.h>

int main(int argc, char* argv[]) {
    std::cout << "Hello World from Automata!" << std::endl;

	int w{100};
	int h{100};
	int n{1000};
	
	if(argc > 1)
	{
		for(int i{ 1 }; i < argc;)
		{
			std::string flag = argv[i]; 
			if(flag == "-s" || flag == "--size")
			{
				std::stringstream convertw{ argv[i + 1] };
				if (!(convertw >> w)) w = 1;

				std::stringstream converth{ argv[i + 2] };
				if (!(converth >> h)) h = 1;

				i += 2;
				std::cout << "cordcord\n";
			}

			else if(flag == "-e" || flag == "--epochs")
			{
				std::stringstream convertn{ argv[i + 1] };
				if (!(convertn >> n)) n = 1;

				i++;
				std::cout << "epoepo\n";
			}

			else i++;
		}
	}
	else
	{
		std::cout << "Using default parameter set.\n";
	}
	
	std::cout << "size: " << w << " x " << h << "\n";
	std::cout << "epochs: " << n << "\n\n";

	CellularAutomataBase ca = CellularAutomataBase(w, h);
	ca.run(n);
	ca.savePNG();
	ca.saveWeirdPNG();

    return 0;
}
