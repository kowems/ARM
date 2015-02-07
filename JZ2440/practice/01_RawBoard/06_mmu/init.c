#define MMU_FULL_ACCESS (3 << 10)
#define MMU_DOMAIN      (0 << 5)
#define MMU_SPECIAL     (1 << 4)
#define MMU_CACHEABLE   (1 << 3)
#define MMU_BUFFERABLE  (1 << 2)
#define MMU_SECTION     (2)
#define MMU_SECDESC     (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB  (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)

void create_page_table(void)
{
    unsigned long virtual_addr,physical_addr;
    unsigned long *mmu_tlb_base = (unsigned long *)0x30000000;

    virtual_addr = 0;
    physical_addr = 0;

    *(mmu_tlb_base + (virtual_addr >> 20)) = (physical_addr & 0xFFF00000) | MMU_SECDESC_WB;

    virtual_addr = 0xA0000000;
    physical_addr = 0x56000000;

    *(mmu_tlb_base + (virtual_addr >> 20)) = (physical_addr & 0xFFF00000) | MMU_SECDESC;

    virtual_addr = 0xB0000000;
    physical_addr = 0x30000000;
    
    while(virtual_addr < 0xB4000000){

            *(mmu_tlb_base + (virtual_addr >> 20)) = (physical_addr & 0xFFF00000) | MMU_SECDESC_WB;
            virtual_addr += 0x100000;
            physical_addr += 0x100000;
    }
}
void mmu_init(void)
{
    unsigned long ttb = 0x30000000;
__asm__(
    "mov r0,#0\n"
    "mcr p15,0,r0,c7,c7,0\n"  /* disable ICaches and DCaches */

    "mcr p15,0,r0,c7,c10,4\n"
    "mcr p15,0,r0,c8,c7,0\n"

    "mov r4,%0\n"
    "mcr p15,0,r4,c2,c0,0\n"

    "mvn r0,#0\n"
    "mcr p15,0,r0,c3,c0,0\n"

    /* get c0 to r1 */
    "mrc p15,0,r0,c1,c0,0\n"

    /* low 16 bits in control register：.RVI ..RS B... .CAM
     * R : 表示换出Cache中的条目时使用的算法，
     *     0 = Random replacement；1 = Round robin replacement
     * V : 表示异常向量表所在的位置，
     *     0 = Low addresses = 0x00000000；1 = High addresses = 0xFFFF0000
     * I : 0 = 关闭ICaches；1 = 开启ICaches
     * R、S : 用来与页表中的描述符一起确定内存的访问权限
     * B : 0 = CPU为小字节序；1 = CPU为大字节序
     * C : 0 = 关闭DCaches；1 = 开启DCaches
     * A : 0 = 数据访问时不进行地址对齐检查；1 = 数据访问时进行地址对齐检查
     * M : 0 = 关闭MMU；1 = 开启MMU
     */
    
    /* clear V,I,R,S,B,C,A,M bit */
    "bic r0,r0,#0x3000\n"
    "bic r0,r0,#0x0300\n"
    "bic r0,r0,#0x0087\n"

    /* open align check & DCaches & ICaches & MMU */
    "orr r0,r0,#0x0002\n"
    "orr r0,r0,#0x0004\n"
    "orr r0,r0,#0x1000\n"
    "orr r0,r0,#0x0001\n"

    "mcr p15,0,r0,c1,c0,0\n"
    :/* without output */
    :"r"(ttb));
}

void copy_2th_to_sdram(void)
{
    unsigned int *pdwSrc = (unsigned int *)2048;
    unsigned int *pdwDest = (unsigned int *)0x30004000;
    
    while (pdwSrc < (unsigned int *)4096){
        *pdwDest = *pdwSrc;
        pdwDest++;
        pdwSrc++;
    }
}
