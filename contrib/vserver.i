%module vserver

%{
#include <errno.h>
#include <vserver.h>
%}

%include <stdint.i>
%include <exception.i>

%exception {
    errno = 0;
    $action
    if (errno) {
        SWIG_exception(SWIG_RuntimeError, strerror(errno));
    }
}

typedef unsigned int pid_t;

%include <vserver.h>
