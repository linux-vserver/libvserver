require 'mkmf'
$libs = append_library($libs, "vserver")
create_makefile('libvserver')
