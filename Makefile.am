# Top level makefile
SUBDIRS = lib tools

nobase_include_HEADERS = \
	linux/vserver/context_cmd.h \
	linux/vserver/context.h \
	linux/vserver/cvirt_cmd.h \
	linux/vserver/cvirt_def.h \
	linux/vserver/cvirt.h \
	linux/vserver/dlimit_cmd.h \
	linux/vserver/dlimit.h \
	linux/vserver/inode_cmd.h \
	linux/vserver/inode.h \
	linux/vserver/limit_cmd.h \
	linux/vserver/limit_def.h \
	linux/vserver/limit.h \
	linux/vserver/namespace_cmd.h \
	linux/vserver/namespace.h \
	linux/vserver/network_cmd.h \
	linux/vserver/network.h \
	linux/vserver/sched_cmd.h \
	linux/vserver/sched_def.h \
	linux/vserver/sched.h \
	linux/vserver/signal_cmd.h \
	linux/vserver/switch.h \
	linux/vserver/xid.h

# Stuff from our distribution
CLEANFILES = doxygen.cfg
EXTRA_DIST = doxygen.cfg.in 

# Remove doxygen/ on clean
clean-local: doxygen-clean

# Build source docs with doxygen
.PHONY:
doxygen: doxygen-clean
	@sed -e "s:\@PACKAGE_NAME\@:$(PACKAGE):" \
		 -e "s,\@PACKAGE_VERSION\@,$(VERSION)," doxygen.cfg.in > doxygen.cfg
	@doxygen doxygen.cfg

# Remove build source-docs
doxygen-clean:
	@rm -fr doxygen
