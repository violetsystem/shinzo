_HOME = ../../../

# Build

LDS = link.ld
CC = clang-15
LD = ld.lld-15
ASMC = nasm

CFLAGS = -O3 -Werror -pedantic-errors -I$(_HOME)src --target=x86_64-unknown-none-elf -fno-rtti -ffreestanding -fno-builtin -nostdlib -fshort-wchar -g -mno-red-zone -fno-exceptions -fPIC
ASMFLAGS = 
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib --no-relax

SRCDIR := $(_HOME)src
OBJDIR := $(_HOME)lib
BINDIR = $(_HOME)bin
BUILDDIR = $(_HOME)bin/boot
ARCH = x86_64

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))


SRCC = $(call rwildcard,$(SRCDIR)/arch/$(ARCH),*.c) 
SRCC += $(filter-out $(SRCDIR)/arch/%,$(call rwildcard,$(SRCDIR),*.c))
ASMSRC = $(call rwildcard,$(SRCDIR)/arch/$(ARCH),*.asm)
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCC))
OBJS += $(patsubst $(SRCDIR)/arch/$(ARCH)/%.asm, $(OBJDIR)/arch/$(ARCH)/%_asm.o, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)


build: $(OBJS) link deploy

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo !==== COMPILING $^
	@ mkdir -m 777 -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo !==== COMPILING $^
	@ mkdir -m 777 -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@
	
link:
	@ echo $(SRCC)
	@ echo !==== LINKING
	@ mkdir -m 777 -p $(BUILDDIR)
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/shinzo.elf $(OBJS) $(OBJSCPP)

# Deploy
BOOTLOADER=$(_HOME)bootloader
LIMINE=$(BOOTLOADER)/limine

limine:
    ifeq ("$(wildcard $(LIMINE))", "")
		mkdir -m 777 -p $(BOOTLOADER)
		cd $(BOOTLOADER) && git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1 && $(MAKE) -C limine
    endif

deploy: limine
	cp -v limine.cfg $(LIMINE)/limine-bios.sys $(LIMINE)/limine-bios-cd.bin $(LIMINE)/limine-uefi-cd.bin $(BINDIR)/boot

	rm -f $(BINDIR)/shinzo.iso
	xorriso -as mkisofs -b limine-bios-cd.bin						\
        -no-emul-boot -boot-load-size 4 -boot-info-table 			\
        --efi-boot limine-uefi-cd.bin 								\
        -efi-boot-part --efi-boot-image --protective-msdos-label 	\
        $(BINDIR)/boot -o $(BINDIR)/shinzo.iso

	$(LIMINE)/limine bios-install $(BINDIR)/shinzo.iso


# Run

QEMUFLAGS =	-no-reboot 														\
			-no-shutdown 													\
			-boot d 														\
			-M smm=off 														\
			-serial stdio 													\
			-machine q35 													\
			-cpu qemu64 													\
			-smp 8 															\
			-cdrom $(BINDIR)/shinzo.iso										\
			-m 3G															\
			-rtc base=localtime												\

run:
	qemu-system-x86_64 $(QEMUFLAGS) -accel kvm

debug:
	qemu-system-x86_64 $(QEMUFLAGS) -s -S