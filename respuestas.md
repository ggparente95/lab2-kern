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



Ej: x86-write
¿Por qué se le resta 1 al resultado de sizeof?

    Por que el ultimo caracter es el de fin de string.

¿Funcionaría el programa si se declarase msg como const char *msg = "...";? ¿Por qué?

    No, porque el sizeof devuelve el tamaño de la estructura creada en tiempo de compilación.
    El sizeof de un const char* devuelve el tamaño de un puntero, mientras const char [] devuelve el tamaño de la estructura, que es un array.

Compilar ahora libc_hello.S y verificar que funciona correctamente. Explicar el propósito de cada instrucción, y cómo se corresponde con el código C original.
    Pushea la variable len, que es la longitud del string.
    Pushea el string a imprimir
    Pushea 1 (standard ouput)
    Se llama a la syscall "write"
    Se pushea a la pila el numero 7
    Se llama a la syscall "_exit"

Hex dump de ./libc_hello (.ascii):
0000000  48  65  6c  6c  6f  2c  20  77  6f  72  6c  64  21  0a
          H   e   l   l   o   ,       w   o   r   l   d   !  \n
0000016

Hex dump de ./libc_hello (.asciz):
0000000  48  65  6c  6c  6f  2c  20  77  6f  72  6c  64  21  0a  00
          H   e   l   l   o   ,       w   o   r   l   d   !  \n  \0
0000017

La diferencia es el '\0' en el caso de .asciz. Asciz imprime strings con un nulo al final.




Ej: x86-libc
Salida de nm -u int80_hi:
         w __cxa_finalize@@GLIBC_2.1.3
         w __gmon_start__
         w _ITM_deregisterTMCloneTable
         w _ITM_registerTMCloneTable
         U __libc_start_main@@GLIBC_2.

Salida de nm -u int80_strlen:
        nose


¿qué significa que un registro sea callee-saved en lugar de caller-saved?
    Callee-saved : la funcion que usa ese registro, lo guarda. Si una funcion1 llama a una funcion2 que toca, por ejemplo, el EBX, no necesita guardarlo antes de la llamada.
    Caller-saved: la funcion que usa ese registro, no lo guarda. Esto hace que si por ejemplo, una funcion1 llama a una funcion2 y esa funcion2 modifica el valor del EAX, la funcion1 tiene que encargarse de guardar el contenido del EAX antes de la llamada a funcion2, para poder tenerlo despues

en x86 ¿de qué tipo, caller-saved o callee-saved, es cada registro según la convención de llamadas de GCC?
    Son Caller-saved: EAX, ECX y EDX
    Son Callee-saved: EBP, EBX, EDI y ESI