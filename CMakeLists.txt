cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{MEPSDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{MEPSDK}/share/mep.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define MEPSDK to point to your SDK path!")
  endif()
endif()

project(libpdclib C)

add_definitions(-mtiny=0 -mabsdiff -maverage -mbitops -mclip -mdiv -mleadz -mminmax -mmult -mrepeat -msatur -mvl64 -mvliw -mcop64 -D__MEP_CONFIG_CP_DATA_BUS_WIDTH=64 -mivc2 -Wl,-q -Wall -Werror -O3 -std=c99 -ffreestanding -D__STDC_NO_THREADS__)

# List of source files.
set( PDCLIB_SOURCES
     functions/ctype/isalnum.c
     functions/ctype/isalpha.c
     functions/ctype/isblank.c
     functions/ctype/iscntrl.c
     functions/ctype/isdigit.c
     functions/ctype/isgraph.c
     functions/ctype/islower.c
     functions/ctype/isprint.c
     functions/ctype/ispunct.c
     functions/ctype/isspace.c
     functions/ctype/isupper.c
     functions/ctype/isxdigit.c
     functions/ctype/tolower.c
     functions/ctype/toupper.c

     functions/inttypes/imaxabs.c
     functions/inttypes/imaxdiv.c
     functions/inttypes/strtoimax.c
#     functions/inttypes/strtoumax.c

#     functions/locale/localeconv.c
#     functions/locale/setlocale.c

#     platform/venezia/functions/signal/raise.c
#     platform/venezia/functions/signal/signal.c

#     functions/stdio/clearerr.c
#     functions/stdio/fclose.c
#     functions/stdio/feof.c
#     functions/stdio/ferror.c
#     functions/stdio/fflush.c
#     functions/stdio/fgetc.c
#     functions/stdio/fgetpos.c
#     functions/stdio/fgets.c
#     functions/stdio/fopen.c
#     functions/stdio/fopen_s.c
     functions/stdio/fprintf.c
     functions/stdio/fputc.c
     functions/stdio/fputs.c
#     functions/stdio/fread.c
#     functions/stdio/freopen.c
#     functions/stdio/freopen_s.c
#     functions/stdio/fscanf.c
#     functions/stdio/fseek.c
#     functions/stdio/fsetpos.c
#     functions/stdio/ftell.c
#     functions/stdio/fwrite.c
#     functions/stdio/getc.c
#     functions/stdio/getchar.c
#     functions/stdio/perror.c
     functions/stdio/printf.c
     functions/stdio/putc.c
     functions/stdio/putchar.c
     functions/stdio/puts.c
#     functions/stdio/remove.c
#     functions/stdio/rename.c
#     functions/stdio/rewind.c
#     functions/stdio/scanf.c
#     functions/stdio/setbuf.c
#     functions/stdio/setvbuf.c
     functions/stdio/snprintf.c
     functions/stdio/sprintf.c
#     functions/stdio/sscanf.c
#     functions/stdio/tmpfile_s.c
#     functions/stdio/tmpnam.c
#     functions/stdio/ungetc.c
     functions/stdio/vfprintf.c
#     functions/stdio/vfscanf.c
#     functions/stdio/vprintf.c
#     functions/stdio/vscanf.c
     functions/stdio/vsnprintf.c
     functions/stdio/vsprintf.c
#     functions/stdio/vsscanf.c
#     platform/venezia/functions/stdio/tmpfile.c
	 platform/venezia/functions/stdio/uart.c

     functions/stdlib/abort.c
#     functions/stdlib/abort_handler_s.c
     functions/stdlib/abs.c
     functions/stdlib/at_quick_exit.c
     functions/stdlib/atexit.c
     functions/stdlib/atoi.c
     functions/stdlib/atol.c
     functions/stdlib/atoll.c
     functions/stdlib/bsearch.c
#     functions/stdlib/bsearch_s.c
     functions/stdlib/div.c
     functions/stdlib/exit.c
     functions/stdlib/_Exit.c
#     functions/stdlib/ignore_handler_s.c
     functions/stdlib/labs.c
     functions/stdlib/ldiv.c
     functions/stdlib/llabs.c
     functions/stdlib/lldiv.c
     functions/stdlib/qsort.c
#     functions/stdlib/qsort_s.c
     functions/stdlib/quick_exit.c
     functions/stdlib/rand.c
#     functions/stdlib/set_constraint_handler_s.c
     functions/stdlib/srand.c
     functions/stdlib/strtol.c
     functions/stdlib/strtoll.c
     functions/stdlib/strtoul.c
#     functions/stdlib/strtoull.c
#     platform/venezia/functions/stdlib/getenv.c
#     platform/venezia/functions/stdlib/getenv_s.c
#     platform/venezia/functions/stdlib/system.c

     functions/string/memchr.c
     functions/string/memcmp.c
     functions/string/memcpy.c
     functions/string/memmove.c
     functions/string/memset.c
     functions/string/strcat.c
     functions/string/strchr.c
     functions/string/strcmp.c
     functions/string/strcoll.c
     functions/string/strcpy.c
     functions/string/strcspn.c
#     functions/string/strerror.c
     functions/string/strlen.c
     functions/string/strncat.c
     functions/string/strncmp.c
     functions/string/strncpy.c
     functions/string/strpbrk.c
     functions/string/strrchr.c
     functions/string/strspn.c
     functions/string/strstr.c
#     functions/string/strtok.c
#     functions/string/strtok_s.c
     functions/string/strxfrm.c
#     functions/string/memcpy_s.c
#     functions/string/memmove_s.c
#     functions/string/memset_s.c
#     functions/string/strcat_s.c
#     functions/string/strcpy_s.c
#     functions/string/strerror_s.c
#     functions/string/strerrorlen_s.c
#     functions/string/strncat_s.c
#     functions/string/strncpy_s.c
     platform/venezia/functions/string/memcpy_cop.c
	 platform/venezia/functions/string/memzero_cop.c
	 
	 functions/math/ldexpf.c
	 functions/math/fabsf.c
	 functions/math/sinf.c
	 functions/math/cosf.c
	 functions/math/floorf.c
	 functions/math/powf.c
	 functions/math/expf.c
	 functions/math/logf.c

#     platform/venezia/functions/threads/call_once.c
#     platform/venezia/functions/threads/cnd_broadcast.c
#     platform/venezia/functions/threads/cnd_destroy.c
#     platform/venezia/functions/threads/cnd_init.c
#     platform/venezia/functions/threads/cnd_signal.c
#     platform/venezia/functions/threads/cnd_timedwait.c
#     platform/venezia/functions/threads/cnd_wait.c
#     platform/venezia/functions/threads/mtx_destroy.c
#     platform/venezia/functions/threads/mtx_init.c
#     platform/venezia/functions/threads/mtx_lock.c
#     platform/venezia/functions/threads/mtx_timedlock.c
#     platform/venezia/functions/threads/mtx_trylock.c
#     platform/venezia/functions/threads/mtx_unlock.c
#     platform/venezia/functions/threads/thrd_create.c
#     platform/venezia/functions/threads/thrd_current.c
#     platform/venezia/functions/threads/thrd_detach.c
#     platform/venezia/functions/threads/thrd_equal.c
#     platform/venezia/functions/threads/thrd_exit.c
#     platform/venezia/functions/threads/thrd_join.c
#     platform/venezia/functions/threads/thrd_sleep.c
#     platform/venezia/functions/threads/thrd_yield.c
#     platform/venezia/functions/threads/tss_create.c
#     platform/venezia/functions/threads/tss_delete.c
#     platform/venezia/functions/threads/tss_get.c
#     platform/venezia/functions/threads/tss_set.c

#     functions/time/asctime.c
#     functions/time/asctime_s.c
#     functions/time/ctime.c
#     functions/time/ctime_s.c
#     functions/time/difftime.c
#     functions/time/gmtime.c
#     functions/time/gmtime_s.c
#     functions/time/localtime.c
#     functions/time/localtime_s.c
#     functions/time/mktime.c
#     functions/time/strftime.c
#     platform/venezia/functions/time/clock.c
#     platform/venezia/functions/time/time.c
#     platform/venezia/functions/time/timespec_get.c

#     functions/_tzcode/_PDCLIB_gmtcheck.c
#     functions/_tzcode/_PDCLIB_gmtsub.c
#     functions/_tzcode/_PDCLIB_increment_overflow.c
#     functions/_tzcode/_PDCLIB_init_ttinfo.c
#     functions/_tzcode/_PDCLIB_localsub.c
#     functions/_tzcode/_PDCLIB_localtime_tzset.c
#     functions/_tzcode/_PDCLIB_mktime_tzname.c
#     functions/_tzcode/_PDCLIB_timesub.c
#     functions/_tzcode/_PDCLIB_tzload.c
#     functions/_tzcode/_PDCLIB_tzparse.c
#     functions/_tzcode/_PDCLIB_tzset_unlocked.c
#     functions/_tzcode/_PDCLIB_update_tzname_etc.c

     functions/_PDCLIB/assert.c
     functions/_PDCLIB/errno.c
#     functions/_PDCLIB/_PDCLIB_atomax.c
#     functions/_PDCLIB/_PDCLIB_bigint.c
#     functions/_PDCLIB/_PDCLIB_bigint2.c
#     functions/_PDCLIB/_PDCLIB_bigint10.c
#     functions/_PDCLIB/_PDCLIB_bigint32.c
#     functions/_PDCLIB/_PDCLIB_bigint64.c
#     functions/_PDCLIB/_PDCLIB_bigint_add.c
#     functions/_PDCLIB/_PDCLIB_bigint_sub.c
#     functions/_PDCLIB/_PDCLIB_bigint_cmp.c
#     functions/_PDCLIB/_PDCLIB_bigint_invlog2.c
#     functions/_PDCLIB/_PDCLIB_bigint_log2.c
#     functions/_PDCLIB/_PDCLIB_bigint_mant.c
#     functions/_PDCLIB/_PDCLIB_bigint_mul.c
#     functions/_PDCLIB/_PDCLIB_bigint_mul_dig.c
#     functions/_PDCLIB/_PDCLIB_bigint_div.c
#     functions/_PDCLIB/_PDCLIB_bigint_div_dig.c
#     functions/_PDCLIB/_PDCLIB_bigint_shl.c
#     functions/_PDCLIB/_PDCLIB_bigint_tostring.c
     functions/_PDCLIB/_PDCLIB_closeall.c
     functions/_PDCLIB/_PDCLIB_digits.c
#     functions/_PDCLIB/_PDCLIB_filemode.c
#     functions/_PDCLIB/_PDCLIB_getstream.c
#     functions/_PDCLIB/_PDCLIB_init_file_t.c
#     functions/_PDCLIB/_PDCLIB_is_leap.c
#     functions/_PDCLIB/_PDCLIB_isstream.c
#     functions/_PDCLIB/_PDCLIB_load_lc_collate.c
#     functions/_PDCLIB/_PDCLIB_load_lc_ctype.c
#     functions/_PDCLIB/_PDCLIB_load_lc_messages.c
#     functions/_PDCLIB/_PDCLIB_load_lc_monetary.c
#     functions/_PDCLIB/_PDCLIB_load_lc_numeric.c
#     functions/_PDCLIB/_PDCLIB_load_lc_time.c
#     functions/_PDCLIB/_PDCLIB_load_lines.c
#     functions/_PDCLIB/_PDCLIB_prepread.c
#     functions/_PDCLIB/_PDCLIB_prepwrite.c
     functions/_PDCLIB/_PDCLIB_print.c
#     functions/_PDCLIB/_PDCLIB_print_fp.c
     functions/_PDCLIB/_PDCLIB_print_integer.c
     functions/_PDCLIB/_PDCLIB_print_string.c
#     functions/_PDCLIB/_PDCLIB_scan.c
     functions/_PDCLIB/_PDCLIB_seed.c
#     functions/_PDCLIB/_PDCLIB_strtod_main.c
#     functions/_PDCLIB/_PDCLIB_strtod_scan.c
#     functions/_PDCLIB/_PDCLIB_strtok.c
     functions/_PDCLIB/_PDCLIB_strtox_main.c
     functions/_PDCLIB/_PDCLIB_strtox_prelim.c
#     functions/_PDCLIB/stdarg.c

#     platform/venezia/functions/_PDCLIB/_PDCLIB_changemode.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_close.c
     platform/venezia/functions/_PDCLIB/_PDCLIB_Exit.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_fillbuffer.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_flushbuffer.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_open.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_realpath.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_rename.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_remove.c
#     platform/venezia/functions/_PDCLIB/_PDCLIB_seek.c
     platform/venezia/functions/_PDCLIB/_PDCLIB_stdinit.c
)

# List of header files. Not required for actually building, but if they
# are not listed (in add_library()), they do not show up in IDE project
# files (like MSVC solutions).
# These get installed to your system's default include directory.
set( PDCLIB_HEADERS
     include/assert.h
     include/ctype.h
     include/errno.h
     include/inttypes.h
     include/iso646.h
     include/limits.h
     include/locale.h
     include/stdalign.h
     include/stdarg.h
     include/stdbool.h
     include/stddef.h
     include/stdint.h
     include/stdio.h
     include/stdlib.h
     include/stdnoreturn.h
     include/string.h
     include/time.h
     include/wctype.h
	 include/math.h

#     platform/venezia/include/float.h
#     platform/venezia/include/signal.h
#     platform/venezia/include/threads.h
     platform/venezia/include/string_cop.h
	 platform/venezia/include/uart.h
)

# These get installed in a "pdclib" subdirectory of your system's default
# "include" directory.
set( PDCLIB_PRIVATE_HEADERS
     include/pdclib/_PDCLIB_glue.h
     include/pdclib/_PDCLIB_internal.h
     include/pdclib/_PDCLIB_lib_ext1.h
     platform/venezia/include/pdclib/_PDCLIB_config.h
)

include_directories(include)
include_directories(include/pdclib)
include_directories(platform/venezia/include/pdclib)
include_directories(platform/venezia/include)

add_library(${PROJECT_NAME}_objs OBJECT 
	${PDCLIB_SOURCES}
)

add_library(pdclib $<TARGET_OBJECTS:${PROJECT_NAME}_objs>)

install(FILES
	${PDCLIB_HEADERS}
	platform/venezia/include/pdclib/_PDCLIB_config.h
	DESTINATION include
)

install(FILES
	platform/venezia/include/pdclib/_PDCLIB_config.h
	DESTINATION include/pdclib
)

install(DIRECTORY
	include/pdclib/
	DESTINATION include/pdclib
)

install(TARGETS pdclib
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
