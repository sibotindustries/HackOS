; bootloader.asm
BITS 16
ORG 0x7c00

start:
    cli                 ; Desabilitar interrupções

    ; Configuração do stack
    xor ax, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Configuração do modo de vídeo (modo texto)
    mov ax, 0x03
    int 0x10

    ; Configuração do segmento de dados
    mov ax, 0x07C0
    mov ds, ax

    ; Carregamento do kernel
    mov si, msg_loading
    call print_string

    ; Configuração do modo protegido
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 08h:protected_mode

gdt:
    dq 0x0000000000000000 ; NULL descriptor
    dq 0x00CF9A000000FFFF ; Código segmento
    dq 0x00CF92000000FFFF ; Data segment

gdt_descriptor:
    dw gdt_end - gdt - 1
    dd gdt

gdt_end:

msg_loading db "Loading kernel...", 0

protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    ; Carregar o kernel (assume-se que o kernel está logo após o bootloader)
    mov si, msg_kernel
    call print_string

    mov ax, 0x07e0
    mov es, ax
    mov bx, 0x0000
    mov dh, 15
    mov dl, 0
    mov cx, 1
    mov ax, 0x0201
    int 0x13

    ; Salta para o kernel carregado
    jmp 0x08:0x0000

print_string:
    mov ah, 0x0E
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ret

times 510-($-$$) db 0
dw 0xAA55  ; Assinatura de boot
