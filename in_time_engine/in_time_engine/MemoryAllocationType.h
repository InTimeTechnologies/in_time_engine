/******************************************************************************
 * Copyright (c) 2024 Christopher Barrios Agosto. All Rights Reserved.
 *
 * Licensing Information:
 *  This software and associated documentation files (the "Software") may not
 *  be used, copied, modified, merged, published, distributed, sublicensed,
 *  or sold without the prior written permission of the copyright owner.
 *
 *  Unauthorized use of this file, via any medium, is strictly prohibited.
 *****************************************************************************/

/******************************************************************************
 * Project: In Time Engine
 * File: MemoryAllocationType.h
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  This enum exists to track whether an object is stack or heap allocated.
 *  If it is heap allocated, the engine will call delete if
 *  deleteOnDestroy == true, but will ignore it if is stack allocated.
 *****************************************************************************/

#pragma once

namespace it {
	enum class MemoryAllocationType {
		STACK,
		HEAP
	};
}