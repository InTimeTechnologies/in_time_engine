#include "ComponentRegistry.h"

// Dependencies | std
#include <cassert>

namespace it {
	// struct ComponentRegistry::Entry

	// Constructor
	ComponentRegistry::Entry::Entry(std::type_index typeIndex, size_t id, std::string&& name, std::function<Component* ()>&& constructor) :
		typeIndex(typeIndex),
		id(id),
		name(std::move(name)),
		constructor(std::move(constructor)) {
	}

	// class ComponentRegistry

	// Object | public

	// Getters
	const std::vector<ComponentRegistry::Entry>& ComponentRegistry::getEntries() const {
		return entries;
	}
	const std::unordered_map<std::type_index, size_t>& ComponentRegistry::getTypeIndexToEntryMap() const {
		return typeIndexToEntryMap;
	}
	const std::unordered_map<size_t, size_t>& ComponentRegistry::getIdToEntryMap() const {
		return idToEntryMap;
	}
	const ComponentRegistry::Entry* ComponentRegistry::getEntry(std::type_index typeIndex) const {
		auto typeIndexToEntryMapIterator = typeIndexToEntryMap.find(typeIndex);
		if (typeIndexToEntryMapIterator == typeIndexToEntryMap.end())
			return nullptr;

		size_t i = typeIndexToEntryMapIterator->second;
		const Entry* entry = &entries[i];
		return entry;
	}
	const ComponentRegistry::Entry* ComponentRegistry::getEntry(size_t id) const {
		auto idToEntryMapIterator = idToEntryMap.find(id);
		if (idToEntryMapIterator == idToEntryMap.end())
			return nullptr;

		size_t i = idToEntryMapIterator->second;
		const Entry* entry = &entries[i];
		return entry;
	}

	// Functions
	bool ComponentRegistry::add(std::type_index typeIndex, size_t id, std::string&& name, std::function<Component* ()>&& constructor) {
		bool entryAlreadyExists = typeIndexToEntryMap.contains(typeIndex) || idToEntryMap.contains(id);
		if (entryAlreadyExists) {
			assert(!entryAlreadyExists && "typeIndex or id already exists in the registry.");
			return false;
		}

		size_t index = entries.size();
		entries.emplace_back(typeIndex, id, std::move(name), std::move(constructor));
		typeIndexToEntryMap[typeIndex] = index;
		idToEntryMap[id] = index;

		return true;
	}
	bool ComponentRegistry::add(const Entry& entry) {
		bool entryAlreadyExists = typeIndexToEntryMap.contains(entry.typeIndex) || idToEntryMap.contains(entry.id);
		if (entryAlreadyExists) {
			assert(!entryAlreadyExists && "entry already exists in the registry.");
			return false;
		}

		size_t index = entries.size();
		typeIndexToEntryMap[entry.typeIndex] = index;
		idToEntryMap[entry.id] = index;
		entries.push_back(entry);

		return true;
	}
	bool ComponentRegistry::add(Entry&& entry) {
		bool entryAlreadyExists = typeIndexToEntryMap.contains(entry.typeIndex) || idToEntryMap.contains(entry.id);
		if (entryAlreadyExists) {
			assert(!entryAlreadyExists && "entry already exists in the registry.");
			return false;
		}

		size_t index = entries.size();
		typeIndexToEntryMap[entry.typeIndex] = index;
		idToEntryMap[entry.id] = index;
		entries.push_back(std::move(entry));

		return true;
	}
	bool ComponentRegistry::remove(std::type_index typeIndex) {
		auto typeIndexToEntryMapIterator = typeIndexToEntryMap.find(typeIndex);
		if (typeIndexToEntryMapIterator == typeIndexToEntryMap.end())
			return false;

		size_t i = typeIndexToEntryMapIterator->second;
		size_t id = entries[i].id;

		idToEntryMap.erase(id);
		typeIndexToEntryMap.erase(typeIndex);

		if (i != entries.size() - 1) {
			std::swap(entries[i], entries.back());
			typeIndexToEntryMap[entries[i].typeIndex] = i;
			idToEntryMap[entries[i].id] = i;
		}

		entries.pop_back();

		return true;
	}
	bool ComponentRegistry::remove(size_t id) {
		auto idToEntryMapIterator = idToEntryMap.find(id);
		if (idToEntryMapIterator == idToEntryMap.end())
			return false;

		size_t i = idToEntryMapIterator->second;
		std::type_index typeIndex = entries[i].typeIndex;

		typeIndexToEntryMap.erase(typeIndex);
		idToEntryMap.erase(idToEntryMapIterator);

		if (i != entries.size() - 1) {
			std::swap(entries[i], entries.back());
			typeIndexToEntryMap[entries[i].typeIndex] = i;
			idToEntryMap[entries[i].id] = i;
		}

		entries.pop_back();

		return true;
	}
	bool ComponentRegistry::has(std::type_index typeIndex) const {
		return typeIndexToEntryMap.contains(typeIndex);
	}
	bool ComponentRegistry::has(size_t id) const {
		return idToEntryMap.contains(id);
	}
	size_t ComponentRegistry::size() const {
		return entries.size();
	}
	Component* ComponentRegistry::create(const std::type_info& typeInfo) {
		auto typeIndexToEntryMapIterator = typeIndexToEntryMap.find(typeInfo);
		if (typeIndexToEntryMapIterator == typeIndexToEntryMap.end())
			return nullptr;

		// i == index used in entries
		size_t i = typeIndexToEntryMapIterator->second;
		return entries[i].constructor();
	}
	Component* ComponentRegistry::create(size_t id) {
		auto idToEntryMapIterator = idToEntryMap.find(id);
		if (idToEntryMapIterator == idToEntryMap.end())
			return nullptr;

		// i == index used in entries
		size_t i = idToEntryMapIterator->second;
		return entries[i].constructor();
	}
}

/*
#include "ComponentRegistry.h"

namespace it {
	// class ComponentRegistry

	// Object | public

	// Getters
	const std::unordered_map<std::type_index, std::function<Component* ()>>& ComponentRegistry::getFactory() const {
		return factory;
	}
	const std::unordered_map<size_t, std::function<Component* ()>>& ComponentRegistry::getIdFactory() const {
		return idFactory;
	}
	const std::unordered_map<std::type_index, size_t>& ComponentRegistry::getTypeToId() const {
		return typeToId;
	}
	size_t ComponentRegistry::size() const {
		return factory.size() == idFactory.size() ? factory.size() : 0;
	}
	bool ComponentRegistry::corrupted() const {
		return factory.size() != idFactory.size() || factory.size() != typeToId.size();
	}

	// Functions
	bool ComponentRegistry::add(const std::type_info& typeInfo, size_t id, std::function<Component* ()> constructor) {
		bool entryNotInFactory = true, entryNotInIdFactory = true, entryNotInTypeToId = true;
		std::type_index typeIndex = std::type_index(typeInfo);
		
		// Search for typeInfo in factory
		auto factoryIterator = factory.find(typeIndex);
		entryNotInFactory = factoryIterator == factory.end();

		// Search for typeInfo in idFactory
		auto idFactoryIterator = idFactory.find(id);
		entryNotInIdFactory = idFactoryIterator == idFactory.end();

		// Search for typeInfo in typeToId
		auto typeToIdIterator = typeToId.find(typeIndex);
		entryNotInTypeToId = typeToIdIterator == typeToId.end();

		// Should add to factory?
		if (entryNotInFactory && entryNotInIdFactory && entryNotInTypeToId) {
			factory[typeIndex] = constructor;
			idFactory[id] = constructor;
			typeToId[typeIndex] = id;
			return true; // Successfully added component entry to both factories
		}

		// typeIndex and/or id exist in either/both factories
		return false;
	}
	bool ComponentRegistry::has(const std::type_info& typeInfo) {
		std::type_index typeIndex = std::type_index(typeInfo);
		auto factoryIterator = factory.find(typeIndex);
		return factoryIterator != factory.end();
	}
	bool ComponentRegistry::remove(const std::type_info& typeInfo) {
		std::type_index typeIndex = std::type_index(typeInfo);

		auto factoryIterator = factory.find(typeIndex);
		if (factoryIterator != factory.end())
			factory.erase(factoryIterator);
		else
			return false;

		size_t id = 0;
		auto typeToIdIterator = typeToId.find(typeIndex);
		if (typeToIdIterator != typeToId.end()) {
			id = typeToIdIterator->second;
			typeToId.erase(typeToIdIterator);
		}
		else
			return false;

		auto idFactoryIterator = idFactory.find(id);
		if (idFactoryIterator != idFactory.end())
			idFactory.erase(idFactoryIterator);
		else
			return false;

		return true;
	}
	Component* ComponentRegistry::create(const std::type_info& typeInfo) {
		std::type_index typeIndex = std::type_index(typeInfo);
		auto factoryIterator = factory.find(typeIndex);
		return factoryIterator == factory.end() ? nullptr : factoryIterator->second();
		//if (factoryIterator != factory.end())
		//	return factoryIterator->second();
		//else
		//	return nullptr;
	}
	Component* ComponentRegistry::create(size_t id) {
		auto idFactoryIterator = idFactory.find(id);
		return idFactoryIterator == idFactory.end() ? nullptr : idFactoryIterator->second();
		//if (idFactoryIterator != idFactory.end())
		//	return idFactoryIterator->second();
		//else
		//	return nullptr;
	}
}
*/
