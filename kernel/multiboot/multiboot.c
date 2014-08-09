#include <stdint.h>
#include <kernel/multiboot/multiboot.h>
#include <arch/x86/x86.h>
multiboot_info_t* mboot_info;
void initialise_mboot(uint32_t mboot_info_phys)
{
	mboot_info = (multiboot_info_t*)PHYSICAL_TO_VIRTUAL(mboot_info_phys);
}
