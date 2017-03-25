pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pupvm.pc

settingsdir = $(sysconfdir)/xdg/pup-volume-monitor
settings_DATA = main.conf

scriptsdir = $(libexecdir)/pup-volume-monitor
scripts_SCRIPTS = mount umount

dist_bin_SCRIPTS = pup-volume-monitor-starter

init_ddir = $(sysconfdir)/init.d
init_d_SCRIPTS = start-pup-volume-monitor

EXTRA_DIST = pupvm.pc.in \
		main.conf \
		$(scripts_SCRIPTS)
