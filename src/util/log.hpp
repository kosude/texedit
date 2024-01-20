/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#if defined(_DEBUG)
#   define ZF_LOG_LEVEL ZF_LOG_DEBUG
#else
#   define ZF_LOG_LEVEL ZF_LOG_INFO
#endif
#include <zf_log.h>

#include <cstdlib>

#define LLOG ZF_LOGD
#define LINFO ZF_LOGI
#define LWARN ZF_LOGW
#define LERR ZF_LOGE
#define LFATAL ZF_LOGF

#define KILL() std::exit(EXIT_FAILURE)
#define KILLSUCC() std::exit(EXIT_SUCCESS)
