//		     PUP-VOLUME-MONITOR : Volume management

//pupvm-plugin.h
//Plugin API header file

//Warning: Include only this header, don't directly include others in this
//directory.

#ifndef PUP_VM_H
#define PUP_VM_H

#include <gio/gio.h>

#include <libudev.h>

#include <sys/socket.h>

#if ! GLIB_CHECK_VERSION(2, 32, 0)
#define g_hash_table_add(ht, key) g_hash_table_replace(ht, key, key)
/* http://lists.geany.org/pipermail/github-comments/2016-January/002026.html */
#define g_hash_table_contains(ht, key) g_hash_table_lookup_extended(ht, key, NULL, NULL)
/* https://gist.github.com/shadeslayer/1607267 */
#define GRecMutex GStaticRecMutex
#define g_rec_mutex_init(x) g_static_rec_mutex_init(x)
#define g_rec_mutex_lock(x) g_static_rec_mutex_lock(x)
#define g_rec_mutex_unlock(x) g_static_rec_mutex_unlock(x)
/* https://developer.gnome.org/glib/stable/glib-Deprecated-Thread-APIs.html */
#define g_thread_new(name,func,data) g_thread_create(func,data,TRUE,NULL)
#define g_thread_try_new(name,func,data,error) g_thread_create(func,data,TRUE,error)
#endif

G_BEGIN_DECLS

#define PUP_VM_H_INSIDE

#define PUPSOCK_ERR_DOMAIN g_quark_from_string("pupsock")
#include "utils.h"
#include "core.h"
#include "socket.h"
#include "transfer.h"
#include "protocol.h"
#include "conv.h"
#include "pupvm-utils.h"
#include "pupvm-settings.h"
#include "pupvm-classes.h"
#include "pupvm-monitor.h"

#undef PUP_VM_H_INSIDE

G_END_DECLS

#endif //PUP_VM_H

