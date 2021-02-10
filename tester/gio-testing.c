#include <glib.h>
#include <gio/gio.h>
#include <stdio.h>

gboolean throw_error(GError *error, gboolean terminate)
{
	if (! error) return FALSE;
	
	if (terminate)
		g_error("An error occurred (Domain: %s): %s\nCode: %d",
				g_quark_to_string(error->domain), error->message, 
				error->code);
	else
		g_warning("An error occurred (Domain: %s): %s\nCode: %d",
				g_quark_to_string(error->domain), error->message, 
				error->code);
	
	return TRUE;
}

int main(int argc, char *argv[])
{
	GVolumeMonitor *monitor;
	GList *volumes, *iter;
	GVolume * vol;
	
#if !GLIB_CHECK_VERSION(2, 36, 0) //g_type_init() was deprecated in 2.36
	g_type_init();
#endif
	
	monitor = g_volume_monitor_get();
	
	volumes = g_volume_monitor_get_volumes(monitor);
	g_assert(volumes != NULL);
	
	//Testing volumes...
	
	for (iter = g_list_first(volumes); iter != NULL; iter = iter->next)
	{
		vol = G_VOLUME (iter->data);
		printf ("%s: label=\"%s\", uuid=\"%s\"\n",
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE),
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_LABEL),
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UUID));
		g_object_unref (vol);
		g_object_unref (vol); //Torture test
	}
	g_list_free(volumes);
	
	volumes = g_volume_monitor_get_volumes(monitor);
	g_assert(volumes != NULL);
	puts("Testing reuse of objects");
	
	for (iter = g_list_first(volumes); iter != NULL; iter = iter->next)
	{
		vol = G_VOLUME (iter->data);
		printf ("%s: label=\"%s\", uuid=\"%s\"\n",
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE),
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_LABEL),
		        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UUID));
		g_object_unref (vol);
	}
	g_list_free(volumes);
	
	//Testing drives

	puts("\nTesting drives");
	GList *drives = g_volume_monitor_get_connected_drives(monitor);
	for (iter = g_list_first(drives); iter != NULL; iter = iter->next)
	{
		GList *iter2;
		char * drive_name = g_drive_get_name (G_DRIVE (iter->data));
		printf("%s: \n", drive_name);
		g_free (drive_name);

		volumes = g_drive_get_volumes ((GDrive *) iter->data);
		for (iter2 = g_list_first(volumes); iter2 != NULL; iter2 = iter2->next)
		{
			vol = G_VOLUME (iter2->data);
			printf ("\t%s: label=\"%s\", uuid=\"%s\"\n",
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE),
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_LABEL),
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UUID));
			g_object_unref (vol);
			g_object_unref (vol); //Torture test
		}
		g_list_free(volumes);
		
		g_object_unref(iter->data);
	}
	g_list_free(drives);
	
	//Again...
	puts ("");
	drives = g_volume_monitor_get_connected_drives(monitor);
	for (iter = g_list_first(drives); iter != NULL; iter = iter->next)
	{
		GList *iter2;
		char * drive_name = g_drive_get_name (G_DRIVE (iter->data));
		printf("%s: \n", drive_name);
		g_free (drive_name);

		volumes = g_drive_get_volumes((GDrive *) iter->data);
		for (iter2 = g_list_first(volumes); iter2 != NULL; iter2 = iter2->next)
		{
			vol = G_VOLUME (iter2->data);
			printf ("\t%s: label=\"%s\", uuid=\"%s\"\n",
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE),
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_LABEL),
			        g_volume_get_identifier (vol, G_VOLUME_IDENTIFIER_KIND_UUID));
			g_object_unref (vol);
			g_object_unref (vol);
		}
		g_list_free(volumes);
		
		g_object_unref(iter->data);
	}
	g_list_free(drives);
	
	g_object_unref(G_OBJECT(monitor));
	
	return 0;
}
