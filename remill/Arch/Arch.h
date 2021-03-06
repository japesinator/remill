/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#ifndef REMILL_ARCH_ARCH_H_
#define REMILL_ARCH_ARCH_H_

#include <string>

#include "remill/OS/OS.h"

namespace llvm {
class Module;
class BasicBlock;
class Function;
}  // namespace llvm.

namespace remill {

class Instruction;

enum ArchName : unsigned {
  kArchInvalid,
  kArchX86,
  kArchX86_AVX,
  kArchX86_AVX512,
  kArchAMD64,
  kArchAMD64_AVX,
  kArchAMD64_AVX512
};

class Arch {
 public:
  virtual ~Arch(void);

  inline static const Arch *Create(OSName os, const std::string &arch_name) {
    return Create(os, GetName(arch_name));
  }

  // Factory method for loading the correct architecture class for a given
  // operating system and architecture class.
  static const Arch *Create(OSName os, ArchName arch_name);

  // Convert the string name of an architecture into a canonical form.
  static ArchName GetName(const std::string &arch_name);

  // Converts an LLVM module object to have the right triple / data layout
  // information for the target architecture.
  virtual void PrepareModule(llvm::Module *mod) const = 0;

  // Decode an instruction.
  virtual Instruction *DecodeInstruction(
      uint64_t address,
      const std::string &instr_bytes) const = 0;

  // Number of bits in an address.
  const OSName os_name;
  const ArchName arch_name;
  const unsigned address_size;

 protected:
  Arch(OSName os_name_, ArchName arch_name_, unsigned address_size_);

 private:

  // Defined in `remill/Arch/X86/Arch.cpp`.
  static const Arch *CreateX86(
      OSName os, ArchName arch_name, unsigned address_size_);

  Arch(void) = delete;
};

}  // namespace remill

#endif  // MC_SEMA_ARCH_ARCH_H_
