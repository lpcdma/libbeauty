/*===-- llvm-c/Disassembler.h - Disassembler Public C Interface ---*- C -*-===*\
|*                                                                            *|
|*                     The LLVM Compiler Infrastructure                       *|
|*                                                                            *|
|* This file is distributed under the University of Illinois Open Source      *|
|* License. See LICENSE.TXT for details.                                      *|
|*                                                                            *|
|*===----------------------------------------------------------------------===*|
|*                                                                            *|
|* This header provides a public interface to a disassembler library.         *|
|* LLVM provides an implementation of this interface.                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifndef LLVM_C_DECODEASM_H
#define LLVM_C_DECODEASM_H

#include "llvm/Support/DataTypes.h"
#include <stddef.h>

/**
 * @defgroup LLVMCDisassembler Disassembler
 * @ingroup LLVMC
 *
 * @{
 */

/**
 * An opaque reference to a disassembler context.
 */
typedef void *LLVMDecodeAsmContextRef;
typedef void *LLVMDecodeAsmMIIRef;

struct instruction_low_level_s {
	int opcode;
	int src_kind;
	int dst_kind; // For now, this should always be == 1
	int src_operands[16];
	int imm_offset[16];
	int imm_size[16];
	int dst_operands[2];
};

#ifdef __cplusplus
extern "C" {
#endif /* !defined(__cplusplus) */


void *LLVMCreateMCInst(void);

/**
 * Create a disassembler for the TripleName.  Symbolic disassembly is supported
 * by passing a block of information in the DisInfo parameter and specifying the
 * TagType and callback functions as described above.  These can all be passed
 * as NULL.  If successful, this returns a disassembler context.  If not, it
 * returns NULL.
 */
LLVMDecodeAsmContextRef LLVMCreateDecodeAsm(const char *TripleName, void *DisInfo,
                                      int TagType, LLVMOpInfoCallback GetOpInfo,
                                      LLVMSymbolLookupCallback SymbolLookUp);

/**
 * Dispose of a disassembler context.
 */
//void LLVMDisasmDispose(LLVMDisasmContextRef DC);

/**
 * Disassemble a single instruction using the disassembler context specified in
 * the parameter DC.  The bytes of the instruction are specified in the
 * parameter Bytes, and contains at least BytesSize number of bytes.  The
 * instruction is at the address specified by the PC parameter.  If a valid
 * instruction can be disassembled, its string is returned indirectly in
 * OutString whose size is specified in the parameter OutStringSize.  This
 * function returns the number of bytes in the instruction or zero if there was
 * no valid instruction.
 */
size_t LLVMDecodeAsmInstruction(void *DisInfo, LLVMDecodeAsmContextRef DC, uint8_t *Bytes,
                             uint64_t BytesSize, uint64_t PC,
                             uint8_t *OutString, size_t OutStringSize, uint64_t *opcode, const char **opcode_name,
                             uint64_t *TSFlags);


LLVMDecodeAsmMIIRef LLVMDecodeAsmGetMII(LLVMDecodeAsmContextRef DCR);
int LLVMDecodeAsmGetNumOpcodes(LLVMDecodeAsmContextRef DCR);
uint64_t LLVMDecodeAsmGetTSFlags(LLVMDecodeAsmContextRef DCR, uint64_t opcode);
int LLVMDecodeAsmPrintOpcodes(LLVMDecodeAsmContextRef DCR);
int LLVMDecodeAsmOpcodesSource(LLVMDecodeAsmContextRef DCR);
void LLVMPrintTargets(void);
void LLVMDisasmInstructionPrint(int octets, uint8_t *buffer, int buffer_size, uint8_t *buffer1);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* !defined(__cplusplus) */

#endif /* !defined(LLVM_C_DISASSEMBLER_H) */
