#pragma once

// Dependencies | std
#include <list>
#include <utility>

namespace util {
	class IdFactory {
		// Object
		private:
			// Properties
			std::list<std::pair<int, int>> idRangeList = std::list<std::pair<int, int>>();
			int registeredIdsCount = 1;
			int idsAvailableCount = 1;

		public:
			// Constructor / Destructor
			IdFactory();
			IdFactory(int idCount);
			~IdFactory();

			// Getters
			std::list<std::pair<int, int>> getIdRangeList() const;
			int getRegisteredIdsCount() const;
			int getIdsAvailableCount() const;

			// Functions
			bool resize(int idAmount);
			int pop();
			bool has(int id) const;
			bool pop(int id);
			bool push(int id);
	};
}