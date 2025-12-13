// Dependencies | std
#include <iostream>

// Dependencies | glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Dependencies | glfw

// Functions
template <typename T> void printArray(T* array, size_t size) {
	std::cout << "{ ";
	for (size_t i = 0; i < size; i++) {
		std::cout << array[i];
		if (i + 1 == size)
			std::cout << " }";
		else
			std::cout << ", ";
	}
}

int main(int argc, char* argv[]) {
	std::cout << "Program operating" << std::endl;
	
	glm::vec4 vec4{ 1, 1, 0, 1 };
	printArray<float>((float*)&vec4, 4);
	std::cout << std::endl;

	std::cout << "Program terminating" << std::endl;
}
