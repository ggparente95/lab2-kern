Ej: kern0-boot

Compilar kern0 y lanzarlo en QEMU tal y como se ha indicado. Responder:
¿emite algún aviso el proceso de compilado o enlazado? Si lo hubo, indicar cómo usar la opción --entry de ld(1) para subsanarlo.
Rta: Si, emite un mensaje de que no encuentra el simbolo de entrada _start. Con el comando --entry, le especifico que comience en cierta funcion.

¿cuánta CPU consume el proceso qemu-system-i386 mientras ejecuta este kernel? ¿Qué está haciendo?
Rta: Consume entre el 99-101% de CPU. Lo que hace es loopear infinitamente sin hacer absolutamente nada en cada loop.



Ej: kern0-quit

Asimismo, la combinación Ctrl-a c permite entrar al “monitor” de QEMU, desde donde se puede obtener información adicional sobre el entorno de ejecución. Ejecutar el comando info registers en el monitor de QEMU, e incluir el resultado en la entrega. 

QEMU 2.11.1 monitor - type 'help' for more information
(qemu) info registers
EAX=2badb002 EBX=00009500 ECX=00100000 EDX=00000511
ESI=00000000 EDI=00102000 EBP=00000000 ESP=00006f08
EIP=00100000 EFL=00000006 [-----P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
CS =0008 00000000 ffffffff 00cf9a00 DPL=0 CS32 [-R-]
SS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
DS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
FS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
GS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
LDT=0000 00000000 0000ffff 00008200 DPL=0 LDT
TR =0000 00000000 0000ffff 00008b00 DPL=0 TSS32-busy
GDT=     000caa68 00000027
IDT=     00000000 000003ff
CR0=00000011 CR2=00000000 CR3=00000000 CR4=00000000
DR0=00000000 DR1=00000000 DR2=00000000 DR3=00000000 
DR6=ffff0ff0 DR7=00000400
EFER=0000000000000000
FCW=037f FSW=0000 [ST=0] FTW=00 MXCSR=00001f80
FPR0=0000000000000000 0000 FPR1=0000000000000000 0000
FPR2=0000000000000000 0000 FPR3=0000000000000000 0000
FPR4=0000000000000000 0000 FPR5=0000000000000000 0000
FPR6=0000000000000000 0000 FPR7=0000000000000000 0000
XMM00=00000000000000000000000000000000 XMM01=00000000000000000000000000000000
XMM02=00000000000000000000000000000000 XMM03=00000000000000000000000000000000
XMM04=00000000000000000000000000000000 XMM05=00000000000000000000000000000000
XMM06=00000000000000000000000000000000 XMM07=00000000000000000000000000000000




Ej: kern0-hlt

una vez invocado hlt ¿cuándo se reanuda la ejecución?
Rta: La ejecucion se reanudara cuando haya una interrupcion (señales que manda el hardware al CPU para indicar que paso algun evento al que deberia reaccionar)


Sin hlt:
Uso       Evento/s    Categoría       Descripción
996,1 ms/s      35,3        Process        [PID 10957] qemu-system-i386 -serial mon:stdio -kernel kern0

Con hlt:
Uso       Evento/s    Categoría       Descripción
655,8 ms/s      33,5        Process        [PID 10953] qemu-system-i386 -serial mon:stdio -kernel kern0




Ej: kern0-gdb:
