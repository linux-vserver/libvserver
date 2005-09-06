MODULE    = vserver
INTERFACE = $(MODULE).i
RUBY      = ruby
SWIG      = swig
SWIGOPT   = -ruby -I../src
WRAPPER   = $(MODULE)_wrap.c


swigall: $(WRAPPER) Makefile

$(WRAPPER): $(INTERFACE)
	$(SWIG) $(SWIGOPT) -o $@ $(INTERFACE)

Makefile: extconf.rb
	$(RUBY) extconf.rb
	@if [ -f Makefile ]; then \
		echo "include Makefile.swig" >> Makefile; \
	fi

swigclean:
	@if [ -f Makefile ]; then \
		make -f Makefile clean; \
	fi
	rm -f Makefile $(WRAPPER)
