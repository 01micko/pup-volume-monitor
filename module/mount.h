//GMount class implementation: PupMount
//mount.h

struct _PupMount
{
	GObject parent;

	PupClientVolume *holder;
};

typedef struct
{
	GObjectClass parent;

} PupMountClass;

GType pup_mount_get_type(void);

#define PUP_TYPE_MOUNT       (pup_mount_get_type())
#define PUP_MOUNT(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_MOUNT, PupMount))
#define PUP_IS_MOUNT(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_MOUNT))
#define PUP_MOUNT_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_MOUNT, PupMountClass))
#define PUP_IS_MOUNT_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_MOUNT))
#define PUP_MOUNT_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_MOUNT, PupMountClass))
#define PUP_MOUNT_NAME "PupMount"

PupMount *pup_mount_get(PupClientVolume *parent);
const gchar *pup_mount_get_sort_key(GMount *mount);
void pup_mount_eject_w_operation(GMount *mount,GMountUnmountFlags flags,GMountOperation *mount_operation,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
void pup_mount_umount_w_operation(GMount *mount,GMountUnmountFlags flags,GMountOperation *mount_operation,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
GIcon *pup_mount_get_icon(GMount *mount);
void pup_mount_eject(GMount *mount,GMountUnmountFlags flags,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
void pup_mount_umount(GMount *mount,GMountUnmountFlags flags,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
gboolean pup_mount_can_eject(GMount *mount);
gboolean pup_mount_can_umount(GMount *mount);
GDrive *pup_mount_get_drive(GMount *mount);
GVolume *pup_mount_get_volume(GMount *mount);
gchar *pup_mount_get_uuid(GMount *mount);
gchar *pup_mount_get_name(GMount *mount);
GFile *pup_mount_get_root(GMount *mount);
void pup_mount_register(GIOModule *module);
void pup_mount_finalize(GObject *instance);
void pup_mount_init_iface(GMountIface *interface);
