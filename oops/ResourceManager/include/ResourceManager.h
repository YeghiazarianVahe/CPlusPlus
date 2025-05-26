#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>

class ResourceManager {
	private:
		int* data;
		size_t size;
	public:
		ResourceManager(size_t);
		~ResourceManager();

		ResourceManager(const ResourceManager&);
		ResourceManager& operator=(const ResourceManager&);

		ResourceManager(ResourceManager&&) noexcept;
		ResourceManager& operator=(ResourceManager&&) noexcept;

		void set(size_t index, int value);
		int get(size_t index) const;

};

#endif // RESOURCE_MANAGER
