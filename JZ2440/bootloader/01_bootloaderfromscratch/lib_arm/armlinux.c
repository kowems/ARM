/*
 * armlinux - armlinux code for ARM 2440
 *
 * Copyright (c) 2015 Eric Ju <Eric.X.Ju@gmail.com>
 * 
 * This program is free software;you can registribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;Either version 2 of
 * the License,or (at your option) any later version.
 *
 */

/*                  History
 *
 *   02/14/2015 Eric: initialization creation
 *
 */

#include<linux/string.h>
#include<asm/setup.h>

static struct tag *params;

static void setup_start_tag(void)
{
    params = (struct tag *)0x30000100;

    params->hdr.tag = ATAG_CORE;
    params->hdr.size = tag_size(tag_core);

    params->u.core.flags = 0;
    params->u.core.pagesize = 0;
    params->u.core.rootdev = 0;

    params = tag_next(params);
}
static void setup_memory_tags(void)
{
    params->hdr.tag = ATAG_MEM;
    params->hdr.size = tag_size(tag_mem32);

    params->u.mem.start = 0x30000000;
    params->u.mem.size = 64*1024*1024;

    params = tag_next(params);
}
static void setup_commandline_tag(char *commandline)
{
    // did not set p with commandline,so system can not boot,when kernel start up.
    // only print "uncompressing kernel.....................................",display device is light.
    char *p = commandline;

    if(!commandline)
        return;

    params->hdr.tag = ATAG_CMDLINE;
    params->hdr.size = (sizeof(struct tag_header) + strlen(p) + 1 + 3) >> 2;

    strcpy(params->u.cmdline.cmdline,p);

    params = tag_next(params);
}
static void setup_end_tag(void)
{
    params->hdr.tag = ATAG_NONE;
    params->hdr.size = 0;
}

void do_bootm_linux(void)
{
    setup_start_tag();
    setup_memory_tags();
    setup_commandline_tag("noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0");
    setup_end_tag();
}
