MODULE    = libvserver
INTERFACE = $(MODULE).i
WRAPPER   = $(MODULE).c

SWIG      = swig
SWIGOPT   = -ruby -I../src


$(WRAPPER): $(INTERFACE)
	$(SWIG) $(SWIGOPT) -o $@ $(INTERFACE)

clean:
	rm -f $(WRAPPER)
