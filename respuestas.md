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


qué se imprime por pantalla al arrancar.
qué representan cada uno de los valores enteros (incluyendo 0xb8000).
por qué se usa el modificador volatile para el puntero al buffer.

    Imprime 'OK' al comienzo
    La memoria de video para monitores de color reside en 0xB8000.
    El 79 es el caracter ASCII de 'O'
    El 75 es el caracter ASCII de 'K'
    El 47 corresponde al color con el que se quiere pintar
    Se usa el modificador volatile para indicarle al compilador que el valor de la variable al que esta asociado puede cambiar en cualquier momento. El buffer de video puede ser usado por otros programas, por eso cada vez que va a usar la variable debe volver a leer.





Ej: kern0-endian

Compilar el siguiente programa y justificar la salida que produce en la terminal:

    #include <stdio.h>

    int main(void) {
        unsigned int i = 0x00646c72;
        printf("H%x Wo%s\n", 57616, (char *) &i);
    }

    Esto imprime He110 World.
    57616 corresponde, en hexadecimal, a e110. El %x del printf permite mostrarlo
    Se lee como string 0x00646c72. segun la tabla ascii:
    0x72 = 'r'
    0x6c = 'l'
    0x64 = 'd'
    0x00 = NULL
    Y como la arquitectura usa little endian, el resultado es 'He110 World'

A continuación, reescribir el código para una arquitectura big-endian, de manera que imprima exactamente lo mismo.

    Bastaría con cambiar el numero hexadecimal de la variable i.
    unsigned int i = 0x00646c72; -------->  unsigned int i = 0x726c6400;


