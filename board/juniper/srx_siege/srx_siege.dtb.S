.section .rodata, "a"
.balign 8
.global __dtb_begin
__dtb_begin:
.incbin "srx_siege.dtb" 
__dtb_end:
.global __dtb_end
.balign 8
