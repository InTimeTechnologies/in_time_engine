#pragma once

// Dependencies | std
#include <memory>

namespace it {
	class VirtualResource {
		// Object
		private:
			// Properties
			std::shared_ptr<VirtualResource*> sharedPointer = std::make_shared<VirtualResource*>(this);

		public:
			// Constructor / Destructor
			VirtualResource() = default;
			VirtualResource(const VirtualResource& other) = default;
			VirtualResource(VirtualResource&& other) = default;
			virtual ~VirtualResource() = default;

			// Operators | assignment
			VirtualResource& operator=(const VirtualResource& other) = default;
			VirtualResource& operator=(VirtualResource&& other) = default;

			// Getters
			virtual std::weak_ptr<VirtualResource*> getWeakPointer() { return std::weak_ptr<VirtualResource*>(sharedPointer); };
	};
}
