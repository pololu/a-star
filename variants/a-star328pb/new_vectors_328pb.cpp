/*
 * Define the interrupt vectors for the ATmega328PB on the Pololu A-Star 328PB
 * that are not present on the ATmega328P.  We are counting on the linker to
 * place the __vectors_328pb function immediately after the __vectors symbol
 * defined in crtatmega328p.o.
 */

#ifdef __cplusplus
extern "C" {
#endif

void __bad_interrupt_328pb() __attribute__((used, naked));
void __bad_interrupt_328pb(){ asm("jmp __bad_interrupt"); }

void __vector_26() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_27() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_28() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_29() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_30() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_31() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_32() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_33() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_34() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_35() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_36() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_37() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_38() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_39() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_40() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_41() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_42() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_43() __attribute__((used, weak, alias("__bad_interrupt_328pb")));
void __vector_44() __attribute__((used, weak, alias("__bad_interrupt_328pb")));

void __vectors_328pb() __attribute__((used, naked, section(".vectors")));
void __vectors_328pb()
{
  asm("jmp __vector_26");
  asm("jmp __vector_27");
  asm("jmp __vector_28");
  asm("jmp __vector_29");
  asm("jmp __vector_30");
  asm("jmp __vector_31");
  asm("jmp __vector_32");
  asm("jmp __vector_33");
  asm("jmp __vector_34");
  asm("jmp __vector_35");
  asm("jmp __vector_36");
  asm("jmp __vector_37");
  asm("jmp __vector_38");
  asm("jmp __vector_39");
  asm("jmp __vector_40");
  asm("jmp __vector_41");
  asm("jmp __vector_42");
  asm("jmp __vector_43");
  asm("jmp __vector_44");
}

#ifdef __cplusplus
}
#endif
