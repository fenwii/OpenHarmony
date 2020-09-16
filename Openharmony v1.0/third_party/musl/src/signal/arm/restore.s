.syntax unified

.global arm_signal_process
.global arm_do_signal
.hidden arm_do_signal
.type arm_do_signal,%function
arm_do_signal:
	stmfd sp!, {r0-r12}
	mov r4, sp
	bic sp, sp, #7
	blx arm_signal_process
	mov sp, r4
	ldmfd sp!, {r0-r12}
	b __restore

.global __restore
.hidden __restore
.type __restore,%function
__restore:
	mov r7,#119
	swi 0x0

.global __restore_rt
.hidden __restore_rt
.type __restore_rt,%function
__restore_rt:
	mov r7,#173
	swi 0x0
