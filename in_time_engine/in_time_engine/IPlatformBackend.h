#pragma once

namespace it {
	class IPlatformBackend {
		public:
			// Functions
			virtual bool init() = 0;
			virtual bool isInit() const = 0;
			virtual bool deinit() = 0;
			virtual bool update() = 0;
	};
}
