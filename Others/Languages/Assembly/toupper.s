.section .data
.equ OPEN,5
.equ WRITE,4
.equ READ,3
.equ CLOSE,6
.equ EXIT,1
.equ O_RDONLY,0
.equ O_CREAT_WRONLY_TRUNC,03101
.equ LINUX_SYSCALL,0x80
.equ END_OF_FILE,0

.section .bss
.equ BUFFER_SIZE,500
.lcomm BUFFER_DATA,BUFFER_SIZE

.section .text
.equ ST_SIZE_RESERVE,8
.equ ST_FD_IN,0
.equ ST_FD_OUT,4
.equ ST_ARGC,8
.equ ST_ARGV_0,12
.equ ST_ARGV_1,16
.equ ST_ARGV_2,20

.globl _start
_start:
subl $ST_SIZE_RESERVE,%esp
movl %esp,%ebp
open_files:
open_fd_in:
##OPEN INPUT FILE
movl ST_ARGV_1(%ebp),%ebx
movl O_RDONLY,%ecx
movl $0666,%edx
movl $OPEN,%eax
int $LINUX_SYSCALL

store_fd_in:
movl %eax,ST_FD_IN(%ebp)

open_fd_out:
movl ST_ARGV_2(%ebp),%ebx
movl $O_CREAT_WRONLY_TRUNC,%ecx
movl $0666,%edx
movl $OPEN,%eax
int $LINUX_SYSCALL

store_fd_out:
movl %eax,ST_FD_OUT(%ebp)

read_loop_begin:
movl ST_FD_IN(%ebp),%ebx
movl $BUFFER_DATA,%ecx
movl $BUFFER_SIZE,%edx
movl $READ,%eax
int $LINUX_SYSCALL



