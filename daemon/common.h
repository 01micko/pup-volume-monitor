//common.h
//Common includes

#ifndef __DAEMON_COMMON_H
#define __DAEMON_COMMON_H

#include <libpupvm/common-includes.h>
#include <blkid/blkid.h>
#include <glib/gstdio.h>

/*
 operations.h
 Contains code for builtin operations
 Currently "mount" and "umount" is implemented for PupVolume.
*/
void pup_vm_impl_init ();


/*
 monitor.h 
 Server side volume monitor implementation
*/

typedef struct
{
	PupVMMonitor parent;
	gboolean initialized;
	//udev stuff
	struct udev *udev_ctx;
	GThread *udev_thread;
	//probing
	GThreadPool *dev_probe_thread_pool;
} PupServerMonitor;

typedef struct
{
	PupVMMonitorClass parent;
	guint broadcast_signal_id;
} PupServerMonitorClass;

#define PUP_TYPE_SERVER_MONITOR       (pup_server_monitor_get_type())
#define PUP_SERVER_MONITOR(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitor))
#define PUP_IS_SERVER_MONITOR(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_SERVER_MONITOR))
#define PUP_SERVER_MONITOR_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitorClass))
#define PUP_IS_SERVER_MONITOR_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_SERVER_MONITOR))
#define PUP_SERVER_MONITOR_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitorClass))
#define PUP_SERVER_MONITOR_NAME "PupServerMonitor"

void pup_server_monitor_start_operation(PupServerMonitor *self,guint category,const gchar *sysname,PupOperation *operation);
gboolean pup_server_monitor_mounts_check_func(gpointer data);
void pup_server_monitor_start_udev_thread(PupServerMonitor *self);
void pup_server_monitor_dump_contents(PupServerMonitor *self);
GType pup_server_monitor_get_type();


/*
 drive-probes.h
 Probing for drives and volumes
*/
void pup_volume_set_icon(PupVolume *volume,PupVMMonitor *monitor);
struct udev_device *pup_volume_search_for_drive(struct udev_device *dev);
void pup_volume_update_from_blkid_probe(PupVolume *volume,struct udev_device *dev,blkid_probe probe);
gboolean pup_volume_assert(struct udev_device *dev,blkid_probe *probe_return);
PupVolume *pup_volume_new_from_blkid_cache(blkid_cache cache,const gchar *devnode);
guint pup_volume_update_mount(PupVolume *volume,PupMntEntry *entry);
void pup_drive_update(PupDrive *drive,struct udev_device *dev);
gboolean pup_drive_assert(struct udev_device *dev);


/* 
 server.h
 Connecting to clients, sharing information, handling operations
*/

typedef struct
{
	PupSock *sock;
	GHashTable *clients;
	PupServerMonitor *monitor;
} PupServer;

PupServer *pup_server_setup();
gboolean pup_server_check_is_running();

#endif /* __DAEMON_COMMON_H */
