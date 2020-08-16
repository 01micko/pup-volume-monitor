//volume.h
//GVolume interface implementation: PupClientVolume

typedef struct _PupMount PupMount;

typedef struct
{
	PupClientDevice parent;
	
	PupMount *mount;
} PupClientVolume;

typedef struct
{
	PupClientDeviceClass parent;

} PupClientVolumeClass;

GType pup_client_volume_get_type(void);

#define PUP_TYPE_CLIENT_VOLUME (pup_client_volume_get_type())
#define PUP_CLIENT_VOLUME(ptr)       (G_TYPE_CHECK_INSTANCE_CAST((ptr), PUP_TYPE_CLIENT_VOLUME, PupClientVolume))
#define PUP_IS_CLIENT_VOLUME(ptr)    (G_TYPE_CHECK_INSTANCE_TYPE((ptr), PUP_TYPE_CLIENT_VOLUME))
#define PUP_CLIENT_VOLUME_CLASS(ptr) (G_TYPE_CHECK_CLASS_CAST((ptr), PUP_TYPE_CLIENT_VOLUME, PupClientVolumeClass))
#define PUP_IS_CLIENT_VOLUME_CLASS(ptr)  (G_TYPE_CHECK_CLASS_TYPE((ptr), PUP_TYPE_CLIENT_VOLUME))
#define PUP_CLIENT_VOLUME_GET_CLASS(ptr) (G_TYPE_INSTANCE_GET_CLASS((ptr), PUP_TYPE_CLIENT_VOLUME, PupClientVolumeClass))
#define PUP_CLIENT_VOLUME_NAME "PupClientVolume"

#define PUP_VOLUME_IDENTIFIER_KIND_FSTYPE "fstype"

extern gchar *pup_client_volume_identifiers[];
gboolean pup_client_volume_uuid_test_hfunc(gpointer key,gpointer value,gpointer user_data);
const gchar *pup_client_volume_get_sort_key(GVolume *volume);
void pup_client_volume_eject_w_operation(GVolume *volume,GMountUnmountFlags flags,GMountOperation *mount_operation,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
gboolean pup_client_volume_should_automount(GVolume *volume);
GIcon *pup_client_volume_get_icon(GVolume *volume);
void pup_client_volume_eject(GVolume *volume,GMountUnmountFlags flags,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
void pup_client_volume_mount(GVolume *volume,GMountMountFlags flags,GMountOperation *mount_operation,GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data);
gboolean pup_client_volume_can_eject(GVolume *volume);
gboolean pup_client_volume_can_mount(GVolume *volume);
GMount *pup_client_volume_get_mount(GVolume *volume);
gchar *pup_client_volume_get_identifier(GVolume *volume,const gchar *id);
gchar **pup_client_volume_enum_identifiers(GVolume *volume);
GDrive *pup_client_volume_get_drive(GVolume *volume);
gchar *pup_client_volume_get_uuid(GVolume *volume);
gchar *pup_client_volume_get_name(GVolume *volume);

void pup_client_volume_register(GIOModule *module);
void pup_client_volume_finalize(GObject *instance);
void pup_client_volume_init_iface(GVolumeIface *interface);

