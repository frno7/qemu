# QEMU for the R5900 Emotion Engine in the PlayStation 2

This [QEMU](https://www.qemu.org/) branch implements [o32 and n32 Linux ABI](https://www.linux-mips.org/wiki/MIPS_ABI_History) user mode for the Sony/Toshiba [R5900 Emotion Engine](https://en.wikipedia.org/wiki/Emotion_Engine) MIPS III main processor of the [PlayStation 2](https://en.wikipedia.org/wiki/PlayStation_2).

An important use-case is to compile and test R5900 programs via QEMU user mode emulation on modern hardware. Compilation is, in general, impractical directly on PlayStation 2 hardware since its total amount of memory is limited to 32 MiB, whereas modern software may require 500 MiB or even more to compile. QEMU user mode also simplifies R5900 compilation because a cross-compiler is unnecessary.

## Building

The QEMU build targets `mipsel-linux-user` and `mipsn32el-linux-user` support the R5900 o32 and n32 ABIs, respectively.

## Limitations

At the moment, only the 32-bit and 64-bit MIPS psABIs are implemented, in addition to the R5900 specific three-operand MULT and MULTU instructions that GCC is known to generate for the R5900 target.

The R5900 specific set of 93 128-bit multimedia instructions is not yet supported by QEMU (see [#4](https://github.com/frno7/qemu/issues/4)). Likewise, QEMU user mode does not emulate any PlayStation 2 specific devices.

R5900 QEMU system mode is not yet implemented (see [#6](https://github.com/frno7/qemu/issues/6)).

## Dependencies when compiling R5900 programs

GCC 9.1 or later is recommended. Older GCC versions can be used if commit [d728eb9085d8](https://gcc.gnu.org/git/?p=gcc.git;a=commit;h=d728eb9085d8) (MIPS: Default to --with-llsc for the R5900 Linux target as well) is applied.

Glibc 2.29 or later is recommended. Additional patches are required to support the n32 ABI. Older Glibc versions can be used if commit [8e3c00db16fc](https://sourceware.org/git/?p=glibc.git;a=commit;h=8e3c00db16fc) (MIPS: Use `.set mips2' to emulate LL/SC for the R5900 too) is applied.

GAS 2.32 or later is optional. It has the `-mfix-r5900` option to compile generic MIPS II and MIPS III code with the appropriate workaround for the R5900 short-loop hardware bug.

## R5900 Linux kernel

See the [PlayStation 2 Linux kernel](https://github.com/frno7/linux/tree/ps2-master).

## R5900 Linux distributions

A modern [Gentoo Linux](https://gentoo.org/) can be compiled for the R5900 and the PlayStation 2. The Gentoo [sys-devel/crossdev](https://wiki.gentoo.org/wiki/Crossdev) package page and the [cross build environment guide](https://wiki.gentoo.org/wiki/Cross_build_environment) explain the details involving configuring for example a Gentoo profile and a corresponding overlay. Once those simple steps have been taken the command `# crossdev -s4 -t mipsr5900el-unknown-linux-gnu` can be used to obtain an R5900 cross toolchain as well as the basis of an R5900 Gentoo root filesystem in `/usr/mipsr5900el-unknown-linux-gnu`. As the guide explains, the R5900 base system can be built from scratch using the command `# mipsr5900el-unknown-linux-gnu-emerge -uva --keep-going @system`. The root filesystem can then be used with R5900 QEMU user mode emulation for further compilations and testing, or directly in Linux on PlayStation 2 hardware.

## General README

Read the general [README](README) for further information on QEMU.
