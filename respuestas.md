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

mostrar el valor del stack pointer en ese momento (p $esp), así como del registro %eax en formato hexadecimal (p/x $eax). (Opcional: leer la sección Machine state en la documentación de Multiboot para entender el valor peculiar del registro %eax.)
    (gdb) p $esp                                                                                                                                                
    $1 = (void *) 0x6f08                                                                                                                                        
    (gdb) p/x $eax                                                                                                                                             
    $2 = 0x2badb002

Valores de ebx:
    0x0000024f      0x0000027f      0x0001fb80      0x8000ffff
    Los primeros 4 bytes se usan para los flags de configuracion. (En binario, los ultimos 12 son: 001001001111)
    Los segundos 4 bytes se usan para la direccion inicial de la memoria que esta asignada.
    Los terceros 4 bytes se usan para la direccion final de la memoria que esta asignada.
    Los cuartos 4 bytes nos dan la informacion de que bootloader cargó el sistema operativo.

cantidad de memoria baja en decimal:
    (gdb) x/2dw $ebx
    0x9500: 591     639 
    639 es la cantidad de memoria baja. Esta en KiloBytes.

linea de comandos o cadena de arranque:
    (gdb) x/5xw $ebx
    0x9500: 0x0000024f      0x0000027f      0x0001fb80      0x8000ffff
    0x9510: 0x00103000
    (gdb) x/s 0x00103000
    0x103000:       "kern0 "



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
    Se pushea a la pila el numero 7 (exitcode)
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


Ej: x86-call:
Usar stepi para ver los primeros cuatro valores de la pila, antes y despues del write.

    (gdb) si
    9               call write
    (gdb) x/4xw $esp
    0xffffcf70:     0x00000001      0x56557008      0x56557008      0xf7de6e81
    (gdb) si
    0xf7eb4d80 in write () from /lib/i386-linux-gnu/libc.so.6
    (gdb) finish
    Correr hasta la salida desde #0  0xf7eb4d80 in write () from /lib/i386-linux-gnu/libc.so.6
    Hello, world!
    main () at libc_hello.S:11
    11              push $7
    (gdb) x/4xw $esp
    0xffffcf70:     0x00000001      0x56557008      0x56557008      0xf7de6e81

    Los valores en el stack, son los mismos de antes de la llamada. Son el 1, el 
    TODO: COMPLETAR ESTO




Ej: x86-libc
Salida de nm -u int80_hi:
    ggparente95@ggparente95-X510UQ:~/Gaston/facultad/Facu/Sistemas Operativos/Labs/lab2-kern/extras$ nm --undefined int80_hi
         w __cxa_finalize@@GLIBC_2.1.3
         w __gmon_start__
         w _ITM_deregisterTMCloneTable
         w _ITM_registerTMCloneTable
         U __libc_start_main@@GLIBC_2.0

Salida de nm -u int80_strlen:
    ggparente95@ggparente95-X510UQ:~/Gaston/facultad/Facu/Sistemas Operativos/Labs/lab2-kern/extras$ nm --undefined int80_strlen
         w __cxa_finalize@@GLIBC_2.1.3
         w __gmon_start__
         w _ITM_deregisterTMCloneTable
         w _ITM_registerTMCloneTable
         U __libc_start_main@@GLIBC_2.0
         U strlen@@GLIBC_2.0


¿qué significa que un registro sea callee-saved en lugar de caller-saved?
    Callee-saved : la funcion que usa ese registro, lo guarda. Si una funcion1 llama a una funcion2 que toca, por ejemplo, el EBX, no necesita guardarlo antes de la llamada.
    Caller-saved: la funcion que usa ese registro, no lo guarda. Esto hace que si por ejemplo, una funcion1 llama a una funcion2 y esa funcion2 modifica el valor del EAX, la funcion1 tiene que encargarse de guardar el contenido del EAX antes de la llamada a funcion2, para poder tenerlo despues

en x86 ¿de qué tipo, caller-saved o callee-saved, es cada registro según la convención de llamadas de GCC?
    Son Caller-saved: EAX, ECX y EDX
    Son Callee-saved: EBP, EBX, EDI y ESI




Ej: x86-ret.
En asm: Como se pasa el valor de retorno?
    Se pasa por el registro eax.

Responder, en términos del frame pointer %ebp de una función f:

¿dónde se encuentra (de haberlo) el primer argumento de f?
se encuentra en ebp + 8
¿dónde se encuentra la dirección a la que retorna f cuando ejecute ret?
se encuentra en ebp + 4
¿dónde se encuentra el valor de %ebp de la función anterior, que invocó a f?
Suponiendo que la primera f tiene un solo argumento, se encontraria en ebp+12
¿dónde se encuentra la dirección a la que retornará la función que invocó a f?
Suponiendo que la primera f tiene un solo argumento, se encontraria en ebp+16



Incluir codigo de la funcion backtrace:

    void backtrace(){
        int *ebp = (int *)__builtin_frame_address(0);
        ebp = (int*)*ebp;
        int flag = 1;
        int numfrm = 1;

        while(flag == 1){
            printf("#%d [0x%x] 0x%x ( 0x%x 0x%x 0x%x )\n", numfrm, ebp, *(ebp+1), *(ebp+2), *(ebp+3), *(ebp+4));  
            ebp = (int*)*ebp;
            numfrm++;
            if (ebp == NULL)
                flag = 0;
        }
    }


incluir la salida del comando bt al entrar en la función backtrace

    (gdb) bt
    #0  backtrace () at backtrace.c:9
    #1  0x08048557 in my_write (fd=2, msg=0x80486ab, count=15) at backtrace.c:26
    #2  0x080485a3 in recurse (level=0) at backtrace.c:35
    #3  0x080485b4 in recurse (level=1) at backtrace.c:33
    #4  0x080485b4 in recurse (level=2) at backtrace.c:33
    #5  0x080485b4 in recurse (level=3) at backtrace.c:33
    #6  0x080485b4 in recurse (level=4) at backtrace.c:33
    #7  0x080485b4 in recurse (level=5) at backtrace.c:33
    #8  0x080485c6 in start_call_tree () at backtrace.c:39
    #9  0x080485e1 in main () at backtrace.c:43

incluir la salida del programa al ejecutarse la función backtrace (el número de frames y sus direcciones de retorno deberían coincidir con la salida de bt)

    (gdb) c
    Continuando.
    #1 [0xffffce78] 0x80485a3 ( 0x2 0x80486ab 0xf )
    #2 [0xffffce98] 0x80485b4 ( 0x0 0x0 0x0 )
    #3 [0xffffceb8] 0x80485b4 ( 0x1 0xf63d4e2e 0xf7ffdaf8 )
    #4 [0xffffced8] 0x80485b4 ( 0x2 0x1 0xf7fcf410 )
    #5 [0xffffcef8] 0x80485b4 ( 0x3 0xc30000 0x0 )
    #6 [0xffffcf18] 0x80485b4 ( 0x4 0xffffd1c8 0xf7dfe4a9 )
    #7 [0xffffcf38] 0x80485c6 ( 0x5 0x0 0xffffd01c )
    #8 [0xffffcf58] 0x80485e1 ( 0xf7fe59b0 0xffffcf80 0x0 )
    #9 [0xffffcf68] 0xf7de6e81 ( 0xf7fa6000 0xf7fa6000 0x0 )

    Como vemos, los return address coinciden con las direcciones que nos mostro GDB.

usando los comandos de selección de frames, y antes de salir de la función backtrace, el valor de %ebp en cada marco de ejecución detectado por GDB (valores que también deberían coincidir).

    (gdb) up
    #1  0x08048557 in my_write (fd=2, msg=0x80486ab, count=15) at backtrace.c:22
    22          backtrace();
    (gdb) p/x $ebp
    $1 = 0xffffce78
    (gdb) up
    #2  0x080485a3 in recurse (level=0) at backtrace.c:31
    31              my_write(2, "Hello, world!\n", 15);
    (gdb) p/x $ebp
    $2 = 0xffffce98
    (gdb) up
    #3  0x080485b4 in recurse (level=1) at backtrace.c:29
    29              recurse(level - 1);
    (gdb) p/x $ebp
    $3 = 0xffffceb8
    (gdb) up
    #4  0x080485b4 in recurse (level=2) at backtrace.c:29
    29              recurse(level - 1);
    (gdb) p/x $ebp
    $4 = 0xffffced8
    (gdb) up
    #5  0x080485b4 in recurse (level=3) at backtrace.c:29
    29              recurse(level - 1);
    (gdb) p/x $ebp
    $5 = 0xffffcef8
    (gdb) up
    #6  0x080485b4 in recurse (level=4) at backtrace.c:29
    29              recurse(level - 1);
    (gdb) p/x $ebp
    $6 = 0xffffcf18
    (gdb) up
    #7  0x080485b4 in recurse (level=5) at backtrace.c:29
    29              recurse(level - 1);
    (gdb) p/x $ebp
    $7 = 0xffffcf38
    (gdb) up
    #8  0x080485c6 in start_call_tree () at backtrace.c:35
    35          recurse(5);
    (gdb) p/x $ebp
    $8 = 0xffffcf58
    (gdb) up
    #9  0x080485e1 in main () at backtrace.c:39
    39          start_call_tree();
    (gdb) p/x $ebp
    $9 = 0xffffcf68
    (gdb) up
    Initial frame selected; you cannot go up.
