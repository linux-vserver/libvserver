/* Swig interface to libvserver */

%module libvserver

%{
#include "vserver.h"
%}

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef int int32_t;
typedef int pid_t;

%include "vserver.h"
