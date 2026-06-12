#include "idt.h"
#include "../../SHARED/klog.h"

struct IDTEntry idt[256];
struct IDTDescriptor idtr;

extern void populate_isr_table(void** table);
void* isr_stub_table[256];

static void IDT_SetGate(int num, uint64_t base, uint16_t sel, uint8_t flags) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].ist = 0;
    idt[num].type_attr = flags;
    idt[num].offset_mid = (base >> 16) & 0xFFFF;
    idt[num].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt[num].zero = 0;
}

void IDT_Init() {
    SystemLog("IN PROGRESS", "Initializing Interrupt Descriptor Table (IDT)...");
    idtr.size = sizeof(idt) - 1;
    idtr.offset = (uint64_t)&idt[0];

    populate_isr_table(isr_stub_table);

    for (int i = 0; i < 256; i++) {
        IDT_SetGate(i, (uint64_t)isr_stub_table[i], 0x08, 0x8E); // 0x8E = Interrupt Gate, ring 0
    }

    __asm__ volatile("lidt %0" : : "m"(idtr));
    SystemLog("PASS", "IDT Loaded. Exceptions will now be caught.");
}

static const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void isr_handler(Registers *regs) {
    // Print Kernel Panic
    SystemLog("FAIL", "**************** KERNEL PANIC ****************");
    if (regs->int_no < 32) {
        printf("[FAIL] Exception: %s (Interrupt %d)\n", exception_messages[regs->int_no], (int)regs->int_no);
    } else {
        printf("[FAIL] Interrupt %d\n", (int)regs->int_no);
    }
    printf("Error Code: 0x%X\n", (uint32_t)regs->err_code);
    printf("RIP: 0x%X   CS: 0x%X   RFLAGS: 0x%X\n", regs->rip, regs->cs, regs->rflags);
    printf("RSP: 0x%X   SS: 0x%X\n", regs->rsp, regs->ss);
    printf("RAX: 0x%X   RBX: 0x%X   RCX: 0x%X\n", regs->rax, regs->rbx, regs->rcx);
    printf("RDX: 0x%X   RSI: 0x%X   RDI: 0x%X\n", regs->rdx, regs->rsi, regs->rdi);
    printf("RBP: 0x%X   R8:  0x%X   R9:  0x%X\n", regs->rbp, regs->r8, regs->r9);
    printf("R10: 0x%X   R11: 0x%X   R12: 0x%X\n", regs->r10, regs->r11, regs->r12);
    printf("R13: 0x%X   R14: 0x%X   R15: 0x%X\n", regs->r13, regs->r14, regs->r15);
    
    // Halt forever
    while (1) {
        __asm__ volatile("cli; hlt");
    }
}
