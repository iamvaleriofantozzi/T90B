import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.DWordDataType;

public class SeedT90UiTargets extends GhidraScript {
    @Override public void run() throws Exception {
        var first = toAddr(0x08016100L);
        var listing = currentProgram.getListing();
        var memory = currentProgram.getMemory();
        for (int index = 0; index < 16; index++) {
            long pointer = Integer.toUnsignedLong(memory.getInt(first.add(4L * index)));
            if (pointer != 0 && ((pointer & 1) == 0 || pointer < 0x08013639L ||
                    pointer > 0x08015b25L)) {
                throw new IllegalStateException("Unexpected callback word at index " + index);
            }
        }
        clearListing(first, first.add(63));
        createLabel(first, "ui_callback_candidates", true);
        for (int index = 0; index < 16; index++) {
            var entry = first.add(4L * index);
            createData(entry, DWordDataType.dataType);
            long pointer = Integer.toUnsignedLong(memory.getInt(entry));
            if (pointer == 0) {
                continue;
            }
            var target = toAddr(pointer & ~1L);
            if (listing.getFunctionAt(target) != null) {
                continue;
            }
            var enclosing = listing.getFunctionContaining(target);
            if (enclosing != null) {
                println(entry + " points inside " + enclosing.getName() + " at " + target);
                continue;
            }
            if (disassemble(target) && createFunction(target, null) != null) {
                println("Seeded callback candidate " + target);
            }
        }
    }
}
