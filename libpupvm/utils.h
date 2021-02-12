//Useful utility functions and macros

//utils.h

#define G_LIST_ITER(l, i) (i = l; i != NULL; i = i->next)

typedef struct
{
	GTimer *timer;
	gdouble target;
} PSTimer;

#define PUP_STATIC static

gboolean pstimer_is_time_remaining(PSTimer *timer);
struct timeval *pstimer_get_remaining_time(PSTimer *timer,struct timeval *time_return);
void pstimer_destroy(PSTimer *timer);
PSTimer *pstimer_new(const gdouble target);
int psutil_set_nonblock_flag(int fd,gboolean value);
void psutil_fill_sockaddr_local(const char *name,struct sockaddr **addr,gsize *size_return);
