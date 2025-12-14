#pragma once

// Dependencies | std
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <string>

// Dependencies | in_time_engine
#include "Component.h"

namespace it {
	class ComponentRegistry {
		// Struct
		public:
			struct Entry {
				// Properties
				std::type_index typeIndex{ typeid(nullptr) };
				size_t id{ 0 };
				std::string name{ "nullptr"};
				std::function<Component* ()> constructor{ []() { return nullptr; } };

				// Constructor
				Entry() = default;
				Entry(std::type_index typeIndex, size_t id, std::string&& name, std::function<Component* ()>&& constructor);
			};

		// Object
		private:
			// Properties
			std::vector<Entry> entries{};
			std::unordered_map<std::type_index, size_t> typeIndexToEntryMap{};
			std::unordered_map<size_t, size_t> idToEntryMap{};

		public:
			// Getters
			const std::vector<Entry>& getEntries() const;
			const std::unordered_map<std::type_index, size_t>& getTypeIndexToEntryMap() const;
			const std::unordered_map<size_t, size_t>& getIdToEntryMap() const;
			const Entry* getEntry(std::type_index typeId) const;
			const Entry* getEntry(size_t typeId) const;

			// Functions
			bool add(std::type_index typeIndex, size_t id, std::string&& name, std::function<Component* ()>&& contructor);
			bool add(const Entry& entry);
			bool add(Entry&& entry);
			bool remove(std::type_index typeIndex);
			bool remove(size_t id);
			bool has(std::type_index typeIndex) const;
			bool has(size_t id) const;
			size_t size() const;
			Component* create(const std::type_info& typeInfo);
			Component* create(size_t id);
			template <typename T> T* createAs(const std::type_info& typeInfo) {
				return reinterpret_cast<T*>(create(typeInfo));
			}
			template <typename T> T* createAs(size_t id) {
				return reinterpret_cast<T*>(create(id));
			}
	};
}

/*
#pragma once

// Dependencies | std
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <string>

// Dependencies | in_time_engine
#include "Component.h"

namespace it {
	class ComponentRegistry {
		struct Entry {
			// Properties
			std::type_index typeIndex{ typeid(Component) };
			size_t id{ 0 };
			std::string name{ "nullptr"};
			std::function<Component* ()> constructor{ []() { return nullptr; } };
		};

		struct EntryHasher {
			std::size_t operator()(const Entry& entry) const noexcept {
				return std::hash<std::type_index>{}(entry.typeIndex);
				//std::size_t h1 = std::hash<std::type_index>{}(entry.typeIndex);
				//std::size_t h2 = std::hash<size_t>{}(entry.id);
				//std::size_t h3 = std::hash<std::string>{}(entry.name);

				//// Combine hashes (a simple, common method)
				//std::size_t seed = h1;
				//seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				//seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				//return seed;
			}
		};

		// Object
		private:
			// Properties
			std::unordered_map<std::type_index, std::function<Component* ()>> factory;
			std::unordered_map<size_t, std::function<Component* ()>> idFactory;
			std::unordered_map<std::type_index, size_t> typeToId;

		public:
			// Getters
			const std::unordered_map<std::type_index, std::function<Component* ()>>& getFactory() const;
			const std::unordered_map<size_t, std::function<Component* ()>>& getIdFactory() const;
			const std::unordered_map<std::type_index, size_t>& getTypeToId() const;
			size_t size() const;
			bool corrupted() const;

			// Functions
			bool add(const std::type_info& typeInfo, size_t id, std::function<Component* ()> constructor);
			bool has(const std::type_info& typeInfo);
			bool remove(const std::type_info& typeInfo);
			Component* create(const std::type_info& typeInfo);
			Component* create(size_t id);
			template <typename T> T* createAs(const std::type_info& typeInfo) {
				return reinterpret_cast<T*>(create(typeInfo));
			}
			template <typename T> T* createAs(size_t id) {
				return reinterpret_cast<T*>(create(id));
			}
	};
}

*/
