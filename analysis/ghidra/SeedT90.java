import java.math.BigInteger;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;

public class SeedT90 extends GhidraScript {
    @Override public void run() throws Exception {
        Address base = currentProgram.getMinAddress();
        Address limit = currentProgram.getMaxAddress();
        var memory = currentProgram.getMemory();
        var context = currentProgram.getProgramContext();
        var thumb = context.getRegister("TMode");
        context.setValue(thumb, base, limit, BigInteger.ONE);
        // Cortex-M exception and interrupt vectors. Reserved entries are zero.
        for (int i = 1; i < 82; i++) {
            long vector = Integer.toUnsignedLong(memory.getInt(base.add(4L * i)));
            if ((vector & 1) == 0) continue;
            Address target = toAddr(vector & ~1L);
            if (target.compareTo(base) < 0 || target.compareTo(limit) > 0) continue;
            disassemble(target);
            if (getFunctionAt(target) == null)
                createFunction(target, i == 1 ? "Reset_Handler" : null);
        }
    }
}
