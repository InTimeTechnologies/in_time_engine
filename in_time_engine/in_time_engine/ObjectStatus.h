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
 * File: ObjectStatus.h
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  ObjectStatus:
 *   This enum exists to track where in the lifecycle are game objects and
 *   components by the game engine.
 *****************************************************************************/

#pragma once

namespace it {
	enum class ObjectStatus {
		HEALTHY = 0,
		MARKED_FOR_DESTROY,
		DESTROYED
	};
}
