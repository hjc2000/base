#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <string>

int main()
{
	double a = std::pow(2, 1.0 / 12);
	std::cout << "a = " << a << std::endl;

	std::string names[] = {
		"C",
		"C#",
		"D",
		"D#",
		"E",
		"F",
		"F#",
		"G",
		"G#",
		"A",
		"A#",
		"B",
	};

	for (int i = 0; i < 7 * 12; i++)
	{
		std::string name = names[i % 12] + std::to_string(i / 12 + 1);
		double f = 440.0 * std::pow(a, i - 45);
		std::cout << name << "\t --> \t" << f << std::endl;
	}
}
