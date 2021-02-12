#include <libpupvm/pupvm-plugin.h>
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

guint32 allocator = 0;

void on_client_data_recieved(PupSock *client, PupSockData *data, 
		gpointer num)
{
	gchar *rcvd;
	GString *buf = g_string_new(NULL);
	gdouble val = (gdouble) GPOINTER_TO_INT(num);
	PSDataParser *parser;
	PSDataEncoder *encoder;
	gboolean error = FALSE;
	
	//Read the data
	parser = ps_data_parser_new_from_data(data);
	rcvd = ps_data_parser_parse_str0(parser, &error);
	ps_data_parser_destroy(parser);
	g_return_if_fail(!error);
	printf ("Client %d sent data: \n%s\n", GPOINTER_TO_INT(num), rcvd);
	
	g_string_printf(buf, "A sample reply from server (quote: %s)", rcvd);
	g_free(rcvd);
	
	encoder = ps_data_encoder_new();
	ps_data_encoder_add_str0(encoder, buf->str, 0);
	ps_data_encoder_add_val(encoder, val, gdouble, 0);
	ps_data_encoder_queue_send(encoder, client);
	
	g_string_free(buf, TRUE);
	ps_data_encoder_destroy(encoder);
	
}

gboolean on_client_hup(PupSock *client, gpointer data)
{
	printf ("Client %d disconnected\n", GPOINTER_TO_INT(data));
	g_object_unref(G_OBJECT(client));
	
	return FALSE;
}

gboolean on_client_connected(PupSock *sock, PupSock *client, gpointer data)
{
	PSDataEncoder *encoder;
	
	encoder = ps_data_encoder_new();
	ps_data_encoder_add_val(encoder, allocator, guint32, 0);
	ps_data_encoder_queue_send(encoder, client);
	ps_data_encoder_destroy(encoder);
	
	g_signal_connect(client, "data-recvd", G_CALLBACK(on_client_data_recieved),
	                 GINT_TO_POINTER(allocator));
	g_signal_connect(client, "hup", G_CALLBACK(on_client_hup),
	                 GINT_TO_POINTER(allocator));
	pup_sock_add_to_g_main(client, NULL);
	pup_sock_set_destroy_params(client, FALSE, 0.0);
			
	printf("\nClient connected: %d\n", allocator);
	
	allocator++;
	
	return TRUE;
}

int main(int argc, char *argv[])
{
	PupSock *sock;
	GMainLoop *loop;
	GError *error = NULL;
	
#if !GLIB_CHECK_VERSION(2, 36, 0) //g_type_init() was deprecated in 2.36
	g_type_init();
#endif
	
	//Create new socket
	sock = pup_sock_new_local(&error);
	throw_error(error, TRUE);
	g_debug("svr=%p", (void *) sock);
	
	//Bind address
	unlink("/tmp/pup_sock_testing");
	pup_sock_setup_as_local_server(sock, "/tmp/pup_sock_testing", &error);
	throw_error(error, TRUE);
	
	//Setup main loop
	loop = g_main_loop_new(NULL, FALSE);
	pup_sock_add_to_g_main(sock, NULL);
	g_signal_connect(sock, "accept", G_CALLBACK(on_client_connected), NULL);
	
	//Now run...
	g_main_loop_run(loop);
	
	return 0;
}

