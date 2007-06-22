require 'mkmf'
exit 1 if not have_library("vserver", "vx_create")
create_makefile("vserver")
