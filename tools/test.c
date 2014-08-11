void tmain(void)
{
	uint16_t* vga = 0xc0000000 + 0xb8000;
	*vga = 'A' | 0x0F;
	return;
}
