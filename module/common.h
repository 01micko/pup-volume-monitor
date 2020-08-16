//Common stuff

#ifndef __MODULE_COMMON_H
#define __MODULE_COMMON_H

#include <libpupvm/common-includes.h>

//Environment variables that control behavior
#define PUP_VOLUME_MONITOR_IGNORE "PUP_VOLUME_MONITOR_IGNORE"
#define PUP_VOLUME_MONITOR_DEBUG "PUP_VOLUME_MONITOR_DEBUG"
#define PUP_VOLUME_MONITOR_BE_NATIVE "PUP_VOLUME_MONITOR_BE_NATIVE"

#include "utils.h"
#include "client-monitor.h"
#include "volume-monitor.h"
#include "volume.h"
#include "mount.h"
#include "drive.h"

#endif /* __MODULE_COMMON_H */
