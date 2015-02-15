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
    char *p;

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
