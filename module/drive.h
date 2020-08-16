//GDrive class implementation: PupClientDrive

typedef struct
{
	PupClientDevice parent;

} PupClientDrive;

typedef struct
{
	PupClientDeviceClass parent;

} PupClientDriveClass;

GType pup_client_drive_get_type(void);

#define PUP_TYPE_CLIENT_DRIVE       (pup_client_drive_get_type())
#define PUP_CLIENT_DRIVE(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_CLIENT_DRIVE, PupClientDrive))
#define PUP_IS_CLIENT_DRIVE(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_CLIENT_DRIVE))
#define PUP_CLIENT_DRIVE_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_CLIENT_DRIVE, PupClientDriveClass))
#define PUP_IS_CLIENT_DRIVE_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_CLIENT_DRIVE))
#define PUP_CLIENT_DRIVE_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_CLIENT_DRIVE, PupClientDriveClass))
#define PUP_CLIENT_DRIVE_NAME "PupClientDrive"

gboolean pup_client_drive_can_poll_for_media(GDrive *drive);
GVolume *pup_client_drive_next_volume(PupClientMonitor *monitor,const gchar *sysname,GHashTableIter *iter);
const gchar *pup_client_drive_get_sort_key(GDrive *drive);
void pup_client_drive_eject_w_operation(GDrive *drive,GMountUnmountFlags flags,GMountOperation *mount_operation,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
GIcon *pup_client_drive_get_icon(GDrive *drive);
gchar **pup_client_drive_enum_identifiers(GDrive *drive);
gchar *pup_client_drive_get_identifier(GDrive *drive,const gchar *id);
void pup_client_drive_eject(GDrive *drive,GMountUnmountFlags flags,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
gboolean pup_client_drive_can_eject(GDrive *drive);
gboolean pup_client_drive_is_media_check_automatic(GDrive *drive);
gboolean pup_client_drive_has_media(GDrive *drive);
gboolean pup_client_drive_is_removable(GDrive *drive);
GList *pup_client_drive_get_volumes(GDrive *drive);
gboolean pup_client_drive_has_volumes(GDrive *drive);
gchar *pup_client_drive_get_name(GDrive *drive);
void pup_client_drive_register(GIOModule *module);
void pup_client_drive_finalize(GObject *instance);
void pup_client_drive_init_iface(GDriveIface *interface);
