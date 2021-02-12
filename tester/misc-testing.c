#include <libpupvm/pupvm-plugin.h>
#include <stdio.h>
#include <string.h>

gint main()
{
	GError *error = NULL;
	gint exitcode;
	gchar *output;

	gboolean res = pup_vm_launch_script_cmdline("myexec",
	                                     &exitcode, &output, &error);

	printf("exitcode: %d\noutput=\"%s\"\nres=%d\n",
	       exitcode, output, res);
	if (error)
		printf("error=%s\n", error->message);

	return 0;
}
