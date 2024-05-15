/*************************
 * @file Config.h
 * @author zhuzhile08 (zhuzhile08@gmail.com)
 * 
 * @brief a file containing engine and application settings
 * 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022
 *************************/

#pragma once

#include <Common/Common.h>
#include <Common/Array.h>

#include <string_view>

namespace lstd {

namespace config {

// Disable logging enum
// Setting a logging level as config::disableLog only disables all severities BELOW it. This means that exceptions can't (and also shouldn't) be disabled
enum class DisableLog {
	none,
	trace,
	debug,
	info,
	warning,
	error,
	exception
};

inline constexpr DisableLog disableLog = DisableLog::none;
inline constexpr bool coloredLog = true;

} // namespace config

} // namespace lstd
