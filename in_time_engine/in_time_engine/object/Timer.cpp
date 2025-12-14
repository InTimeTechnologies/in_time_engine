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
 * File: Timer.h
 * Author: Christopher Barrios Agosto
 * Created on: 25DEC2024
 *
 * Description:
 *  Timer class that uses the In Time Engine's core time.
 *  Set a function to call when time is up.
 *  When running is set to true, it starts ticking down when engine is running.
 *****************************************************************************/

#include "Timer.h"

// class Timer

// Static | public

// Properties
std::chrono::nanoseconds it::Timer::defaultTimeLeft = std::chrono::seconds(5);
