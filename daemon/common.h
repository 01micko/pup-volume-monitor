//common.h
//Common includes

#include <libpupvm/common-includes.h>
#include <blkid/blkid.h>
#include <glib/gstdio.h>


/*
 operations.h
 Contains code for builtin operations
 Currently "mount" and "umount" is implemented for PupVolume.
*/

typedef enum
{
	PUP_EXEC_MOUNT = 0,
	PUP_EXEC_UMOUNT = 1
} PupMountAction;

typedef struct
{
	PupVolume *volume;
	PupVolume *rpl_volume;
	PupMountAction action;
	gchar *event;
	PupOperation *operation;
	gchar *retval;
} PupMountExec;

void pup_vm_impl_init();
void pup_device_destroy_dbg_info(gpointer dev);
void pup_volume_umount_func(PupDevice *dev,PupOperation *operation);
void pup_volume_mount_func(PupDevice *dev,PupOperation *operation);


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

//FILE_HEADER_SUBST:gobject_macro_gen PUP_SERVER_MONITOR PupServerMonitor pup_server_monitor pup
#define PUP_TYPE_SERVER_MONITOR (pup_server_monitor_get_type())
#define PUP_SERVER_MONITOR(ptr) \
		(G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitor))
#define PUP_IS_SERVER_MONITOR(ptr) \
		(G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_SERVER_MONITOR))
#define PUP_SERVER_MONITOR_CLASS(ptr) \
		(G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitorClass))
#define PUP_IS_SERVER_MONITOR_CLASS(ptr) \
		(G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_SERVER_MONITOR))
#define PUP_SERVER_MONITOR_GET_CLASS(ptr) \
		(G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_SERVER_MONITOR, PupServerMonitorClass))
#define PUP_SERVER_MONITOR_NAME "PupServerMonitor"

void pup_server_monitor_start_operation(PupServerMonitor *self,guint category,const gchar *sysname,PupOperation *operation);
gboolean pup_server_monitor_mounts_check_func(gpointer data);
void pup_drive_process_event(PupVMMonitor *monitor,struct udev_device *dev,gboolean process_change);
void pup_server_monitor_start_udev_thread(PupServerMonitor *self);
gpointer pup_server_monitor_udev_thread(gpointer data);
void pup_server_monitor_device_event_broadcast(PupVMMonitor *monitor,PSDataEncoder *encoder);
extern const gchar *pup_volume_events[];
extern const gchar *pup_event_strv[];
void pup_server_monitor_dump_contents(PupServerMonitor *self);
void pup_server_monitor_probe_thread_func(struct udev_device *dev,PupVMMonitor *monitor);
void pup_server_monitor_update_mnt_info(PupVMMonitor *monitor,gpointer dummy);
void pup_server_monitor_device_event_cb(PupVMMonitor *monitor,PupDevice *dev,guint event,const gchar *detail);
void pup_server_monitor_udev_event(PupVMMonitor *monitor,struct udev_device *dev);
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

typedef struct
{
	PupServer *server;
	PupConvMgr *cmgr;
	gulong event_signal_handle;
	PupConv *event_conv;
} PupClient;

typedef struct
{
	PupOperation parent;
	PupConv *conv;
	gboolean is_valid;
} PupServerOperation;

void pup_client_operation_query_response_cb(PupConv *conv,PSDataParser *parser,gboolean is_new,PupClient *client,PupServerOperation *operation);
void pup_client_operation_msg_delayed(PupServerOperation *operation,PSDataEncoder *encoder);
void pup_client_operation_invalidate(PupConv *conv,PupServerOperation *operation);
void pup_client_operation_msg_cb(PupOperation *operation,PSDataEncoder *encoder);
void pup_client_start_operation(PupClient *client,PSDataParser *parser,PupConv *conv);
void pup_client_unset_event_conv_cb(PupConv *conv,PupClient *client);
void pup_client_send_event(PupServerMonitor *monitor,PSDataEncoder *encoder,PupConv *conv);
void pup_client_set_event_conv(PupClient *client,PupConv *conv);
void pup_client_disconnect_cb(PupSock *sock,PupClient *client);
void pup_client_new_conv_cb(PupConv *conv,PSDataParser *recvd_data,gboolean is_new,gpointer user_data,gpointer dummy);
void pup_client_destroy(PupClient *client);
void pup_server_new_client_cb(PupSock *sock,PupSock *new_connection,PupServer *self);
PupServer *pup_server_setup();
gboolean pup_server_check_is_running();

