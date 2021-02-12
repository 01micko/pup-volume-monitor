//The volume monitor, server side
//pupvm-monitor.h

//icons
typedef struct
{
	gchar *devnode;
	gchar *mntpnt;
	guint flags;
} PupMntEntry;

struct _PupVMMonitor
{
	GObject parent;

	GHashTable *drives;
	GHashTable *volumes;

	gboolean udev_cancel;

	GHashTable *mounts;
	gchar *mtab_file;
	GRecMutex lock;
};

typedef struct 
{
	GObjectClass parent;
	//Device management
	void (*device_event_cb) (PupVMMonitor *monitor, PupDevice *dev,
	                         guint event, const gchar *detail_if_any);
	//Udev events
	void (*udev_event) (PupVMMonitor *monitor, struct udev_device *dev);
	//Signals
	guint udev_signal_id;
	guint udev_after_signal_id;
	guint device_event_signal_id;
	guint mounts_check_signal_id;
	//icons
} PupVMMonitorClass;

typedef void (*PupUdevEventCB) (PupVMMonitor *monitor,
                                struct udev_device *dev, gpointer user_data);

typedef void (*PupDeviceEventCB) (PupVMMonitor *monitor,
                                  PupDevice *dev,
                                  guint action,
                                  const gchar *detail,
                                  gpointer user_data);

#define PUP_TYPE_VM_MONITOR       (pup_vm_monitor_get_type())
#define PUP_VM_MONITOR(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_VM_MONITOR, PupVMMonitor))
#define PUP_IS_VM_MONITOR(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_VM_MONITOR))
#define PUP_VM_MONITOR_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_VM_MONITOR, PupVMMonitorClass))
#define PUP_IS_VM_MONITOR_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_VM_MONITOR))
#define PUP_VM_MONITOR_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_VM_MONITOR, PupVMMonitorClass))
#define PUP_VM_MONITOR_NAME "PupVMMonitor"


void pup_vm_monitor_destroy(PupVMMonitor *self);
PupMntEntry *pup_vm_monitor_get_mount_for_devnode(PupVMMonitor *self,const gchar *devnode,gboolean dup);
void pup_vm_monitor_get_mounts(PupVMMonitor *self);
void pup_vm_monitor_get_mounts_unlocked(PupVMMonitor *self);
void pup_vm_monitor_stop_processing_uevent(PupVMMonitor *self);
void pup_vm_monitor_raise_uevent(PupVMMonitor *self,struct udev_device *udev_dev);
void pup_vm_monitor_copy_back_device(PupVMMonitor *self,PupDevice *dev,const gchar *detail);
PupDevice *pup_vm_monitor_lookup(PupVMMonitor *self,guint category,const gchar *sysname,gboolean dup);
PupVolume *pup_vm_monitor_lookup_volume(PupVMMonitor *self,const gchar *sysname,gboolean dup);
PupDrive *pup_vm_monitor_lookup_drive(PupVMMonitor *self,const gchar *sysname,gboolean dup);
void pup_vm_monitor_change_device(PupVMMonitor *self,PupDevice *dev,const gchar *detail);
void pup_vm_monitor_remove_device(PupVMMonitor *self,PupDevice *dev);
gboolean pup_vm_monitor_add_device(PupVMMonitor *self,PupDevice *dev);
PupVolume *pup_vm_monitor_lookup_volume_unlocked(PupVMMonitor *self,const gchar *sysname,gboolean dup);
PupDrive *pup_vm_monitor_lookup_drive_unlocked(PupVMMonitor *self,const gchar *sysname,gboolean dup);
void pup_vm_monitor_change_device_unlocked(PupVMMonitor *self,PupDevice *dev,const gchar *detail);
void pup_vm_monitor_remove_device_unlocked(PupVMMonitor *self,PupDevice *dev);
gboolean pup_vm_monitor_add_device_unlocked(PupVMMonitor *self,PupDevice *dev);
GHashTable *pup_vm_monitor_get_hash_table(PupVMMonitor *self,PupDevice *dev);
void pup_vm_monitor_unlock(PupVMMonitor *self);
void pup_vm_monitor_lock(PupVMMonitor *self);
PupVMMonitor *pup_vm_monitor_get();
GType pup_vm_monitor_get_type();
void pup_mnt_entry_free(PupMntEntry *entry);
