;                                                                       Sort.asm
;###############################################################################
;# Encoding: UTF-8                                                 Tab size: 4 #
;#                                                                             #
;#             ARRAY SORTING ALGORITHMS WRITTEN ON FLAT ASSEMBLER              #
;#                                                                             #
;# License: LGPLv3+                              Copyleft (Ɔ) 2012, Jack Black #
;###############################################################################
; This code is part of LinAsm libraries collection
; Web-site: http://linasm.sourceforge.net/
; E-mail: ezamlinsky@gmail.com (Jack Black)

;###############################################################################
;#      Export section                                                         #
;###############################################################################
format	ELF64

;******************************************************************************;
;       Sorting algorithms                                                     ;
;******************************************************************************;

;==============================================================================;
;       Mapping functions                                                      ;
;==============================================================================;
public	Map_flt32				as	'_Map_flt32'
public	Map_flt64				as	'_Map_flt64'

;==============================================================================;
;       Quick sort                                                             ;
;==============================================================================;

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Ascending sort order                                                   ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
public	QuickSortAsc_uint8		as	'Array_QuickSortAsc_uint8'
public	QuickSortAsc_uint16		as	'Array_QuickSortAsc_uint16'
public	QuickSortAsc_uint32		as	'Array_QuickSortAsc_uint32'
public	QuickSortAsc_uint64		as	'Array_QuickSortAsc_uint64'
public	QuickSortAsc_uint8		as	'_ZN5Array12QuickSortAscEPhm'
public	QuickSortAsc_uint16		as	'_ZN5Array12QuickSortAscEPtm'
public	QuickSortAsc_uint32		as	'_ZN5Array12QuickSortAscEPjm'
public	QuickSortAsc_uint64		as	'_ZN5Array12QuickSortAscEPym'

; Signed integer types
public	QuickSortAsc_sint8		as	'Array_QuickSortAsc_sint8'
public	QuickSortAsc_sint16		as	'Array_QuickSortAsc_sint16'
public	QuickSortAsc_sint32		as	'Array_QuickSortAsc_sint32'
public	QuickSortAsc_sint64		as	'Array_QuickSortAsc_sint64'
public	QuickSortAsc_sint8		as	'_ZN5Array12QuickSortAscEPam'
public	QuickSortAsc_sint16		as	'_ZN5Array12QuickSortAscEPsm'
public	QuickSortAsc_sint32		as	'_ZN5Array12QuickSortAscEPim'
public	QuickSortAsc_sint64		as	'_ZN5Array12QuickSortAscEPxm'

; Floating-point types
public	QuickSortAsc_flt32		as	'Array_QuickSortAsc_flt32'
public	QuickSortAsc_flt64		as	'Array_QuickSortAsc_flt64'
public	QuickSortAsc_flt32		as	'_ZN5Array12QuickSortAscEPfm'
public	QuickSortAsc_flt64		as	'_ZN5Array12QuickSortAscEPdm'

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Descending sort order                                                  ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
public	QuickSortDsc_uint8		as	'Array_QuickSortDsc_uint8'
public	QuickSortDsc_uint16		as	'Array_QuickSortDsc_uint16'
public	QuickSortDsc_uint32		as	'Array_QuickSortDsc_uint32'
public	QuickSortDsc_uint64		as	'Array_QuickSortDsc_uint64'
public	QuickSortDsc_uint8		as	'_ZN5Array12QuickSortDscEPhm'
public	QuickSortDsc_uint16		as	'_ZN5Array12QuickSortDscEPtm'
public	QuickSortDsc_uint32		as	'_ZN5Array12QuickSortDscEPjm'
public	QuickSortDsc_uint64		as	'_ZN5Array12QuickSortDscEPym'

; Signed integer types
public	QuickSortDsc_sint8		as	'Array_QuickSortDsc_sint8'
public	QuickSortDsc_sint16		as	'Array_QuickSortDsc_sint16'
public	QuickSortDsc_sint32		as	'Array_QuickSortDsc_sint32'
public	QuickSortDsc_sint64		as	'Array_QuickSortDsc_sint64'
public	QuickSortDsc_sint8		as	'_ZN5Array12QuickSortDscEPam'
public	QuickSortDsc_sint16		as	'_ZN5Array12QuickSortDscEPsm'
public	QuickSortDsc_sint32		as	'_ZN5Array12QuickSortDscEPim'
public	QuickSortDsc_sint64		as	'_ZN5Array12QuickSortDscEPxm'

; Floating-point types
public	QuickSortDsc_flt32		as	'Array_QuickSortDsc_flt32'
public	QuickSortDsc_flt64		as	'Array_QuickSortDsc_flt64'
public	QuickSortDsc_flt32		as	'_ZN5Array12QuickSortDscEPfm'
public	QuickSortDsc_flt64		as	'_ZN5Array12QuickSortDscEPdm'

;==============================================================================;
;       Radix sort                                                             ;
;==============================================================================;

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Ascending sort order                                                   ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
public	RadixSortAsc_uint8		as	'Array_RadixSortAsc_uint8'
public	RadixSortAsc_uint16		as	'Array_RadixSortAsc_uint16'
public	RadixSortAsc_uint32		as	'Array_RadixSortAsc_uint32'
public	RadixSortAsc_uint64		as	'Array_RadixSortAsc_uint64'
public	RadixSortAsc_uint8		as	'_ZN5Array12RadixSortAscEPhS0_m'
public	RadixSortAsc_uint16		as	'_ZN5Array12RadixSortAscEPtS0_m'
public	RadixSortAsc_uint32		as	'_ZN5Array12RadixSortAscEPjS0_m'
public	RadixSortAsc_uint64		as	'_ZN5Array12RadixSortAscEPyS0_m'

; Signed integer types
public	RadixSortAsc_sint8		as	'Array_RadixSortAsc_sint8'
public	RadixSortAsc_sint16		as	'Array_RadixSortAsc_sint16'
public	RadixSortAsc_sint32		as	'Array_RadixSortAsc_sint32'
public	RadixSortAsc_sint64		as	'Array_RadixSortAsc_sint64'
public	RadixSortAsc_sint8		as	'_ZN5Array12RadixSortAscEPaS0_m'
public	RadixSortAsc_sint16		as	'_ZN5Array12RadixSortAscEPsS0_m'
public	RadixSortAsc_sint32		as	'_ZN5Array12RadixSortAscEPiS0_m'
public	RadixSortAsc_sint64		as	'_ZN5Array12RadixSortAscEPxS0_m'

; Floating-point types
public	RadixSortAsc_flt32		as	'Array_RadixSortAsc_flt32'
public	RadixSortAsc_flt64		as	'Array_RadixSortAsc_flt64'
public	RadixSortAsc_flt32		as	'_ZN5Array12RadixSortAscEPfS0_m'
public	RadixSortAsc_flt64		as	'_ZN5Array12RadixSortAscEPdS0_m'

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Descending sort order                                                  ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
public	RadixSortDsc_uint8		as	'Array_RadixSortDsc_uint8'
public	RadixSortDsc_uint16		as	'Array_RadixSortDsc_uint16'
public	RadixSortDsc_uint32		as	'Array_RadixSortDsc_uint32'
public	RadixSortDsc_uint64		as	'Array_RadixSortDsc_uint64'
public	RadixSortDsc_uint8		as	'_ZN5Array12RadixSortDscEPhS0_m'
public	RadixSortDsc_uint16		as	'_ZN5Array12RadixSortDscEPtS0_m'
public	RadixSortDsc_uint32		as	'_ZN5Array12RadixSortDscEPjS0_m'
public	RadixSortDsc_uint64		as	'_ZN5Array12RadixSortDscEPyS0_m'

; Signed integer types
public	RadixSortDsc_sint8		as	'Array_RadixSortDsc_sint8'
public	RadixSortDsc_sint16		as	'Array_RadixSortDsc_sint16'
public	RadixSortDsc_sint32		as	'Array_RadixSortDsc_sint32'
public	RadixSortDsc_sint64		as	'Array_RadixSortDsc_sint64'
public	RadixSortDsc_sint8		as	'_ZN5Array12RadixSortDscEPaS0_m'
public	RadixSortDsc_sint16		as	'_ZN5Array12RadixSortDscEPsS0_m'
public	RadixSortDsc_sint32		as	'_ZN5Array12RadixSortDscEPiS0_m'
public	RadixSortDsc_sint64		as	'_ZN5Array12RadixSortDscEPxS0_m'

; Floating-point types
public	RadixSortDsc_flt32		as	'Array_RadixSortDsc_flt32'
public	RadixSortDsc_flt64		as	'Array_RadixSortDsc_flt64'
public	RadixSortDsc_flt32		as	'_ZN5Array12RadixSortDscEPfS0_m'
public	RadixSortDsc_flt64		as	'_ZN5Array12RadixSortDscEPdS0_m'

;###############################################################################
;#      Code section                                                           #
;###############################################################################
section	'.text'		executable align 16

;******************************************************************************;
;       Array copying                                                          ;
;******************************************************************************;
macro	COPY	temp, scale
{
;---[Parameters]---------------------------
target	equ		rdi							; pointer to target array
source	equ 	rsi							; pointer to source array
size	equ		rdx							; array size (count of elements)
;---[Internal variables]-------------------
value	equ		xmm0						; value to process with
bytes	= 1 shl scale						; size of array element (bytes)
step	= 16 / bytes						; step size (in bytes)
;------------------------------------------
		sub		size, step					; size -= step
		jb		.sclr						; if (size < step) then skip vector code
;---[Vector loop]--------------------------
@@:		lddqu	value, [source]				; value = source[0]
		movdqu	[target], value				; target[0] = value
		add		source, 16					; source++
		add		target, 16					; target++
		sub		size, step					; size -= step
		jae		@b							; do while (size >= step)
;------------------------------------------
.sclr:	add		size, step					; size += step
		jz		.exit						; If no scalar code is required, then exit
;---[Scalar loop]--------------------------
@@:		mov		temp, [source]				; temp = source[0]
		mov		[target], temp				; target[0] = temp
		add		source, bytes				; source++
		add		target, bytes				; target++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
.exit:	ret
}
Copy8:	COPY	al, 0

;******************************************************************************;
;       Sorting algorithms                                                     ;
;******************************************************************************;

;==============================================================================;
;       Mapping floating-point values to signed integer values                 ;
;==============================================================================;
macro	MAP	val, x
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to array
size	equ		rsi							; array size (count of elements)
;---[Internal variables]-------------------
value	equ		xmm0						; value of array element
temp	equ		xmm1						; temporary register
temp1	equ		xmm2						; temporary register to hold 1
temp2	equ		xmm3						; temporary register to hold mask
if x eq d
one		= one_uint32						; 1 (integer value)
mask	= data_mask_flt32					; data mask
bytes	= 4									; array element size (bytes)
else
one		= one_uint64						; 1 (integer value)
mask	= data_mask_flt32					; data mask
bytes	= 8									; array element size (bytes)
end if
step	= 16 / bytes						; step size (in bytes)
;------------------------------------------
		sub		size, step					; size -= step
		jb		.sclr						; if (size < step) then skip vector code
		movdqa	temp1, [one]				; temp1 = 1
		movdqa	temp2, [mask]				; temp = mask
;---[Vector loop]--------------------------
@@:		movdqu	value, [array]				; value = array[0]
		movdqa	temp, value					; temp = value
		psrl#x	temp, bytes * 8 - 1			; temp >>= sizeof (type) - 1
		psub#x	temp, temp1					; temp -= 1
		pandn	temp, temp2					; temp = !temp & mask
		pxor	value, temp					; value ^= temp
		movdqu	[array], value				; array[0] = value
		add		array, 16					; array++
		sub		size, step					; size -= step
		jae		@b							; do while (size >= step)
;------------------------------------------
.sclr:	add		size, step					; size += step
		jz		.exit						; go to exit from the procedure
;---[Scalar loop]--------------------------
@@:		mov		val, [array]				; val = array[0]
		sar		val, bytes * 8 - 2			; val >>= sizeof (type) - 2
		shr		val, 1						; val >>= 1
		xor		[array], val				; array[0] ^= val
		add		array, bytes				; array++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
.exit:	ret
}
Map_flt32:	MAP	eax, d
Map_flt64:	MAP	rax, q

;==============================================================================;
;       Quick sort                                                             ;
;==============================================================================;
macro	QUICK_SORT_CORE	median, swap1, swap2, op1, op2, scale
{
;---[Parameters]---------------------------
left	equ		rdi							; pointer to start of the data array
right	equ		rsi							; pointer to end of the data array
;---[Internal variables]-------------------
size	equ		rax							; data array size
sizel	equ		al							; lower part of size variable
l_ptr	equ		r8							; left pointer to split data array
r_ptr	equ		r9							; right pointer to split data array
l_size	equ		rcx							; size of left part of array
r_size	equ		rdx							; size of right part of array
stack	equ		rsp							; stack pointer
s_ptr1	equ		stack +  0 * 8				; stack position of ptr1
s_ptr2	equ		stack +  1 * 8				; stack position of ptr2
N		= 32								; Max array size aceptable for Insert sort
space	= 3 * 8								; stack size required by the procedure
bytes	= 1 shl scale						; size of array element (bytes)
;---[QUICK SORT]---------------------------
		jmp		.start
.qloop:	shr		size, 1						; size /= 2
		mov		l_ptr, left					; l_ptr = left
if scale > 1
		and		sizel, -bytes
end if
		mov		r_ptr, right				; r_ptr = right
		mov		median, [left + size]		; median = left [size]
		jmp		@f							; skip swap section
;---[Swap loop]----------------------------
if bytes = 16
.swap:	movdqu	swap1, [l_ptr]				; swap1 = l_ptr[0]
		movdqu	swap2, [r_ptr]				; swap2 = r_ptr[0]
		movdqu	[l_ptr], swap2				; l_ptr[0] = swap2
		movdqu	[r_ptr], swap1				; r_ptr[0] = swap1
else
.swap:	mov		swap1, [l_ptr]				; swap1 = l_ptr[0]
		mov		swap2, [r_ptr]				; swap2 = r_ptr[0]
		mov		[l_ptr], swap2				; l_ptr[0] = swap2
		mov		[r_ptr], swap1				; r_ptr[0] = swap1
end if
;---[Internal loop 1]----------------------
@@:		add		l_ptr, bytes				; l_ptr++
		cmp		[l_ptr], median
		j#op1	@b							; do while (l_ptr[0] condition median)
;---[Internal loop 2]----------------------
@@:		sub		r_ptr, bytes				; r_ptr--
		cmp		[r_ptr], median
		j#op2	@b							; do while (r_ptr[0] condition median)
;------------------------------------------
		cmp		l_ptr, r_ptr
		jb		.swap						; do while (l_ptr < r_ptr)
;---[Swap loop end]------------------------
		mov		l_size, l_ptr
		mov		r_size, right
		sub		l_size, left				; l_size = l_ptr - left
		sub		r_size, r_ptr				; r_size = right - r_ptr
		cmp		l_size, r_size				; if (l_size <= r_size), then do the
		ja		.else						; first section, else the second one
;---[if]-----------------------------------
		sub		stack, space				; Preserving stack space for variables
		mov		[s_ptr2], right				; save "right" variable into the stack
		mov		[s_ptr1], r_ptr				; save "r_ptr" variable into the stack
		cmp		l_size, 2 * bytes			; if (l_size > 2)
		jbe		@f							; then do recursive call
		mov		right, l_ptr
		call	.start
@@:		mov		left, [s_ptr1]				; left = r_ptr
		mov		right, [s_ptr2]				; restore "right" variable from the stack
		add		stack, space				; Restoring stack space back
		jmp		.start
;---[else]---------------------------------
.else:	sub		stack, space				; Preserving stack space for variables
		mov		[s_ptr2], left				; save "left" variable into the stack
		mov		[s_ptr1], l_ptr				; save "l_ptr" variable into the stack
		cmp		r_size, 2 * bytes			; if (r_size > 2)
		jbe		@f							; then do recursive call
		mov		left, r_ptr
		call	.start
@@:		mov		right, [s_ptr1]				; right = l_ptr
		mov		left, [s_ptr2]				; restore "left" variable from the stack
		add		stack, space				; Restoring stack space back
;---[end if]-------------------------------
.start:	mov		size, right
		sub		size, left					; size = right - left
		cmp		size, N * bytes
		ja		.qloop						; do while (size > N)
;---[INSERT SORT]--------------------------
.ins:	add		left, bytes
		lea		l_ptr, [left + bytes]
;---[Insert sort loop]---------------------
.iloop:	mov		median, [l_ptr]
if bytes = 16
		movdqu	swap1, [l_ptr]
end if
		mov		r_ptr, l_ptr
;---[Internal loop]------------------------
@@:		cmp		median, [r_ptr - bytes]
		jn#op1	@f
if bytes = 16
		movdqu	swap2, [r_ptr - bytes]
		movdqu	[r_ptr], swap2
else
		mov		swap2, [r_ptr - bytes]
		mov		[r_ptr], swap2
end if
		sub		r_ptr, bytes
		cmp		r_ptr, left
		ja		@b
;---[Internal loop end]--------------------
@@:		add		l_ptr, bytes
if bytes = 16
		movdqu	[r_ptr], swap1
else
		mov		[r_ptr], median
end if
		cmp		l_ptr, right
		jb		.iloop
;---[Insert sort loop end]-----------------
		ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	QUICK_SORT_INT	sort_func, scale
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to array
size	equ		rsi							; array size (count of elements)
;---[Internal variables]-------------------
bytes	= 1 shl scale						; size of array element (bytes)
;------------------------------------------
		cmp		size, 1						; if (size <= 1)
		jbe		.exit						; then go to exit from the procedure
;---[Call sort function]-------------------
		shl		size, scale
		add		size, array					; size = array + size
		sub		array, bytes				; array--
		jmp		sort_func					; call sorting function
.exit:	ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	QUICK_SORT_FLT	sort_func, convert_func, scale
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to array
size	equ		rsi							; array size (count of elements)
;---[Internal variables]-------------------
stack	equ		rsp							; stack pointer
s_array	equ		stack +  0 * 8				; stack position of array variable
s_size	equ		stack +  1 * 8				; stack position of size variable
space	= 3 * 8								; stack size required by the procedure
bytes	= 1 shl scale						; size of array element (bytes)
;------------------------------------------
		cmp		size, 1						; if (size <= 1)
		jbe		.exit						; then go to exit from the procedure
		sub		stack, space				; reserving stack size for local vars
;---[Convert array]------------------------
		mov		[s_array], array			; save "array" variable into the stack
		mov		[s_size], size				; save "size" variable into the stack
		call	convert_func				; call converting function
;---[Sort array]---------------------------
		mov		size, [s_size]				; get "size" variable from the stack
		mov		array, [s_array]			; get "array" variable from the stack
		shl		size, scale
		add		size, array					; size = array + size
		sub		array, bytes				; array--
		call	sort_func					; call sorting function
;---[Convert array]------------------------
		mov		array, [s_array]			; get "array" variable from the stack
		mov		size, [s_size]				; get "size" variable from the stack
		call	convert_func				; call converting function
		add		stack, space				; restoring back the stack pointer
.exit:	ret
}

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Ascending sort order                                                   ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
QuickSortCoreAsc_uint8:		QUICK_SORT_CORE	al, cl, dl, b, a, 0
QuickSortCoreAsc_uint16:	QUICK_SORT_CORE	ax, cx, dx, b, a, 1
QuickSortCoreAsc_uint32:	QUICK_SORT_CORE	eax, ecx, edx, b, a, 2
QuickSortCoreAsc_uint64:	QUICK_SORT_CORE	rax, rcx, rdx, b, a, 3
QuickSortAsc_uint8:			QUICK_SORT_INT	QuickSortCoreAsc_uint8, 0
QuickSortAsc_uint16:		QUICK_SORT_INT	QuickSortCoreAsc_uint16, 1
QuickSortAsc_uint32:		QUICK_SORT_INT	QuickSortCoreAsc_uint32, 2
QuickSortAsc_uint64:		QUICK_SORT_INT	QuickSortCoreAsc_uint64, 3

; Signed integer types
QuickSortCoreAsc_sint8:		QUICK_SORT_CORE	al, cl, dl, l, g, 0
QuickSortCoreAsc_sint16:	QUICK_SORT_CORE	ax, cx, dx, l, g, 1
QuickSortCoreAsc_sint32:	QUICK_SORT_CORE	eax, ecx, edx, l, g,2
QuickSortCoreAsc_sint64:	QUICK_SORT_CORE	rax, rcx, rdx, l, g, 3
QuickSortAsc_sint8:			QUICK_SORT_INT	QuickSortCoreAsc_sint8, 0
QuickSortAsc_sint16:		QUICK_SORT_INT	QuickSortCoreAsc_sint16, 1
QuickSortAsc_sint32:		QUICK_SORT_INT	QuickSortCoreAsc_sint32, 2
QuickSortAsc_sint64:		QUICK_SORT_INT	QuickSortCoreAsc_sint64, 3

; Floating-point types
QuickSortAsc_flt32:			QUICK_SORT_FLT	QuickSortCoreAsc_sint32, Map_flt32, 2
QuickSortAsc_flt64:			QUICK_SORT_FLT	QuickSortCoreAsc_sint64, Map_flt64, 3

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Descending sort order                                                  ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
QuickSortCoreDsc_uint8:		QUICK_SORT_CORE	al, cl, dl, a, b, 0
QuickSortCoreDsc_uint16:	QUICK_SORT_CORE	ax, cx, dx, a, b, 1
QuickSortCoreDsc_uint32:	QUICK_SORT_CORE	eax, ecx, edx, a, b, 2
QuickSortCoreDsc_uint64:	QUICK_SORT_CORE	rax, rcx, rdx, a, b, 3
QuickSortDsc_uint8:			QUICK_SORT_INT	QuickSortCoreDsc_uint8, 0
QuickSortDsc_uint16:		QUICK_SORT_INT	QuickSortCoreDsc_uint16, 1
QuickSortDsc_uint32:		QUICK_SORT_INT	QuickSortCoreDsc_uint32, 2
QuickSortDsc_uint64:		QUICK_SORT_INT	QuickSortCoreDsc_uint64, 3

; Signed integer types
QuickSortCoreDsc_sint8:		QUICK_SORT_CORE	al, cl, dl, g, l, 0
QuickSortCoreDsc_sint16:	QUICK_SORT_CORE	ax, cx, dx, g, l, 1
QuickSortCoreDsc_sint32:	QUICK_SORT_CORE	eax, ecx, edx, g, l, 2
QuickSortCoreDsc_sint64:	QUICK_SORT_CORE	rax, rcx, rdx, g, l, 3
QuickSortDsc_sint8:			QUICK_SORT_INT	QuickSortCoreDsc_sint8, 0
QuickSortDsc_sint16:		QUICK_SORT_INT	QuickSortCoreDsc_sint16, 1
QuickSortDsc_sint32:		QUICK_SORT_INT	QuickSortCoreDsc_sint32, 2
QuickSortDsc_sint64:		QUICK_SORT_INT	QuickSortCoreDsc_sint64, 3

; Floating-point types
QuickSortDsc_flt32:			QUICK_SORT_FLT	QuickSortCoreDsc_sint32, Map_flt32, 2
QuickSortDsc_flt64:			QUICK_SORT_FLT	QuickSortCoreDsc_sint64, Map_flt64, 3

;==============================================================================;
;       Radix sort                                                             ;
;==============================================================================;
AscOrder_ui:
;---[Parameters]---------------------------
target	equ		rdi							; pointer to target array
stat	equ		rsi							; pointer to statistics array
;---[Internal variables]-------------------
size	equ		rcx							; size of statistics array
temp	equ		rdx							; temporary register
;------------------------------------------
		mov		size, 256					; size = 256 (partial key range)
;---[Address calculating loop]-------------
@@:		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		add		stat, 8						; stat++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		ret
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
DscOrder_ui:
;---[Parameters]---------------------------
target	equ		rdi							; pointer to target array
stat	equ		rsi							; pointer to statistics array
;---[Internal variables]-------------------
size	equ		rcx							; size of statistics array
temp	equ		rdx							; temporary register
;------------------------------------------
		add		stat, 256 * 8				; stat += 256
		mov		size, 256					; size = 256 (partial key range)
;---[Address calculating loop]-------------
@@:		sub		stat, 8						; stat--
		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		ret
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
AscOrder_si:
;---[Parameters]---------------------------
target	equ		rdi							; pointer to target array
stat	equ		rsi							; pointer to statistics array
;---[Internal variables]-------------------
size	equ		rcx							; size of statistics array
temp	equ		rdx							; temporary register
;------------------------------------------
		add		stat, 128 * 8				; stat += 128
		mov		size, 128					; size = 128 (partial key half range)
;---[Address calculating loop]-------------
@@:		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		add		stat, 8						; stat++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		sub		stat, 256 * 8				; stat -= 256
		mov		size, 128					; size = 128 (partial key half range)
;---[Address calculating loop]-------------
@@:		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		add		stat, 8						; stat++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		ret
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
DscOrder_si:
;---[Parameters]---------------------------
target	equ		rdi							; pointer to target array
stat	equ		rsi							; pointer to statistics array
;---[Internal variables]-------------------
size	equ		rcx							; size of statistics array
temp	equ		rdx							; temporary register
;------------------------------------------
		add		stat, 128 * 8				; stat += 128
		mov		size, 128					; size = 128 (partial key half range)
;---[Address calculating loop]-------------
@@:		sub		stat, 8						; stat--
		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		add		stat, 256 * 8				; stat += 256
		mov		size, 128					; size = 128 (partial key half range)
;---[Address calculating loop]-------------
@@:		sub		stat, 8						; stat--
		mov		temp, [stat]				; temp = stat[0]
		mov		[stat], target				; stat[0] = target
		add		target, temp				; target += temp
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		ret
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	STAT	scale, step
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to array
size	equ		rsi							; array size (count of elements)
stat	equ		rdx							; pointer to statistics array
;---[Internal variables]-------------------
zero	equ		xmm0						; zero value (vector register)
ptr		equ		rcx							; temporarry pointer to stat array
count	equ		rax							; count of vector elements is stat array
key		equ		rax							; key register (is used to compute adress)
keyl	equ		al							; low part of key register
bytes	= 1 shl scale						; size of array element (bytes)
;------------------------------------------
		pxor	zero, zero					; zero = 0
		mov		ptr, stat					; ptr = stat
		mov		count, 256 * bytes / 2		; calculating count
;---[Stat initialization loop]-------------
@@:		movdqu	[ptr], zero					; ptr[0] = 0
		add		ptr, 16						; ptr++
		sub		count, 1					; count--
		jnz		@b							; do while (count != 0)
;------------------------------------------
		xor		key, key					; clearing key register
;---[Statistics loop]----------------------
@@:
i = 0
while i < bytes
		mov		keyl, [array + i]			; get partial key
		add		qword [stat + i * 256 * 8 + key * 8], step
	i = i + 1
end while
		add		array, step					; move to next partial key
		sub		size, 1						; size--
		jnz		@b							; do while (count != 0)
;------------------------------------------
		ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	SORTSTAGE	cmd, temp, step
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to source array
size	equ		rsi							; array size (count of elements)
stat	equ		rdx							; pointer to statistics array
index	equ		rcx							; index of partial key
;---[Internal variables]-------------------
addr	equ		r8							; address where element should be copied
key		equ		rax							; key register (is used to compute adress)
keyl	equ		al							; low part of key register
;------------------------------------------
		xor		key, key					; clearing key register
;---[Sorting loop]-------------------------
@@:		mov		keyl, [array + index]		; get partial key
		cmd		temp, [array]				; temp = aray[0]
		mov		addr, [stat + key * 8]		; addr = stat[key]
		cmd		[addr], temp				; addr[0] = temp
		add		array, step					; array++
		add		qword [stat + key * 8], step; stat[key]++
		sub		size, 1						; size--
		jnz		@b							; do while (size != 0)
;------------------------------------------
		ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	RADIX_SORT_CORE	order1, order2, stat, stage, scale
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to source array
temp	equ		rsi							; pointer to temporary array
size	equ		rdx							; size of array
;---[Internal variables]-------------------
param1	equ		rdi							; register to pass 1 parameter to function
param2	equ		rsi							; register to pass 2 parameter to function
param3	equ		rdx							; register to pass 3 parameter to function
param4	equ		rcx							; register to pass 4 parameter to function
stack	equ		rsp							; stack pointer
bytes	= 1 shl scale						; size of array element (bytes)
stat_sz	= bytes * 256 * 8					; size of statistics array (bytes)
space	= stat_sz + 3 * 8					; stack size required by the procedure
s_array	equ		stack +  stat_sz + 0 * 8	; stack position of array variable
s_temp	equ		stack +  stat_sz + 1 * 8	; stack position of temp variable
s_size	equ		stack +  stat_sz + 2 * 8	; stack position of size variable
;------------------------------------------
		sub		stack, space				; reserving stack size for local vars
		mov		[s_array], array			; save "array" variable into the stack
		mov		[s_temp], temp				; save "temp" variable into the stack
		mov		[s_size], size				; save "size" variable into the stack
;---[Collect statistics]-------------------
		mov		param2, size
		mov		param3, stack
		call	stat						; call Statistics (array, size, stack);
;---[Sort partial keys]--------------------
if bytes = 1
		mov		param1, [s_temp]
		mov		param2, [s_array]
		mov		param3, [s_size]
		call	Copy8						; call Copy (temp, array, size)
end if
i = 0
while i < bytes - 1
	if i mod 2 = 0
		mov		param1, [s_temp]
		lea		param2, [stack + i * 256 * 8]
		call	order1						; call order1 (temp, stack[i])
		mov		param1, [s_array]
		mov		param2, [s_size]
		lea		param3, [stack + i * 256 * 8]
		mov		param4, i
		call	stage						; call stage (array, size, stack[i], i)
	else
		mov		param1, [s_array]
		lea		param2, [stack + i * 256 * 8]
		call	order1						; call order1 (array, stack[i])
		mov		param1, [s_temp]
		mov		param2, [s_size]
		lea		param3, [stack + i * 256 * 8]
		mov		param4, i
		call	stage						; call stage (temp, size, stack[i], i)
	end if
	i = i + 1
end while
		mov		param1, [s_array]
		lea		param2, [stack + i * 256 * 8]
		call	order2						; call order2 (array, stack)
		mov		param1, [s_temp]
		mov		param2, [s_size]
		lea		param3, [stack + i * 256 * 8]
		mov		param4, i
		call	stage						; call stage (temp, size, stack[i], i)
		add		stack, space				; restoring back the stack pointer
		ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	RADIX_SORT_INT	sort_func
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to source array
temp	equ		rsi							; pointer to temporary array
size	equ		rdx							; size of array
;------------------------------------------
		cmp		size, 1						; if (size <= 1)
		jbe		.exit						; then go to exit from the procedure
;---[Call sort function]-------------------
		jmp		sort_func					; call sorting function
.exit:	ret
}
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
macro	RADIX_SORT_FLT	sort_func, convert_func
{
;---[Parameters]---------------------------
array	equ		rdi							; pointer to source array
temp	equ		rsi							; pointer to temporary array
size	equ		rdx							; size of array
;---[Internal variables]-------------------
param1	equ		rdi							; register to pass 1 parameter to function
param2	equ		rsi							; register to pass 2 parameter to function
param3	equ		rdx							; register to pass 3 parameter to function
stack	equ		rsp							; stack pointer
s_array	equ		stack +  0 * 8				; stack position of array variable
s_temp	equ		stack +  1 * 8				; stack position of array variable
s_size	equ		stack +  2 * 8				; stack position of size variable
space	= 3 * 8								; stack size required by the procedure
;------------------------------------------
		cmp		size, 1						; if (size <= 1)
		jbe		.exit						; then go to exit from the procedure
		sub		stack, space				; reserving stack size for local vars
		mov		[s_array], array			; save "array" variable into the stack
		mov		[s_temp], temp				; save "temp" variable into the stack
		mov		[s_size], size				; save "size" variable into the stack
;---[Convert array]------------------------
		mov		param2, size				; save "size" variable into the stack
		call	convert_func				; call converting function
;---[Sort array]---------------------------
		mov		param1, [s_array]			; get "array" variable from the stack
		mov		param2, [s_temp]			; get "temp" variable from the stack
		mov		param3, [s_size]			; get "size" variable from the stack
		call	sort_func					; call sorting function
;---[Convert array]------------------------
		mov		param1, [s_array]			; get "array" variable from the stack
		mov		param2, [s_size]			; get "size" variable from the stack
		call	convert_func				; call converting function
		add		stack, space				; restoring back the stack pointer
.exit:	ret
}

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Statistic functions                                                    ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
Stat8:		STAT	0, 1
Stat16:		STAT	1, 2
Stat32:		STAT	2, 4
Stat64:		STAT	3, 8

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Sorting stage functions                                                ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
Stage8:		SORTSTAGE	mov, r9b, 1
Stage16:	SORTSTAGE	mov, r9w, 2
Stage32:	SORTSTAGE	mov, r9d, 4
Stage64:	SORTSTAGE	mov, r9, 8

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Ascending sort order                                                   ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
RadixSortCoreAsc_uint8:		RADIX_SORT_CORE	AscOrder_ui, AscOrder_ui, Stat8, Stage8, 0
RadixSortCoreAsc_uint16:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_ui, Stat16, Stage16, 1
RadixSortCoreAsc_uint32:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_ui, Stat32, Stage32, 2
RadixSortCoreAsc_uint64:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_ui, Stat64, Stage64, 3
RadixSortAsc_uint8:			RADIX_SORT_INT	RadixSortCoreAsc_uint8
RadixSortAsc_uint16:		RADIX_SORT_INT	RadixSortCoreAsc_uint16
RadixSortAsc_uint32:		RADIX_SORT_INT	RadixSortCoreAsc_uint32
RadixSortAsc_uint64:		RADIX_SORT_INT	RadixSortCoreAsc_uint64

; Signed integer types
RadixSortCoreAsc_sint8:		RADIX_SORT_CORE	AscOrder_ui, AscOrder_si, Stat8, Stage8, 0
RadixSortCoreAsc_sint16:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_si, Stat16, Stage16, 1
RadixSortCoreAsc_sint32:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_si, Stat32, Stage32, 2
RadixSortCoreAsc_sint64:	RADIX_SORT_CORE	AscOrder_ui, AscOrder_si, Stat64, Stage64, 3
RadixSortAsc_sint8:			RADIX_SORT_INT	RadixSortCoreAsc_sint8
RadixSortAsc_sint16:		RADIX_SORT_INT	RadixSortCoreAsc_sint16
RadixSortAsc_sint32:		RADIX_SORT_INT	RadixSortCoreAsc_sint32
RadixSortAsc_sint64:		RADIX_SORT_INT	RadixSortCoreAsc_sint64

; Floating-point types
RadixSortAsc_flt32:			RADIX_SORT_FLT	RadixSortCoreAsc_sint32, Map_flt32
RadixSortAsc_flt64:			RADIX_SORT_FLT	RadixSortCoreAsc_sint64, Map_flt64

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
;       Descending sort order                                                  ;
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;

; Unsigned integer types
RadixSortCoreDsc_uint8:		RADIX_SORT_CORE	DscOrder_ui, DscOrder_ui, Stat8, Stage8, 0
RadixSortCoreDsc_uint16:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_ui, Stat16, Stage16, 1
RadixSortCoreDsc_uint32:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_ui, Stat32, Stage32, 2
RadixSortCoreDsc_uint64:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_ui, Stat64, Stage64, 3
RadixSortDsc_uint8:			RADIX_SORT_INT	RadixSortCoreDsc_uint8
RadixSortDsc_uint16:		RADIX_SORT_INT	RadixSortCoreDsc_uint16
RadixSortDsc_uint32:		RADIX_SORT_INT	RadixSortCoreDsc_uint32
RadixSortDsc_uint64:		RADIX_SORT_INT	RadixSortCoreDsc_uint64

; Signed integer types
RadixSortCoreDsc_sint8:		RADIX_SORT_CORE	DscOrder_ui, DscOrder_si, Stat8, Stage8, 0
RadixSortCoreDsc_sint16:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_si, Stat16, Stage16, 1
RadixSortCoreDsc_sint32:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_si, Stat32, Stage32, 2
RadixSortCoreDsc_sint64:	RADIX_SORT_CORE	DscOrder_ui, DscOrder_si, Stat64, Stage64, 3
RadixSortDsc_sint8:			RADIX_SORT_INT	RadixSortCoreDsc_sint8
RadixSortDsc_sint16:		RADIX_SORT_INT	RadixSortCoreDsc_sint16
RadixSortDsc_sint32:		RADIX_SORT_INT	RadixSortCoreDsc_sint32
RadixSortDsc_sint64:		RADIX_SORT_INT	RadixSortCoreDsc_sint64

; Floating-point types
RadixSortDsc_flt32:			RADIX_SORT_FLT	RadixSortCoreDsc_sint32, Map_flt32
RadixSortDsc_flt64:			RADIX_SORT_FLT	RadixSortCoreDsc_sint64, Map_flt64

;###############################################################################
;#      Read-only data section                                                 #
;###############################################################################
section	'.rodata'	align 16

; integer values
one_uint32			dd	4 dup (1)						; +1
one_uint64			dq	2 dup (1)						; +1

; flt32_t
data_mask_flt32		dd	4 dup (0x7FFFFFFF)				; data mask

; flt64_t
data_mask_flt64		dq	2 dup (0x7FFFFFFFFFFFFFFF)		; data mask

;###############################################################################
;#                                 END OF FILE                                 #
;###############################################################################
