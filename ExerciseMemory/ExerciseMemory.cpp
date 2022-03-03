// ExerciseMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <chrono>
#include <iostream>
	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};


class GameObject3D
{
public:
	Transform transform;
	int ID{1};
};

class GameObject3DAlt
{
public:
	Transform* transform{};
	int ID{ 1 };
};

std::array<GameObject3D, 1000000> objectArray{};
std::array<GameObject3DAlt, 1000000> objectAltArray{};
std::array<int, 1000000> intArray{};

void TimingWithSampleSize(int sampleSize);

int main()
{
	int stepSize = 1;
	std::cout << "int array\nstep\ttime\tcounter\t\n";
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		int counter{};
		auto lastTime = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < intArray.size(); i += stepSize)
		{
			intArray[i] *= 2;
			++counter;
		}
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();

		std::cout << stepSize << ";\t" << timeDiff << ";\t" << counter << "\n";
	}
    
	std::cout << "\n\n=========================================\n";
	std::cout << "GameObject array\nstep\ttime\tcounter\t\n";
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		int counter{};
		auto lastTime = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < objectArray.size(); i += stepSize)
		{
			objectArray[i].ID *= 2;
			++counter;
		}
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();

		std::cout << stepSize << ";\t" << timeDiff << ";\t" << counter << "\n";
	}


	std::cout << "\n\n=========================================\n";
	std::cout << "GameObjectAlt array\nstep\ttime\tcounter\t\n";
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		int counter{};
		auto lastTime = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < objectAltArray.size(); i += stepSize)
		{
			objectAltArray[i].ID *= 2;
			++counter;
		}
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();

		std::cout << stepSize << ";\t" << timeDiff << ";\t" << counter << "\n";
	}

	std::cout << "\n\n=========================================\n";
	TimingWithSampleSize(10);
}


//The function that we talked about on discord, this was experimental
void TimingWithSampleSize(int sampleSize)
{
	int stepSize = 1;
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		int counter{};
		long long avgTime{  };
		for (int sampleNr = 0; sampleNr < sampleSize; ++sampleNr)
		{
			auto lastTime = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < intArray.size(); i += stepSize)
			{
				intArray[i] *= 2;
				++counter;
			}
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const auto timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
			std::cout << sampleNr << " " << timeDiff << "\n";
			avgTime += timeDiff;
		}
		avgTime /= sampleSize;
		std::cout << "avg: " << avgTime << "\n\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
