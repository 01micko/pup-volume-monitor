//Connecting to server, getting jobs done through server, etc.

// =================================
//      PupClientMonitor
// =================================

typedef struct
{
	PupVMMonitor parent;

	PupConvMgr *cmgr;
	PupConv *event_conv;
	gboolean initialized;

	GType volume_type;
	GType drive_type;
	GObject *volume_monitor;
} PupClientMonitor;

typedef struct 
{
	PupVMMonitorClass parent;

	guint hup_signal_id;
} PupClientMonitorClass;

GType pup_client_monitor_get_type();
#define PUP_TYPE_CLIENT_MONITOR       (pup_client_monitor_get_type())
#define PUP_CLIENT_MONITOR(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_CLIENT_MONITOR, PupClientMonitor))
#define PUP_IS_CLIENT_MONITOR(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_CLIENT_MONITOR))
#define PUP_CLIENT_MONITOR_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_CLIENT_MONITOR, PupClientMonitorClass))
#define PUP_IS_CLIENT_MONITOR_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_CLIENT_MONITOR))
#define PUP_CLIENT_MONITOR_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_CLIENT_MONITOR, PupClientMonitorClass))
#define PUP_CLIENT_MONITOR_NAME "PupClientMonitor"


// =================================
//      PupClientDevice
// =================================

typedef struct
{
	GObject parent;

	PupDevice *holder;
	PupClientMonitor *monitor;
	GObject *volume_monitor;
	gpointer iface;
} PupClientDevice;

typedef void (*PupClientDeviceSetup) (PupClientDevice *client_device,
                                      PupDevice *holder);
typedef struct
{
	GObjectClass parent;

	PupClientDeviceSetup setup_func;
} PupClientDeviceClass;

GType pup_client_device_get_type();

#define PUP_TYPE_CLIENT_DEVICE       (pup_client_device_get_type())
#define PUP_CLIENT_DEVICE(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_CLIENT_DEVICE, PupClientDevice))
#define PUP_IS_CLIENT_DEVICE(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_CLIENT_DEVICE))
#define PUP_CLIENT_DEVICE_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_CLIENT_DEVICE, PupClientDeviceClass))
#define PUP_IS_CLIENT_DEVICE_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_CLIENT_DEVICE))
#define PUP_CLIENT_DEVICE_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_CLIENT_DEVICE, PupClientDeviceClass))
#define PUP_CLIENT_DEVICE_NAME "PupClientDevice"

typedef struct 
{
	PupRemoteOperation parent;

	PupDevice *dev;
	GMountOperation *mount_operation;
#if GLIB_CHECK_VERSION(2, 46, 0)
	GTask *result;
#else
	GSimpleAsyncResult *result;
#endif	
	guint current_query;
} PupGIOOperation;

// ==========================================================================================

void pup_client_unlock(PupClientDevice *self);
void pup_client_lock(PupClientDevice *self);
gint pup_client_device_compare(gconstpointer dev1,gconstpointer dev2);
PupClientDevice *pup_client_device_get_from_device(PupClientMonitor *monitor,PupDevice *dev);
void pup_client_device_release_device(gpointer dev);
void pup_client_device_finalize(GObject *instance);
void pup_client_device_register(GIOModule *module);
GQuark pup_client_device_quark();

gboolean pup_client_monitor_connect (PupClientMonitor *self);
void pup_client_monitor_ask_question_cb(PupRemoteOperation *operation,const gchar *question,const gchar **choices);
void pup_client_monitor_ask_passwd_cb(PupRemoteOperation *operation,const gchar *msg,GAskPasswordFlags flags);
void pup_client_monitor_operation_return_cb(PupRemoteOperation *operation,gboolean success,guint error_code,const gchar *detail);
void pup_client_monitor_start_operation(PupClientMonitor *monitor,PupDevice *dev,const gchar *oper_name,const gchar *args,GMountOperation *mount_operation,
#if GLIB_CHECK_VERSION(2, 46, 0)
	GTask *result);
#else
	GSimpleAsyncResult *result);
#endif	
void pup_client_monitor_register(GIOModule *module);

